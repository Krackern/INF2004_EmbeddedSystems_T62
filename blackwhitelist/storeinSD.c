#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/bootrom.h"
#include "sd_card.h"
#include "ff.h"

bool initializeSDCard() {
    if (!sd_init_driver()) {
        printf("ERROR: Could not initialize SD card\r\n");
        return false;
    }
    return true;
}

bool mountDrive(FATFS* fs) {
    FRESULT fr = f_mount(fs, "0:", 1);
    if (fr != FR_OK) {
        printf("ERROR: Could not mount filesystem (%d)\r\n", fr);
        return false;
    }
    return true;
}

bool openFileForWriting(FIL* fil, const char* filename) {
    FRESULT fr = f_open(fil, filename, FA_WRITE | FA_CREATE_ALWAYS);
    if (fr != FR_OK) {
        printf("ERROR: Could not open file for writing (%d)\r\n", fr);
        return false;
    }
    return true;
}

bool writeTextToFile(FIL* fil, const char* text) {
    int ret = f_printf(fil, text);
    if (ret < 0) {
        printf("ERROR: Could not write to file (%d)\r\n", ret);
        return false;
    }
    return true;
}

bool closeFile(FIL* fil) {
    FRESULT fr = f_close(fil);
    if (fr != FR_OK) {
        printf("ERROR: Could not close file (%d)\r\n", fr);
        return false;
    }
    return true;
}

int main() {
    FATFS fs;
    FIL whitelistFile, blacklistFile;

    stdio_init_all();
    sleep_ms(50);
    printf("\r\nSD card test. Press 'enter' to start.\r\n");

    while (true) {
        char buf[1];
        buf[0] = getchar();
        if ((buf[0] == '\r') || (buf[0] == '\n')) {
            break;
        }
    }

    if (initializeSDCard() && mountDrive(&fs)) {
        if (openFileForWriting(&whitelistFile, "0:/whitelist.txt") && openFileForWriting(&blacklistFile, "0:/blacklist.txt")) {
            if (writeTextToFile(&whitelistFile, "This is a line in the whitelist.\r\n") && writeTextToFile(&blacklistFile, "This is a line in the blacklist.\r\n")) {
                closeFile(&whitelistFile);
                closeFile(&blacklistFile);
            }
        }
    }

    f_unmount("0:");

    while (true) {
        sleep_ms(1000);
    }
}
