program wstester;

uses
  Forms,
  wstestform in 'wstestform.pas' {Form1},
  RegCheckServiceIntf in 'RegCheckServiceIntf.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
