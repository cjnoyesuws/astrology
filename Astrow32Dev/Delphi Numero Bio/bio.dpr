program bio;

uses
  Forms,
  biochart in 'biochart.pas' {BioForm},
  DBConfig in 'DBConfig.pas',
  inheritedregistry in 'inheritedregistry.pas',
  dbmaint in 'dbmaint.pas' {DbMaintForm},
  demo in 'demo.pas' {demofrm},
  biocalc_TLB in '..\Biocalc\biocalc_TLB.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.Title := 'Instant Biorythms for Windows';
  Application.CreateForm(TBioForm, BioForm);
  Application.Run;
end.
