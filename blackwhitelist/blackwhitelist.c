#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"
// Define the serial port to# use
#define SERIAL_PORT "COM5"

int main() {
  FILE *textFile, *blacklistFile, *whitelistFile; // Declare file pointers for the text file, blacklist file, and whitelist file
  char textLine[256], blacklist[100], whitelist[100]; // Declare character arrays to store lines from the text file, blacklist file, and whitelist file
  int foundBlacklist, foundWhitelist; // Declare integer variables to track whether a line is found in the blacklist or whitelist
  int number_of_lines = 0; // Initialize a counter to count the number of text files

  // Open the serial port for writing
  FILE *serialPort = fopen(SERIAL_PORT, "w");
  if (!serialPort) {
    printf("Error opening serial port\n");
    return 1;
  }

  // Open the text file in read mode
  textFile = fopen("text.txt", "r");
  if (textFile == NULL) {
    printf("Error opening text file\n");
    return 1;
  }

  // Open the blacklist file in read mode
  blacklistFile = fopen("blacklist.txt", "r");
  if (blacklistFile == NULL) {
    printf("Error opening blacklist file\n");
    return 1;
  }

  // Open the whitelist file in read mode
  whitelistFile = fopen("whitelist.txt", "r");
  if (whitelistFile == NULL) {
    printf("Error opening whitelist file\n");
    return 1;
  }

  // Read the blacklist file line by line and store each line in the blacklist array
  while (fgets(blacklist, sizeof(blacklist), blacklistFile) != NULL) {
    blacklist[strlen(blacklist) - 1] = '\0'; // Remove the newline character from the blacklist entry
  }

  // Read the whitelist file line by line and store each line in the whitelist array
  while (fgets(whitelist, sizeof(whitelist), whitelistFile) != NULL) {
    whitelist[strlen(whitelist) - 1] = '\0'; // Remove the newline character from the whitelist entry
  }

  // Read the text file line by line
  while (fgets(textLine, sizeof(textLine), textFile) != NULL) {
    number_of_lines++; // Increment the counter for each text file

    // Check if the line is found in the blacklist
    foundBlacklist = 0; // Initialize the foundBlacklist flag to 0
    for (int i = 0; i < strlen(blacklist); i++) {
      if (strstr(textLine, blacklist[i])) { // Check if the current blacklist entry is found in the text line
        foundBlacklist = 1; // Set the foundBlacklist flag to 1 if the blacklist entry is found
        break; // Break out of the loop if the blacklist entry is found
      }
    }

    // Check if the line is found in the whitelist
    foundWhitelist = 0; // Initialize the foundWhitelist flag to 0
    for (int i = 0; i < strlen(whitelist); i++) {
      if (strstr(textLine, whitelist[i])) { // Check if the current whitelist entry is found in the text line
        foundWhitelist = 1; // Set the foundWhitelist flag to 1 if the whitelist entry is found
        break; // Break out of the loop if the whitelist entry is found
      }
    }

    // If the line is not blacklisted and whitelisted, send it to the serial port
    if (!foundBlacklist && foundWhitelist) { // Check if the line is not blacklisted and whitelisted
      fprintf(serialPort, "%s", textLine); // Send the text line to the serial port
    }
  }

  // Print the number of lines processed
  printf("\nNumber of lines processed: %d\n", number_of_lines);

  // Close the files
  fclose(serialPort); // Close the serial port
  fclose(textFile); // Close the text file
  fclose(blacklistFile); // Close the blacklist file
  fclose(whitelistFile); // Close the whitelist file

  return 0; // Return 0 indicating successful execution
}