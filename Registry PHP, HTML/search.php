<?php
        require_once "/home/dziedzic/domains/jaroslawskaksiegakresowian.pl/connect.php";
		

?>
<style type="text/css">
<?php 
include './style.css'; 
?>
</style>
<?php
    $query = $_GET['query']; 
     
    $min_length = 3;
     
    if(strlen($query) >= $min_length){ 
         
        $query = htmlspecialchars($query); 
       
         
        $query = mysql_real_escape_string($query);
    
         
        $raw_results = mysql_query("SELECT * FROM rejestr
            WHERE (`nazwiskoiimie` LIKE '%".$query."%') OR (`rokuro` LIKE '%".$query."%') OR (`miejscowosckresy` LIKE '%".$query."%') OR (`miejscowoscjaroslaw` LIKE '%".$query."%') OR (`opis` LIKE '%".$query."%')") or die(mysql_error());
             

        if(mysql_num_rows($raw_results) > 0){
		 include './wyszukaj.php'; 
		 echo "<br><br><br><br>";
            
			          		echo "<table cellpadding=\"5\">	
				 <tr>
				 <th style=\"border-top-left-radius: 10px;\">Nazwisko i imię</th>
				 <th>Rok urodzenia</th>
				 <th>Miejsce zamieszkania na Kresach</th>
				 <th>Miejsce osiedlenia w powiecie Jarosławskim</th>	
				 <th style=\"border-top-right-radius: 10px;\">Pełen opis</th>
				 </tr>";
			
            while($results = mysql_fetch_array($raw_results)){

   
		

				
		echo "<tr>"; 
        echo "<td>".$results['nazwiskoiimie']."</td>"; 
		echo "<td>".$results['rokuro']."</td>"; 
        echo "<td>".$results['miejscowosckresy']."</td>"; 
		echo "<td>".$results['miejscowoscjaroslaw']."</td>"; 
		echo "<td>".$results['opis']."</td>";  
        echo "</tr>"; 
                
            }
             
        }
        else{ 
			echo "<center><img src=\"sad.png\" width=\"150px\" height=\"150px\"></center>";
            echo "<div style=\"text-align: center;\">Brak wyników. Być może nie ma takiej osoby w rejestrze.";
			echo "<br/>";
			echo "</div>";
				include './paginacja.php'; 
        }
         
    }
    else{ 
        echo "Minimalna ilość znaków to ".$min_length;
    }
	mysql_close();
?>