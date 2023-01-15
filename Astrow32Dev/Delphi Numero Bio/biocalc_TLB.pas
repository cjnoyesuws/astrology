unit biocalc_TLB;

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

// PASTLWTR : 1.2
// File generated on 10/25/2007 7:40:21 PM from Type Library described below.

// ************************************************************************  //
// Type Lib: h:\astrow32dev\biocalc\release\biocalc.dll (1)
// LIBID: {F2B59736-4D14-4DB1-960C-0B4F14ACE444}
// LCID: 0
// Helpfile: 
// HelpString: biocalc 1.0 Type Library
// DepndLst: 
//   (1) v2.0 stdole, (C:\WINDOWS\system32\stdole2.tlb)
// Errors:
//   Hint: Parameter 'file' of IBioDataCalc.SaveData changed to 'file_'
// ************************************************************************ //
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
  biocalcMajorVersion = 1;
  biocalcMinorVersion = 0;

  LIBID_biocalc: TGUID = '{F2B59736-4D14-4DB1-960C-0B4F14ACE444}';

  IID_IBioDataCalc: TGUID = '{18B41BCD-EA9C-48FD-B6BC-EE8C411C4073}';
  CLASS_CBioDataCalc: TGUID = '{37A3EB90-807D-4CA1-921D-BCAC087ED99C}';
type

// *********************************************************************//
// Forward declaration of types defined in TypeLibrary                    
// *********************************************************************//
  IBioDataCalc = interface;
  IBioDataCalcDisp = dispinterface;

// *********************************************************************//
// Declaration of CoClasses defined in Type Library                       
// (NOTE: Here we map each CoClass to its Default Interface)              
// *********************************************************************//
  CBioDataCalc = IBioDataCalc;


// *********************************************************************//
// Declaration of structures, unions and aliases.                         
// *********************************************************************//
  PShortint1 = ^Shortint; {*}


// *********************************************************************//
// Interface: IBioDataCalc
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {18B41BCD-EA9C-48FD-B6BC-EE8C411C4073}
// *********************************************************************//
  IBioDataCalc = interface(IDispatch)
    ['{18B41BCD-EA9C-48FD-B6BC-EE8C411C4073}']
    procedure Set_PersName(const pVal: WideString); safecall;
    procedure Set_BirthDate(pVal: TDateTime); safecall;
    procedure Set_StartDate(pVal: TDateTime); safecall;
    procedure Set_Index(Param1: Smallint); safecall;
    function Get_Physical: Double; safecall;
    function Get_Emotional: Double; safecall;
    function Get_Intellectual: Double; safecall;
    function Get_EmotionalDesc: WideString; safecall;
    function Get_PhysicalDesc: WideString; safecall;
    function Get_IntellectualDesc: WideString; safecall;
    procedure Calc; safecall;
    procedure SaveData(file_: PChar); safecall;
    procedure LoadData(name: PChar); safecall;
    procedure Export(name: PChar); safecall;
    function Get_Days: Smallint; safecall;
    function Get_Critical: Double; safecall;
    function Get_CriticalDesc: WideString; safecall;
    function Get_PersName: WideString; safecall;
    function Get_BirthDate: TDateTime; safecall;
    function Get_StartDate: TDateTime; safecall;
    property PersName: WideString read Get_PersName write Set_PersName;
    property BirthDate: TDateTime read Get_BirthDate write Set_BirthDate;
    property StartDate: TDateTime read Get_StartDate write Set_StartDate;
    property Index: Smallint write Set_Index;
    property Physical: Double read Get_Physical;
    property Emotional: Double read Get_Emotional;
    property Intellectual: Double read Get_Intellectual;
    property EmotionalDesc: WideString read Get_EmotionalDesc;
    property PhysicalDesc: WideString read Get_PhysicalDesc;
    property IntellectualDesc: WideString read Get_IntellectualDesc;
    property Days: Smallint read Get_Days;
    property Critical: Double read Get_Critical;
    property CriticalDesc: WideString read Get_CriticalDesc;
  end;

// *********************************************************************//
// DispIntf:  IBioDataCalcDisp
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {18B41BCD-EA9C-48FD-B6BC-EE8C411C4073}
// *********************************************************************//
  IBioDataCalcDisp = dispinterface
    ['{18B41BCD-EA9C-48FD-B6BC-EE8C411C4073}']
    property PersName: WideString dispid 1;
    property BirthDate: TDateTime dispid 2;
    property StartDate: TDateTime dispid 3;
    property Index: Smallint writeonly dispid 4;
    property Physical: Double readonly dispid 5;
    property Emotional: Double readonly dispid 6;
    property Intellectual: Double readonly dispid 7;
    property EmotionalDesc: WideString readonly dispid 8;
    property PhysicalDesc: WideString readonly dispid 9;
    property IntellectualDesc: WideString readonly dispid 10;
    procedure Calc; dispid 11;
    procedure SaveData(var file_: {??Shortint}OleVariant); dispid 12;
    procedure LoadData(var name: {??Shortint}OleVariant); dispid 13;
    procedure Export(var name: {??Shortint}OleVariant); dispid 14;
    property Days: Smallint readonly dispid 15;
    property Critical: Double readonly dispid 16;
    property CriticalDesc: WideString readonly dispid 17;
  end;

// *********************************************************************//
// The Class CoCBioDataCalc provides a Create and CreateRemote method to          
// create instances of the default interface IBioDataCalc exposed by              
// the CoClass CBioDataCalc. The functions are intended to be used by             
// clients wishing to automate the CoClass objects exposed by the         
// server of this typelibrary.                                            
// *********************************************************************//
  CoCBioDataCalc = class
    class function Create: IBioDataCalc;
    class function CreateRemote(const MachineName: string): IBioDataCalc;
  end;

implementation

uses ComObj;

class function CoCBioDataCalc.Create: IBioDataCalc;
begin
  Result := CreateComObject(CLASS_CBioDataCalc) as IBioDataCalc;
end;

class function CoCBioDataCalc.CreateRemote(const MachineName: string): IBioDataCalc;
begin
  Result := CreateRemoteComObject(MachineName, CLASS_CBioDataCalc) as IBioDataCalc;
end;

end.
