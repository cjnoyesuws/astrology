unit DBConfig;

interface

uses inheritedregistry, sysutils, shlobj;

type TDBConfig = class(TObject)
protected
    sDBName : String;
    sProvider : String;
    sConnect : String;
    sDBDirectory : String;
public
    Constructor Create(sApp : String);
    function DBName : String;
    function DBDirectory : String;
    Function DBDirectoryandName : String;
    function Provider : String;
    function Connect : String;
end;

const
    DEF_DB  = 'astrow.mdb';
    DEF_EXT = '.mdb';
    DEF_PROV = 'Microsoft.Jet.OLEDB.4.0';
    DEF_CONNECT = 'Provider=Microsoft.Jet.OLEDB.4.0;Password=""'+
       ';User ID=Admin;Mode=Share Deny None;Extended Properties="'+
       '";Jet OLEDB:System database="";Jet OLEDB:Registry Path="'+
       '";Jet OLEDB:Database Password="";Jet OLEDB:Engine Type=5;'+
       'Jet OLEDB:Database Locking Mode=1;Jet OLEDB:Global Partial Bulk Ops=2;'+
       'Jet OLEDB:Global Bulk Transactions=1;Jet OLEDB:New Database Password=""'+
       ';Jet OLEDB:Create System Database=False;Jet OLEDB:Encrypt Database=False;'+
       'Jet OLEDB:Don''t Copy Locale on Compact=False;'+
       'Jet OLEDB:Compact Without Replica Repair=False;Jet OLEDB:SFP=False;Data Source=';

implementation

Constructor TDBConfig.Create(sApp : String);
var
  oReg : TInheritedRegistry;
  sbuf : String[250];
  sName : String;
begin
  oReg := TInheritedRegistry.Create(sApp);
  if oReg.Open('Directories',false,true) then
  begin
     ShGetSpecialFolderPath(0,PChar(@sBuf[1]),CSIDL_PERSONAL,LongBool(0));
     if ( Copy(sbuf,length(sbuf)-1,1) <> '\' ) then
       sbuf := sbuf + '\';
     if oReg.bKeyWasSuite then
       sName := 'Astro For Windows'
     else
       sName := sApp;
     sDBDirectory := oReg.ReadString('DB',sBuf+sName);
     oReg.CloseKey();
  end else
  begin
    ShGetSpecialFolderPath(0,PChar(@sBuf[1]),CSIDL_PERSONAL,LongBool(0));
    if ( Copy(sbuf,length(sbuf)-1,1) <> '\' ) then
       sbuf := sbuf + '\';
    sDBDirectory := sbuf + sApp + '\';
  end;
  if oReg.Open('Database',false,true) then
  begin
     if (oReg.bKeyWasSuite) or (sApp='Astro For Windows') then
        sName := DEF_DB
     else
        sName := sApp + DEF_EXT;
     sDBName := oReg.ReadString('DatabaseName',sName);
     sProvider := oReg.ReadString('Provider',DEF_PROV);
     sConnect := oReg.ReadString('Connect',DEF_CONNECT+DBDirectoryandName);
     oReg.CloseKey();
  end else
  begin
     sDBName := sbuf + sApp + DEF_EXT;
     sProvider := DEF_PROV;
     sConnect := DEF_CONNECT + DBDirectoryandName;
  end;
end;

Function TDBConfig.DBDirectoryandName : String;
begin
  if copy(sDBDirectory,length(sDBDirectory)-1,1)='\' then
     result := sDbDirectory+sDbName
  else
     Result := sDBDirectory + '\' + sDBName;
end;

function TDBConfig.Connect : String;
begin
   result := sConnect;
end;

Function TDBConfig.Provider : String;
begin
  result := sProvider;
end;

Function TDBConfig.DBDirectory : String;
begin
  result := sDBDirectory;
end;

Function TDBConfig.DBName : String;
begin
  Result := sDBName;
end;



end.
