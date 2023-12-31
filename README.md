# INF2004_EmbeddedSystems_T62
# Introduction
Our team will be proposing a PC Auditing tool using Raspberry Pi Pico W for Lab Technicians to use. The tool will assist lab technicians in auditing PCs and will work on Windows Operating System. Although the Raspberry Pi Pico W is a microcontroller, it is suited for developing a PC Auditing tool as it is low cost and widely available. 

# Features
1. Collection of Applications Running on the Windows PCs
The tool will be able to determine what applications are running on the Windows PC and their versions.

2. Blacklisting & Whitelisting of Applications
The tool is capable of blacklisting and whitelisting applications to control which applications can be executed or accessed on the system. For example, if an application is not updated and may contain security vulnerabilities, the tool can blacklist the application. The applications are not listed under blacklist and whitelist will fall under the "others" category.
* Blacklisting: Prevent the execution of specific applications known to pose security risks or vulnerabilities. For instance, if an application is outdated or malicious, it can be blacklisted to protect the system.
* Whitelisting: Define a list of trusted applications to enhance security and restrict unauthorised software installations.
* Others: List of applications that are not under the blacklist and whitelist files.

3. Generation of Report
The PC Auditing Tool offers a report generation feature, enabling lab technicians to create detailed audit reports for each audited PC. These reports may include information on blacklisted/whitelisted applications, system configurations, and potential security issues.
Reports can be exported in various formats such as text file and CSV file, allowing for easy documentation and sharing of audit results.

4. Data Logging in MicroSD Module
To ensure data integrity and maintain an audit trail, the tool is equipped with a MicroSD module for logging and storing audit-related data.
Detailed logs are maintained, including application execution history, system changes, and any security events or incidents that occur during the audit.
Blacklisted and Whitelisted files will be stored in the microSD card.

# Benefits:
Affordability: The use of the Raspberry Pi Pico W ensures a low-cost solution for PC auditing, making it accessible for educational institutions and small businesses with budget constraints.

Enhanced Security: By blacklisting insecure, outdated or unauthorised applications and monitoring system changes, the tool significantly improves the security posture of audited PCs.

Versatility: The lab technicians can use the tool on a wide variety of PCs with WIndows Operating System, streamlining the auditing process.

Documentation: Detailed and exportable audit reports enable lab technicians to maintain comprehensive records of PC audits and security assessments.


