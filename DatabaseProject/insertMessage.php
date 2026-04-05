<?php session_start (); ?>
<html>
<head>
<title>MU Trading Post - Insert Message</title>
<body text = "#FFFF00" bgcolor = "#000000">

<p>

<font face="Arial Black">&nbsp;</font></p>

<?php

mysql_connect( "localhost", "dbteam4", "team42005" );
mysql_select_db( "shawnjoe" );

$sender = $_SESSION['UserID'];
$date = '2005-05-09 10:18:45';
$receiver = $_POST[sendTo];
$message = $_POST[theMessage];


if (($message != "") && ($receiver != $sender) && ($sender != ""))
{
  $sql = "INSERT into message VALUES ('', '$date', '$message', '$sender', '$receiver')";
  $results = mysql_query ($sql);
  echo "<br><br>";
  echo "Message Succesfully Sent!";
  echo "<META HTTP-EQUIV='Refresh' CONTENT='2000; URL=login.php'>";
?>
   <form action="messagessent.php" method="POST" >
   <p><input type="submit" value="Main Menu" name="submitbox"></p>
   </form>
<?
}
else
{
   echo "<br><br>";
   echo "Message Transmission Unsuccessful - Please Try Again!";
   echo "<META HTTP-EQUIV='Refresh' CONTENT='2000; URL=writeMessage.php'>";
?>
   <form action="writeMessage.php" method="POST" >
   <p><input type="submit" value="Write Message" name="submitbox"></p>
   </form>
<?
}

?>

</body>
</html>
