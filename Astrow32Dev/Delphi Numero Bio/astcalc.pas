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


implementation


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
begin
   dtnow := Date;
   DecodeDate(dtnow,year, month, day);
   dtnow := Time;
   DecodeTime(dtnow,hour, min, sec, msec);
   calc.StartAt(month, day, year, (hour * 24)+min  );
   calc.Index := P_ASCEND;
   lblAscend.Caption := calc.Value;
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
