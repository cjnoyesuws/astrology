program Numerow;

uses
  Forms,
  main32 in 'main32.pas' {MainForm},
  about in 'about.pas' {AboutBox},
  Birthdat in 'Birthdat.pas' {frmNumData},
  Childwin in 'Childwin.pas' {frmMDIChild},
  ldrched in 'ldrched.pas',
  NumDll in 'numdll.pas',
  Openf in 'Openf.pas' {frmOpenFile},
  Options in 'Options.pas' {frmOptions},
  Viewtxt in 'Viewtxt.pas' {frmViewText},
  Years in 'Years.pas' {frmNameTrans};

{$R *.RES}

begin
  Application.Title := 'NUMERO UNO For Windows';
  Application.HelpFile := 'NUMEROW.HLP';
  Application.CreateForm(TMainForm, MainForm);
  Application.CreateForm(TAboutBox, AboutBox);
  Application.CreateForm(TfrmNumData, frmNumData);
  Application.CreateForm(TfrmOpenFile, frmOpenFile);
  Application.CreateForm(TfrmOptions, frmOptions);
  Application.CreateForm(TfrmViewText, frmViewText);
  Application.CreateForm(TfrmNameTrans, frmNameTrans);
  Application.Run;
end.
