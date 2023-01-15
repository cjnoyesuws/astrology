program instastr;

uses
  Forms,
  astcalc in 'astcalc.pas' {InstCalcForm},
  _instcalc_TLB in '_instcalc_TLB.pas',
  inheritedregistry in 'inheritedregistry.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TInstCalcForm, InstCalcForm);
  Application.Run;
end.
