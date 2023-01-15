unit numerocalc_TLB;

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
// File generated on 9/5/2005 3:32:05 PM from Type Library described below.

// ************************************************************************  //
// Type Lib: C:\cjnoyessw\numerocalc.dll (1)
// LIBID: {96EE2450-3081-450C-B99C-719AB1A784F7}
// LCID: 0
// Helpfile: 
// DepndLst: 
//   (1) v2.0 stdole, (C:\WINDOWS\system32\STDOLE2.TLB)
//   (2) v4.0 StdVCL, (C:\WINDOWS\system32\stdvcl40.dll)
// Errors:
//   Hint: Parameter 'file' of INumerowCalcer.CalcChart changed to 'file_'
//   Hint: Parameter 'type' of INumerowCalcer.CalcChart changed to 'type_'
//   Hint: Parameter 'type' of INumerowCalcer.ConvertFile changed to 'type_'
//   Error creating palette bitmap of (TCNumerowCalcer) : Server C:\cjnoyessw\numerocalc.dll contains no icons
//   Error creating palette bitmap of (TCTextGetter) : Server C:\cjnoyessw\numerocalc.dll contains no icons
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
  numerocalcMajorVersion = 1;
  numerocalcMinorVersion = 0;

  LIBID_numerocalc: TGUID = '{96EE2450-3081-450C-B99C-719AB1A784F7}';

  IID_INumerowCalcer: TGUID = '{B480AEC1-0F33-49B2-AF97-C89DBD206D32}';
  CLASS_CNumerowCalcer: TGUID = '{C2875FFB-F20C-46D6-8701-3FC4E1AC2FA2}';
  IID_ITextGetter: TGUID = '{74EAD860-7971-4E4D-B7CD-1C9C9F96B854}';
  CLASS_CTextGetter: TGUID = '{9654336F-86B5-4970-821A-4DDFDE04EB0E}';
type

// *********************************************************************//
// Forward declaration of types defined in TypeLibrary                    
// *********************************************************************//
  INumerowCalcer = interface;
  INumerowCalcerDisp = dispinterface;
  ITextGetter = interface;
  ITextGetterDisp = dispinterface;

// *********************************************************************//
// Declaration of CoClasses defined in Type Library                       
// (NOTE: Here we map each CoClass to its Default Interface)              
// *********************************************************************//
  CNumerowCalcer = INumerowCalcer;
  CTextGetter = ITextGetter;


// *********************************************************************//
// Declaration of structures, unions and aliases.                         
// *********************************************************************//
  PShortint1 = ^Shortint; {*}


// *********************************************************************//
// Interface: INumerowCalcer
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {B480AEC1-0F33-49B2-AF97-C89DBD206D32}
// *********************************************************************//
  INumerowCalcer = interface(IDispatch)
    ['{B480AEC1-0F33-49B2-AF97-C89DBD206D32}']
    procedure Set_Index(Param1: Smallint); safecall;
    procedure Set_FirstName(const Param1: WideString); safecall;
    procedure Set_MiddleName(const Param1: WideString); safecall;
    procedure Set_LastName(const Param1: WideString); safecall;
    procedure Set_BirthDate(Param1: TDateTime); safecall;
    procedure CalcChart(var file_: PChar; var person: PChar; var comments: PChar; 
                        var type_: PChar; typecode: Smallint); safecall;
    procedure Set_TransStart(Param1: Smallint); safecall;
    procedure Set_TransEnd(Param1: Smallint); safecall;
    procedure Set_FontName(const Param1: WideString); safecall;
    procedure Set_FontSize(Param1: Smallint); safecall;
    procedure Set_FontCodes(Param1: Smallint); safecall;
    procedure Set_FontColor(Param1: LongWord); safecall;
    procedure Set_LeftMargin(Param1: Smallint); safecall;
    procedure Set_TextWidth(Param1: Smallint); safecall;
    procedure Set_DemoMode(Param1: Smallint); safecall;
    procedure ConvertFile(var in_name: PChar; var out_name: PChar; type_: Smallint); safecall;
    property Index: Smallint write Set_Index;
    property FirstName: WideString write Set_FirstName;
    property MiddleName: WideString write Set_MiddleName;
    property LastName: WideString write Set_LastName;
    property BirthDate: TDateTime write Set_BirthDate;
    property TransStart: Smallint write Set_TransStart;
    property TransEnd: Smallint write Set_TransEnd;
    property FontName: WideString write Set_FontName;
    property FontSize: Smallint write Set_FontSize;
    property FontCodes: Smallint write Set_FontCodes;
    property FontColor: LongWord write Set_FontColor;
    property LeftMargin: Smallint write Set_LeftMargin;
    property TextWidth: Smallint write Set_TextWidth;
    property DemoMode: Smallint write Set_DemoMode;
  end;

