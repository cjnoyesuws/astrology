unit calc;

{$WARN SYMBOL_PLATFORM OFF}

interface

uses
  ComObj, ActiveX, instcalc_TLB, StdVcl;

type
  TAstInstCalc = class(TAutoObject, IAstInstCalc)
  protected
    function Get_Index: Integer; safecall;
    function Get_Value: OleVariant; safecall;
    procedure Set_Index(Value: Integer); safecall;
    procedure StartAt(month, day, year, hour: Integer); safecall;
    { Protected declarations }
  end;

implementation

uses ComServ;

function TAstInstCalc.Get_Index: Integer;
begin
   Result := 1;
end;

function TAstInstCalc.Get_Value: OleVariant;
begin
   Result := '10ARI33';
end;

procedure TAstInstCalc.Set_Index(Value: Integer);
begin

end;

procedure TAstInstCalc.StartAt(month, day, year, hour: Integer);
begin

end;

initialization
  TAutoObjectFactory.Create(ComServer, TAstInstCalc, Class_AstInstCalc,
    ciMultiInstance, tmApartment);
end.
