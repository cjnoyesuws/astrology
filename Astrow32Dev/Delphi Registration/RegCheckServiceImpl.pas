{ Invokable implementation File for TRegCheckService which implements IRegCheckService }

unit RegCheckServiceImpl;

interface

uses InvokeRegistry, Types, XSBuiltIns, RegCheckServiceIntf, sysutils, dateutils, RegCheckSvc;

type

  { TRegCheckService }
  TRegCheckService = class(TInvokableClass, IRegCheckService)
  public
    Function GetRegistrationId(StrProgram,Name,Address,Address2,City,State,Zip,Country,Phone,Email,MayContact : WideString) : WideString; stdcall;
    Function GetRegStartDate(RegId : WideString) : TDateTime;  stdcall;
    Function GetRegEndDate(RegId : WideString) : TDateTime;   stdcall;
    Function GetRegistrationStatus(RegId : WideString) : WideString;  stdcall;
    Function GetRegistrationCodeStr(RegId : WideString) : WideString;  stdcall;
    Function GetRegistrationIdByCompName(StrProgram,CompName,MacAddr : WideString) : WideString; stdcall;
  end;

var

FRegCheckService : TRegCheckService;
FRegCheckServiceInterface : IRegCheckService;
procedure CreateRegCheckService(out obj: TObject);
procedure LogError( sError : String );

implementation



Function TRegCheckService.GetRegistrationId(StrProgram,Name,Address,Address2,City,State,Zip,Country,Phone,Email,MayContact : WideString) : WideString;
begin
   Result := WebModule1.GetId(StrProgram,Name,Address,Address2,City,State,Zip,
     Country,Phone,Email,MayContact);
end;

Function TRegCheckService.GetRegStartDate(RegId : WideString) : TDateTime;
begin
   Result :=WebModule1.RegStartDate(RegId);
end;

Function TRegCheckService.GetRegEndDate(RegId : WideString) : TDateTime;
begin
    Result := WebModule1.RegEndDate(RegId);
end;

Function TRegCheckService.GetRegistrationStatus(RegId : WideString) : WideString;
begin
   if RegId = '' then
   begin
      Result := 'Error: Invalid Registration Information';
      Exit;
   end;
   RegId := Copy(RegId,1,5);
   if RegId = 'INVAL' then
      Result := 'Error: Invalid Registration Information'
   else if RegId='REGUS' then
      result := 'Registered User'
   else if (RegId='DLOAD') or (RegId='ANONY') then
      result := 'Trial Version User'
   else
      Result := 'Error: Invalid Registration Information';
end;

Function TRegCheckService.GetRegistrationCodeStr(RegId : WideString) : WideString;
begin
   Result :=  WebModule1.GetRegString(RegId);
end;

Function TRegCheckService.GetRegistrationIdByCompName(StrProgram,CompName,MacAddr : WideString) : WideString;
begin
   result := WebModule1.GetTheAnonId(StrProgram,CompName,MacAddr);
end;

procedure CreateRegCheckService(out obj: TObject);
begin
  if FRegCheckService = nil then
  begin
    FRegCheckService := TRegCheckService.Create;
    {save a reference to the interface so that the global instance doesn't free itself }
    FRegCheckServiceInterface := FRegCheckService as IRegCheckService;
  end;
  obj := FRegCheckService; { return global instance }
  LogError('Object Created');
end;

procedure LogError( sError : String );
var
   txtf : Textfile;
begin
   AssignFile(txtf,'c:\Errors.log');
   if FileExists('c:\Errors.log') then
      Append( txtf )
   else
      Rewrite( txtf );
   Writeln( txtf, DateToStr(Date) + ' : ' + sError );
   CloseFile(txtf);
   //MessageBox(0,Pchar(sError), PChar('LogError'), MB_OK);
end;



initialization
  { Invokable classes must be registered }
  InvRegistry.RegisterInvokableClass(TRegCheckService, CreateRegCheckService);

end.
