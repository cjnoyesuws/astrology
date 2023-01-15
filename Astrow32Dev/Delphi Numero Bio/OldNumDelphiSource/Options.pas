unit Options;

interface

{$IFDEF WIN32}
uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ComCtrls, StdCtrls, Buttons, Tabnotbk, ExtCtrls, Inifiles, NUMDLL, printers;
{$ELSE}
uses
  Messages, WinTypes, WinProcs, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  Tabnotbk, StdCtrls, Buttons, ExtCtrls, Inifiles, NUMDLL31, printers;
{$ENDIF}

type
  TfrmOptions = class(TForm)
    Panel1: TPanel;
    TabbedNotebook1: TTabbedNotebook;
    btnOk: TBitBtn;
    btnCancel: TBitBtn;
    ckWY: TCheckBox;
    btnRegular: TBitBtn;
    btnBold: TBitBtn;
    btnItal: TBitBtn;
    btnHead: TBitBtn;
    Label1: TLabel;
    Label2: TLabel;
    cmbFormat: TComboBox;
    fntFont: TFontDialog;
    procedure btnRegularClick(Sender: TObject);
    procedure btnItalClick(Sender: TObject);
    procedure btnBoldClick(Sender: TObject);
    procedure btnHeadClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure cmbFormatChange(Sender: TObject);
    procedure ckWYClick(Sender: TObject);
    procedure btnOkClick(Sender: TObject);
    procedure btnCancelClick(Sender: TObject);
  private
    { Private declarations }
    procedure FontButton( s : String );
  public
    { Public declarations }
  end;

var
  frmOptions: TfrmOptions;
  inif : TIniFile;
  fontar : FONT_AR;
  colora : COLOR_AR;
  stl : TStringList;
  convert : integer;
  dev : string;

Function SetupPrinterDevice : string;
Function FontStyleToString( t : TFontStyles ) : String;
Function StringToFontStyle( s : String ) : TFontStyles;
procedure WriteFontToIni( i : TIniFile; id : String; f : TFont; code : Longint );
Procedure ReadFontFromIni( i : TIniFile; id : String; var f : TFont; var code : Longint );
Procedure GetFontFromIni( id : String; var f : TFont; var code : Longint );
procedure DoRTFSettings( lft, wid, usecvt : integer );
procedure ConvertTFont2Font(tf : TFont; code : longint; wh : cardinal );
Procedure DefaultFonts( s : string; var f : TFont; var code : Longint );

implementation

{$R *.DFM}

Function SetupPrinterDevice : string;
var
 print : TPrinter;
 s : string;
 p : PChar;
Begin
print := Printer;
SetupPrinterDevice := Print.Printers[Print.PrinterIndex];
end;

procedure TfrmOptions.btnRegularClick(Sender: TObject);
begin
FontButton('Reg');
end;

procedure TfrmOptions.btnItalClick(Sender: TObject);
begin
FontButton('Ital');
end;

procedure TfrmOptions.btnBoldClick(Sender: TObject);
begin
FontButton('Bold');
end;

procedure TfrmOptions.btnHeadClick(Sender: TObject);
begin
FontButton('Head');
end;

procedure TfrmOptions.FormCreate(Sender: TObject);
var
  ifn : string;
begin
colora[0]:=0;
colora[1]:=$ff0000;
colora[2]:=$ff;
colora[3]:=$800080;
GetDir(0,ifn);
if ifn[length(ifn)-1]<> '\' then ifn := ifn + '\';
ifn := ifn + 'NUMERO.INI';
inif := TIniFile.Create(ifn);
stl := TStringList.Create;
stl.Clear;
inif.ReadSectionValues('Options',stl);
ckWY.Checked := inif.ReadBool('Options', 'WYasVowels', False );
if ckWy.Checked then
   SetWYVowel( 1 )
else
   SetWYVowel( 0 );
cmbFormat.ItemIndex := inif.ReadInteger('Options', 'ConvOpt', 0 );
convert:=cmbFormat.ItemIndex;
end;

procedure TfrmOptions.cmbFormatChange(Sender: TObject);
begin
inif.WriteInteger('Options', 'ConvOpt', cmbFormat.ItemIndex );
convert:=cmbFormat.ItemIndex;
end;

procedure TfrmOptions.ckWYClick(Sender: TObject);
begin
inif.WriteBool('Options', 'WYasVowels', ckWY.checked );
if ckWy.Checked then
   SetWYVowel( 1 )
else
   SetWYVowel( 0 );
end;

procedure TfrmOptions.FontButton( s : String );
Var
   code :Longint;
   ft : TFont;
   tm : TTextMetric;
begin
code := FF_ROMAN+VARIABLE_PITCH;
ft := TFont.Create;
ReadFontFromIni(inif, s, ft, code );
fntfont.font := ft;
if Not fntFont.Execute then exit;
canvas.Font := fntFont.font;
GetTextMetrics( canvas.handle, tm );
code := (tm.tmPitchAndFamily and $f0);
WriteFontToIni( inif, s, fntFont.Font, code );
end;

Function FontStyleToString( t : TFontStyles ) : String;
var s : string;
begin
if fsBold in t then s := 'B' else s := '-';
if fsItalic in t then s := s + 'I' else s := s + '-';
if fsUnderline in t then s := s + 'U' else s := s + '-';
if fsStrikeout in t then s := s + 'S' else s := s + '-';
FontStyleToString := s;
end;

Function StringToFontStyle( s : String ) : TFontStyles;
var
  fs : TFontStyles;
