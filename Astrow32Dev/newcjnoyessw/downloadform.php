<?php

if ( count($_POST) > 0 ) {
  $filename = $_POST['filename'];
  $dir = $_POST['dir'];
  $fullurl = "http://www.cjnoyessw.com/';
  if (strlen($dir) > 0 )
     $fullurl .= "$dir/$filename";
  else
     $fullurl .= $filename;
  $stage = 'submit';
  headers("Location: $fullurl");
  if ( !array_key_exists('rathernot', $_POST ) ) {
     $name = mysql_real_escape($_POST['name']);
     $address1 = mysql_real_escape($_POST['address1']);
     $address2 = mysql_real_escape($_POST['address2']);
     $city = mysql_real_escape($_POST['city']);
     $state = mysql_real_escape($_POST['state']);
     $country = mysql_real_escape($_POST['country']);
     $zipcode = mysql_real_escape($_POST['zipcode']);
     $telephone = mysql_real_escape($_POST['telephone']);
     $email = mysql_real_escape($_POST['email']);
     $contactme = mysql_real_escape($_POST['contactme']);
     $product = mysql_real_escape($_POST['product']);
     $conn = mysql_connect('mysql101.isqsolutions.com', 'cjnoyesuser', 'astrowwin32');
	 if (!$conn) {
	    die('Could not connect: ' . mysql_error());
	 }
     mysql_select_db('cjnoyesswdb',$conn);
     $sql = 'INSERT INTO DOWNLOADCONTACTS (name,address1,address2,city,state,zipcode,telephone,email,contactme,product)'
     $sql .= "VALUES('$name','$address1','$address2','$city','$state',";
     $sql .= "'$zipcode','$telephone','$email','$contactme','$product')";
     $result = mysql_query($sql,$conn);
	 if (!$result) {
	    die('Query failed: ' . mysql_error());
}

  }
}
else {
  $filename = $_GET['filename'];
  $dir = $_GET['dir'];
  $stage = 'initial';
  $product = $_GET['product'];
}

echo<<< page start
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<title>Downloading $downloadname</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<link href="cjnoyessw.css" rel="stylesheet" type="text/css">
</head>

<body>
<h1 align="center" class="title">Download</h1>
<h2 align="center" class="subtitle">You Have Selected to Download $downloadname</h2>
<P><CENTER><HR SIZE="1"></CENTER></P>
start;

if ( $stage=='initial' ) {
echo<<<pageform
<h1 align="center" class="title">Tell Us About Yourself </h1>
<form name="form1" method="post" action="downloadform.php">
  <p>I would Rather Not Provide This Information:
    <input type="checkbox" name="rathernot" value="nodata">
</p>
  <p>Name:&nbsp;&nbsp;&nbsp;&nbsp;
    <input name="name" type="text" id="name" size="50" maxlength="50">
</p>
  <p>Address:
    <input name="address1" type="text" id="address1" size="50" maxlength="50">
  &nbsp;&nbsp; </p>
  <p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    <input name="address2" type="text" size="50" maxlength="50">
  </p>
  <p>City&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    <input name="city" type="text" id="city" size="25" maxlength="25">
   State or province &nbsp;&nbsp;
   <input name="state" type="text" id="state" size="15" maxlength="15">
  &nbsp;&nbsp;Zip&nbsp;
  <input name="zipcode" type="text" id="zipcode" size="15" maxlength="15">
  </p>
  <p>Country: &nbsp;&nbsp;
    <input name="country" type="text" id="country" value="United States" size="25" maxlength="25">
  </p>
  <p>Email Address: &nbsp;&nbsp;
    <input name="email" type="text" id="email" size="50" maxlength="50">
  </p>
  </p>
    <p>Telephone: &nbsp;&nbsp;
      <input name="telephone" type="text" id="telephone" size="15" maxlength="15">
  </p>
  <p>
    <input name="contactme" type="checkbox" id="maycontact" value="Yes" checked>
  You may contact me about new products or features</p>
  <p>We will not provide your contact information to any other company. </p>
  <p>
    <input type="submit" name="Submit" value="Submit">
&nbsp;&nbsp;
<input type="submit" name="Submit2" value="Submit">
<input name="filename" type="hidden" id="filename" value="$filename">
<input name="dir" type="hidden" id="dir" value="$dir">
<input name="product" type="hidden" id="product" value="$product">
</p>
</form>
pageform;
}
else {

echo<<<startdl
<h1 align="center" class="title">Start Download</h1>
<p align="center">If your download does not start, click on this link, make sure you disable your popup blocker for this to download.</p>
<h2 align="center" class="subtitle"><a class="navLink" href="$fullurl">click to download</a></h2>
<p>&nbsp;</p>
startdl;
}

echo<<<endpage
</body>
</html>
endpage;

?>
