unit Viewtxt;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ComCtrls, Richedit, ldrched, Buttons, ExtCtrls,
  numdll, printers, options;

type
  TfrmViewText = class(TForm)
    RichEdit1: TRichEdit;
    procedure btnCloseClick(Sender: TObject);
    procedure FormKeyPress(Sender: TObject; var Key: Char);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure FormCreate(Sender: TObject);
    procedure FormActivate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
  private
    { Private declarations }
    temp : string;
    name : string;
  public
    { Public declarations }
  procedure SetFileNameCaption( fn, cap : string );
  procedure print;
  Function GetName : string;
  end;

var
  frmViewText: TfrmViewText;

implementation

uses Openf;

{$R *.DFM}

Function TfrmViewText.GetName : String;
begin
getName := name;
end;

procedure TfrmViewText.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  Action := caFree;
end;


procedure TfrmViewText.SetFileNameCaption( fn, cap : string );
Var
  buf : array [0..150] of char;
begin
GetTempFileName( '.', 'NUM', 0, buf );
temp := buf;
ConvertToRTF( PChar(fn), PChar(temp) );
LoadFile(RichEdit1,temp);
name := cap;
Caption := cap;
RichEdit1.Show;
end;

procedure TfrmViewText.btnCloseClick(Sender: TObject);
begin
Hide;
end;

procedure TfrmViewText.FormKeyPress(Sender: TObject; var Key: Char);
begin
key := #0;
beep;
end;

procedure TfrmViewText.print;
var
  LogX, LogY : integer;
  rect : TRect;
begin
with Printer do
begin
    LogX := GetDeviceCaps(Handle, LOGPIXELSX);
    LogY := GetDeviceCaps(Handle, LOGPIXELSY);
    rect.right := PageWidth - ((LogX * 3) div 4);
    rect.bottom := PageHeight - LogY;
    rect.left := ((LogX * 3) div 4);
    rect.top := ((LogY * 3) div 4);
end;
RichEdit1.PageRect:=rect;
RichEdit1.Print(caption);
end;

procedure TfrmViewText.FormCreate(Sender: TObject);
var
   fid : FILE_ID;
   name : string;
   ft : TFileType;
begin
  inherited;
FormStyle := fsMDIChild;
frmOpenFile.SetMode( osmOpenFile );
if frmOpenFile.showModal<>mrOk then begin
   hide;
   exit;
   end;
if frmOpenFile.GetSelection(name, fid, ft ) then
   begin
   DoRTFSettings( 10, 700, -1 );
   SetFileNameCaption(name,name);
   Show;
   end;
end;

procedure TfrmViewText.FormActivate(Sender: TObject);
begin
  inherited;
caption := name;
end;

procedure TfrmViewText.FormDestroy(Sender: TObject);
begin
  inherited;
DeleteFile( temp );
end;

end.