begin
if s = '' then fs := []
else begin;
if s[1] = 'B' then fs := [fsBold] else fs := [];
if s[2] = 'I' then fs := fs + [fsItalic];
if s[3] = 'U' then fs := fs + [fsUnderline];
if s[4] = 'S' then fs := fs + [fsStrikeout];
end;
StringToFontStyle := fs;
end;

procedure WriteFontToIni( i : TIniFile; id : String; f : TFont; code : longint );
var
  s, st : string;
begin

s := Concat(id,'Name');
i.WriteString('Options', s, f.Name );
stl.Values[s] := f.Name;
s := Concat(id,'Size');
i.WriteInteger('Options', s, f.Size );
st := IntToStr(f.Size);
stl.Values[s] := st;
s := Concat(id,'Color');
i.WriteInteger('Options', s, f.Color );
st := IntToStr(f.Color);
stl.Values[s] := st;
s := Concat(id,'Style');
st := FontStyleToString(f.Style);
i.WriteString('Options', s, st );
stl.Values[s] := st;
s := Concat(id,'code');
i.WriteInteger('Options', s, code );
st := IntToStr(code);
stl.Values[s] := st;
end;

Procedure ReadFontFromIni( i : TIniFile; id : String; var f : TFont; var code : longint );
var
  st, sav : string;
begin
sav := '';
sav := id;
st := '';
sav := Concat(id,'Name');
st := i.ReadString('Options', sav, '' );
if st = '' then begin
   defaultFonts( id, f, code );
   exit;
   end;
f.Name := st;
sav := Concat(id,'Size');
f.Size := i.ReadInteger('Options', sav, f.Size );
sav := Concat(id,'Color');
f.Color := i.ReadInteger('Options', sav, f.Color );
sav := Concat(id,'Style');
st := '';
st := i.ReadString('Options', sav, '' );
f.Style := StringToFontStyle(st);
sav := Concat(id,'Code');
code := i.ReadInteger('Options', sav, code );
end;

Procedure GetFontFromIni( id : String; var f : TFont; var code : longint );
var
  st, sav : string;
  size, xcode : integer;
  color : longint;
begin
sav := Concat(id,'Name');
st := stl.Values[sav];
if st = '' then begin
   defaultFonts( id, f, code );
   exit;
   end;
f.Name := st;
sav := Concat(id,'Size');
st := stl.Values[sav];
val(st,size,xcode);
f.Size := size;
sav := Concat(id,'Color');
st := stl.Values[sav];
val(st,color,xcode);
f.Color := color;
sav := Concat(id,'Style');
st := stl.Values[sav];
f.Style := StringToFontStyle(st);
st := stl.Values[sav];
sav := Concat(id,'Code');
st := stl.Values[sav];
end;

procedure TfrmOptions.btnOkClick(Sender: TObject);
begin
hide;
end;

procedure TfrmOptions.btnCancelClick(Sender: TObject);
begin
hide;
end;

procedure DoRTFSettings( lft, wid, usecvt : integer );
var
ft : TFont;
code : longint;
st : string;
dev : array[0..40] of char;
begin

code := FF_ROMAN+VARIABLE_PITCH;
ft := TFont.Create;
st := 'Reg';
GetFontFromIni(st, ft, code );
ConvertTFont2Font(ft,code,_REG_ );
st := 'Bold';
GetFontFromIni(st, ft, code );
ConvertTFont2Font(ft,code,_BOLD_ );
st := 'Ital';
GetFontFromIni(st, ft, code );
ConvertTFont2Font(ft,code,_UITAL_ );
st := 'Head';
GetFontFromIni(st, ft, code );
ConvertTFont2Font(ft,code,_HEAD_ );
st := SetupPrinterDevice;
StrPCopy(dev,st);
if usecvt <> -1 then
   usecvt := convert;
SetupRTFConvert( fontar, colora, lft, wid, usecvt, dev );
end;

procedure ConvertTFont2Font(tf : TFont; code : longint; wh : cardinal );
Var
 fx : FONT;
begin
StrPCopy(fx.lfFaceName, tf.Name );
fx.lfHeight := tf.Size * 2;
if fsbold in tf.Style then fx.lfWeight := FW_BOLD
   else fx.lfWeight := FW_NORMAL;
if fsItalic in tf.Style then fx.lfItalic := 1
   else fx.lfItalic := 0;
if fsUnderline in tf.Style then fx.lfUnderline := 1
   else fx.lfUnderline := 0;
fx.lfPitchandFamily := byte(code);
fontar[wh] := fx;
colora[wh] := tf.Color;
end;

Procedure DefaultFonts( s : string; var f : TFont; var code : Longint );
begin
if s = 'Bold' then
   begin
   code := FF_ROMAN + VARIABLE_PITCH;
   f.Name := 'Times New Roman';
   f.Style := [fsBold];
   f.Size :=12;
   f.color:=colora[_BOLD_];
   end;
if s = 'Ital' then
   begin
   f.Name := 'Times New Roman';
   code := FF_ROMAN + VARIABLE_PITCH;
   f.Style := [fsItalic,fsUnderline];
   f.Size :=12;
   f.color:=colora[_UITAL_];
   end;
if s = 'Head' then
   begin
   f.Name := 'Arial';
   code := FF_SWISS + VARIABLE_PITCH;
   f.Style := [fsBold];
   f.Size := 14;
   f.color:=colora[_HEAD_];
   end;
if s = 'Reg' then
   begin
   f.Name := 'Times New Roman';
   code := FF_ROMAN + VARIABLE_PITCH;
   f.Style := [];
   f.Size := 12;
   f.color:=colora[_REG_];
   end;
end;

end.
