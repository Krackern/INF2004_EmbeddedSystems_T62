# INF2004_EmbeddedSystems_T62
System Overview
![image](https://github.com/Krackern/INF2004_EmbeddedSystems_T62/assets/114002549/091ce864-409b-47be-a5ac-37c7290d2fc9)

# Block Diagram
<img width="689" alt="image" src="https://github.com/Krackern/INF2004_EmbeddedSystems_T62/assets/121931429/b93a0258-6bf4-4003-a97d-f0035602ee2d">


# Flowchart
<img width="500" alt="image" src="https://github.com/Krackern/INF2004_EmbeddedSystems_T62/assets/121931429/f814d108-0a3a-420f-9a4d-768e8c240fe8">

This project involves using a Raspberry Pi Pico microcontroller to perform file comparison tasks and interact with a web server. The Pico communicates with a connected computer via USB to execute commands and read/write data on an SD card. The primary functionalities include running HID commands, file comparison, and sending data to a web server.

Flowchart Overview:

Run HID Command (MSC Communication):

Press a button on the Raspberry Pi Pico to initiate an HID command.
The Pico executes the command, such as reading or writing files using MSC (Mass Storage Class) communication through USB.
Output to SD Card:

The output of the HID command is stored on the SD card.
Error handling: If the HID command is unsuccessful, rerun the command in PowerShell.
Read Output from SD Card:

Read the output files (e.g., blacklist.txt, whitelist.txt) from the SD card.
Error handling: If reading encounters issues, loop back to HID to rerun the command in PowerShell to retrieve the output.
Compare Files:

Compare the contents of the latest output files.
Error handling: If files are not comparable, generate an additional "Others" file.
Blacklist/Whitelist:

Identify items based on the comparison, categorizing them into blacklist and whitelist.
Send to Web Server and Generate PDF/CSV:

Send the categorized data to a web server.
Generate PDF or CSV reports based on the categorized data.
Error handling: If the server interaction encounters issues, loop back to rerun the command in PowerShell.

This project utilizes the Raspberry Pi Pico's capabilities to perform file operations, comparisons, and web server interactions. The HID commands, file comparison, and server communication are integrated to achieve a streamlined workflow for managing data categorization and reporting.