// *********************************************************************//
// DispIntf:  INumerowCalcerDisp
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {B480AEC1-0F33-49B2-AF97-C89DBD206D32}
// *********************************************************************//
  INumerowCalcerDisp = dispinterface
    ['{B480AEC1-0F33-49B2-AF97-C89DBD206D32}']
    property Index: Smallint writeonly dispid 1;
    property FirstName: WideString writeonly dispid 2;
    property MiddleName: WideString writeonly dispid 3;
    property LastName: WideString writeonly dispid 4;
    property BirthDate: TDateTime writeonly dispid 5;
    procedure CalcChart( file_: OleVariant;  person: OleVariant;
                         comments: OleVariant; type_: OleVariant;
                        typecode: Smallint); dispid 6;
    property TransStart: Smallint writeonly dispid 7;
    property TransEnd: Smallint writeonly dispid 8;
    property FontName: WideString writeonly dispid 9;
    property FontSize: Smallint writeonly dispid 10;
    property FontCodes: Smallint writeonly dispid 11;
    property FontColor: LongWord writeonly dispid 12;
    property LeftMargin: Smallint writeonly dispid 13;
    property TextWidth: Smallint writeonly dispid 14;
    property DemoMode: Smallint writeonly dispid 15;
    procedure ConvertFile(in_name: OleVariant;
                          out_name: OleVariant; type_: Smallint); dispid 16;
  end;

// *********************************************************************//
// Interface: ITextGetter
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {74EAD860-7971-4E4D-B7CD-1C9C9F96B854}
// *********************************************************************//
  ITextGetter = interface(IDispatch)
    ['{74EAD860-7971-4E4D-B7CD-1C9C9F96B854}']
    procedure Set_Row(Param1: Smallint); safecall;
    procedure Set_Col(Param1: Smallint); safecall;
    function Get_Text: WideString; safecall;
    property Row: Smallint write Set_Row;
    property Col: Smallint write Set_Col;
    property Text: WideString read Get_Text;
  end;

// *********************************************************************//
// DispIntf:  ITextGetterDisp
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {74EAD860-7971-4E4D-B7CD-1C9C9F96B854}
// *********************************************************************//
  ITextGetterDisp = dispinterface
    ['{74EAD860-7971-4E4D-B7CD-1C9C9F96B854}']
    property Row: Smallint writeonly dispid 1;
    property Col: Smallint writeonly dispid 2;
    property Text: WideString readonly dispid 3;
  end;

// *********************************************************************//
// The Class CoCNumerowCalcer provides a Create and CreateRemote method to          
// create instances of the default interface INumerowCalcer exposed by              
// the CoClass CNumerowCalcer. The functions are intended to be used by             
// clients wishing to automate the CoClass objects exposed by the         
// server of this typelibrary.                                            
// *********************************************************************//
  CoCNumerowCalcer = class
    class function Create: INumerowCalcer;
    class function CreateRemote(const MachineName: string): INumerowCalcer;
  end;


