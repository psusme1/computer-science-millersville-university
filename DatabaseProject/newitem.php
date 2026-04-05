<html>
<head><title>Sell Item</title></head>
<body text="#FFFF00" bgcolor="#000000">

<p><u><font face="Arial Black" size="4">PUT AN ITEM UP FOR SALE</font></u></p>
<form method="POST" action="submititem.php">
  Type:&nbsp;
  <select size="1" name="itemtype">
  <option selected value="book">Book</option>
  <option value="CD">CD</option>
  <option value="DVD">DVD</option>
  </select></p>
  <p>Title:&nbsp; <input type="text" name="title" size="20"></p>
  <p>Release date:&nbsp; <input type="text" name="date" size="20"></p>
  <p>Author / Artist / Director:&nbsp; <input type="text" name="artist" size="20"></p>
  <p>Length (in pages / tracks / minutes ):&nbsp;
  <input type="text" name="length" size="20"></p>
  <p>Publisher / Label / Studio:&nbsp; <input type="text" name="label" size="20"></p>
  <p>Picture URL:&nbsp; <input type="text" name="url" size="20"></p>
  <p>Price:&nbsp; <input type="text" name="price" size="20"></p>
  <p>&nbsp;</p>
  <p><input type="submit" value="Submit"><input type="reset" value="Reset"></p>
</form>
<p>&nbsp;</p>

</body>

</html>
