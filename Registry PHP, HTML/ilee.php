<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
    <title>Jarosławska Księga Kresowian &copy;</title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <link rel="stylesheet" type="text/css" href="style.css"/>
</head>
<body>

<?php
        require_once "/home/dziedzic/domains/jaroslawskaksiegakresowian.pl/connect.php";
		

?>
<style type="text/css">
<?php 
include './styl.css'; 
?>
</style>


<?php

$sql = 'SELECT COUNT(*) FROM rejestr';
$res = mysql_query($sql) or die(mysql_error());
$num = mysql_fetch_row($res);
echo "<center>W rejestrze znajduje się <br />";
echo "<b>".$num[0]."</b><br/ >"; 
echo " osób!</center>";
		mysql_close()
?>



</body>
</html>
