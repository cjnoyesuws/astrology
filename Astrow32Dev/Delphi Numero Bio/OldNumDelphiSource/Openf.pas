unit Openf;

interface

{$IFDEF WIN32}
uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ComCtrls, StdCtrls, FileCtrl, Buttons, ExtCtrls, NUMDLL;
{$ELSE}
uses
  Messages, WinTypes, WinProcs, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  Tabnotbk, StdCtrls, Buttons, ExtCtrls, FileCtrl, NUMDLL31;
{$ENDIF}



type
  TOpenScreenMode = ( osmOpenFile, osmCreateFile, osmSaveFile, osmModifyFile );

type
  TFileType = ( ftNumData, ftRichText, ftNumRept, ftUnknown, ftError );


type
  TfrmOpenFile = class(TForm)
    flbList: TFileListBox;
    Label1: TLabel;
    Label2: TLabel;
    edtFileName: TEdit;
    edtComment: TEdit;
    btnOk: TBitBtn;
    btnCancel: TBitBtn;
    Label3: TLabel;
    btnChangeDir: TBitBtn;
    Open: TOpenDialog;
    edtType: TEdit;
    procedure flbListClick(Sender: TObject);
    procedure btnChangeDirClick(Sender: TObject);
    procedure btnOkClick(Sender: TObject);
    procedure btnCancelClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
    mode : TOpenScreenMode;
  Function Validate : Boolean;
  public
    { Public declarations }
  filehead : FILE_ID;
  Procedure SetMode( m : TOpenScreenMode );
  Procedure SetMultiSelect( b : boolean );
  function  GetSelection(var fn : String; var rh : FILE_ID; var ft : TFileType ) : boolean;
  function  GetMultiSelection( var s : TStringList ) : Integer;
  procedure setInitial( n : NAME_REC );
  function GetFileHeaderType( s : string; var rh : FILE_ID; var cmt, ftp : PChar ) : TFileType;
  end;

var
  frmOpenFile: TfrmOpenFile;

implementation

{$R *.DFM}

Procedure TfrmOpenFile.SetMode( m : TOpenScreenMode );
begin
mode := m;
case mode of
     osmOpenFile : edtComment.enabled := False;
     osmCreateFile : edtComment.enabled := True;
     osmSaveFile : edtComment.enabled := True;
     osmModifyFile : edtComment.enabled := True;
     end;
flbList.Update;
end;

function TfrmOpenFile.GetFileHeaderType( s : string; var rh : FILE_ID; var cmt, ftp : PChar ) : TFileType;
Var
  f : File;
  id : array [0..10] of Char;
  r : integer;
  rech : FILE_ID;
  handle : integer;
begin
if Not FileExists(s) then GetFileHeaderType := ftError;
handle := FileOpen(s, fmOpenRead );
if handle < 0 then GetFileHeaderType := ftError;
FileRead( handle, id, 6 );
id[4] := #0;
if StrComp( id, 'NDT1' ) = 0 then
   begin
   FileClose(handle);
   GetFileHeaderType := ftNumData;
   end
else if StrComp( id, '{\rt' ) = 0 then
   begin
   FileClose(handle);
   GetFileHeaderType := ftRichText;
   end
else if StrComp( id, 'NRP1' ) = 0 then
   begin
   StrCopy( rech.id, id );
   FileRead( handle, rech.fType, 30 );
   FileRead( handle, rech.Comment, 80 );

   FileClose(handle);
   rh := rech;
   ftp := rh.ftype;
   cmt := rh.Comment;
   GetFileHeaderType := ftNumRept;
   end
else
   begin
   CloseFile(f);
   GetFileHeaderType := ftUnknown;
   end;
end;

procedure TfrmOpenFile.flbListClick(Sender: TObject);
var
   c, t : PChar;
   ft : TFileType;
   str : String;
begin
str := flbList.Items[flbList.ItemIndex];
edtFileName.text := str;
ft := GetFileHeaderType( str, filehead, c, t );
case ft of
     ftNumData : edtType.Text := 'Numero Data File';
     ftRichText : edtType.Text := 'Rich Text File';
     ftNumRept: begin
           edtComment.Text := StrPas(c);
           edtType.Text := StrPas(t);
           end;
     end;
end;


Function TfrmOpenFile.Validate : Boolean;
var
  b : Boolean;
  s : string;
begin
case mode of
  osmCreateFile, osmSaveFile : begin
     if FileExists( ExpandFileName(edtFileName.text) ) then
        begin
        s := format( '%s Exists, OverWrite?', [edtFileName.Text] );
        if MessageDlg( s, mtWarning, [mbYes, mbNo], 0 ) = mrYes then
           b := True else b := False;
        end
     else b:= True
     end;
  osmOpenFile, osmModifyFile : begin
     if Not FileExists( ExpandFileName(edtFileName.Text) ) then
        begin
        s := format( '%s Does Not Exist!', [edtFileName.Text] );
        MessageDlg( s, mtError, [mbOk], 0 );
        b := False;
        end
     else b:= True;
     end;
     end;
Validate := b;
end;

procedure TfrmOpenFile.SetMultiSelect( b : boolean );
begin
flbList.MultiSelect := b;
end;

procedure TfrmOpenFile.btnChangeDirClick(Sender: TObject);
begin
if Open.Execute then
   begin
   flbList.Directory := ExtractFilePath(Open.FileName);
   edtFileName.text := ExtractFileName(Open.FileName);
   end;
end;

procedure TfrmOpenFile.btnOkClick(Sender: TObject);
begin
if Validate then begin
  btnOk.ModalResult := mrOK;
  Hide;
  end
else btnOk.ModalResult := mrNone;
end;

procedure TfrmOpenFile.btnCancelClick(Sender: TObject);
begin
Hide;
end;

procedure TfrmOpenFile.FormCreate(Sender: TObject);
begin
SetMode( osmCreateFile );
end;

function TfrmOpenFile.GetSelection(var fn : String; var rh : FILE_ID; var ft : TFileType ) : boolean;
var
  ftp, cmt : PChar;
begin
fn := ExpandFileName(edtFileName.Text);
if Not FileExists( fn ) then
   begin
   StrCopy( rh.id, 'NRP1' );
   StrPLCopy( rh.Comment, edtComment.Text, 79 );
   strPlCopy( rh.fType, edtType.Text, 29 );
   ft := ftUnknown;
   end
else if mode = osmOpenFile then ft := GetFileHeaderType( fn, rh, cmt, ftp )
else
   begin
   ft := GetFileHeaderType( fn, rh, cmt, ftp );
   StrCopy( rh.id, 'NRP1' );
   StrPLCopy( cmt, edtComment.Text, 79 );
   strPlCopy( ftp, edtType.Text, 29 );
   end;
if ft = ftError then GetSelection := False
else
   GetSelection := True;
end;

function TfrmOpenFile.GetMultiSelection( var s : TStringList ) : Integer;
var
  i, c : integer;
  st : String;
begin
if Not flbList.MultiSelect then GetMultiSelection := -1;
s.Clear;
c := 0;
for i := 1 to flbList.items.Count do
    begin
    if flbList.Selected[i-1] then
       begin
       st := ExpandFileName(flbList.Items[i-1]);
       s.Add(st);
       c := c + 1;
       end;
    end;
GetMultiSelection := c;
end;

procedure TfrmOpenFile.setInitial( n : NAME_REC );
begin
edtFileName.Text := n.first + ' ' + n.middle + ' ' + n.last + '.NRP'
end;
end.

