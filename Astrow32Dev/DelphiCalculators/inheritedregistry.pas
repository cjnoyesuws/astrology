unit inheritedregistry;

interface

uses registry, sysutils;

type
   TInheritedRegistry = class(TRegistry)
   private
   public
      bKeyWasSuite : Boolean;
      constructor Create(sApp : String);
      function Open(key : String; CanCreate, bSuite : Boolean) : Boolean;
      function ReadString( key, default : String ) : string;
      function ReadInteger( key : String; default : integer ) : integer;
      function ReadFloat( key : String; default : double ) : double;
      function ReadDate( key : String; default : TDateTime ) : TDateTime;
   protected
      sApplication : String;
      sBasePath : String;
      sUsedPath : String;
      function isSuite : boolean;
   end;

implementation

constructor TInheritedRegistry.Create(sApp: String);
begin
   sApplication := sApp;
   sBasePath := '\Software\Christopher J. Noyes Software\';
   inherited create;
end;

function TInheritedRegistry.isSuite : boolean;
var
  oReg : TRegistry;
begin
  oReg := TRegistry.Create;
  Result := oReg.OpenKey(sBasePath+'Suite',false);
  if result then
  begin
     oReg.CloseKey;
     bKeyWasSuite := True;
  end else
     bKeyWasSuite := False;
  oReg.Destroy;
end;

Function TInheritedRegistry.Open(key : String; CanCreate, bSuite : Boolean ) : Boolean;
begin
  try
     if not bSuite then
        sUsedPath := sBasePath + sApplication + '\' + key
     else if isSuite then
        sUsedPath := sBasePath + 'Astro For Windows\' + key
     else
        sUsedPath := sBasePath + sApplication + '\' + key;
     Result := OpenKey( sUsedPath, CanCreate );
  except
     result := false;
  end;
end;

function TInheritedRegistry.ReadString( key, default : String ) : string;
var
  sRead : String;
begin
  try
  sRead := inherited ReadString( key );
  if sRead = '' then
     Result := default
  else
     Result := sRead;
  except
     Result := default;
  end;
end;

function TInheritedRegistry.ReadInteger( key : String; default : integer ) : integer;
var
  iRead : Integer;
begin
  try
     iRead := inherited ReadInteger( key );
     Result := iRead;
  except
     Result := StrToInt(ReadString(key, IntToStr(default)));
  end;
end;

function TInheritedRegistry.ReadFloat( key : String; default : double ) : double;
var
  dRead : double;
begin
  try
     dRead := inherited ReadFloat( key );
     Result := dRead;
  except
     Result := StrToFloat(ReadString(key, FloatToStr(default)));
  end;
end;

function TInheritedRegistry.ReadDate( key : String; default : TDateTime ) : TDateTime;
var
  dRead : TDateTime;
begin
  try
     dRead := inherited ReadDate( key );
     Result := dRead;
  except
     Result := StrToDate(ReadString(key, DateToStr(default)));
  end;
end;

end.