// *********************************************************************//
// OLE Server Proxy class declaration
// Server Object    : TCNumerowCalcer
// Help String      : NumerowCalcer Class
// Default Interface: INumerowCalcer
// Def. Intf. DISP? : No
// Event   Interface: 
// TypeFlags        : (2) CanCreate
// *********************************************************************//
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  TCNumerowCalcerProperties= class;
{$ENDIF}
  TCNumerowCalcer = class(TOleServer)
  private
    FIntf:        INumerowCalcer;
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
    FProps:       TCNumerowCalcerProperties;
    function      GetServerProperties: TCNumerowCalcerProperties;
{$ENDIF}
    function      GetDefaultInterface: INumerowCalcer;
  protected
    procedure InitServerData; override;
    procedure Set_Index(Param1: Smallint);
    procedure Set_FirstName(const Param1: WideString);
    procedure Set_MiddleName(const Param1: WideString);
    procedure Set_LastName(const Param1: WideString);
    procedure Set_BirthDate(Param1: TDateTime);
    procedure Set_TransStart(Param1: Smallint);
    procedure Set_TransEnd(Param1: Smallint);
    procedure Set_FontName(const Param1: WideString);
    procedure Set_FontSize(Param1: Smallint);
    procedure Set_FontCodes(Param1: Smallint);
    procedure Set_FontColor(Param1: LongWord);
    procedure Set_LeftMargin(Param1: Smallint);
    procedure Set_TextWidth(Param1: Smallint);
    procedure Set_DemoMode(Param1: Smallint);
  public
    constructor Create(AOwner: TComponent); override;
    destructor  Destroy; override;
    procedure Connect; override;
    procedure ConnectTo(svrIntf: INumerowCalcer);
    procedure Disconnect; override;
    procedure CalcChart(var file_: PChar; var person: PChar; var comments: PChar; 
                        var type_: PChar; typecode: Smallint);
    procedure ConvertFile(var in_name: PChar; var out_name: PChar; type_: Smallint);
    property DefaultInterface: INumerowCalcer read GetDefaultInterface;
    property Index: Smallint write Set_Index;
    property FirstName: WideString write Set_FirstName;
    property MiddleName: WideString write Set_MiddleName;
    property LastName: WideString write Set_LastName;
    property BirthDate: TDateTime write Set_BirthDate;
    property TransStart: Smallint write Set_TransStart;
    property TransEnd: Smallint write Set_TransEnd;
    property FontName: WideString write Set_FontName;
    property FontSize: Smallint write Set_FontSize;
    property FontCodes: Smallint write Set_FontCodes;
    property FontColor: LongWord write Set_FontColor;
    property LeftMargin: Smallint write Set_LeftMargin;
    property TextWidth: Smallint write Set_TextWidth;
    property DemoMode: Smallint write Set_DemoMode;
  published
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
    property Server: TCNumerowCalcerProperties read GetServerProperties;
{$ENDIF}
  end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
// *********************************************************************//
// OLE Server Properties Proxy Class
// Server Object    : TCNumerowCalcer
// (This object is used by the IDE's Property Inspector to allow editing
//  of the properties of this server)
// *********************************************************************//
 TCNumerowCalcerProperties = class(TPersistent)
  private
    FServer:    TCNumerowCalcer;
    function    GetDefaultInterface: INumerowCalcer;
    constructor Create(AServer: TCNumerowCalcer);
  protected
    procedure Set_Index(Param1: Smallint);
    procedure Set_FirstName(const Param1: WideString);
    procedure Set_MiddleName(const Param1: WideString);
    procedure Set_LastName(const Param1: WideString);
    procedure Set_BirthDate(Param1: TDateTime);
    procedure Set_TransStart(Param1: Smallint);
    procedure Set_TransEnd(Param1: Smallint);
    procedure Set_FontName(const Param1: WideString);
    procedure Set_FontSize(Param1: Smallint);
    procedure Set_FontCodes(Param1: Smallint);
    procedure Set_FontColor(Param1: LongWord);
    procedure Set_LeftMargin(Param1: Smallint);
    procedure Set_TextWidth(Param1: Smallint);
    procedure Set_DemoMode(Param1: Smallint);
  public
    property DefaultInterface: INumerowCalcer read GetDefaultInterface;
  published
  end;
{$ENDIF}


