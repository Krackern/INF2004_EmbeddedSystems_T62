<?php

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $uploadDir = '/var/www/html/Embedded-PHP/uploads/upload/';
    
    if (!file_exists($uploadDir)) {
        (mkdir($uploadDir, 0777, true));
    }
    
    // Convert file to PDF using the TCPDF library
    require_once('tcpdf/tcpdf.php');

    $pdf = new TCPDF();
    $pdf->setPrintHeader(false);
    $pdf->setPrintFooter(false);

    if (isset($_POST["pdf"])) {
        
        $filesInDir = scandir($uploadDir);
        
        foreach ($filesInDir as $file) {
            
            if ($file != '.' && $file != '..') {
                $uploadedFile = $uploadDir . $file;
                        
                // Check if the file is a valid type
                $allowedTypes = ['doc', 'docx', 'txt', 'pdf'];
                $fileType = strtolower(pathinfo($uploadedFile, PATHINFO_EXTENSION));

                if (!in_array($fileType, $allowedTypes)) {
                    die('Invalid file');
                }

                $pdf->AddPage();
                $pdf->SetFont('dejavusans', '', 12);

                $content = file_get_contents($uploadedFile);
                $pdf->writeHTML($content);
            
                $pdfFile = pathinfo($uploadedFile, PATHINFO_FILENAME) . '.pdf';
                $pdf->Output('/var/www/html/Embedded-PHP/uploads/upload/' . $pdfFile, 'D');
            
                echo '<p> Generate PDF here: <a href="' . $pdfFile . '">' . $pdfFileFile .
                    '</a></p>';
        }
    }
    }

    if (isset($_POST["csv"])) {
        
        $filesInDir = scandir($uploadDir);
        
        foreach($filesInDir as $file) {
            if($file != '.' && $file != '.') {
                $uploadedFile = $uploadDir . $file;

                $csvFile = pathinfo($uploadedFile, PATHINFO_FILENAME) . '.csv';

                // Open the text file in read mode
                $textFile = fopen($uploadedFile, "r");
                if ($textFile === FALSE) {
                    die('Error opening text file');
                }

                // Open the CSV file for writing
                $csvFileHandle = fopen($csvFile, "w");
                if ($csvFileHandle === FALSE) {
                    die('Error opening CSV file');
                }

                // Read the text file line by line and write to the CSV file
                while (($textLine = fgetcsv($textFile)) !== FALSE) {
                    fputcsv($csvFileHandle, $textLine);
                }

                fclose($textFile);
                fclose($csvFileHandle);

                echo '<p> Generate CSV here: <a href="' . $csvFile . '">' . $csvFile .
                    '</a></p>';
        }
    }
    }
}

