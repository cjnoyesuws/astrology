program expertImporter;

uses
  Forms,
  inheritedregistry in '..\Delphi Registration\inheritedregistry.pas',
  DBConfig in '..\Delphi Registration\DBConfig.pas',
  expimp in 'expimp.pas' {ExpImpForm};

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TExpImpForm, ExpImpForm);
  Application.Run;
end.
