// #include "blackwhitelist.h"

// #include <stdio.h>
// #include "ff.h"        // Include the FatFs library header
// #include <string.h>    // Include for string manipulation functions
// #include <stdbool.h>   // Include for boolean types

// // Function to check if a line contains a keyword
// bool containsKeyword(const char *line, const char *keyword) {
//     return strstr(line, keyword) != NULL;
// }

// // Function to filter the content of an input file into a whitelist and blacklist file
// bool filterContent(const char *inputPath, const char *whitelistPath, const char *blacklistPath) {
//     FIL inputFile, whitelistFile, blacklistFile; // File objects for FatFs
//     FRESULT fr;    // Variable to hold the result of FatFs operations
//     char line[256]; // Buffer to hold lines read from the input file

//     // Open the input file for reading
//     fr = f_open(&inputFile, inputPath, FA_READ);
//     if (fr != FR_OK) return false;

//     // Open the whitelist file for writing
//     fr = f_open(&whitelistFile, whitelistPath, FA_WRITE | FA_CREATE_ALWAYS);
//     if (fr != FR_OK) {
//         f_close(&inputFile);
//         return false;
//     }

//     // Open the blacklist file for writing
//     fr = f_open(&blacklistFile, blacklistPath, FA_WRITE | FA_CREATE_ALWAYS);
//     if (fr != FR_OK) {
//         f_close(&inputFile);
//         f_close(&whitelistFile);
//         return false;
//     }

//     // Read each line from the input file and filter into the appropriate list
//     while (f_gets(line, sizeof(line), &inputFile)) {
//         if (containsKeyword(line, "Windows Driver Package") ||
//             containsKeyword(line, "Microsoft Visual") ||
//             containsKeyword(line, "NVIDIA ") ||
//             containsKeyword(line, "Adobe")) {
//             // If the line contains a keyword, write it to the whitelist
//             if (f_puts(line, &whitelistFile) == EOF) {
//                 break; // Stop if write fails
//             }
//         } else {
//             // Otherwise, write it to the blacklist
//             if (f_puts(line, &blacklistFile) == EOF) {
//                 break; // Stop if write fails
//             }
//         }
//     }

//     // Close all files
//     f_close(&inputFile);
//     f_close(&whitelistFile);
//     f_close(&blacklistFile);

//     // If we exited the loop without breaking, the operation was successful
//     return fr == FR_OK;
// }

#include "ff.h"    // Include for FatFs library
#include <string.h> // Include for string manipulation functions
#include <stdbool.h> // Include for boolean type

// Function to copy the content of one file to another
bool copyFileContent(const char *sourcePath, const char *destinationPath) {
    FIL sourceFile, destinationFile; // File objects for FatFs
    FRESULT fr; // Variable to hold the result of FatFs operations
    char line[256]; // Buffer to hold lines read from the source file

    // Open the source file for reading
    fr = f_open(&sourceFile, sourcePath, FA_READ);
    if (fr != FR_OK) return false;

    // Open the destination file for writing
    fr = f_open(&destinationFile, destinationPath, FA_WRITE | FA_CREATE_ALWAYS);
    if (fr != FR_OK) {
        f_close(&sourceFile);
        return false;
    }

    // Copy each line from the source file to the destination file
    while (f_gets(line, sizeof(line), &sourceFile)) {
        if (f_puts(line, &destinationFile) < 0) {
            // If writing fails, close both files and return false
            f_close(&sourceFile);
            f_close(&destinationFile);
            return false;
        }
    }

    // Close both files
    f_close(&sourceFile);
    f_close(&destinationFile);

    return true;
}
