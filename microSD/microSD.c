#include <stdio.h>
#include "pico/stdlib.h"
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

bool openFileForReading(FIL* fil, const char* filename) {
    FRESULT fr = f_open(fil, filename, FA_READ);
    if (fr != FR_OK) {
        printf("ERROR: Could not open file for reading (%d)\r\n", fr);
        return false;
    }
    return true;
}

void printFileContents(FIL* fil) {
    char buf[100];
    printf("Reading from file:\r\n");
    printf("---\r\n");
    while (f_gets(buf, sizeof(buf), fil)) {
        printf(buf);
    }
    printf("\r\n---\r\n");
}

int main() {
    FATFS fs;
    FIL fil;
    char filename[] = "test02.txt";

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
        // if (openFileForWriting(&fil, filename)) {
        //     // if (writeTextToFile(&fil, "This is another test\r\n") && writeTextToFile(&fil, "of writing to an SD card.\r\n")) {
        //         if (openFileForReading(&fil, filename)) {
        //             printFileContents(&fil);
        //             closeFile(&fil);
        //         }
        //     // }
        // }
        if(openFileForReading(&fil, filename)){
            printFileContents(&fil);
            closeFile(&fil);
        }
    }
        f_unmount("0:");


    while (true) {
        sleep_ms(1000);
    }

}