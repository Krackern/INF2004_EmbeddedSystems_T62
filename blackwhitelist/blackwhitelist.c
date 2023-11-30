#include <stdio.h>
#include <string.h>
//#include "blackwhitelist.h"


bool filterContent(const char *inputPath, const char *whitelistPath, const char *blacklistPath, const char *othersPath) {
    FIL inputFile, whitelistFile, blacklistFile, othersFile;
    char line[1000];
    FRESULT fr;

    // Open the input file
    fr = f_open(&inputFile, inputPath, FA_READ);
    if (fr != FR_OK) return false;

    // Open the whitelist, blacklist, and others files
    fr = f_open(&whitelistFile, whitelistPath, FA_WRITE | FA_CREATE_ALWAYS);
    if (fr != FR_OK) {
        f_close(&inputFile);
        return false;
    }
    fr = f_open(&blacklistFile, blacklistPath, FA_WRITE | FA_CREATE_ALWAYS);
    if (fr != FR_OK) {
        f_close(&inputFile);
        f_close(&whitelistFile);
        return false;
    }
    fr = f_open(&othersFile, othersPath, FA_WRITE | FA_CREATE_ALWAYS);
    if (fr != FR_OK) {
        f_close(&inputFile);
        f_close(&whitelistFile);
        f_close(&blacklistFile);
        return false;
    }

    // Filter content
    while (f_gets(line, sizeof(line), &inputFile)) {
        if (strstr(line, "Windows Driver Package") ||
            strstr(line, "Microsoft Visual") ||
            strstr(line, "NVIDIA ") ||
            strstr(line, "Adobe")) {
            f_puts(line, &whitelistFile);
        } else if (strstr(line, "Bitdefender") ||
                   strstr(line, "Microsoft 365 - en-us") ||
                   strstr(line, "GlobalProtect")) {
            f_puts(line, &blacklistFile);
        } else {
            f_puts(line, &othersFile);
        }
    }

    // Close all files
    f_close(&inputFile);
    f_close(&whitelistFile);
    f_close(&blacklistFile);
    f_close(&othersFile);

    return true;
}
