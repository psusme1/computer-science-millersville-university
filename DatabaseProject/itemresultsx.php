<html>

<head>
<meta http-equiv="Content-Language" content="en-us">

<title>MU Trading Post - Item Search Results</title>
</head>

<body text="#FFFF00" bgcolor="#000000">

<p><u><font size="4" face="Arial Black">ITEM SEARCH RESULTS</font></u></p>
<a href=itemsearch.php>Search again</a><p>
<?php

mysql_connect( "localhost", "dbteam4", "team42005" );
mysql_select_db( "shawnjoe" );
$itemquery = "SELECT *
              FROM merchandise
              WHERE Type = '" . $_POST[ "itemtype" ] . "'
              ORDER BY Description";
$itemfound = mysql_query( $itemquery );

echo "<table cellspacing=10>\n";
while( $details = mysql_fetch_array( $itemfound ) )
{
if( $details[ "Upforsale" ] )
{
   $typedetails = array( "Director:", "min", "Studio:" );
   if( $details[ "Type" ] == "book" )
      $typedetails = array( "Author:", "pages", "Publisher:" );
   if( $details[ "Type" ] == "CD" )
      $typedetails = array( "Artist:", "tracks", "Label:" );

   echo "<tr valign=top><td><img src=" . $details[ "PictureURL" ] . " height=200><br>\n";
   echo "<td align=right>Title:<br>Release date:<br>" . $typedetails[0] . "<br>Length (" . $typedetails[1] . "):<br>" . 
        $typedetails[2] . "<br>Price:<br><br>Owner:\n";
   echo "<td>" . $details[ "Description" ] . "<br>" . $details[ "Price" ] . "<br>" . $details[ "Owner" ] . "\n";
}
}
echo "</table>\n";

?>

<a href=itemsearch.php>Search again</a><p>
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
