<? session_start(); ?>
<html>
<body text="#FFFF00" bgcolor="#000000">

<?php

mysql_connect( "localhost", "dbteam4", "team42005" );
mysql_select_db( "shawnjoe" );
$description = $_POST[ "title" ] . "<br>\r\n" . $_POST[ "date" ] . "<br>\r\n" . 
               $_POST[ "artist" ] . "<br>\r\n" . $_POST[ "length" ] . "<br>\r\n" . 
               $_POST[ "label" ];
$submitquery = "INSERT INTO merchandise ( PictureURL , Type , Description , Owner , Price )
                VALUES ( '" . $_POST[ "url" ] . "', '" . $_POST[ "itemtype" ] . 
                      "', '" . $description . "', '" . $_SESSION[ "UserID"] . "', " . $_POST[ "price" ] . " )";
$success = mysql_query( $submitquery );
if( $success )
   echo "Your item was submitted.<P>\n";
else
   echo "There was a problem. &nbsp;Please try again.<p>\n";
?>

<font size="4" face="Arial Black">Please Choose an Action to Perform</font><br><br>
<form action="xactions.php" method="POST" >
  <p><input type="submit" value="View Transactions" name="submitbox"></p>
</form>
<form action="itemsearch.php" method="POST" >
  <p><input type="submit" value="View Items For Sale" name="submitbox"></p>
</form>
<form action="messagesrcvd.php" method="POST" >
  <p><input type="submit" value="Messages Received" name="submitbox"></p>
</form>
<form action="messagessent.php" method="POST" >
  <p><input type="submit" value="Messages Sent" name="submitbox"></p>
</form>
<br><br><br>
<form action="index.php" method="POST" >
  <p><input type="submit" value="SignOut" name="submitbox"></p>
</form>
</font>

</body>

</html>
