<?php session_start (); ?>
<html>
<head>
<title>MU Trading Post - Write A Message </title>
<body text = "#FFFF00" bgcolor = "#000000">

<font face="Arial Black">Please Write Your Message
</font>
<br><br><br>

<form method="POST" action="insertMessage.php">

<p><font color = "#FFFF00">Send To:</font>
<br><input type=textbox name=sendTo size="20"> 
</p>

<p><textarea rows="5" name="theMessage" cols="40"></textarea></p>

<p><input type="submit" value="Send" name="B1"></p>
</form>

</body>
</html>
