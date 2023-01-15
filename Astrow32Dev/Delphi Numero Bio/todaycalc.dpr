program todaycalc;

uses
  Forms,
  today in 'today.pas' {TodayPlanForm};

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TTodayPlanForm, TodayPlanForm);
  Application.Run;
end.
