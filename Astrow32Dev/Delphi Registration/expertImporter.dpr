program expertImporter;

uses
  Forms,
  expimp in 'expimp.pas' {ExpImpForm},
  inheritedregistry in 'inheritedregistry.pas',
  DBConfig in 'DBConfig.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TExpImpForm, ExpImpForm);
  Application.Run;
end.
