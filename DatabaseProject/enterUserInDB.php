<html>
<head>
<title>MU Trading Post - Registration Page </title>
<body text = "#FFFF00" bgcolor = "#000000">

<font face="Arial Black">Please Provide the Following Information to Register
</font>

<?php

mysql_connect( "localhost", "dbteam4", "team42005" );
mysql_select_db( "shawnjoe" );

$userCheck = "SELECT UserID
               FROM user
               WHERE UserID = '" . $_POST[ "uName" ]. "'";

$results = mysql_query ($userCheck);
$count = mysql_num_rows ($results);
$name = mysql_fetch_array ($results);
echo "$_POST[uName]";


if (($count == 0) && ($_POST[uName] != "") && ($_POST[fName] != "") && ($_POST[lName] != "") && ($_POST[pWord] != "") )
{
  $sql = "INSERT into user VALUES ('$_POST[uName]', '$_POST[eAddress]', '$_POST[pWord]', '$_POST[fName]', '$_POST[lName]')";
  $results = mysql_query ($sql);
  echo "<br><br>";
  echo "Registration Successful - You May Now Login!";
  echo "<META HTTP-EQUIV='Refresh' CONTENT='2000; URL=index.php'>";
}
else
{
   echo "<br><br>";
   echo "Registration Unsuccesful - Please Try Again!";
   echo "<META HTTP-EQUIV='Refresh' CONTENT='2000; URL=signup.php'>";
}

?>

</body>
</html>
