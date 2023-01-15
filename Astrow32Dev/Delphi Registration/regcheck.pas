unit regcheck;

{$WARN SYMBOL_PLATFORM OFF}

interface

uses
  Windows, ActiveX, Classes, ComObj, RegChecker_TLB, StdVcl, registry,
  inheritedregistry, sysutils, dateutils;

type
  TRegistrationChecker = class(TTypedComObject, IRegistrationChecker)
  protected
    function Get_DaysLeft(out Value: Smallint): HResult; stdcall;
    function Get_Status(out Value: WideString): HResult; stdcall;
    function Set_ProgramName(const Param1: WideString): HResult; stdcall;
    function Set_Shareware(Value: Smallint): HResult; stdcall;
    function Set_Suite(Value: Smallint): HResult; stdcall;
  private
    FSuite : Boolean;
    FProgramName : String;
    FShareware : Boolean;
    FStatus : String;
    FDaysLeft : SmallInt;
    FReg : TInheritedRegistry;
    FChecked : Boolean;
    procedure DoCheck;
  public
    constructor Create;
    destructor  Destroy; override;
  end;

implementation

uses ComServ;

function TRegistrationChecker.Get_DaysLeft(out Value: Smallint): HResult;
begin
   if not FChecked then
      DoCheck;
   Value := FDaysLeft;
   Result := S_OK;
end;

function TRegistrationChecker.Get_Status(out Value: WideString): HResult;
begin
   if not FChecked then
      DoCheck;
   Value := FStatus;
   Result := S_OK;
end;

function TRegistrationChecker.Set_ProgramName(
  const Param1: WideString): HResult;
begin
  FProgramName := Param1;
  FChecked := False;
  Result := S_OK;
end;

function TRegistrationChecker.Set_Shareware(Value: Smallint): HResult;
begin
   FSuite := (Value<>0);
   FChecked := False;
   Result := S_OK;
end;

function TRegistrationChecker.Set_Suite(Value: Smallint): HResult;
begin
   FSuite := (Value<>0);
   FChecked := False;
   Result := S_OK;
end;

constructor TRegistrationChecker.Create;
begin
   inherited Create;
   FProgramName := 'Astro For Windows';
   FSuite := False;
   FShareware := True;
   FStatus := 'Unknown';
   FDaysLeft := 0;
   FChecked := False;
end;

Destructor TRegistrationChecker.Destroy;
begin
   if Assigned(FReg) then
      FReg.Free;
   inherited Destroy;
end;

Procedure TRegistrationChecker.DoCheck;
var
   RegString : String;
   dtStart, dtEnd : TDateTime;
   nLen, iIndex : integer;
   bHex : Boolean;
begin
   if Assigned(FReg) then
      FReg.Free
   else
      FReg := TInheritedRegistry.Create(FProgramName);
   if not FReg.Open('Registration', False, FSuite) then
   begin
      FDaysLeft := -1;
      FStatus := 'This Product is Not Registered For use';
   end else
   begin
      dtStart := FReg.ReadDate('RegisterStart',0);
      dtEnd   := FReg.ReadDate('RegisterEnd',0);
      RegString := FReg.ReadString('RegisteredCodeString','NoReg');
      nlen := Length(RegString);
      bHex := True;
      for iIndex := 1 to nLen do
         if not (RegString[iIndex] in ['A'..'Z','a'..'z','0'..'9']) then
            bHex := False;
      if ( dtStart = 0 ) or ( dtEnd = 0 ) then
      begin
         FDaysLeft := -1;
         FStatus := 'This Product is Not Registered For use';
      end else if date < dtStart then
      begin
         FDaysLeft := -1;
         FStatus := 'System Date Set Before Start of Registration, Invalid, Program Can''t Run';
      end else if (RegString <> 'NoReg') and (nLen < 20) and (not bHex) then
      begin
         FDaysLeft := -1;
         FStatus := 'Illegal Registration String, Program Can''t Run';
      end else if (date > dtEnd) and (RegString = 'NoReg') then
      begin
         FDaysLeft := 0;
         FStatus := 'Trial Days Have Expired, Program Can''t Run';
      end else if (date > dtEnd) and (RegString <> 'NoReg') then
      begin
         FDaysLeft := 0;
         FStatus := 'You Need to Renew Your Registration, Program Can''t Run';
      end else if (date > dtEnd) and (RegString = 'NoReg') then
      begin
         FDaysLeft := DaysBetween(dtEnd, Date);
         FStatus := 'You Have ' + IntToStr(FDaysLeft) + ' Trial Days Left of Use';
      end else if (date > dtEnd) and (RegString = 'NoReg') then
      begin
         FDaysLeft :=  DaysBetween(dtEnd, Date);
         FStatus := 'Program is Registered';
      end;
   end;
   FChecked := True;
end;

initialization
  TTypedComObjectFactory.Create(ComServer, TRegistrationChecker, Class_RegistrationChecker,
    ciSingleInstance, tmApartment);
end.
