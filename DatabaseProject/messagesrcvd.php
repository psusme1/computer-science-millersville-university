<? session_start(); ?>
<html>

<head>
<meta http-equiv="Content-Language" content="en-us">

<title>MU Trading Post - Messages Received</title>
</head>

<body text="#FFFF00" bgcolor="#000000">

<p><u><font size="4" face="Arial Black">MESSAGES RECEIVED</font></u></p>

<?php

$user = $_SESSION['UserID'];
echo "$user";

mysql_connect( "localhost", "dbteam4", "team42005" );
mysql_select_db( "shawnjoe" );
$messagequery = "SELECT *
                 FROM message
                 WHERE Receiver = '" . $user . "'";
$messagelist = mysql_query( $messagequery );

echo "<table border=2 cellpadding=4 cellspacing=4>\n";
echo "   <tr>\n";
echo "      <td><u>Message</u>\n";
echo "      <td><u>From</u>\n";
while( $message = mysql_fetch_array( $messagelist ) )
{
   echo "   <tr>\n";
   echo "      <td>" . $message[ "Message" ] . "\n";
   echo "      <td>" . $message[ "Sender" ] . "\n";
}
echo "</table>";

?>

<br>
<font size="4" face="Arial Black"></font><br><br>

<form action="writeMessage.php" method="POST" >
  <p><input type="submit" value="Send a Message" name="submitbox"></p>
</form>
<br><br>
<form action="itemsearch.php" method="POST" >
  <p><input type="submit" value="View Items For Sale" name="submitbox"></p>
</form>
<form action="messagesrcvd.php" method="POST" >
  <p><input type="submit" value="Messages Received" name="submitbox"></p>
</form>
<form action="messagessent.php" method="POST" >
  <p><input type="submit" value="Messages Sent" name="submitbox"></p>
</form>
<br>
<form action="index.php" method="POST" >
  <p><input type="submit" value="SignOut" name="submitbox"></p>
</form>
</font>


</body>
</html>
