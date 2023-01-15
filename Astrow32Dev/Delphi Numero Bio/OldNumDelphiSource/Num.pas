unit Num;

interface
uses
  WinTypes, WinProcs, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, birth, Numbers, poputxt, inifiles, demo;


type
  TfrmNum = class(TForm)
    Label1: TLabel;
    lblDate: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    btnPeYr: TButton;
    btnUnYr: TButton;
    btnPeMo: TButton;
    btnUnMo: TButton;
    btnPeDay: TButton;
    btnUnDay: TButton;
    btnClose: TButton;
    btnSetBirth: TButton;
    procedure btnCloseClick(Sender: TObject);
    procedure btnSetBirthClick(Sender: TObject);
    procedure btnPeYrClick(Sender: TObject);
    procedure FormActivate(Sender: TObject);
    procedure btnPeMoClick(Sender: TObject);
    procedure btnPeDayClick(Sender: TObject);
    procedure btnUnYrClick(Sender: TObject);
    procedure btnUnMoClick(Sender: TObject);
    procedure btnUnDayClick(Sender: TObject);
    procedure FormShow(Sender: TObject);
  private
    { Private declarations }
    procedure setupButton( t : TButton; w : Word);
    public
    { Public declarations }
  end;

procedure doCalc;

var
  frmNum: TfrmNum;
  theDate: TDateTime;
  bYear, bMonth, bDay : Word;
  tYear, tMonth, tDay : Word;
  peYear, peMonth, peDay : Word;
  unYear, unMonth, unDay : Word;
  inifile : Tinifile;
  demo_mode : integer;

implementation

{$R *.DFM}

{$IFNDEF WIN32 }
procedure doClick( key , id : SmallInt; title : string ); far; external 'VIEWDLL';
{$ENDIF}


procedure TfrmNum.btnCloseClick(Sender: TObject);
begin
Application.Terminate;
end;

procedure TfrmNum.btnSetBirthClick(Sender: TObject);
begin
birth.frmBirth.show;
end;

procedure TfrmNum.btnPeYrClick(Sender: TObject);
begin
doClick( PERS_YEAR, peYear, 'Your Personal Year...' );
end;

procedure TfrmNum.FormActivate(Sender: TObject);
begin
theDate := Date;
lblDate.Caption := DateToStr(theDate);
DecodeDate(theDate, tYear, tMonth, tDay );
getBirth(bYear, bMonth, bDay);
doCalc;
setupButton( btnPeYr, peYear );
setupButton( btnUnYr, unYear );
setupButton( btnPeMo, peMonth );
setupButton( btnUnMo, unMonth );
setupButton( btnPeDay, peDay );
setupButton( btnUnDay, unDay );
end;

procedure TfrmNum.setupButton( t : TButton; w : Word);
var
  s : string;
begin
s := format( '%d...', [w] );
t.Caption := s;
end;

procedure doCalc;
begin
peYear := personalYear(bMonth, bDay, tYear );
peMonth := personalMonth(bMonth, bDay, tYear, tMonth );
peDay := personalDay(bMonth, bDay, tYear, tMonth, tDay );
unYear := universalYear(tYear);
unMonth := universalMonth(tMonth);
unDay := universalDay(tyear, tMonth, tDay);
end;

procedure TfrmNum.btnPeMoClick(Sender: TObject);
begin
doClick( PERS_MONTH, peMonth, 'Your Personal Month...' );
end;

procedure TfrmNum.btnPeDayClick(Sender: TObject);
begin
doClick( PERS_DAY, peDay, 'Your Personal Day...' );
end;

procedure TfrmNum.btnUnYrClick(Sender: TObject);
begin
doClick( UNIV_YEAR, unYear, 'Your Universal Year...' );
end;

procedure TfrmNum.btnUnMoClick(Sender: TObject);
begin
doClick( UNIV_MONTH, unMonth, 'Your Universal Month...' );
end;

procedure TfrmNum.btnUnDayClick(Sender: TObject);
begin
doClick( UNIV_DAY, unDay, 'Your Universal Day...' );
end;

procedure TfrmNum.FormShow(Sender: TObject);
var
  ifn, s : string;
begin
{$IFDEF DEMO}
GetDir(0,ifn);
if ifn[length(ifn)-1]<> '\' then ifn := ifn + '\';
ifn := ifn + 'NUMERO.INI';
if iniFile = nil then iniFile := TIniFile.Create(ifn);
s := iniFile.ReadString('Shareware','Reg','0');
if s = '1&Numbers&9' then demo_mode := 0
   else demo_mode := 100;
if demo_mode=100 then demofrm.Show;
{$ENDIF}
end;

end.
