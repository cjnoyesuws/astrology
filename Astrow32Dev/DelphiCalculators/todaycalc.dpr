program todaycalc;

uses
  Forms,
  today in 'today.pas' {TodayPlanForm},
  inheritedregistry in 'inheritedregistry.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TTodayPlanForm, TodayPlanForm);
  Application.Run;
end.
