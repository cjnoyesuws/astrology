unit _instcalc_TLB;

// ************************************************************************ //
// WARNING                                                                    
// -------                                                                    
// The types declared in this file were generated from data read from a       
// Type Library. If this type library is explicitly or indirectly (via        
// another type library referring to this type library) re-imported, or the   
// 'Refresh' command of the Type Library Editor activated while editing the   
// Type Library, the contents of this file will be regenerated and all        
// manual modifications will be lost.                                         
// ************************************************************************ //

// PASTLWTR : $Revision:   1.130.1.0.1.0.1.6  $
// File generated on 9/2/2005 10:49:01 AM from Type Library described below.

// ************************************************************************  //
// Type Lib: C:\cjnoyessw\_instcalc.tlb (1)
// LIBID: {C4EF3B73-E7FA-46F1-9DCE-EBBA34FC2CAF}
// LCID: 0
// Helpfile: 
// DepndLst: 
//   (1) v2.0 stdole, (C:\WINDOWS\system32\STDOLE2.TLB)
//   (2) v4.0 StdVCL, (C:\WINDOWS\system32\stdvcl40.dll)
// Errors:
//   Error creating palette bitmap of (TCAstInstCalc) : No Server registered for this CoClass
// ************************************************************************ //
// *************************************************************************//
// NOTE:                                                                      
// Items guarded by $IFDEF_LIVE_SERVER_AT_DESIGN_TIME are used by properties  
// which return objects that may need to be explicitly created via a function 
// call prior to any access via the property. These items have been disabled  
// in order to prevent accidental use from within the object inspector. You   
// may enable them by defining LIVE_SERVER_AT_DESIGN_TIME or by selectively   
// removing them from the $IFDEF blocks. However, such items must still be    
// programmatically created via a method of the appropriate CoClass before    
// they can be used.                                                          
{$TYPEDADDRESS OFF} // Unit must be compiled without type-checked pointers. 
{$WARN SYMBOL_PLATFORM OFF}
{$WRITEABLECONST ON}
{$VARPROPSETTER ON}
interface

uses Windows, ActiveX, Classes, Graphics, OleServer, StdVCL, Variants;
  

// *********************************************************************//
// GUIDS declared in the TypeLibrary. Following prefixes are used:        
//   Type Libraries     : LIBID_xxxx                                      
//   CoClasses          : CLASS_xxxx                                      
//   DISPInterfaces     : DIID_xxxx                                       
//   Non-DISP interfaces: IID_xxxx                                        
// *********************************************************************//
const
  // TypeLibrary Major and minor versions
  instcalcMajorVersion = 1;
  instcalcMinorVersion = 0;

  LIBID_instcalc: TGUID = '{C4EF3B73-E7FA-46F1-9DCE-EBBA34FC2CAF}';

  IID_IAstInstCalc: TGUID = '{AE6B81CB-38A6-4171-B2F2-A1F47658EEE4}';
  CLASS_CAstInstCalc: TGUID = '{53F0DCB8-C083-4931-B261-2D15BE63035D}';
type

// *********************************************************************//
// Forward declaration of types defined in TypeLibrary                    
// *********************************************************************//
  IAstInstCalc = interface;
  IAstInstCalcDisp = dispinterface;

// *********************************************************************//
// Declaration of CoClasses defined in Type Library                       
// (NOTE: Here we map each CoClass to its Default Interface)              
// *********************************************************************//
  CAstInstCalc = IAstInstCalc;


// *********************************************************************//
// Interface: IAstInstCalc
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {AE6B81CB-38A6-4171-B2F2-A1F47658EEE4}
// *********************************************************************//
  IAstInstCalc = interface(IDispatch)
    ['{AE6B81CB-38A6-4171-B2F2-A1F47658EEE4}']
    function Get_Value: OleVariant; safecall;
    procedure Set_Index(Param1: Integer); safecall;
    procedure StartAt(month: Integer; day: Integer; year: Integer; hour: Integer); safecall;
    property Value: OleVariant read Get_Value;
    property Index: Integer write Set_Index;
  end;

// *********************************************************************//
// DispIntf:  IAstInstCalcDisp
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {AE6B81CB-38A6-4171-B2F2-A1F47658EEE4}
// *********************************************************************//
  IAstInstCalcDisp = dispinterface
    ['{AE6B81CB-38A6-4171-B2F2-A1F47658EEE4}']
    property Value: OleVariant readonly dispid 1;
    property Index: Integer writeonly dispid 2;
    procedure StartAt(month: Integer; day: Integer; year: Integer; hour: Integer); dispid 3;
  end;

// *********************************************************************//
// The Class CoCAstInstCalc provides a Create and CreateRemote method to          
// create instances of the default interface IAstInstCalc exposed by              
// the CoClass CAstInstCalc. The functions are intended to be used by             
// clients wishing to automate the CoClass objects exposed by the         
// server of this typelibrary.                                            
// *********************************************************************//
  CoCAstInstCalc = class
    class function Create: IAstInstCalc;
    class function CreateRemote(const MachineName: string): IAstInstCalc;
  end;


