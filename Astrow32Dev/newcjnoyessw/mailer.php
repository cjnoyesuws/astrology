<?

function DefinedOrDefault($key,$def) {
 if (array_key_exists($key,$_POST))
    return $_POST[$key];
 else
    return $def;

}

if ( count($_POST) > 0 && $_POST['Submit'] == 'Submit' ) {

    $mail = new COM('CDO.Message');

    if ( array_key_exists('topic',$_POST ) )
       $mail->Subject = 'Topic: ' . $_POST['topic'] . '--' . DefinedOrDefault('subject','no subject');
    else
       $mail->Subject = DefinedOrDefault('subject','no subject');
	$mail->From= 'mailer@cjnoyessw.com';
	$mail->To= $_POST['cjn_email_to'];

	$body  = 'Product: '. $_POST['product'] . "\n";
	$body .= 'Name: ' . DefinedOrDefault('name','no name') . "\n";
    $body .= 'Telephone: ' . DefinedOrDefault('telno','no telno') . "\n";
	$body .= 'Email Address: ' .  DefinedOrDefault('emailto','no email') . "\n";
	$body .= "Message:\n";
	$body .= DefinedOrDefault('message','No message');

	$mail->TextBody=$body;

	$mail->Configuration->Fields->Item("http://schemas.microsoft.com/cdo/configuration/sendusing")->Value=2;
	$mail->Configuration->Fields->Item("http://schemas.microsoft.com/cdo/configuration/smtpserver")->Value="smtp.cjnoyessw.com";

	$mail->Configuration->Fields("http://schemas.microsoft.com/cdo/configuration/smtpauthenticate")->Value = 1;
	$mail->Configuration->Fields("http://schemas.microsoft.com/cdo/configuration/sendusername")->Value = "mailer@cjnoyessw.com";
	$mail->Configuration->Fields("http://schemas.microsoft.com/cdo/configuration/sendpassword")->Value = "cjnmailer";
	$mail->Configuration->Fields->Item("http://schemas.microsoft.com/cdo/configuration/smtpserverport")->Value=25;

	$mail->Configuration->Fields->Update;
    $mail->Send;
	echo "Email sent.";

}
else {
  $what = $_REQUEST['what'];
  if ( strcasecmp($what,'david') )
     $cjn_email_to = $what . '@cjnoyessw.com';
  else
     $cjn_email_to = $what . 'kp2703@aol.com';
echo<<<pagestart
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<title>Email $what</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<title>Astrology &amp; Related Pages</title>
<LINK REL="STYLESHEET" TYPE="text/css" HREF="astrow.css">
</head>

<BODY BGCOLOR="#c0c0ff">

<body>
<form method="post" action="mailer.php">
  <p>Email Address To Respond To:
    <input name="emailto" type="text" id="emailto" size="77" maxlength="77">
  </p>
  <p>Telephone Number:
    <input name="telno" type="text" id="telno" size="15" maxlength="15">
     &nbsp;&nbsp;Name:
     <input name="name" type="text" id="name" size="65" maxlength="85">
  </p>
pagestart;
   if ( !strcasecmp($what,'comments' ) )
      echo "<p>";
   else if ( strcasecmp($what,'david') ) {
      echo<<<prodselect
      What Product? <select name="product" id="product">
      <option >Astro For Windows</option>
	  <option >Numero Uno</option>
	  <option >CJN Fonts</option>
      <option >Yahoo Poster</option>
      <option >Internet Services</option>
      <option >Other</option>
      </select>&nbsp;&nbsp;

prodselect;
   }
   if ( strcasecmp($what,'david') ) {
      echo 'What is this About? <select name="topic" id="topic"> ';
      if ( !strcasecmp($what,'sales') ) {
      echo <<< option1
      <option >Want Info</option>
      <option >Order Problem</option>
      <option >Need a Refund</option>
      <option >Other</option>
option1;
      }
      else if ( !strcasecmp($what,'support') ) {
      echo<<<option2
      <option >Need Help</option>
	  <option >Suggestion</option>
	  <option >Need a Refund</option>
      <option >Other</option>
option2;
      }
      else {
      echo<<<option3
      <option >Link Add/Change</option>
	  <option >Problem With Site</option>
	  <option >Suggestion</option>
      <option >Other</option>
option3;
      }
      echo '</select>';
   }
echo<<<pageend
    <input name="cjn_email_to" type="hidden" id="cjn_email_to" value="$cjn_email_to">
</p>
  <p>Subject:
    <input name="subject" type="text" id="subject" size="100" maxlength="100">
  </p>
  <p>Message Text:  </p>
  <p>
    <textarea name="message" cols="105" rows="15" id="message"></textarea>
</p>
  <p>
    <input type="submit" name="Submit" value="Submit">
    <input name="Reset" type="reset" id="Reset" value="Reset">
  </p>
</form>
</body>
</html>

pageend;
}
?>


