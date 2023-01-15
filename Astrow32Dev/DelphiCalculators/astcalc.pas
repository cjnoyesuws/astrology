unit astcalc;

interface

uses

  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls,
{$IFNDEF DEBUG}
   _instcalc_TLB,
{$ELSE}
   instcalc_TLB,
{$ENDIF}
   StdCtrls;

type
  TInstCalcForm = class(TForm)
    Timer1: TTimer;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    lblMoon: TLabel;
    lblNode: TLabel;
    lblAscend: TLabel;
    lblMedCoeli: TLabel;
    Label5: TLabel;
    lblSun: TLabel;
    procedure FormCreate(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
  private
    calc : IAstInstCalc;
{$IFNDEF DEBUG}
    coclass : TCAstInstCalc;
{$ENDIF }
    { Private declarations }
  public
    { Public declarations }
  end;

var
  InstCalcForm: TInstCalcForm;

const
  P_ASCEND = 0;
  P_MOON = 2;
  P_MED_COELI = 13;
  P_NNODE = 11;
  P_SUN = 1;

implementation

uses inheritedregistry;


{$R *.dfm}

procedure TInstCalcForm.FormCreate(Sender: TObject);
begin
{$IFNDEF DEBUG }
   coclass := TCAstInstCalc.Create(Self);
   calc := coclass.DefaultInterface;
{$ELSE}
   Calc := CoAstInstCalc.Create;
{$ENDIF}
end;

procedure TInstCalcForm.FormShow(Sender: TObject);
begin
   Timer1Timer(Sender);
end;

procedure TInstCalcForm.Timer1Timer(Sender: TObject);
var
   dtnow : TDateTime;
   month, day, year, hour, min, sec, msec : Word;
   oReg : TInheritedRegistry;
   str : string;
begin
  oReg := TInheritedRegistry.Create('');
  oReg.Open('InstCalc', true, false );
  str := oReg.ReadString('MidnightEphem','Y');
  oReg.CloseKey;
  oReg.Destroy;
   dtnow := Date;
   DecodeDate(dtnow,year, month, day);
   dtnow := Time;
   DecodeTime(dtnow,hour, min, sec, msec);
   if ( str = 'N' ) then
      hour := 12;
   while ( hour > 24 ) do
   begin
      hour := hour - 24;
      dtnow := dtNow +1;
      DecodeDate(dtnow,year, month, day);
   end;
   calc.StartAt(month, day, year, (hour * 60)+min  );
   calc.Index := P_ASCEND;
   lblAscend.Caption := calc.Value;
   calc.Index := P_SUN;
   lblSun.Caption := calc.value;
   calc.Index := P_MOON;
   lblMoon.Caption := calc.Value;
   calc.Index := P_NNODE;
   lblNode.Caption := calc.Value;
   calc.Index := P_MED_COELI;
   lblMedCoeli.Caption := calc.Value;
end;

procedure TInstCalcForm.FormDestroy(Sender: TObject);
begin
{$IFNDEF DEBUG}
   coclass.Disconnect;
   coclass.Destroy;
{$ENDIF}
end;

end.