// *********************************************************************//
// OLE Server Proxy class declaration
// Server Object    : TCAstInstCalc
// Help String      : AstInstCalc Class
// Default Interface: IAstInstCalc
// Def. Intf. DISP? : No
// Event   Interface: 
// TypeFlags        : (2) CanCreate
// *********************************************************************//
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  TCAstInstCalcProperties= class;
{$ENDIF}
  TCAstInstCalc = class(TOleServer)
  private
    FIntf:        IAstInstCalc;
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
    FProps:       TCAstInstCalcProperties;
    function      GetServerProperties: TCAstInstCalcProperties;
{$ENDIF}
    function      GetDefaultInterface: IAstInstCalc;
  protected
    procedure InitServerData; override;
    function Get_Value: OleVariant;
    procedure Set_Index(Param1: Integer);
  public
    constructor Create(AOwner: TComponent); override;
    destructor  Destroy; override;
    procedure Connect; override;
    procedure ConnectTo(svrIntf: IAstInstCalc);
    procedure Disconnect; override;
    procedure StartAt(month: Integer; day: Integer; year: Integer; hour: Integer);
    property DefaultInterface: IAstInstCalc read GetDefaultInterface;
    property Value: OleVariant read Get_Value;
    property Index: Integer write Set_Index;
  published
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
    property Server: TCAstInstCalcProperties read GetServerProperties;
{$ENDIF}
  end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
// *********************************************************************//
// OLE Server Properties Proxy Class
// Server Object    : TCAstInstCalc
// (This object is used by the IDE's Property Inspector to allow editing
//  of the properties of this server)
// *********************************************************************//
 TCAstInstCalcProperties = class(TPersistent)
  private
    FServer:    TCAstInstCalc;
    function    GetDefaultInterface: IAstInstCalc;
    constructor Create(AServer: TCAstInstCalc);
  protected
    function Get_Value: OleVariant;
    procedure Set_Index(Param1: Integer);
  public
    property DefaultInterface: IAstInstCalc read GetDefaultInterface;
  published
  end;
{$ENDIF}


procedure Register;

resourcestring
  dtlServerPage = 'ActiveX';

implementation

uses ComObj;

class function CoCAstInstCalc.Create: IAstInstCalc;
begin
  Result := CreateComObject(CLASS_CAstInstCalc) as IAstInstCalc;
end;

class function CoCAstInstCalc.CreateRemote(const MachineName: string): IAstInstCalc;
begin
  Result := CreateRemoteComObject(MachineName, CLASS_CAstInstCalc) as IAstInstCalc;
end;

procedure TCAstInstCalc.InitServerData;
const
  CServerData: TServerData = (
    ClassID:   '{53F0DCB8-C083-4931-B261-2D15BE63035D}';
    IntfIID:   '{AE6B81CB-38A6-4171-B2F2-A1F47658EEE4}';
    EventIID:  '';
    LicenseKey: nil;
    Version: 500);
begin
  ServerData := @CServerData;
end;

procedure TCAstInstCalc.Connect;
var
  punk: IUnknown;
begin
  if FIntf = nil then
  begin
    punk := GetServer;
    Fintf:= punk as IAstInstCalc;
  end;
end;

procedure TCAstInstCalc.ConnectTo(svrIntf: IAstInstCalc);
begin
  Disconnect;
  FIntf := svrIntf;
end;

procedure TCAstInstCalc.DisConnect;
begin
  if Fintf <> nil then
  begin
    FIntf := nil;
  end;
end;

function TCAstInstCalc.GetDefaultInterface: IAstInstCalc;
begin
  if FIntf = nil then
    Connect;
  Assert(FIntf <> nil, 'DefaultInterface is NULL. Component is not connected to Server. You must call ''Connect'' or ''ConnectTo'' before this operation');
  Result := FIntf;
end;

constructor TCAstInstCalc.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  FProps := TCAstInstCalcProperties.Create(Self);
{$ENDIF}
end;

destructor TCAstInstCalc.Destroy;
begin
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  FProps.Free;
{$ENDIF}
  inherited Destroy;
end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
function TCAstInstCalc.GetServerProperties: TCAstInstCalcProperties;
begin
  Result := FProps;
end;
{$ENDIF}

function TCAstInstCalc.Get_Value: OleVariant;
var
  InterfaceVariant : OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  Result := InterfaceVariant.Value;
end;

procedure TCAstInstCalc.Set_Index(Param1: Integer);
begin
  Exit;
end;

procedure TCAstInstCalc.StartAt(month: Integer; day: Integer; year: Integer; hour: Integer);
begin
  DefaultInterface.StartAt(month, day, year, hour);
end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
constructor TCAstInstCalcProperties.Create(AServer: TCAstInstCalc);
begin
  inherited Create;
  FServer := AServer;
end;

function TCAstInstCalcProperties.GetDefaultInterface: IAstInstCalc;
begin
  Result := FServer.DefaultInterface;
end;

function TCAstInstCalcProperties.Get_Value: OleVariant;
var
  InterfaceVariant : OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  Result := InterfaceVariant.Value;
end;

procedure TCAstInstCalcProperties.Set_Index(Param1: Integer);
begin
  Exit;
end;

{$ENDIF}

procedure Register;
begin
  RegisterComponents(dtlServerPage, [TCAstInstCalc]);
end;

end.
