unit Calendar;

interface

uses
  WinTypes, WinProcs, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Buttons, ExtCtrls, Tabnotbk, Numbers,
  Perpcal, Printers, inifiles, ComCtrls, demo;


type
  TfrmCal = class(TForm)
    Panel1: TPanel;
    bbPrevMo: TBitBtn;
    bbNextMo: TBitBtn;
    bbPrevYr: TBitBtn;
    bbNextYr: TBitBtn;
    TabbedNotebook1: TTabbedNotebook;
    edtBMo: TEdit;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    edtBDay: TEdit;
    edtBYr: TEdit;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    edtSMo: TEdit;
    Label11: TLabel;
    edtSYr: TEdit;
    PersBox: TPaintBox;
    UnivBox: TPaintBox;
    Label12: TLabel;
    Label13: TLabel;
    Label14: TLabel;
    cmbHead: TComboBox;
    cmbBig: TComboBox;
    cmbBase: TComboBox;
    bbPrint: TBitBtn;
    Label15: TLabel;
    Label16: TLabel;
    chkPortrait: TCheckBox;
    cmbClrHead: TComboBox;
    cmbClrBig: TComboBox;
    YrtxtBtn: TSpeedButton;
    procedure FormKeyPress(Sender: TObject; var Key: Char);
    procedure edtBMoChange(Sender: TObject);
    procedure edtBDayChange(Sender: TObject);
    procedure edtBYrChange(Sender: TObject);
    procedure edtSMoChange(Sender: TObject);
    procedure edtSYrChange(Sender: TObject);
    procedure bbPrevMoClick(Sender: TObject);
    procedure bbNextMoClick(Sender: TObject);
    procedure bbPrevYrClick(Sender: TObject);
    procedure bbNextYrClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure PersBoxPaint(Sender: TObject);
    procedure UnivBoxPaint(Sender: TObject);
    procedure Panel1DblClick(Sender: TObject);
    procedure UnivBoxDblClick(Sender: TObject);
    procedure PersBoxDblClick(Sender: TObject);
    procedure FormKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure PersBoxMouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure UnivBoxMouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure cmbHeadChange(Sender: TObject);
    procedure cmbBigChange(Sender: TObject);
    procedure cmbBaseChange(Sender: TObject);
    procedure chkPortraitClick(Sender: TObject);
    procedure cmbClrHeadChange(Sender: TObject);
    procedure cmbClrBigChange(Sender: TObject);
    procedure bbPrintClick(Sender: TObject);
    procedure YrtxtBtnClick(Sender: TObject);
    procedure FormShow(Sender: TObject);
    private
     { Private declarations }
    procedure doGrid(b : TPaintBox; sy : SmallInt; can : TCanvas; x, yy, h, w : SmallInt );
    procedure CenterText( b : TCanvas; x, y : SmallInt; s : string );
    procedure PrintDateNumbers( b : TPaintBox;  can : TCanvas; xx, yy, h : SmallInt; cd : CalData );
    procedure PrintNumNumbers( b : TPaintBox; can : TCanvas; xx, yy, h : SmallInt; cd : CalData; d : array of SmallInt  );
    procedure calc;
    public
    { Public declarations }
  end;

const
  monthnames : array [1..12] of string = ( 'January',
     'February','March','April','May','June','July',
     'August','September','October','November','December' );
  daynames : array [1..7] of string = ('Sunday','Monday',
    'Tuesday','Wednesday','Thursday','Friday','Saturday');
  daynums : array [1..31] of string = ( '1','2','3','4','5','6',
    '7','8','9','10','11','12','13','14','15','16','17','18',
    '19','20','21','22','23','24','25','26','27','28','29',
    '30','31');
 colors : array [0..14] of TColor = ( clBlack, clMaroon,
     clGreen, clOlive, clNavy, clPurple, clTeal, clGray, clSilver, clRed, clLime, clBlue, clFuchsia, clAqua, clWhite );
 HeadFactor = 18;
 SubFactor = 30;
 NameFactor = 40;
 DateFactor = 32;
 NumFactor = 14;


