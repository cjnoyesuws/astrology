program Setreg;

uses
  Forms,
  Sreg in 'SREG.PAS' {frmSReg};

{$R *.RES}

begin
  Application.Title := 'Setup Registration Code';
  Application.CreateForm(TfrmSReg, frmSReg);
  Application.Run;
end.
