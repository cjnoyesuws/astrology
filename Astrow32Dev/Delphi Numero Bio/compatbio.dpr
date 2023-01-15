program compatbio;

uses
  Forms,
  compatbiochart in 'compatbiochart.pas' {CompatBioForm},
  biocalc_TLB in 'biocalc_TLB.pas',
  DBConfig in 'DBConfig.pas',
  inheritedregistry in 'inheritedregistry.pas',
  dbmaint in 'dbmaint.pas' {DbMaintForm},
  Demo in 'demo.pas' {demofrm};

{$R *.res}

begin
  Application.Initialize;
  Application.Title := 'Instant Compatibility Biorythms';
  Application.CreateForm(TCompatBioForm, CompatBioForm);
  Application.Run;
end.
