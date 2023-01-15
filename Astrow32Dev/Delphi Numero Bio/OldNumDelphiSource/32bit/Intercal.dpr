program Intercal;

uses
  Forms,
  Calendar in '..\Calendar.pas' {frmCal},
  Numbers in '..\Numbers.pas',
  PerpCal in '..\Perpcal.pas',
  poputxt in '..\poputxt.pas' {frmPopupText},
  Demo in '..\demo.pas' {demofrm},
  numerocalc_TLB in '..\..\numerocalc_TLB.pas';

{$R *.RES}

begin
{$IFDEF WIN32} Application.Initialize; {$ENDIF}
  Application.Title := 'Interactive Calendar For Windows';
  Application.HelpFile := 'Numero.hlp';
  Application.CreateForm(TfrmCal, frmCal);
  Application.CreateForm(TfrmPopupText, frmPopupText);
  Application.CreateForm(Tdemofrm, demofrm);
  Application.Run;
end.
