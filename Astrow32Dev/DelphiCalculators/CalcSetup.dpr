program CalcSetup;

uses
  Forms,
  setup in 'setup.pas' {CalcSetupForm},
  inheritedregistry in 'inheritedregistry.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TCalcSetupForm, CalcSetupForm);
  Application.Run;
end.
