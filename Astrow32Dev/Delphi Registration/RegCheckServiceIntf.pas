{ Invokable interface IRegCheckService }

unit RegCheckServiceIntf;

interface

uses InvokeRegistry, Types, XSBuiltIns;

type

  { Invokable interfaces must derive from IInvokable }
  IRegCheckService = interface(IInvokable)
  ['{D8E8DEA0-9DDC-4E58-A2A2-194935F6C1C2}']
    Function GetRegistrationId(StrProgram,Name,Address,Address2,City,State,Zip,Country,Phone,Email,MayContact  : WideString) : WideString; stdcall;
    Function GetRegistrationIdByCompName(StrProgram,CompName,MacAddr : WideString) : WideString; stdcall;
    Function GetRegStartDate(RegId : WideString) : TDateTime;  stdcall;
    Function GetRegEndDate(RegId : WideString) : TDateTime;   stdcall;
    Function GetRegistrationStatus(RegId : WideString) : WideString;  stdcall;
    Function GetRegistrationCodeStr(RegId : WideString) : WideString;  stdcall;
    { Methods of Invokable interface must not use the default }
    { calling convention; stdcall is recommended }
  end;

implementation

initialization
  { Invokable interfaces must be registered }
  InvRegistry.RegisterInterface(TypeInfo(IRegCheckService));

end.
 