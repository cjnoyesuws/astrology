library RegChecker;

uses
  ComServ,
  RegChecker_TLB in 'RegChecker_TLB.pas',
  regcheck in 'regcheck.pas' {RegistrationChecker: CoClass};

exports
  DllGetClassObject,
  DllCanUnloadNow,
  DllRegisterServer,
  DllUnregisterServer;

{$R *.TLB}

{$R *.RES}

begin
end.