var
  bYear, bMonth, bDay : Word;
  bDate : TDateTime;
  sYear, sMonth : Word;
  frmCal: TfrmCal;
  pYear, pMonth : SmallInt;
  uYear, uMonth : SmallInt;
  uDays : array [0..31] of SmallInt;
  pDays : array [0..31] of SmallInt;
  boxht, boxwd, boxy, clickx, clicky : SmallInt;
  perp : CalData;
  sHead, sBase, sBig : String;
  scHead, scBig : String;
  cHead, cBig : TColor;
  cchHead, cchBig : SmallInt;
  prPortrait, isPrinting : Boolean;
  iniFile: TIniFile;
  demo_mode : integer;

function RCToDay( r, c : SmallInt ) : SmallInt;
function HeightToSize( h, fac : SmallInt ) : SmallInt;



implementation

uses poputxt;


{$R *.DFM}

{$IFNDEF WIN32}
procedure doClick( key , id : SmallInt; title : string ); far; external 'VIEWDLL';
{$ENDIF}


procedure TfrmCal.FormKeyPress(Sender: TObject; var Key: Char);
begin
if not (Key in ['0'..'9',#8]) then
   begin
   Key := #0;
   MessageBeep( Word(-1) );
   end;
end;

procedure TfrmCal.edtBMoChange(Sender: TObject);
var
  r, v : integer;
  s : String;
begin
if edtBMo.Text='' then Exit;
Val( edtBMo.Text, v, r );
if not (v in [1..12]) then
   begin
   edtBMo.text := '1';
   MessageBeep( Word(-1) );
   end
else
   begin
   bMonth := v;
   bDate := EncodeDate(bYear, bMonth, bDay);
   end;
s := FloatToStr(bDate);
iniFile.WriteString('InterCal','BirthDate',s );
calc;
end;

procedure TfrmCal.edtBDayChange(Sender: TObject);
var
  r, v : integer;
  s : String;
begin
if edtBDay.Text='' then Exit;
Val( edtBDay.Text, v, r );
if not (v in [1..31]) then
   begin
   edtBDay.text := '1';
   MessageBeep( Word(-1) );
   end
else
   begin
   bDay := v;
   bDate := EncodeDate(bYear, bMonth, bDay);
   end;
s := FloatToStr(bDate);
iniFile.WriteString('InterCal','BirthDate',s );
calc;
end;

procedure TfrmCal.edtBYrChange(Sender: TObject);
var
  r, v : integer;
  s : String;
begin
if edtBYr.Text='' then Exit;
Val( edtBYr.Text, v, r );
if (v < 10) or ( v > 2900 ) then
   begin
   edtBYr.text := '1996';
   MessageBeep( Word(-1) );
   end
else
   begin
   bYear := v;
   bDate := EncodeDate(bYear, bMonth, bDay);
   end;
s := FloatToStr(bDate);
iniFile.WriteString('InterCal','BirthDate',s );
calc;
end;

procedure TfrmCal.edtSMoChange(Sender: TObject);
var
  r, v : integer;
begin
if edtSMo.Text='' then Exit;
Val( edtSMo.Text, v, r );
if not (v in [1..12]) then
   begin
   edtSMo.text := '1';
   MessageBeep( Word(-1) );
   end
else
   begin
   sMonth := v;
   end;
iniFile.WriteString('InterCal','StartMonth',edtSMo.Text );
calc;
end;

procedure TfrmCal.edtSYrChange(Sender: TObject);
var
  r, v : integer;
begin
if edtSYr.Text='' then Exit;
Val( edtSYr.Text, v, r );
if (v < 10) or ( v > 2900 ) then
   begin
   edtSYr.text := '1996';
   MessageBeep( Word(-1) );
   end
else
   begin
   sYear := v;
   end;
iniFile.WriteString('InterCal','StartYear',edtSYr.Text );
calc;
end;

procedure TfrmCal.bbPrevMoClick(Sender: TObject);
begin
sMonth := sMonth -1;
if sMonth = 0 then
   begin
   sMonth := 12;
   sYear := sYear -1;
   end;
edtSMo.Text := IntToStr(sMonth);
edtSYr.Text := IntToStr(sYear);
iniFile.WriteString('InterCal','StartMonth',edtSMo.Text );
iniFile.WriteString('InterCal','StartYear',edtSYr.Text );
calc;
end;

procedure TfrmCal.bbNextMoClick(Sender: TObject);
begin
sMonth := sMonth +1;
if sMonth = 13 then
   begin
   sMonth := 1;
   sYear := sYear +1;
   end;

edtSMo.Text := IntToStr(sMonth);
edtSYr.Text := IntToStr(sYear);
iniFile.WriteString('InterCal','StartMonth',edtSMo.Text );
iniFile.WriteString('InterCal','StartYear',edtSYr.Text );
calc;
end;

procedure TfrmCal.bbPrevYrClick(Sender: TObject);
begin
sYear := sYear -1;
edtSYr.Text := IntToStr(sYear);
iniFile.WriteString('InterCal','StartMonth',edtSMo.Text );
iniFile.WriteString('InterCal','StartYear',edtSYr.Text );
calc;
end;

procedure TfrmCal.bbNextYrClick(Sender: TObject);
begin
sYear := sYear +1;
edtSYr.Text := IntToStr(sYear);
iniFile.WriteString('InterCal','StartMonth',edtSMo.Text );
iniFile.WriteString('InterCal','StartYear',edtSYr.Text );
calc;
end;

procedure TfrmCal.FormCreate(Sender: TObject);
var
  dt: TDateTime;
  d : Word;
  s, ifn : string;
begin
isPrinting := False;
GetDir(0,ifn);
if ifn[length(ifn)-1]<> '\' then ifn := ifn + '\';
ifn := ifn + 'NUMERO.INI';
inifile := TIniFile.Create(ifn);
dt := Date;
DecodeDate(dt, sYear, sMonth, d );
bYear := 1958;
bMonth := 3;
bDay := 29;
bDate := EncodeDate(bYear, bMonth, bDay);
s := FloatToStr( bDate );
s := iniFile.ReadString('InterCal','BirthDate',s );
bDate := StrToFloat(s);
DecodeDate(bDate, bYear, bMonth, bDay );
edtSYr.Text := IntToStr(sYear);
edtSMo.Text := IntToStr(sMonth);
iniFile.WriteString('InterCal','StartMonth',edtSMo.Text );
iniFile.WriteString('InterCal','StartYear',edtSYr.Text );
calc;
sHead := 'Arial';
sHead := iniFile.ReadString('InterCal','HeadFont',sHead );
cmbHead.Clear;
cmbHead.Items := Screen.Fonts;
cmbHead.ItemIndex := cmbHead.Items.IndexOf( sHead );
sBase := 'Arial';
sBase := iniFile.ReadString('InterCal','BaseFont',sBase );
cmbBase.Clear;
cmbBase.Items := Screen.Fonts;
cmbBase.ItemIndex := cmbBase.Items.IndexOf( sBase );
sBig := 'Arial';
sBig := iniFile.ReadString('InterCal','BigFont',sBig );
cmbBig.Clear;
cmbBig.Items := Screen.Fonts;
cmbBig.ItemIndex := cmbBig.Items.IndexOf(sBig);
prPortrait := True;
prPortrait := iniFile.ReadBool('InterCal','PrintPortrait', prPortrait);
chkPortrait.Checked := prPortrait;
cchHead := 5;
cHead := colors[cchHead];
cmbClrHead.ItemIndex := cchHead;
scHead := iniFile.ReadString('InterCal','HeadColor', cmbClrHead.Text );
cmbClrHead.ItemIndex := cmbClrHead.Items.IndexOf(scHead);
cchHead := cmbClrHead.ItemIndex;
cHead := colors[cchHead];
cchBig := 9;
cBig := colors[cchBig];
cmbClrBig.ItemIndex := cchBig;
scBig := iniFile.ReadString('InterCal','BigColor', cmbClrBig.Text );
cmbClrBig.ItemIndex := cmbClrBig.Items.IndexOf(scBig);
cchBig := cmbClrBig.ItemIndex;
cBig := colors[cchBig];
end;

procedure TfrmCal.doGrid(b: TPaintBox; sy : SmallInt; can : TCanvas; x, yy, h, w : SmallInt );
var i, incx, incy, y, spc  : SmallInt;
    s : string;
begin
  with can do
     begin
     Font.Color := cHead;
     Font.Name := sHead;
     Font.Size := HeightToSize(h,HeadFactor);
     Font.Style := [fsBold];
     spc := abs(Font.Height div 6);
     incx := w div 7;
     incx := incx -1;
     w := incx * 7;
     Rectangle(x, yy, x+w, yy+h );
     if b.name = 'UnivBox' then
        begin
        s := Format( 'Universal Calendar for Month %s', [monthnames[sMonth]] );
        CenterText( can, (w div 2)+x, yy+spc, s );
        s := Format( 'Year: %d, Universal Year: %d, Universal Month: %d',
               [sYear, uYear, uMonth] );
        end
     else
        begin
        s := Format( 'Personal Calendar for Month %s', [monthnames[sMonth]] );
        CenterText( can, (w div 2)+x, yy+spc, s );
        s := Format( 'Year: %d, Personal Year: %d, Personal Month: %d, Birth Date: %s',
               [sYear, pYear, pMonth, DateTimeToStr(bDate)] );
        end;
     y := TextHeight('H')+spc+spc;
     Font.Size := HeightToSize(h, SubFactor);
     Font.Style := [];
     Font.Name := sBase;
     Font.Color := clBlack;
     CenterText( can, x+(w div 2), y+yy, s );
     Font.Size := HeightToSize(h,NameFactor);
     sy := y + TextHeight('H')+spc+spc+spc;
     MoveTo(x, sy+yy-2 );
     LineTo(w+x, sy+yy-2 );
     for i := 1 to 7  do
         begin
         CenterText( can, (incx * i) - (incx div 2) + x, sy+yy,
           daynames[i] );
         MoveTo((incx * i)+x, sy+yy-2 );
         LineTo((incx * i)+x, h+yy);
         end;
     sy := sy + TextHeight('H');
     incy := (h-sy)div 5;
     incy := incy -1;
     sy := sy + yy;
     boxy := sy;
     boxwd := incx;
     boxht := incy;
     MoveTo(x, sy );
     LineTo(w+x, sy );
     for i := 1 to 4 do
         begin
         MoveTo(x,sy+(i*incy));
         LineTo(w+x, sy+(i*incy));
         end;
     end;
end;

procedure TfrmCal.CenterText( b : TCanvas; x, y : SmallInt; s : string );
var
h, w : integer;
begin
with b do
     begin
     {h := TextHeight(s);}
     w := TextWidth(s);
     {y := y - h;}
     w := w div 2;
     x := x - w;
     TextOut( x, y, s );
     end
end;


procedure TfrmCal.calc;
var
  i : SmallInt;
begin
pYear := personalYear(bMonth, bDay, sYear );
pMonth := personalMonth(bMonth, bDay, sYear, sMonth );
for i := 1 to 31 do
    pDays[i] := personalDay(bMonth, bDay, sYear, sMonth, i );
uYear := universalYear(sYear);
uMonth := universalMonth(sMonth);
for i := 1 to 31 do
    uDays[i] := universalDay(syear, sMonth, i);
perp := PerpetualCalendar( sYear, sMonth );
PersBox.Repaint;
UnivBox.Repaint;
end;

procedure TfrmCal.PrintDateNumbers(b : TPaintBox; can : TCanvas; xx, yy, h : SmallInt; cd : CalData );
var
x, y, i, r : SmallInt;
begin
    with can do
    begin
    Font.Color := clBlack;
    Font.Name := sBase;
    Font.Size := HeightToSize(h, DateFactor);
    Font.Style := [];
    y := boxy + boxht-(TextHeight('1'))-2;
    x := (boxwd * cd.start)+(boxwd div 32) + xx;
    r := cd.start;
    for i := 1 to cd.days do
        begin
        TextOut(x, y, daynums[i] );
        r := r + 1;
        x := x + boxwd;
        if r = 7 then
           begin
           r := 0;
           x := 2 + xx;
           y := y + boxht;
           end;
        end;
    end;
end;

procedure TfrmCal.PrintNumNumbers(b : TPaintBox; can : TCanvas; xx, yy, h : SmallInt; cd : CalData; d : array of SmallInt );
var
x, y, i, r : SmallInt;
begin
    with can do
    begin
    Font.Name := sBig;
    Font.Size := HeightToSize(h, NumFactor);
    Font.Style := [fsBold];
    Font.Color := cBig;
    y := (boxy +(boxht div 32));
    x := (boxwd * cd.start)+ boxwd -(boxwd div 32) + xx;
    r := cd.start;
    for i := 1 to cd.days do
        begin
        TextOut(x-TextWidth(daynums[d[i]]), y, daynums[d[i]] );
        r := r + 1;
        x := x + boxwd;
        if r = 7 then
           begin
           r := 0;
           x := boxwd -(boxwd div 32) + xx;
           y := y + boxht;
           end;
        end;
    end;
end;

procedure TfrmCal.PersBoxPaint(Sender: TObject);
begin
doGrid(PersBox, 1, PersBox.Canvas, 0, 0, PersBox.Height, PersBox.Width);
PrintDateNumbers(PersBox, PersBox.Canvas, 0, 0, PersBox.Height, perp );
PrintNumNumbers(PersBox, PersBox.Canvas, 0, 0, PersBox.Height, perp, pDays );
end;

procedure TfrmCal.UnivBoxPaint(Sender: TObject);
begin
doGrid(UnivBox, 1, UnivBox.Canvas, 0, 0, UnivBox.Height, UnivBox.Width);
PrintDateNumbers(UnivBox, UnivBox.Canvas, 0, 0,UnivBox.Height, perp );
PrintNumNumbers(UnivBox, UnivBox.Canvas, 0, 0, UnivBox.Height, perp, uDays );
end;

procedure TfrmCal.Panel1DblClick(Sender: TObject);
var
  ret : Boolean;
begin
if TabbedNotebook1.ActivePage = 'Personal Calendar' then
   DoClick( PERS_YEAR, pYear, 'Your Personal Year' )
else
   DoClick( UNIV_YEAR, uYear, 'Your Universal Year');
end;


procedure TfrmCal.UnivBoxDblClick(Sender: TObject);
var
   r, c, d : SmallInt;
begin
if clicky < boxy then doClick( UNIV_MONTH, uMonth, 'Your Universal Month' )
else
   begin
   c := clickx div boxwd;
   r := (clicky - boxy) div boxht;
   d := RCToDay(r,c);
   if ( d >= 1 ) and ( d <= 31 ) then
      doClick( UNIV_DAY, uDays[d], 'Your Universal Day' )
   else
      doClick( UNIV_MONTH, uMonth, 'Your Universal Month' );
   end;
end;

procedure TfrmCal.PersBoxDblClick(Sender: TObject);
var
  r, c, d : SmallInt;
begin

if clicky < boxy then doClick( PERS_MONTH, pMonth, 'Your Personal Month' )
else
   begin
   c := clickx div boxwd;
   r := (clicky - boxy) div boxht;
   d := RCToDay(r,c);
   if ( d >= 1 ) and ( d <= 31 ) then
      doClick( PERS_DAY, pDays[d], 'Your Personal Day' )
   else
      doClick( PERS_MONTH, pMonth, 'Your Personal Month' );
   End;
end;

function RCToDay( r, c : SmallInt ) : SmallInt;
var
 rv : SmallInt;
begin
if ( r = 0 ) and ( c < perp.start )  then rv := -1 else
     if ( r = 0 ) then rv := c - perp.start
        else if perp.start = 0 then
        begin
        rv := ((r * 7) + c )+1;
        if rv > perp.days then rv := -1;
        end
else
   begin
   rv := ((r * 7) + c ) - (7 - perp.start )+1;
   if rv > perp.days then rv := -1;
   end;
RCToDay := rv+1;
end;

procedure TfrmCal.FormKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
if (Key = VK_PRIOR) and (ssAlt in Shift) then bbPrevYrClick( Sender )
   else if (Key = VK_PRIOR) then bbPrevMoClick ( Sender )
        else if (Key = VK_NEXT) and (ssAlt in Shift) then bbNextYrClick( Sender )
           else if (Key = VK_NEXT) then bbNextMoClick( Sender );

end;

procedure TfrmCal.PersBoxMouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin
clickx := X;
clicky := Y;
end;

procedure TfrmCal.UnivBoxMouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin
clickx := X;
clicky := Y;
end;

procedure TfrmCal.cmbHeadChange(Sender: TObject);
begin
sHead := cmbHead.Text;
iniFile.WriteString('InterCal','HeadFont',sHead );
end;

procedure TfrmCal.cmbBigChange(Sender: TObject);
begin
sBig := cmbBig.Text;
iniFile.WriteString('InterCal','BigFont',sBig );
end;

procedure TfrmCal.cmbBaseChange(Sender: TObject);
begin
sBase := cmbBase.Text;
iniFile.WriteString('InterCal','BaseFont',sBase );
end;

function HeightToSize( h, fac : SmallInt ) : SmallInt;
begin
    h := h div fac;
    if h < 10 then h := 10;
    if isPrinting then
    begin
    case fac of
         HeadFactor : h := 20;
         SubFactor :  h := 13;
         NameFactor : h := 10;
         DateFactor : H:= 13;
         NumFactor :  H:= 30;
         end;
    end;
    HeightTosize := h;
end;

procedure TfrmCal.chkPortraitClick(Sender: TObject);
begin
prPortrait:=chkPortrait.Checked;
iniFile.WriteBool('InterCal','PrintPortrait', prPortrait);
end;

procedure TfrmCal.cmbClrHeadChange(Sender: TObject);
begin
if cmbClrHead.ItemIndex <> -1 then
   cHead := colors[cmbClrHead.ItemIndex];
iniFile.WriteString('InterCal','HeadColor', cmbClrHead.Text );
end;

procedure TfrmCal.cmbClrBigChange(Sender: TObject);
begin
if cmbClrBig.ItemIndex <> -1 then
   cBig := colors[cmbClrBig.ItemIndex];
iniFile.WriteString('InterCal','BigColor', cmbClrBig.Text );
end;

procedure TfrmCal.bbPrintClick(Sender: TObject);
var
  m : smallInt;
begin
if (TabbedNotebook1.ActivePage <> 'Personal Calendar')
     and (TabbedNotebook1.ActivePage <> 'Universal Calendar') then exit;
with Printer do
     begin
     m := PageWidth div 33;
     Title := TabbedNotebook1.ActivePage;
     if prPortrait then Orientation := poPortrait
          else Orientation := poLandscape;
     isPrinting := True;
     BeginDoc;
     if TabbedNotebook1.ActivePage = 'Personal Calendar' then
        begin
        doGrid(PersBox, m, Canvas, m, m, PageHeight-m-m, PageWidth-m-m);
        PrintDateNumbers(PersBox, Canvas, m, m, PageHeight-m-m, perp );
        PrintNumNumbers(PersBox, Canvas, m, m, PageHeight-m-m, perp, pDays );
        end
     else
        begin
        doGrid(UnivBox, m, Canvas, m, m, PageHeight-m-m, PageWidth-m-m);
        PrintDateNumbers(UnivBox, Canvas, m, m, PageHeight-m-m, perp );
        PrintNumNumbers(UnivBox, Canvas, m, m, PageHeight-m-m, perp, uDays );
        end;
     EndDoc;
     isPrinting := False;
     end;
end;

procedure TfrmCal.YrtxtBtnClick(Sender: TObject);
begin
if (TabbedNotebook1.ActivePage = 'Personal Calendar') then
   doClick( PERS_YEAR, pYear, 'Your Personal Year' )
else if (TabbedNotebook1.ActivePage = 'Universal Calendar') then
   doClick( UNIV_YEAR, uYear, 'Your Universal Year');
end;

procedure TfrmCal.FormShow(Sender: TObject);
begin
{$IFDEF DEMO}
 doDemoCheck('Numerow For Windows');
{$ENDIF}
end;


end.