// *********************************************************************//
// The Class CoCTextGetter provides a Create and CreateRemote method to          
// create instances of the default interface ITextGetter exposed by              
// the CoClass CTextGetter. The functions are intended to be used by             
// clients wishing to automate the CoClass objects exposed by the         
// server of this typelibrary.                                            
// *********************************************************************//
  CoCTextGetter = class
    class function Create: ITextGetter;
    class function CreateRemote(const MachineName: string): ITextGetter;
  end;


// *********************************************************************//
// OLE Server Proxy class declaration
// Server Object    : TCTextGetter
// Help String      : TextGetter Class
// Default Interface: ITextGetter
// Def. Intf. DISP? : No
// Event   Interface: 
// TypeFlags        : (2) CanCreate
// *********************************************************************//
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  TCTextGetterProperties= class;
{$ENDIF}
  TCTextGetter = class(TOleServer)
  private
    FIntf:        ITextGetter;
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
    FProps:       TCTextGetterProperties;
    function      GetServerProperties: TCTextGetterProperties;
{$ENDIF}
    function      GetDefaultInterface: ITextGetter;
  protected
    procedure InitServerData; override;
    procedure Set_Row(Param1: Smallint);
    procedure Set_Col(Param1: Smallint);
    function Get_Text: WideString;
  public
    constructor Create(AOwner: TComponent); override;
    destructor  Destroy; override;
    procedure Connect; override;
    procedure ConnectTo(svrIntf: ITextGetter);
    procedure Disconnect; override;
    property DefaultInterface: ITextGetter read GetDefaultInterface;
    property Row: Smallint write Set_Row;
    property Col: Smallint write Set_Col;
    property Text: WideString read Get_Text;
  published
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
    property Server: TCTextGetterProperties read GetServerProperties;
{$ENDIF}
  end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
// *********************************************************************//
// OLE Server Properties Proxy Class
// Server Object    : TCTextGetter
// (This object is used by the IDE's Property Inspector to allow editing
//  of the properties of this server)
// *********************************************************************//
 TCTextGetterProperties = class(TPersistent)
  private
    FServer:    TCTextGetter;
    function    GetDefaultInterface: ITextGetter;
    constructor Create(AServer: TCTextGetter);
  protected
    procedure Set_Row(Param1: Smallint);
    procedure Set_Col(Param1: Smallint);
    function Get_Text: WideString;
  public
    property DefaultInterface: ITextGetter read GetDefaultInterface;
  published
  end;
{$ENDIF}


procedure Register;

resourcestring
  dtlServerPage = 'ActiveX';

implementation

uses ComObj;

class function CoCNumerowCalcer.Create: INumerowCalcer;
begin
  Result := CreateComObject(CLASS_CNumerowCalcer) as INumerowCalcer;
end;

class function CoCNumerowCalcer.CreateRemote(const MachineName: string): INumerowCalcer;
begin
  Result := CreateRemoteComObject(MachineName, CLASS_CNumerowCalcer) as INumerowCalcer;
end;

procedure TCNumerowCalcer.InitServerData;
const
  CServerData: TServerData = (
    ClassID:   '{C2875FFB-F20C-46D6-8701-3FC4E1AC2FA2}';
    IntfIID:   '{B480AEC1-0F33-49B2-AF97-C89DBD206D32}';
    EventIID:  '';
    LicenseKey: nil;
    Version: 500);
begin
  ServerData := @CServerData;
end;

procedure TCNumerowCalcer.Connect;
var
  punk: IUnknown;
begin
  if FIntf = nil then
  begin
    punk := GetServer;
    Fintf:= punk as INumerowCalcer;
  end;
end;

procedure TCNumerowCalcer.ConnectTo(svrIntf: INumerowCalcer);
begin
  Disconnect;
  FIntf := svrIntf;
end;

procedure TCNumerowCalcer.DisConnect;
begin
  if Fintf <> nil then
  begin
    FIntf := nil;
  end;
end;

function TCNumerowCalcer.GetDefaultInterface: INumerowCalcer;
begin
  if FIntf = nil then
    Connect;
  Assert(FIntf <> nil, 'DefaultInterface is NULL. Component is not connected to Server. You must call ''Connect'' or ''ConnectTo'' before this operation');
  Result := FIntf;
