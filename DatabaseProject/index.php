<?php session_start (); ?>
<?php session_destroy (); ?>
<?php session_start (); ?>
<html>
<head><title>MU Trading Post - Login Page</title></head>
<body text="#FFFF00" bgcolor="#000000">
<p align="center"><img border="0" src="MUlogo.gif" width="248" height="69"></p>
<hr color = "#FFFF00" size="1">
<p align="center"><b><font face="Bookman Old Style" size="7" color="#FFFFFF">The Trading Post</font></b></p>
<hr color="#FFFF00" size="1">

<p align="center"><font color="#FFFF00">&nbsp;The place to sell your used 
movies, books, games, and music.&nbsp; The service is free and easy to use!&nbsp; 
Just sign up to sell the items you no longer want and start making some extra 
cash today! </font></p>
<p align="center">&nbsp;</p>

<form action="login.php" method="POST">
<h1><font size="5" color="#FFFF00">Login</font></h1>
<table>
<tr><td><font color="#FFFF00">User Name:</font></td><Td><font color="#FFFF00">
  <input type=textbox name=username size="20"></font></td></tr>
<tr><td><font color="#FFFF00">Password:</font></td><td><font color="#FFFF00">
  <input type=password name=userpw size="20"></font></td></tr>
<tr><td colspan=2 align="right"><input type=submit value="Login"></td></tr>
</table>
</form>


<form action="signup.php" method="POST" >
  <p><input type="submit" value="SignUp" name="submitbox"></p>
</form>



<p align="center">&nbsp;</p>



<p align="center">&nbsp;</p>



<p align="center">



<font color="#FFFFFF" face="Arial" size="1">WebMasters: </font>



<a href="mailto:puffdaddy@dejazzd.com?subject=MU Trading Post">
<font color="#FFFFFF" face="Arial" size="1">Shawn Englerth</font></a><font color="#FFFFFF">
<font face="Arial" size="1">&amp; </font></font>
<a  href="mailto:jgdefeo@cs.millersville.edu?subject=MU Trading Post">
<font color="#FFFFFF" face="Arial" size="1">Joe DeFeo</font></a><font color="#FFFFFF">
<font face="Courier" size="2">&nbsp;</font> </font> </p>



</body>
</html>