#include <iostream>
#include <string>
#include <curl/curl.h>
using namespace std;

// handle the response data 
size_t callback(void* contents, size_t size, size_t nmemb, string* userData) {
    userData->append((char*)contents, size * nmemb);
    return size * nmemb;
}
string response_filter(const string& jsonResponse) {
    size_t start = jsonResponse.find("\"content\":\"");
    if (start != string::npos) {
        start += 11; // Move past "content":"
        size_t end = jsonResponse.find("\"", start);
        if (end != string::npos) {
            return jsonResponse.substr(start, end - start);
        }
    }
    return "Error parsing response";
}
string api_request(const string& userInput) {
    CURL* curl;
    CURLcode res;
    string response_data;

    curl = curl_easy_init();
    if (curl) {
        //  API url
        string apiUrl = "https://api.groq.com/openai/v1/chat/completions";

        // API key
        string apiKey = " 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";

        // headers 
        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, ("Authorization: Bearer" + apiKey).c_str());
        headers = curl_slist_append(headers, "Content-Type: application/json");

        // Create JSON 
        string jsonData = "{\"messages\": [{\"role\": \"user\", \"content\": \"" + userInput + "\"}], \"model\": \"llama3-8b-8192\"}";

        // Configure curl
        curl_easy_setopt(curl, CURLOPT_URL, apiUrl.c_str());//set URL for the HTTP request to apiUrl
        curl_easy_setopt(curl, CURLOPT_POST, 1L);//says HTTP method is POST.
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);//add auth headers
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());//our json data as POST body
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);//specify callback function
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);//send response to callback function
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);//disable SSL certification verification(FOR TESTING)
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        // send request
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            cerr << "CURL error: " << curl_easy_strerror(res) << endl;
        }

        // Cleanup
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }
    return response_data;
}

int main() {
    cout << "Welcome to the Console Application" << endl<< "Type 'exit' to quit the application" << endl;

    string input;
    while (true) {
        cout << "\nYou: ";
        getline(cin,input);
        if (input == "exit") {
            break;
        }

        // Send input to the Groq and get response
        string ai_response = api_request(input);
        string final_response = response_filter(ai_response);


        //AI's response
        cout << "AI: " << final_response << endl;
    }

    cout << "Goodbye!" << endl;
    return 0;
}
