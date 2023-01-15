library instcalc;

uses
  ComServ,
  instcalc_TLB in 'instcalc_TLB.pas',
  calc in 'calc.pas' {AstInstCalc: CoClass};

exports
  DllGetClassObject,
  DllCanUnloadNow,
  DllRegisterServer,
  DllUnregisterServer;

{$R *.TLB}

{$R *.RES}

begin
end.
