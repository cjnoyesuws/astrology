program ephemeris;

uses
  Forms,
  ephform in 'ephform.pas' {EphemForm},
  _instcalc_TLB in '_instcalc_TLB.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.Title := 'Ephemeris';
  Application.CreateForm(TEphemForm, EphemForm);
  Application.Run;
end.
