unit Birthdat;

interface

{$IFDEF WIN32}
uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  ComCtrls, Tabnotbk, StdCtrls, Buttons, ExtCtrls, NUMDLL;
{$ELSE}
uses
  Messages, WinTypes, WinProcs, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  Tabnotbk, StdCtrls, Buttons, ExtCtrls, NUMDLL31;
{$ENDIF}

  type
  TfrmNumData = class(TForm)
    Panel1: TPanel;
    btnOK: TBitBtn;
    btnCancel: TBitBtn;
    TabbedNotebook1: TTabbedNotebook;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    edtMonth: TEdit;
    edtDay: TEdit;
    edtYear: TEdit;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    ckBNInclude: TCheckBox;
    edtBNFirst: TEdit;
    edtBNMiddle: TEdit;
    edtBNLast: TEdit;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    ckO2Include: TCheckBox;
    edtO2First: TEdit;
    edtO2Middle: TEdit;
    edtO2Last: TEdit;
    Label10: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    ckO1Include: TCheckBox;
    edtO1First: TEdit;
    edtO1Middle: TEdit;
    edtO1Last: TEdit;
    Label13: TLabel;
    Label14: TLabel;
    Label15: TLabel;
    ckCNInclude: TCheckBox;
    edtCNFirst: TEdit;
    edtCNMiddle: TEdit;
    edtCNLast: TEdit;
    btnSave: TBitBtn;
    btnLoad: TBitBtn;
    btnClear: TBitBtn;
    Open: TOpenDialog;
    Save: TSaveDialog;
    ckInclude: TCheckBox;
    procedure FormKeyPress(Sender: TObject; var Key: Char);
    procedure edtMonthChange(Sender: TObject);
    procedure edtDayChange(Sender: TObject);
    procedure edtYearChange(Sender: TObject);
    procedure btnSaveClick(Sender: TObject);
    procedure btnLoadClick(Sender: TObject);
    procedure btnClearClick(Sender: TObject);
    procedure btnOKClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure btnCancelClick(Sender: TObject);
    procedure FormActivate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  procedure PutNum( nd : CHART_INFO );
  procedure GetNum( var nd : CHART_INFO );
  end;

var
  frmNumData: TfrmNumData;
  NumerologyData : CHART_INFO;

procedure WriteNum( s : String; nd : CHART_INFO; check : Boolean  );
Procedure ReadNum(  s : String; var nd : CHART_INFO; check : Boolean  );
Procedure ClearNum( var nd : CHART_INFO  );
Procedure ClearName( var n : NAME_REC  );
procedure UpdateDll;

implementation

{$R *.DFM}

