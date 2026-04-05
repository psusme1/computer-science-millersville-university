<html>

<head>
<meta http-equiv="Content-Language" content="en-us">

<title>MU Trading Post - Item Details</title>
</head>

<body text="#FFFF00" bgcolor="#000000">

<p><u><font size="4" face="Arial Black">ITEM DETAILS</font></u></p>

<?php

mysql_connect( "localhost", "dbteam4", "team42005" );
mysql_select_db( "shawnjoe" );
$itemquery = "SELECT *
              FROM merchandise
              WHERE ItemNo = " . $_GET[ "itemno" ];
$itemfound = mysql_query( $itemquery );
$details = mysql_fetch_array( $itemfound );

$typedetails = array( "Director:", "min", "Studio:" );
if( $details[ "Type" ] == "book" )
   $typedetails = array( "Author:", "pages", "Publisher:" );
if( $details[ "Type" ] == "CD" )
   $typedetails = array( "Artist:", "tracks", "Label:" );

echo "<table cellspacing=10><tr valign=top>\n";
echo "<td><img src=" . $details[ "PictureURL" ] . " height=200><br>\n";
echo "<td align=right>Title:<br>Release date:<br>" . $typedetails[0] . "<br>Length (" . $typedetails[1] . "):<br>" . 
     $typedetails[2] . "\n";
echo "<td>" . $details[ "Description" ] . "</text></table>\n";

?>

</body>

</html>
