program Project1;

uses
  Forms,
  Birthdat in 'Birthdat.pas' {frmNumData},
  Openf in 'Openf.pas' {frmOpenFile},
  Years in 'Years.pas' {frmNameTrans},
  Options in 'Options.pas' {frmOptions},
  Viewtxt in 'Viewtxt.pas' {frmViewText},
  ldrched in 'ldrched.pas',
  NameTrVw in 'nametrvw.pas' {frmNameTrVw},
  birtnum in 'birtnum.pas' {frmBirthNum};

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TfrmViewText, frmViewText);
  Application.Run;
end.
