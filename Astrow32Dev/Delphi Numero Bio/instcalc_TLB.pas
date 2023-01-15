unit instcalc_TLB;

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
// File generated on 9/2/2005 10:37:26 AM from Type Library described below.

// ************************************************************************  //
// Type Lib: C:\cjnoyessw\instcalc.tlb (1)
// LIBID: {B8D5F4FC-BEF2-44B5-BEB4-B3ACCAAC62BC}
// LCID: 0
// Helpfile: 
// DepndLst: 
//   (1) v2.0 stdole, (C:\WINDOWS\system32\STDOLE2.TLB)
//   (2) v4.0 StdVCL, (C:\WINDOWS\system32\stdvcl40.dll)
// ************************************************************************ //
{$TYPEDADDRESS OFF} // Unit must be compiled without type-checked pointers. 
{$WARN SYMBOL_PLATFORM OFF}
{$WRITEABLECONST ON}
{$VARPROPSETTER ON}
interface

uses Windows, ActiveX, Classes, Graphics, StdVCL, Variants;
  

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

  LIBID_instcalc: TGUID = '{B8D5F4FC-BEF2-44B5-BEB4-B3ACCAAC62BC}';

  IID_IAstInstCalc: TGUID = '{58E8EF81-9D07-4B04-AF1C-142CF4C9509A}';
  CLASS_AstInstCalc: TGUID = '{FBE5D579-FCE8-41BB-BE21-1576781E09CB}';
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
  AstInstCalc = IAstInstCalc;


// *********************************************************************//
// Interface: IAstInstCalc
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {58E8EF81-9D07-4B04-AF1C-142CF4C9509A}
// *********************************************************************//
  IAstInstCalc = interface(IDispatch)
    ['{58E8EF81-9D07-4B04-AF1C-142CF4C9509A}']
    procedure Set_Index(Value: Integer); safecall;
    function Get_Value: OleVariant; safecall;
    procedure StartAt(month: Integer; day: Integer; year: Integer; hour: Integer); safecall;
    property Index: Integer write Set_Index;
    property Value: OleVariant read Get_Value;
  end;

// *********************************************************************//
// DispIntf:  IAstInstCalcDisp
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {58E8EF81-9D07-4B04-AF1C-142CF4C9509A}
// *********************************************************************//
  IAstInstCalcDisp = dispinterface
    ['{58E8EF81-9D07-4B04-AF1C-142CF4C9509A}']
    property Index: Integer writeonly dispid 2;
    property Value: OleVariant readonly dispid 3;
    procedure StartAt(month: Integer; day: Integer; year: Integer; hour: Integer); dispid 1;
  end;

// *********************************************************************//
// The Class CoAstInstCalc provides a Create and CreateRemote method to          
// create instances of the default interface IAstInstCalc exposed by              
// the CoClass AstInstCalc. The functions are intended to be used by             
// clients wishing to automate the CoClass objects exposed by the         
// server of this typelibrary.                                            
// *********************************************************************//
  CoAstInstCalc = class
    class function Create: IAstInstCalc;
    class function CreateRemote(const MachineName: string): IAstInstCalc;
  end;

implementation

uses ComObj;

class function CoAstInstCalc.Create: IAstInstCalc;
begin
  Result := CreateComObject(CLASS_AstInstCalc) as IAstInstCalc;
end;

class function CoAstInstCalc.CreateRemote(const MachineName: string): IAstInstCalc;
begin
  Result := CreateRemoteComObject(MachineName, CLASS_AstInstCalc) as IAstInstCalc;
end;

end.
