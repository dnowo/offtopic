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
include './style.css'; 
?>
</style>


<?php
include './wyszukaj.php'; 

        //wyciaganie z bazy
        

        $query = "SELECT COUNT(*) as all_posts FROM rejestr";
        $result = mysql_query($query) or die (mysql_error());
        $row = mysql_fetch_array($result);
        extract($row);
        
        $onpage = 50; //ilość osob na stronę
        $navnum = 5; //ilość wyświetlanych numerów stron, ze względów estetycznych niech będzie to liczba nieparzysta
        $allpages = ceil($all_posts/$onpage); //wszysttkie strony to zaokrąglony w górę iloraz wszystkich postów i ilości postów na stronę
        
        //sprawdzamy poprawnośc przekazanej zmiennej $_GET['page'] zwróć uwage na $_GET['page'] > $allpages
        if(!isset($_GET['page']) or $_GET['page'] > $allpages or !is_numeric($_GET['page']) or $_GET['page'] <= 0){
                $page = 1;
        }else{
                $page = $_GET['page'];
        }
        $limit = ($page - 1) * $onpage; //określamy od jakiej osoby będziemy pobierać informacje z bazy danych
         
        $query = "SELECT * FROM rejestr ORDER BY nazwiskoiimie COLLATE utf8_polish_ci ASC LIMIT $limit, $onpage";
        $result = mysql_query($query) or die (mysql_error());
		

		
		echo "<table cellpadding=\"5\">	
				 <tr>
				 <th style=\"border-top-left-radius: 10px;color: #f5f5f5;\">Nazwisko i imię</th>
				 <th style=\"color: #f5f5f5;\">Rok urodzenia</th>
				 <th style=\"color: #f5f5f5;\">Miejsce zamieszkania na Kresach</th>
				 <th style=\"color: #f5f5f5;\">Miejsce osiedlenia w powiecie Jarosławskim</th>	
				 <th style=\"border-top-right-radius: 10px;color: #f5f5f5;\">Pełen opis</th>
				 </tr>";
        
        while($row = mysql_fetch_array($result)){
			asort($nazwiskoiimie);
		reset($nazwiskoiimie);
		
		echo "<tr>"; 
        echo "<td style=\"text-align: left;\">".$row['nazwiskoiimie']."</td>"; 
		echo "<td>".$row['rokuro']."</td>"; 
        echo "<td>".$row['miejscowosckresy']."</td>"; 
		echo "<td>".$row['miejscowoscjaroslaw']."</td>"; 
		echo "<td>".$row['opis']."</td>";  
        echo "</tr>"; 
		
        }
        
        //zabezpieczenie na wypadek gdyby ilość stron okazała sie większa niż ilośc wyświetlanych numerów stron
        if($navnum > $allpages){
                $navnum = $allpages;
        }
        
      
        $forstart = $page - floor($navnum/2);
        $forend = $forstart + $navnum;
        
        if($forstart <= 0){ $forstart = 1; }
        
        $overend = $allpages - $forend;
        
        if($overend < 0){ $forstart = $forstart + $overend + 1; }
        
        // $forstart mogła ulec zmianie
        $forend = $forstart + $navnum;
        //w tych zmiennych przechowujemy numery poprzedniej i następnej strony
        $prev = $page - 1;
        $next = $page + 1;
        
      
        $script_name = $_SERVER['SCRIPT_NAME'];
        
        //odpowiada za wyślwietenie nawigacji
        echo "<div id=\"nav\" style=\"overflow-x: hidden; margin: 5px 15px 5px 5px;\"><ul>";
        if($page > 1) echo "<li><a href=\"".$script_name."?page=".$prev."\">	&lArr;</a></li>";
        if ($forstart > 1) echo "<li><a href=\"".$script_name."?page=1\">1</a></li>";
        if ($forstart > 2) echo "<li>...</li>";
        for($forstart; $forstart < $forend; $forstart++){
                if($forstart == $page){
                        echo "<li class=\"current\">";
                }else{
                        echo "<li>";
                }
                echo "<a href=\"".$script_name."?page=".$forstart."\"><b>".$forstart."</b></a></li>";
        }
        if($forstart < $allpages) echo "<li>...</li>";
        if($forstart - 1 < $allpages) echo "<li><a href=\"".$script_name."?page=".$allpages."\">[".$allpages."]</a></li>";
        if($page < $allpages) echo "<li><a href=\"".$script_name."?page=".$next."\">&rArr;</a></li>";
        echo "</ul></div><div class=\"clear\">";
		


		mysql_close()
		
?>




</body>
</html>
