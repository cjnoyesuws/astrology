program NUMEROW;

uses
  Forms,
  main32 in '\NUMEROW\main32.pas' {MainForm},
  about in '\NUMEROW\about.pas' {AboutBox},
  ldrched in '\NUMEROW\ldrched.pas',
  NumDll in '\NUMEROW\numdll.pas',
  Openf in '\NUMEROW\Openf.pas' {frmOpenFile},
  Options in '\NUMEROW\Options.pas' {frmOptions},
  Viewtxt in '\NUMEROW\Viewtxt.pas' {frmViewText},
  Birthdat in '\NUMEROW\Birthdat.pas' {frmNumData},
  Years in '\NUMEROW\Years.pas' {frmNameTrans},
  Demo in '\NUMEROW\demo.pas' {demofrm},
  Childwin in '\NUMEROW\Childwin.pas' {MDIChild};

{$R *.RES}

begin
  Application.Title := 'Numero Uno For Windows';
  Application.HelpFile := 'Numerow.HLP';
  Application.ShowHint := True;
  Application.CreateForm(TMainForm, MainForm);
  Application.CreateForm(TAboutBox, AboutBox);
  Application.CreateForm(TfrmOpenFile, frmOpenFile);
  Application.CreateForm(TfrmOptions, frmOptions);
  Application.CreateForm(TfrmNumData, frmNumData);
  Application.CreateForm(TfrmNameTrans, frmNameTrans);
  Application.CreateForm(Tdemofrm, demofrm);
  Application.Run;
end.
