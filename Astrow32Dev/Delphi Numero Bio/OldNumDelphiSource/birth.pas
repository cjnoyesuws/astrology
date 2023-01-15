unit birth;

interface

uses
  WinTypes, WinProcs, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, IniFiles;

type
  TfrmBirth = class(TForm)
    Label1: TLabel;
    btnOk: TButton;
    btnCancel: TButton;
    Label2: TLabel;
    Label3: TLabel;
    edtMonth: TEdit;
    edtDay: TEdit;
    edtYear: TEdit;
    procedure btnOkClick(Sender: TObject);
    procedure btnCancelClick(Sender: TObject);
    procedure FormActivate(Sender: TObject);
    procedure FormKeyPress(Sender: TObject; var Key: Char);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  frmBirth: TfrmBirth;
  theBirth: TDateTime;
  iniFile: TIniFile;

function getBirth( var y, m, d : Word ) : Word;

implementation

{$R *.DFM}

procedure TfrmBirth.btnOkClick(Sender: TObject);
var
  month, day, year : Word;
  r : Integer;
  s : String;
begin
val( edtMonth.text, month, r );
val( edtDay.text, day, r );
val( edtYear.text, year, r );
theBirth := EncodeDate( year, month, day );
s := FloattoStr(theBirth);
iniFile.WriteString('Daily Numbers','BirthDate',s);
Hide;
end;

procedure TfrmBirth.btnCancelClick(Sender: TObject);
begin
hide;
end;


procedure TfrmBirth.FormActivate(Sender: TObject);
var
  month, day, year, r : Word;
begin
r := getBirth( year, month, day );
edtMonth.text := IntToStr(month);
edtDay.text := IntToStr(day);
edtYear.text := IntToStr(year);
end;

procedure TfrmBirth. FormKeyPress(Sender: TObject; var Key: Char);
begin
if not (key in ['0'..'9',#8]) then
   begin
   key := #0;
   MessageBeep( Word(-1) );
   end;
end;

function getBirth( var y, m, d : Word ) : Word;
var
  r : Word;
  s, ifn : String;
begin
if theBirth = 0.0 then
   begin
   GetDir(0,ifn);
   if ifn[length(ifn)-1]<> '\' then ifn := ifn + '\';
   ifn := ifn + 'NUMERO.INI';
   if iniFile = nil then iniFile := TIniFile.Create(ifn);
   s := iniFile.ReadString('Daily Numbers','BirthDate','0');
   if s = '0' then r := 0 else r := 1;
   theBirth := StrToFloat(s);
   end;
DecodeDate( theBirth, y, m, d );
end;

end.
