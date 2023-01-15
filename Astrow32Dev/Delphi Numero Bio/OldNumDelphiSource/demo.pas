unit Demo;

interface

uses
  SysUtils, WinTypes, WinProcs, Messages, Classes, Graphics, Controls,
  Forms, Dialogs, StdCtrls, Buttons, ExtCtrls, inifiles;

type
  Tdemofrm = class(TForm)
    Timer1: TTimer;
    Label1: TLabel;
    BitBtn1: TBitBtn;
    Label2: TLabel;
    Label3: TLabel;
    procedure Timer1Timer(Sender: TObject);
    procedure BitBtn1Click(Sender: TObject);
    procedure FormShow(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  demofrm: Tdemofrm;
  times : integer;

implementation

{$R *.DFM}

procedure Tdemofrm.Timer1Timer(Sender: TObject);
begin
Timer1.enabled := false;
BitBtn1Click(Sender);
end;

procedure Tdemofrm.BitBtn1Click(Sender: TObject);
begin
if Timer1.enabled=True then exit else hide;
MessageBeep(0);
MessageBeep(0);
{$IFDEF WEBSELL}
if (times < 0 ) then close;
{$ENDIF}
end;

procedure Tdemofrm.FormShow(Sender: TObject);
var
  inif : TIniFile;
  ifn: string;
  tstr: string;
begin
{$IFDEF WEBSELL}
GetDir(0,ifn);
if ifn[length(ifn)-1]<> '\' then ifn := ifn + '\';
ifn := ifn + 'NUMERO.INI';
inif := TIniFile.Create(ifn);
times := inif.ReadInteger('Shareware', 'Reg', 45 );
inif.WriteInteger('Shareware', 'Reg', times-1 );
if (times > 0) then tstr := 'You Have '+IntToStr(times) + ' times left!'
else tstr:= 'Sorry You Have Run Out of Trials!';
label2.caption:=tstr;
label2.alignment:=taCenter;
{$ENDIF}

Timer1.Enabled:= True;
MessageBeep(0);
MessageBeep(0);
end;

end.
