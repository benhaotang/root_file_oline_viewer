<?php
$allowedExts = array("root");
$temp = explode(".", $_FILES["file"]["name"]);
$extension = end($temp); 
if ((($_FILES["file"]["type"] == "application/octet-stream"))&& ($_FILES["file"]["size"] < 10240000)&& in_array($extension, $allowedExts))
{
    if ($_FILES["file"]["error"] > 0)
    {
        echo "Error:" . $_FILES["file"]["error"] . "<br>";
    }
    else
    {
        echo "File Name: " . $_FILES["file"]["name"] . "<br>";
        echo "Type: CERN ROOT File <br>";
        echo "File Size: " . number_format(($_FILES["file"]["size"] / 1024),1) . " kB<br>";
        exec("rm -f ./upload/*.root");
        exec("rm -f ./result/*.pdf");
        exec("rm -f ./result/*.zip");
        exec("rm -f ./result/*.html");
        move_uploaded_file($_FILES["file"]["tmp_name"], "upload/" . "temp.root");
        exec("/bin/bash do.sh");
        exec("zip ./result/all.zip ./result/*.pdf");
        echo "<hr/>Done!<a href=\"./result/index.html\">Go to result</a>";
    }
}
else
{
    echo "You should upload vaild ROOT File!";
}
?>