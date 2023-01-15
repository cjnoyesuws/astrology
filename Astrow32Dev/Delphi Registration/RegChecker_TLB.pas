unit RegChecker_TLB;

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
// File generated on 10/5/2005 9:48:29 AM from Type Library described below.

// ************************************************************************  //
// Type Lib: C:\cjnoyessw\RegChecker.tlb (1)
// LIBID: {911D263B-2A51-4029-9C05-3CA67B5AACD3}
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
  RegCheckerMajorVersion = 1;
  RegCheckerMinorVersion = 0;

  LIBID_RegChecker: TGUID = '{911D263B-2A51-4029-9C05-3CA67B5AACD3}';

  IID_IRegistrationChecker: TGUID = '{FA1CC012-4C2A-4B3E-8002-CD86ACCD3450}';
  CLASS_RegistrationChecker: TGUID = '{B345987E-AFCF-469C-A8A5-B75BF0870D80}';
type

// *********************************************************************//
// Forward declaration of types defined in TypeLibrary                    
// *********************************************************************//
  IRegistrationChecker = interface;

// *********************************************************************//
// Declaration of CoClasses defined in Type Library                       
// (NOTE: Here we map each CoClass to its Default Interface)              
// *********************************************************************//
  RegistrationChecker = IRegistrationChecker;


// *********************************************************************//
// Interface: IRegistrationChecker
// Flags:     (256) OleAutomation
// GUID:      {FA1CC012-4C2A-4B3E-8002-CD86ACCD3450}
// *********************************************************************//
  IRegistrationChecker = interface(IUnknown)
    ['{FA1CC012-4C2A-4B3E-8002-CD86ACCD3450}']
    function Set_ProgramName(const Param1: WideString): HResult; stdcall;
    function Set_Shareware(Param1: Smallint): HResult; stdcall;
    function Get_DaysLeft(out Value: Smallint): HResult; stdcall;
    function Get_Status(out Value: WideString): HResult; stdcall;
    function Set_Suite(Value: Smallint): HResult; stdcall;
  end;

// *********************************************************************//
// The Class CoRegistrationChecker provides a Create and CreateRemote method to          
// create instances of the default interface IRegistrationChecker exposed by              
// the CoClass RegistrationChecker. The functions are intended to be used by             
// clients wishing to automate the CoClass objects exposed by the         
// server of this typelibrary.                                            
// *********************************************************************//
  CoRegistrationChecker = class
    class function Create: IRegistrationChecker;
    class function CreateRemote(const MachineName: string): IRegistrationChecker;
  end;

implementation

uses ComObj;

class function CoRegistrationChecker.Create: IRegistrationChecker;
begin
  Result := CreateComObject(CLASS_RegistrationChecker) as IRegistrationChecker;
end;

class function CoRegistrationChecker.CreateRemote(const MachineName: string): IRegistrationChecker;
begin
  Result := CreateRemoteComObject(MachineName, CLASS_RegistrationChecker) as IRegistrationChecker;
end;

end.
