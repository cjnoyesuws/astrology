unit ldrched;

interface

Uses
    Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
    StdCtrls, ComCtrls, Richedit;


function EditStreamCallBack (dwCookie: Longint; var pbBuff: PByte; cb: Longint; var pcb: Longint): Longint; stdcall;
procedure LoadFile( re : TRichEdit; s : String );

implementation

var
   stream : TFileStream;

function EditStreamCallBack (dwCookie: Longint; var pbBuff: PByte; cb: Longint; var pcb: Longint): Longint; stdcall;
var
  rv : Longint;
begin
  rv := stream.Position;
  if stream.position + cb > stream.size then
     cb := stream.size - stream.position;
  stream.ReadBuffer( pbBuff, cb );
  rv := stream.Position - rv;
  pcb := rv;
if stream.Size <= stream.Position then
   EditStreamCallBack := 0
else
   EditStreamCallBack := rv;
end;

procedure LoadFile( re : TRichEdit; s : string );
Var
  st : String;
  len, i : integer;
  ch : Char;
  est: TEditStream;

begin
if Not FileExists( s ) then
   begin
   st := Format( '%s Does Not Exist!', [s] );
   MessageDlg( st, mtError, [mbOk], 0 );
   exit;
   end;
stream := TFileStream.Create(s,fmOpenRead);
if stream = nil then begin
   st := Format( '%s Can''t Open!', [s] );
   MessageDlg( st, mtError, [mbOk], 0 );
   exit;
   end;
est.pfnCallback := @EditStreamCallback;
SendMessage( re.Handle, EM_STREAMIN, SF_RTF, Longint(@est) );
stream.free;
end;


end.
