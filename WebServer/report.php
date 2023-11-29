<link rel="stylesheet"
href="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css"
integrity=
"sha384-Vkoo8x4CGsO3+Hhxv8T/Q5PaXtkKtu6ug5TOeNV6gBiFeWPGFN9MuhOf23Q9Ifjh"
crossorigin="anonymous">

<link rel="stylesheet" href="css/main.css">

<!--jQuery-->
    <script defer
        src="https://code.jquery.com/jquery-3.4.1.min.js"
        integrity="sha256-CSXorXvZcTkaix6Yvo6HppcZGetbYMGWSFlBw8HfCJo="
        crossorigin="anonymous">
    </script>
<!--Bootstrap JS-->
    <script defer
        src="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/js/bootstrap.bundle.min.js"
        integrity="sha384-6khuMg9gaYr5AxOqhkVIODVIvm9ynTT5J4V1cfthmT+emCG6yVmEZsRHdxlotUnm"
        crossorigin="anonymous">
    </script>

<!--custom JS-->
<script defer src="js/activateMenu.js"></script>

<body>
    <?php
        include "nav.inc.php"
    ?>
    <header class="jumbotron text-center">
        <h1 class="display-4">Report</h1>
    </header>
    
    <h2>Select File</h2>
    <form action="upload.php" method="post" enctype="multipart/form-data">
        <!--<input type="file" name="file[]" multiple accept=".doc, .docx, .txt">-->
        <button type="submit" name="pdf">PDF</button>
        <button type="submit" name="csv">CSV</button>  
    </form>
    
</body>

