unit today;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls,
{$IFNDEF DEBUG}
   _instcalc_TLB;
{$ELSE}
   instcalc_TLB;
{$ENDIF}

type
  TTodayPlanForm = class(TForm)
    Label1: TLabel;
    lblAscend: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    Label13: TLabel;
    Label14: TLabel;
    lblSun: TLabel;
    lblMoon: TLabel;
    lblMercury: TLabel;
    lblVenus: TLabel;
    lblMars: TLabel;
    lblJupiter: TLabel;
    lblSaturn: TLabel;
    lblUranus: TLabel;
    lblNeptune: TLabel;
    lblPluto: TLabel;
    lblNode: TLabel;
    lblMedCoeli: TLabel;
    lblPartFort: TLabel;
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure FormShow(Sender: TObject);
  private
    calc : IAstInstCalc;
{$IFNDEF DEBUG}
    coclass : TCAstInstCalc;
{$ENDIF }
    { Private declarations }
  public
    { Public declarations }
  end;

const
  P_ASCEND = 0;
  P_SUN = 1;
  P_MOON = 2;
  P_MERCURY = 3;
  P_VENUS = 4;
  P_MARS = 5;
  P_JUPITER = 6;
  P_SATURN = 7;
  P_URANUS = 8;
  P_NEPTUNE = 9;
  P_PLUTO = 10;
  P_NNODE = 11;
  P_SNODE = 12;
  P_MED_COELI = 13;
  P_IM_COELI = 14;
  P_PART_FORTUNE = 15;

var
  TodayPlanForm: TTodayPlanForm;

implementation

{$R *.dfm}

procedure TTodayPlanForm.FormCreate(Sender: TObject);
begin
{$IFNDEF DEBUG }
   coclass := TCAstInstCalc.Create(Self);
   calc := coclass.DefaultInterface;
{$ELSE}
   Calc := CoAstInstCalc.Create;
{$ENDIF}
end;

procedure TTodayPlanForm.FormDestroy(Sender: TObject);
begin
{$IFNDEF DEBUG}
   coclass.Disconnect;
   coclass.Destroy;
{$ENDIF}
end;

procedure TTodayPlanForm.FormShow(Sender: TObject);
var
   dtnow : TDateTime;
   month, day, year, hour, min, sec, msec : Word;
begin
   dtnow := Date;
   DecodeDate(dtnow,year, month, day);
   dtnow := Time;
   DecodeTime(dtnow,hour, min, sec, msec);
   calc.StartAt(month, day, year, (hour * 24)+min  );
   calc.Index := P_ASCEND;
   lblAscend.Caption := calc.Value;
   calc.Index := P_SUN;
   lblSun.Caption := calc.Value;
   calc.Index := P_MOON;
   lblMoon.Caption := calc.Value;
   calc.Index := P_MERCURY;
   lblMercury.Caption := calc.Value;
   calc.Index := P_VENUS;
   lblVenus.Caption := calc.Value;
   calc.Index := P_MARS;
   lblMars.Caption := calc.Value;
   calc.Index := P_JUPITER;
   lblJupiter.Caption := calc.Value;
   calc.Index := P_SATURN;
   lblSaturn.Caption := calc.Value;
   calc.Index := P_URANUS;
   lblUranus.Caption := calc.Value;
   calc.Index := P_NEPTUNE;
   lblNeptune.Caption := calc.Value;
   calc.Index := P_PLUTO;
   lblPluto.Caption := calc.Value;
   calc.Index := P_NNODE;
   lblNode.Caption := calc.Value;
   calc.Index := P_MED_COELI;
   lblMedCoeli.Caption := calc.Value;
   calc.Index := P_PART_FORTUNE;
   lblPartFort.Caption := calc.Value;
end;

end.
