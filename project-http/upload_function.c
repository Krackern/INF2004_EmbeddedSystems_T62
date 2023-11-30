#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pico/time.h>
#include <pico/stdio.h>
#include <boards/pico_w.h>
#include "pico_http_client/pico_http_client.h"
#include <ctype.h>
#include <time.h>

//#define uploadURL "http://35.212.175.193/fileUploadScript.php"
#define uploadURL "http://35.212.228.98/Embedded-PHP/fileUploadScript.php"

// WiFi credentials
char wifi_name[] = "Kuasimikua";
char wifi_password[] = "chaonimab";

// Function to initialize WiFi connection
int init_wifi() {
    if (cyw43_arch_init_with_country(CYW43_COUNTRY_FRANCE)) {
        printf("Failed to initialise WiFi\n");
        return 0;
    }
    cyw43_arch_enable_sta_mode();
    if (cyw43_arch_wifi_connect_async(wifi_name, wifi_password, CYW43_AUTH_WPA2_AES_PSK)) {
        return 0;
    }

    // Wait for WiFi connection
    int flashrate = 500;
    int status = CYW43_LINK_UP + 1;
    while (status >= 0 && status != CYW43_LINK_UP) {
        int new_status = cyw43_tcpip_link_status(&cyw43_state, CYW43_ITF_STA);
        if (new_status != status) {
            status = new_status;
            flashrate = flashrate / (status + 1);
            printf("WiFi connection status: %d %d\n", status, flashrate);
        }
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(flashrate);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        sleep_ms(flashrate);
    }
    printf("WiFi Connected\n");
    return 1;
}

char* generateRandomString(int length){
    srand(time(NULL));
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$_";
    int charsetSize = sizeof(charset) - 1;

    char *randomString = malloc(length + 1);

    if(randomString){
        for(int i = 0; i < length; i++) {
            int key = rand() % charsetSize;
            randomString[i] = charset[key];
        }
        randomString[length] = '\0';
    }

    return randomString;
}

char *renameFile(const char *filename) {
    char *randomStr = generateRandomString(14);

    // Calculate the size of the result string
    int resultSize = strlen(filename) + strlen(randomStr) + 6; // 1 for '_', 4 for ".txt", 1 for null terminator
    char *result = malloc(resultSize);

    // Create the result string
    snprintf(result, resultSize, "%s_%s.txt", filename, randomStr);

    free(randomStr); // Free the memory allocated for the random hash

    return result;
}


// Function to send a simple HTTP GET request
void send_http_request(const char *url, const char *content_type) {
    printf("Hit!\n");
    http_client_t *client = new_http_client(url);
    http_response_t response = http_request("GET", client, NULL); // Use GET enum value directly
    printf("Response: %s\n", response.body);
    free_http_client(client);
    free(response.body);
}

// Function to send a multipart POST request
void send_multipart_post_request(const char *url, const char *boundary, const char *file_field_name, const char *file_name, const char *file_content, const char *submit_field_name, const char *submit_value) {
    printf("Hit Multipart POST!\n");
    http_client_t *client = new_http_client(url);

    // Construct the multipart form data
    char *post_data = (char *)malloc(BUFSIZ);
    if (post_data == NULL) {
        printf("Failed to allocate memory for post_data\n");
        return;
    }

    int post_content = snprintf(post_data, BUFSIZ,
                                "------%s\r\n"
                                "Content-Disposition: form-data; name=\"%s\"; filename=\"%s\"\r\n"
                                "Content-Type: text/plain\r\n\r\n"
                                "%s\r\n"
                                "------%s\r\n"
                                "Content-Disposition: form-data; name=\"%s\"\r\n\r\n"
                                "%s\r\n"
                                "------%s--\r\n",
                                boundary, file_field_name, file_name, file_content, boundary, submit_field_name, submit_value, boundary);

    add_header(client, "Content-Type", "multipart/form-data; boundary=----WebKitFormBoundaryAlBzvVF8cNFazQL2");
    printf("Post_Data: %s\n", post_data);
    // Use POST enum value directly and provide the post_data
    http_response_t response = http_request("POST", client, post_data);

    printf("Response: %s\n", response.body);

    free(post_data);
    free_http_client(client);
    free(response.body);
}

// Function to replace substrings and handle line breaks
char *replaceSubstring(const char *original, const char *find, const char *replace) {
    size_t findLen = strlen(find);
    size_t replaceLen = strlen(replace);

    // Allocate memory for the result string
    char *result = (char *)malloc(1);  // Start with an empty string
    result[0] = '\0';

    // Iterate over the original string
    const char *current = original;
    while (*current != '\0') {
        // Check for the occurrence of "||"
        if (strncmp(current, find, findLen) == 0) {
            // Concatenate the replacement string
            result = (char *)realloc(result, strlen(result) + replaceLen + 1);
            strcat(result, replace);

            // Move to the next position after "||"
            current += findLen;
        } else if (*current == '\n') {
            // Concatenate "\n" and copy leading whitespace
            result = (char *)realloc(result, strlen(result) + 1 + 1);

            // Copy leading whitespace
            while (*(current + 1) != '\0' && (*(current + 1) == ' ' || *(current + 1) == '\t')) {
                strcat(result, " ");
                current++;
            }

            // Concatenate "\n"
            strcat(result, "\n");
            current++;
        } else {
            // Concatenate the current character
            result = (char *)realloc(result, strlen(result) + 1 + 1);
            strncat(result, current, 1);
            current++;
        }
    }

    return result;  
}

// Function to upload a file
int uploadFile(const char *file_name, const char *file_content, int runInit) {
    if(!runInit){
        stdio_init_all();
        if (!init_wifi()) {
            printf("Wifi connection failed");
            return 0; // Exit if WiFi initialization fails
        }
    }

    char *modifiedFileName = renameFile(file_name);
    printf("%s\n",modifiedFileName);

    const char *url = uploadURL;
    const char *boundary = "WebKitFormBoundaryAlBzvVF8cNFazQL2";
    const char *file_field_name = "the_file";
    const char *submit_field_name = "submit";
    const char *submit_value = "Start Upload";

    send_multipart_post_request(url, boundary, file_field_name, modifiedFileName, file_content, submit_field_name, submit_value);

    free(modifiedFileName);

    return 1;
}
