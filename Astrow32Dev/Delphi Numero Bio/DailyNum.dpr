program DailyNum;

uses
  Forms,
  birth in 'birth.pas' {frmBirth},
  Num in 'Num.pas' {frmNum},
  Numbers in 'Numbers.pas',
  poputxt in 'poputxt.pas' {frmPopupText},
  Demo in 'demo.pas' {demofrm};

{$R *.RES}

begin
  Application.Initialize;
  Application.Title := 'Daily Numbers For Windows';
  Application.HelpFile := 'Numero.Hlp';
  Application.CreateForm(TfrmNum, frmNum);
  Application.CreateForm(TfrmBirth, frmBirth);
  Application.CreateForm(TfrmPopupText, frmPopupText);
  Application.CreateForm(Tdemofrm, demofrm);
  Application.Run;
end.
