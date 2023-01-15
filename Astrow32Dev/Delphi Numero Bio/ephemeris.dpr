program ephemeris;

uses
  Forms,
  ephform in 'ephform.pas' {EphemForm};

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TEphemForm, EphemForm);
  Application.Run;
end.
