program instastr;

uses
  Forms,
  astcalc in 'astcalc.pas' {InstCalcForm},
  instcalc_TLB in 'instcalc_TLB.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TInstCalcForm, InstCalcForm);
  Application.Run;
end.
