<?
  $query = strtoupper($_SERVER['QUERY_STRING'] );
  $filename = substr( $_SERVER['QUERY_STRING'],4,strlen($query)-4);
  $ext = strtoupper(substr($query,strlen($query)-3,3));
  if (!strcmp($ext,'EXE') || !strcmp($ext,'ZIP') || !strcmp($ext,'msi')) {
      header("Location: http://www.cjnoyessw.com/download.htm" );
  }
  else {
    $message = "File Not Found: %filename";
    header("Location: http://www.cjnoyessw.com" );
    $mail = new COM('CDO.Message');
	$mail->Subject = "Topic: File Missing:";
	$mail->From = 'mailer@cjnoyessw.com';
	$mail->To = 'comments@cnoyessw.com';
	$mail->TextBody="File: $filename Was not Found, Error 400";
	$mail->Configuration->Fields->Item("http://schemas.microsoft.com/cdo/configuration/sendusing")->Value=2;
	$mail->Configuration->Fields->Item("http://schemas.microsoft.com/cdo/configuration/smtpserver")->Value="smtp.cjnoyessw.com";
	$mail->Configuration->Fields("http://schemas.microsoft.com/cdo/configuration/smtpauthenticate")->Value = 1;
	$mail->Configuration->Fields("http://schemas.microsoft.com/cdo/configuration/sendusername")->Value = "mailer@cjnoyessw.com";
	$mail->Configuration->Fields("http://schemas.microsoft.com/cdo/configuration/sendpassword")->Value = "cjnmailer";
	$mail->Configuration->Fields->Item("http://schemas.microsoft.com/cdo/configuration/smtpserverport")->Value=25;
	$mail->Configuration->Fields->Update;
    $mail->Send;
echo<<<page
  <!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
  <html xmlns="http://www.w3.org/1999/xhtml">
  <head>
  <title>Error 404</title>
  <meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
  <LINK REL="STYLESHEET" TYPE="text/css" HREF="astrow.css">
  </head>
  <body>
  <h2>$message</h2>
  <p>You are being redirected, if the web site does not open,<br>
  Click on this link</p>
  <p><a href="http://www.cjnoyessw.com">Christopher J. Noyes Software</a></p>
  </body>
</html>
page;
}
?>


