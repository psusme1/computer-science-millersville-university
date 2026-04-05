<html>
<head><title>New Page 1</title></head>
<body text="#FFFF00" bgcolor="#000000">

<p><u><font face="Arial Black" size="4">ITEM SEARCH</font></u></p>
<form method="POST" action="itemresults.php">
  <select size="1" name="itemtype">
  <option selected value="book">Books</option>
  <option value="CD">CDs</option>
  <option value="DVD">DVDs</option>
  </select><input type="submit" value="Search" name="B1"></p>
</form>
<font size="4" face="Arial Black"><a href=newitem.php>Put an item up for sale</a>
<p>&nbsp;<p>Please Choose an Action to Perform</font><br><br>
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