# System Overview
![image](https://github.com/Krackern/INF2004_EmbeddedSystems_T62/assets/114002549/091ce864-409b-47be-a5ac-37c7290d2fc9)

The system comprises a MicroSD card for error log storage and information retrieval, a Pico microcontroller for data collection, processing, and transmission, a PC for information transfer, a web server for data visualization and file hosting, and a web interface for data access. Data flows from the MicroSD card and PC to the Pico for processing, then to the web server for storage and visualization, and finally to users for access and download. This system facilitates centralized data collection, processing, filtering, visualization, and download, offering a comprehensive solution for data management.

# Component Diagram
<img width="407" alt="image" src="https://github.com/Krackern/INF2004_EmbeddedSystems_T62/assets/121931429/92ce94fb-da75-4b8e-ab88-6725c4da9129">

The component diagram depicts the interactions between the system's core components: the MicroSD card, Pico microcontroller, PC, web server, and web interface. The Pico, serving as the central processing unit, retrieves information from the MicroSD card, drops scripts to the PC for data gathering, processes and filters the collected data, transmits it to the web server, and renders the data on a webpage. The PC communicates with the Pico via MSC, facilitating information exchange and processing support. The web server hosts the webpage and provides file hosting capabilities, enabling data visualization and PDF download based on whitelist and blacklist rules. The web interface serves as the user interaction point, allowing data access and analysis. This intricate interplay between components ensures centralized data collection, processing, filtering, visualization, and download, offering a streamlined solution for data management.

# Block Diagram
<img width="689" alt="image" src="https://github.com/Krackern/INF2004_EmbeddedSystems_T62/assets/121931429/b93a0258-6bf4-4003-a97d-f0035602ee2d">

Block Diagram Overview:

Pico Drivers:
* MicroSD Driver: Facilitates communication with the MicroSD card for file storage.
* HID Driver: Executes commands, generating text files as output, and links to SD card storage.
* MSC Driver: Manages Mass Storage Class communication, linking to the generation of text files as output.
* WiFi Driver: Enables communication with a web server for uploading and downloading data.

MicroSD (SD Card Storage):
* The MicroSD driver allows the Pico to interact with the SD card, providing a reliable storage medium for files.

HID Driver (Generate Text File as Output):
* Initiates commands through HID, executing operations that result in the generation of text files.
* Links to SD card storage to save the generated text files.

MSC Driver (Link to Generate Text File as Output):
* Manages Mass Storage Class communication, establishing a connection to the generation of text files as output.

WiFi Driver (Web Server - Webpage):
* The WiFi driver facilitates communication with a web server.
* The web server hosts a webpage that allows reading and sorting of blacklist and whitelist files.
* SD card storage enables the retrieval and uploading of files between the Pico and the web server.

# Web Server Details:
* Website: http://35.212.228.98/Embedded-PHP/report.php
* User: dev
* Password: dev123

# Workflow:

File Generation:
* HID and MSC drivers collaborate to execute commands and generate text files on the Pico.
* The generated files are stored on the MicroSD card via the SD card storage driver.

Web Server Interaction:
* The Pico, utilizing the WiFi driver, communicates with a web server.
* The web server hosts a webpage that enables reading and sorting of blacklist and whitelist files stored on the SD card.

Data Upload:
* Files are uploaded from the Pico's SD card to the web server, facilitating data sharing.

This project integrates various drivers on the Raspberry Pi Pico to handle file operations, execute commands through HID, establish Mass Storage Class communication, and enable WiFi connectivity for web server interaction. The collaborative efforts of these components provide a comprehensive solution for managing and categorizing data.



# Flowchart
<img width="500" alt="image" src="https://github.com/Krackern/INF2004_EmbeddedSystems_T62/assets/121931429/f814d108-0a3a-420f-9a4d-768e8c240fe8">

This project involves using a Raspberry Pi Pico microcontroller to perform file comparison tasks and interact with a web server. The Pico communicates with a connected computer via USB to execute commands and read/write data on an SD card. The primary functionalities include running HID commands, file comparison, and sending data to a web server.

Flowchart Overview:

1. Run HID Command (MSC Communication):
Press a button on the Raspberry Pi Pico to initiate an HID command.
The Pico executes the command, such as reading or writing files using MSC (Mass Storage Class) communication through USB.

2. Output to SD Card:
The output of the HID command is stored on the SD card.
Error handling: If the HID command is unsuccessful, rerun the command in PowerShell.

3. Read Output from SD Card:
Read the output files (e.g., blacklist.txt, whitelist.txt) from the SD card.
Error handling: If reading encounters issues, loop back to HID to rerun the command in PowerShell to retrieve the output.

4. Compare Files:
Compare the contents of the latest output files.
Error handling: If files are not comparable, generate an additional "Others" file.

5. Blacklist/Whitelist:
Identify items based on the comparison, categorizing them into blacklist and whitelist.

6. Send to Web Server and Generate PDF/CSV:
Send the categorized data to a web server.
Generate PDF or CSV reports based on the categorized data.
Error handling: If the server interaction encounters issues, loop back to rerun the command in PowerShell.

This project utilizes the Raspberry Pi Pico's capabilities to perform file operations, comparisons, and web server interactions. The HID commands, file comparison, and server communication are integrated to achieve a streamlined workflow for managing data categorization and reporting.

# How to Set Up (Supposedly)
* Put Audit_Tool into your Pico-Example folder, build and run normally
* Wait for SD Card to mount onto PC after plugging it in, press the bootsel button to run the program

 # How to Set Up (Actual)
* Due to incompleted integration, we only managed to integrate USB HID & MSC, and also Blacklist/Whitelist Function & Uploading to Web Server Function via Pico
* Audit_Tool Folder: Contains USB HID & MSC integrated codes
* project-http Folder: Contains Blacklisting/Whitelisting & Uploading to Web Server Function integrated codes
* WebServer Folder: Contains the PHP Codes for Conversion from Text File to PDF and CSV
  
# Future Works
1. Scalability
  - Allow for mounting to different Operating Systems such as Linux and MacOS
  - Allow for different File Systems such as NTFS, not just FATFS
  - Drop not just scripts which get their processes and their running versions, but also scripts that can retrieve other information on the Host PC 
2. Additional Features
  - Allow for Real Time Monitoring System

# Claimed vs Developed Functions
| Claimed Functions  | Developed Functions |
| ------------- | ------------- |
| Drop Scripts into Host PC from Pico | Send Host PC certain keystrokes (in this case, to get the processes and their versions) and output it to a text file to store in the SD Card|
| Error logs to be sent to the SD Card  | Store the output file of the processes and their versions into the SD Card |
| Analyse the output file by blacklisting and whitelisting them  | Store the output file of the processes and their versions in the SD Card,  (SD card does not allow blacklisting and whitelisting to work) |
| Error logs to be sent to the SD Card  | Store the output file of the processes and their versions into the SD Card |
| Let Pico W to convert the files to PDFs or CSVs before uploading to Web Server  | Convert the files to PDFs and CSVs on Web Server |

# Conclusion:
The Raspberry Pi Pico W PC Auditing Tool is a cost-effective, user-friendly, and versatile solution designed to assist lab technicians in auditing and securing PCs. This tool enhances security, streamlines auditing processes, and provides robust documentation capabilities, making it an ideal choice for educational institutions, small businesses, and organisations with limited budgets.


# Limitations / Challenges:
* Integration is not fully completed
  *   Unable to Blacklist/Whitelist from SD Card
* Due to time constraint and limited resources, we were unable to fully integrate the features together
* The mounting of the SD Card from Pico is slow
* There is only 1 output file generated per run, which makes it slow for the user to view multiple files
* The pico device itself cannot generate CSV and PDF, and needs the use of a webpage to generate and view these files (Webserver folder)
    


