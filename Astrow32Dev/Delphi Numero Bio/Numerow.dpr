program Numerow;

uses
  Forms,
  numerowmain in 'numerowmain.pas' {NumeroMain},
  About in 'About.pas' {AboutBox},
  numerocalc_TLB in 'numerocalc_TLB.pas',
  DmNumerow in 'DmNumerow.pas' {DmNumerow: TDataModule},
  ChartSelector in 'ChartSelector.pas' {ChartSelectorForm},
  DBConfig in 'DBConfig.pas',
  inheritedregistry in 'inheritedregistry.pas',
  Demo in 'demo.pas' {demofrm},
  poputxt in 'poputxt.pas' {frmPopupText},
  NumDbMaint in 'NumDbMaint.pas' {NumDBMaintForm},
  numchart in 'numchart.pas' {NumChartForm};

{$R *.RES}

begin
  Application.Initialize;
  Application.CreateForm(TNumeroMain, NumeroMain);
  Application.CreateForm(TAboutBox, AboutBox);
  Application.CreateForm(TDmNumerow, aDmNumerow);
  Application.CreateForm(TNumChartForm, NumChartForm);
  Application.Run;
end.
 
