library RegCheckService;

uses
  ActiveX,
  ComObj,
  WebBroker,
  ISAPIApp,
  ISAPIThreadPool,
  RegCheckSvc in 'RegCheckSvc.pas' {WebModule1: TWebModule},
  RegCheckServiceImpl in 'RegCheckServiceImpl.pas',
  RegCheckServiceIntf in 'RegCheckServiceIntf.pas';

{$R *.RES}

exports
  GetExtensionVersion,
  HttpExtensionProc,
  TerminateExtension;

begin
  CoInitFlags := COINIT_MULTITHREADED;
  Application.Initialize;
  Application.CreateForm(TWebModule1, WebModule1);
  Application.Run;
end.
