program activate;

uses
  Forms,
  activatefrm in 'activatefrm.pas' {ActivateForm},
  RegCheckServiceIntf in 'RegCheckServiceIntf.pas',
  inheritedregistry in 'inheritedregistry.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TActivateForm, ActivateForm);
  Application.Run;
end.
