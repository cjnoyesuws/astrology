program regchecksvccgi;

{$APPTYPE CONSOLE}

uses
  WebBroker,
  CGIApp,
  RegCheckServiceImpl in 'RegCheckServiceImpl.pas',
  RegCheckServiceIntf in 'RegCheckServiceIntf.pas',
  RegCheckSvc in 'RegCheckSvc.pas' {WebModule1: TWebModule};

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TWebModule1, WebModule1);
  Application.Run;
end.