procedure TfrmNumData.FormKeyPress(Sender: TObject; var Key: Char);
begin
if (TabbedNotebook1.ActivePage = 'Birth Date') and
       not (key in ['0'..'9',#8] ) then
   begin
   key := #0;
   MessageBeep( Word(-1) );
   end;
end;

procedure TfrmNumData.edtMonthChange(Sender: TObject);
var
  r, v : integer;
  s : String;
begin
if edtMonth.Text='' then Exit;
Val( edtMonth.Text, v, r );
if not (v in [1..12]) then
   begin
   edtMonth.text := '1';
   MessageBeep( Word(-1) );
   end;
end;

procedure TfrmNumData.edtDayChange(Sender: TObject);
var
  r, v : integer;
  s : String;
begin
if edtDay.Text='' then Exit;
Val( edtDay.Text, v, r );
if not (v in [1..31]) then
   begin
   edtDay.text := '1';
   MessageBeep( Word(-1) );
   end;
end;

procedure TfrmNumData.edtYearChange(Sender: TObject);
var
  r, v : integer;
  s : String;
begin
if edtYear.Text='' then Exit;
Val( edtYear.Text, v, r );
if ( v > 3000 ) then
   begin
   edtYear.text := '2000';
   MessageBeep( Word(-1) );
   end;
end;

procedure TfrmNumData.btnSaveClick(Sender: TObject);
begin
if Save.Execute then
   begin
   GetNum( NumerologyData );
   WriteNum( Save.FileName, NumerologyData, True );
   end;
end;

procedure WriteNum( s : String; nd : CHART_INFO; check : Boolean );
var
   NumFile : File of CHART_INFO;
   st : string;
begin
if check and FileExists( s ) then
   begin
   st := format( 'File "%s" Exists! Write Over It?', [s] );
   if MessageDlg( st, mtCustom, [mbYes, mbNo], 0 ) = mrNo then
      exit;
   end;
AssignFile( Numfile, s);
Rewrite(NumFile);
Write(NumFile,nd);
CloseFile(NumFile);
end;

Procedure ReadNum( s : String; var nd : CHART_INFO; check : Boolean );
var
   NumFile : File of CHART_INFO;
   st : string;
begin
if not FileExists( s ) then
   begin
   if check then
      begin
      st := format( 'File "%s" Does Not Exist! Clear Buffer?', [s] );
      if MessageDlg( st, mtCustom, [mbYes, mbNo], 0 ) = mrYes then ClearNum( nd );
      end;
   exit;
   end;
AssignFile( Numfile, s );
Reset(NumFile);
Read(NumFile,nd);
CloseFile(NumFile);
end;

procedure TfrmNumData.btnLoadClick(Sender: TObject);
begin
if Open.Execute then
   begin
   readNum( Open.FileName, NumerologyData, True  );
   PutNum( NumerologyData );
   end;
end;

procedure ClearName( var n : NAME_REC );
begin
with n do
    begin
    StrCopy( first, '' );
    StrCopy( middle, '' );
    StrCopy( last, '' );
    include := 0;
    end;
end;

Procedure ClearNum( var nd : CHART_INFO  );
begin

with nd do
     begin
     birth_date.include := 1;
     birth_date.month := 1;
     birth_date.day := 1;
     birth_date.year := 2000;
     ClearName( at_birth );
     ClearName( current );
     ClearName( opt1 );
     ClearName( opt2 );
     end;
end;

procedure TfrmNumData.btnClearClick(Sender: TObject);
begin
if MessageDlg( 'Are You Sure You Want To Clear?', mtCustom, [mbYes, mbNo], 0 ) = mrYes then
   begin
   ClearNum( NumerologyData );
   PutNum( NumerologyData );
   end;
end;

{ckInclude:       TCheckBox;
edtMonth:        TEdit;
edtDay:          TEdit;
edtYear:         TEdit;

ckBNInclude:     TCheckBox;
edtBNFirst:      TEdit;
edtBNMiddle:     TEdit;
edtBNLast:       TEdit;

ckO2Include:     TCheckBox;
edtO2First:      TEdit;
edtO2Middle:     TEdit;
edtO2Last:       TEdit;

ckO1Include:     TCheckBox;
edtO1First:      TEdit;
edtO1Middle:     TEdit;
edtO1Last:       TEdit;

ckCNInclude:     TCheckBox;
edtCNFirst:      TEdit;
edtCNMiddle:     TEdit;
edtCNLast:       TEdit; }

procedure TfrmNumData.PutNum( nd : CHART_INFO  );
begin
with nd do
     begin
     edtMonth.Text := IntToStr(birth_date.month);
     edtDay.Text := IntToStr(birth_date.day);
     edtYear.Text := IntToStr(birth_date.year);
     ckInclude.checked := birth_date.include <> 0;
     ckBNInclude.checked := at_birth.include <> 0;
     ckCNInclude.checked := current.include <> 0;
     ckO1Include.checked := opt1.include <> 0;
     ckO2Include.checked := opt2.include <> 0;
     edtBNFirst.Text := at_birth.first;
     edtBNMiddle.Text := at_birth.middle;
     edtBNLast.Text := at_birth.last;
     edtCNFirst.Text := current.first;
     edtCNMiddle.Text := current.middle;
     edtCNLast.Text := current.last;
     edtO1First.Text := opt1.first;
     edtO1Middle.Text := opt1.middle;
     edtO1Last.Text := opt1.last;
     edtO2First.Text := opt2.first;
     edtO2Middle.Text := opt2.middle;
     edtO2Last.Text := opt2.last;
     end;
end;

procedure TfrmNumData.GetNum( var nd : CHART_INFO  );
var
   r : Integer;
begin
with nd do
     begin
     StrPLCopy( id, 'NDT1', 4 );
     Val( edtMonth.Text, birth_date.month, r );
     Val( edtDay.Text, birth_date.day, r );
     Val( edtYear.Text, birth_date.year, r );
     if ( birth_date.year < 100 ) and ( birth_date.year > 10 ) then
        birth_date.year := birth_date.year+1900
     else if ( birth_date.year <= 10 ) then
        birth_date.year := birth_date.year+2000;
     if ckInclude.Checked then
        birth_date.include := 1
     else
        birth_date.include := 0;
     if ckBNInclude.Checked then
        at_birth.include := 1
     else
        at_birth.include := 0;
     if ckCNInclude.Checked then
        current.include := 1
     else
        current.include := 0;
     if ckO1Include.Checked then
        opt1.include := 1
     else
        opt1.include := 0;
     if ckO2Include.Checked then
        opt2.include := 1
     else
        opt2.include := 0;
     StrPLCopy( at_birth.first, edtBNFirst.Text, 80 );
     StrPLCopy( at_birth.middle, edtBNMiddle.Text, 80 );
     StrPLCopy( at_birth.last, edtBNLast.Text, 80 );
     StrPLCopy( current.first, edtCNFirst.Text, 80 );
     StrPLCopy( current.middle, edtCNMiddle.Text, 80 );
     StrPLCopy( current.last, edtCNLast.Text, 80 );
     StrPLCopy( opt1.first, edtO1First.Text, 80 );
     StrPLCopy( opt1.middle, edtO1Middle.Text, 80 );
     StrPLCopy( opt1.last, edtO1Last.Text, 80 );
     StrPLCopy( opt2.first, edtO2First.Text, 80 );
     StrPLCopy( opt2.middle, edtO2Middle.Text, 80 );
     StrPLCopy( opt2.last, edtO2Last.Text, 80 );
     end;
SetChartInfoData( nd );
end;

procedure TfrmNumData.btnOKClick(Sender: TObject);
begin
GetNum( NumerologyData );
hide;
end;

procedure TfrmNumData.FormCreate(Sender: TObject);
begin
readNum( 'NumHist.ndt', NumerologyData, False  );
PutNum( NumerologyData );
end;

procedure TfrmNumData.FormDestroy(Sender: TObject);
begin
GetNum( NumerologyData );
WriteNum( 'NumHist.ndt', NumerologyData, False  );
end;

procedure TfrmNumData.btnCancelClick(Sender: TObject);
begin
hide;
end;

procedure UpdateDll;
begin
SetChartInfoData( NumerologyData );
end;
procedure TfrmNumData.FormActivate(Sender: TObject);
begin
TabbedNotebook1.ActivePage :='Name At Birth';
end;

end.


