Setup Instructions
Dependencies
1.Install libcurl:
  Windows: Download the Windows binaries for libcurl from the official website: https://curl.se/download.html.
  Ensure you download the version compatible with your system architecture (32-bit or 64-bit).
2.Set up libcurl:
  Extract the downloaded libcurl files.
  Add the bin directory (containing libcurl.dll) to your system's PATH environment variable.
  Copy libcurl-x64.dll to Your Project Directory
  Place the libcurl-x64.dll file in the same directory as your compiled executable (llm_app.exe).
4.Compile the application using the following command:
  g++ main.cpp -o llm_app -lcurl -LC:\path\to\libcurl\lib -IC:\path\to\libcurl\include
5.Execute the application in the command prompt:
  llm_app.exe


