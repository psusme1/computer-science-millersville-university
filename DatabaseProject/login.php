<? session_start(); ?>
<html>
<head>
<meta http-equiv="Content-Language" content="en-us">
<title>MU Trading Post - Menu Page</title>
<?php

mysql_connect( "localhost", "dbteam4", "team42005" );
mysql_select_db( "shawnjoe" );
$loginquery = "SELECT firstName
               FROM user
               WHERE UserID = '" . $_POST[ "username" ] . "'" .
               " AND Password = '" . $_POST[ "userpw" ] . "'";
$results = mysql_query( $loginquery );
$count = mysql_num_rows( $results );
$name = mysql_fetch_array( $results );
if( $count == 0)
{
	  echo "<META HTTP-EQUIV='Refresh' CONTENT='0; URL=index.php'>";
?>
   </head>
	<body bgcolor="#000000" link="#FFFF00" vlink="#FFFF00" alink="#FFFF00"></body>
<?
}
else
  {
	     $_SESSION['UserID'] = $_POST["username"];
		 $_SESSION['LoggedIN'] = true;

?>
</head>
<body bgcolor="#000000" link="#FFFF00" vlink="#FFFF00" alink="#FFFF00">
<font color="#FFFF00">
<?
echo "<h2>Login Successful<br></h2><h3>Welcome " .
        $name[ "firstName" ] . "</h3><br>";
?>
<br>
<font size="4" face="Arial Black">Please Choose an Action to Perform</font><br><br>
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

<? } ?>
</html>
