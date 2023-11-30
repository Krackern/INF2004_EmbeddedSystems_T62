#include <stdio.h>
#include "pico/stdlib.h"
#include "upload_function.c"


bool success =false;
bool runInit = 0;

int main(){
    char *fileName = "blacklist";
    char *fileContent = "Display Name & Version || Bitdefender Total Security 27.0.20.105 || Microsoft 365 - en-us 16.0.16924.20150 || GlobalProtect 6.1.1";

    char *modifiedContent = replaceSubstring(fileContent, "|| ", "\n");

    runInit = uploadFile(fileName, modifiedContent, runInit);
    
    free(modifiedContent);

    char *fileName1 = "whitelist";
    char *fileContent1 = "Mozilla Firefox (x64 en-US) 120.0 || Mozilla Maintenance Service 116.0.3 || Microsoft 365 Apps for enterprise - en-us 16.0.16924.20150 || Microsoft OneDrive 23.226.1031.0003 || Microsoft OneNote - en-us 16.0.16924.20150 || Raspberry Pi Pico SDK v1.5.1 1.5.1";
    char *modifiedContent1 = replaceSubstring(fileContent1, "|| ", "\n");
    runInit = uploadFile(fileName1, modifiedContent1, runInit);

    free(modifiedContent1);

    //Get filename
    char *fileName2 = "others";

    //Get file content
    char *fileContent2 = "Planet9 Stub 1.0.142 || AMD Software 20.40.32.13 NVIDIA || Graphics Driver 512.74 512.74 || NVIDIA GeForce Experience 3.21.0.36 3.21.0.36 || NVIDIA PhysX System Software 9.20.0221 9.20.0221 || NVIDIA FrameView SDK 1.1.4923.29548709 1.1.4923.29548709 || NVIDIA SHIELD Streaming 7.1.29457609 || NVIDIA Install Application 2.1002.370.0 || NVIDIA ABHub 14.3.61.0 || NVIDIA Backend 38.0.6.0 NVIDIA Container 1.27 || NVIDIA TelemetryApi helper for NvContainer 1.27 || NVIDIA LocalSystem Container 1.27 || NVIDIA Message Bus for NvContainer 1.27 || NVAPI Monitor plugin for NvContainer 1.27 || NVIDIA NetworkService Container 1.27 || NVIDIA Session Container 1.27 || NVIDIA User Container 1.27 || NvModuleTracker 6.14.24033.38719 || NVIDIA NodeJS 3.21.0.36 || NVIDIA Platform Controllers and Framework 461.44 || NVIDIA Watchdog Plugin for NvContainer 1.27 || NVIDIA Telemetry Client 14.3.61.0 || NVIDIA Virtual Host Controller 3.04.0.1 || Nvidia Share 3.21.0.36 || NVIDIA ShadowPlay 3.21.0.36 3.21.0.36 ||NVIDIA SHIELD Wireless Controller Driver 3.21.0.14 || NVIDIA Update Core 38.0.6.0 || NVIDIA Virtual Audio 4.13.0.0 4.13.0.0 || Microsoft Update Health Tools 5.72.0.0 || Microsoft Visual C++ 2022 X64 Minimum Runtime - 14.32.31326 14.32.31326 || PuTTY release 0.79 (64-bit) 0.79.0.0";         

    
    //To replace || with \n
    char *modifiedContent2 = replaceSubstring(fileContent2, "|| ", "\n");
    
    //Upload
    runInit = uploadFile(fileName2, modifiedContent2, runInit);
}