end;

constructor TCNumerowCalcer.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  FProps := TCNumerowCalcerProperties.Create(Self);
{$ENDIF}
end;

destructor TCNumerowCalcer.Destroy;
begin
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  FProps.Free;
{$ENDIF}
  inherited Destroy;
end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
function TCNumerowCalcer.GetServerProperties: TCNumerowCalcerProperties;
begin
  Result := FProps;
end;
{$ENDIF}

procedure TCNumerowCalcer.Set_Index(Param1: Smallint);
begin
  Exit;
end;

procedure TCNumerowCalcer.Set_FirstName(const Param1: WideString);
  { Warning: The property FirstName has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.FirstName := Param1;
end;

procedure TCNumerowCalcer.Set_MiddleName(const Param1: WideString);
  { Warning: The property MiddleName has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.MiddleName := Param1;
end;

procedure TCNumerowCalcer.Set_LastName(const Param1: WideString);
  { Warning: The property LastName has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.LastName := Param1;
end;

procedure TCNumerowCalcer.Set_BirthDate(Param1: TDateTime);
begin
  Exit;
end;

procedure TCNumerowCalcer.Set_TransStart(Param1: Smallint);
begin
  Exit;
end;

procedure TCNumerowCalcer.Set_TransEnd(Param1: Smallint);
begin
  Exit;
end;

procedure TCNumerowCalcer.Set_FontName(const Param1: WideString);
  { Warning: The property FontName has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.FontName := Param1;
end;

procedure TCNumerowCalcer.Set_FontSize(Param1: Smallint);
begin
  Exit;
end;

procedure TCNumerowCalcer.Set_FontCodes(Param1: Smallint);
begin
  Exit;
end;

procedure TCNumerowCalcer.Set_FontColor(Param1: LongWord);
begin
  Exit;
end;

procedure TCNumerowCalcer.Set_LeftMargin(Param1: Smallint);
begin
  Exit;
end;

procedure TCNumerowCalcer.Set_TextWidth(Param1: Smallint);
begin
  Exit;
end;

procedure TCNumerowCalcer.Set_DemoMode(Param1: Smallint);
begin
  Exit;
end;

procedure TCNumerowCalcer.CalcChart(var file_: PChar; var person: PChar; 
                                    var comments: PChar; var type_: PChar; typecode: Smallint);
begin
  DefaultInterface.CalcChart(file_, person, comments, type_, typecode);
end;

procedure TCNumerowCalcer.ConvertFile(var in_name: PChar; var out_name: PChar; type_: Smallint);
begin
  DefaultInterface.ConvertFile(in_name, out_name, type_);
end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
constructor TCNumerowCalcerProperties.Create(AServer: TCNumerowCalcer);
begin
  inherited Create;
  FServer := AServer;
end;

function TCNumerowCalcerProperties.GetDefaultInterface: INumerowCalcer;
begin
  Result := FServer.DefaultInterface;
end;

procedure TCNumerowCalcerProperties.Set_Index(Param1: Smallint);
begin
  Exit;
end;

procedure TCNumerowCalcerProperties.Set_FirstName(const Param1: WideString);
  { Warning: The property FirstName has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.FirstName := Param1;
end;

procedure TCNumerowCalcerProperties.Set_MiddleName(const Param1: WideString);
  { Warning: The property MiddleName has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.MiddleName := Param1;
end;

procedure TCNumerowCalcerProperties.Set_LastName(const Param1: WideString);
  { Warning: The property LastName has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.LastName := Param1;
end;

procedure TCNumerowCalcerProperties.Set_BirthDate(Param1: TDateTime);
begin
  Exit;
end;

procedure TCNumerowCalcerProperties.Set_TransStart(Param1: Smallint);
begin
  Exit;
end;

procedure TCNumerowCalcerProperties.Set_TransEnd(Param1: Smallint);
begin
  Exit;
end;

procedure TCNumerowCalcerProperties.Set_FontName(const Param1: WideString);
  { Warning: The property FontName has a setter and a getter whose
  types do not match. Delphi was unable to generate a property of
  this sort and so is using a Variant to set the property instead. }
var
  InterfaceVariant: OleVariant;
begin
  InterfaceVariant := DefaultInterface;
  InterfaceVariant.FontName := Param1;
end;

procedure TCNumerowCalcerProperties.Set_FontSize(Param1: Smallint);
begin
  Exit;
end;

procedure TCNumerowCalcerProperties.Set_FontCodes(Param1: Smallint);
begin
  Exit;
end;

procedure TCNumerowCalcerProperties.Set_FontColor(Param1: LongWord);
begin
  Exit;
end;

procedure TCNumerowCalcerProperties.Set_LeftMargin(Param1: Smallint);
begin
  Exit;
end;

procedure TCNumerowCalcerProperties.Set_TextWidth(Param1: Smallint);
begin
  Exit;
end;

procedure TCNumerowCalcerProperties.Set_DemoMode(Param1: Smallint);
begin
  Exit;
end;

{$ENDIF}

class function CoCTextGetter.Create: ITextGetter;
begin
  Result := CreateComObject(CLASS_CTextGetter) as ITextGetter;
end;

class function CoCTextGetter.CreateRemote(const MachineName: string): ITextGetter;
begin
  Result := CreateRemoteComObject(MachineName, CLASS_CTextGetter) as ITextGetter;
end;

procedure TCTextGetter.InitServerData;
const
  CServerData: TServerData = (
    ClassID:   '{9654336F-86B5-4970-821A-4DDFDE04EB0E}';
    IntfIID:   '{74EAD860-7971-4E4D-B7CD-1C9C9F96B854}';
    EventIID:  '';
    LicenseKey: nil;
    Version: 500);
begin
  ServerData := @CServerData;
end;

procedure TCTextGetter.Connect;
var
  punk: IUnknown;
begin
  if FIntf = nil then
  begin
    punk := GetServer;
    Fintf:= punk as ITextGetter;
  end;
end;

procedure TCTextGetter.ConnectTo(svrIntf: ITextGetter);
begin
  Disconnect;
  FIntf := svrIntf;
end;

procedure TCTextGetter.DisConnect;
begin
  if Fintf <> nil then
  begin
    FIntf := nil;
  end;
end;

function TCTextGetter.GetDefaultInterface: ITextGetter;
begin
  if FIntf = nil then
    Connect;
  Assert(FIntf <> nil, 'DefaultInterface is NULL. Component is not connected to Server. You must call ''Connect'' or ''ConnectTo'' before this operation');
  Result := FIntf;
end;

constructor TCTextGetter.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  FProps := TCTextGetterProperties.Create(Self);
{$ENDIF}
end;

destructor TCTextGetter.Destroy;
begin
{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
  FProps.Free;
{$ENDIF}
  inherited Destroy;
end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
function TCTextGetter.GetServerProperties: TCTextGetterProperties;
begin
  Result := FProps;
end;
{$ENDIF}

procedure TCTextGetter.Set_Row(Param1: Smallint);
begin
  Exit;
end;

procedure TCTextGetter.Set_Col(Param1: Smallint);
begin
  Exit;
end;

function TCTextGetter.Get_Text: WideString;
begin
    Result := DefaultInterface.Text;
end;

{$IFDEF LIVE_SERVER_AT_DESIGN_TIME}
constructor TCTextGetterProperties.Create(AServer: TCTextGetter);
begin
  inherited Create;
  FServer := AServer;
end;

function TCTextGetterProperties.GetDefaultInterface: ITextGetter;
begin
  Result := FServer.DefaultInterface;
end;

procedure TCTextGetterProperties.Set_Row(Param1: Smallint);
begin
  Exit;
end;

procedure TCTextGetterProperties.Set_Col(Param1: Smallint);
begin
  Exit;
end;

function TCTextGetterProperties.Get_Text: WideString;
begin
    Result := DefaultInterface.Text;
end;

{$ENDIF}

procedure Register;
begin
  RegisterComponents(dtlServerPage, [TCNumerowCalcer, TCTextGetter]);
end;

end.
