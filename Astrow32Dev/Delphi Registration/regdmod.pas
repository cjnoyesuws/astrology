unit regdmod;

interface

uses
  SysUtils, Classes, DBXpress, FMTBcd, DB, SqlExpr, DBTables, dateutils;

type
  TRegDm = class(TDataModule)
    dbCjnoyessw: TDatabase;
    qryAnon: TQuery;
    qryAnonInsert: TQuery;
    qryDownload: TQuery;
    qryReg: TQuery;
    qryCounterAnon: TQuery;
    qryCounterDload: TQuery;
    qryCounterReg: TQuery;
    qryDloadInsert: TQuery;
    procedure DataModuleCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    function CounterQuery(CntName : String; Value : integer ) : TQuery;
    function RegStartDate(RegId : String) : TDateTime;
    function RegEndDate(RegId : String) : TDateTime;
    function AddAnonRec( ProgName, CompName, MacAddr : String ) : String;
    function GetAnonId( ProgName, CompName, MacAddr : String ) : String;
    function GetTheAnonId( ProgName, CompName, MacAddr : String ) : String;
    function GetRegString(RegId : String) : String;
    function GetRegId( ProgName, Name, Address, Address2, City, State, Zip, Country,  Phone, Email : String ) : String;
    function GetDloadId( ProgName, Name, Address, Address2, City, State, Zip, Country,  Phone, Email : String ) : String;
    function AddDloadRec( ProgName, Name, Address, Address2, City, State, Zip, Country,  Phone, Email, MayContact : String ) : String;
    function GetId( ProgName, Name, Address, Address2, City, State, Zip, Country,  Phone, Email, MayContact : String ) : String;
    Procedure prep( oQuery : TQuery;  ProgName, Name, Address, Address2, City, sState, Zip, Country,  Phone, Email, MayContact : String);
    Function GetCounter( oQuery : TQuery; sName : String ) : String;
    Procedure LogError( sError : String );
  end;

var
  RegDm: TRegDm;

function StrToHex(sStr : String) : String;

implementation

{$R *.dfm}

function TRegDm.CounterQuery(CntName : String; Value : integer ) : TQuery;
begin
   if CntName='DLOAD' then
      Result := qryCounterDload
   else if CntName='REGUS' then
      Result := qryCounterReg
   else
      Result := qryCounterAnon;
   try
      With Result Do
      begin
         ParamByName('cnt').AsInteger := Value;
         if not Prepared then
            prepare;
         Open;
      end;
   except
      on E : EDatabaseError do LogError( e.Message);
   end;
end;

function TRegDm.RegStartDate(RegId : String) : TDateTime;
var
  oQuery : TQuery;
  sCnter  : String;
  iCntVal : integer;
  sDate  : String;
begin
  Result := 0.0;
  sCnter := Copy(RegId,1,5);
  iCntVal := StrToInt(Copy(RegId,6,Length(RegId)-5));
  try
     oQuery := CounterQuery(sCnter, iCntVal);
     with oQuery do
     begin
        if (Active) and (not Eof) then
        begin
           sDate := FieldByName('start_date').AsString;
           if sDate <> '' then
              result := StrToDate(sDate)
           else
              Result := 0;
        end;
        if Active then
           Close;
     end;
  except
     on E : EDatabaseError do LogError( e.Message);
  end;
end;

function TRegDm.RegEndDate(RegId : String) : TDateTime;
var
  oQuery : TQuery;
  sCnter  : String;
  iCntVal : integer;
  adt : TDateTime;
  sDate  : String;
begin
  sCnter := Copy(RegId,1,5);
  iCntVal := StrToInt(Copy(RegId,6,Length(RegId)-5));
  try
     oQuery := CounterQuery(sCnter, iCntVal);
     with oQuery do
     begin
        if (Active) and (not Eof) then
        begin
           sDate := FieldByName('start_date').AsString;
           if ( sDate <> '' ) then
              adt := StrToDate(sDate)
           else
              adt := 0.0;
           if ( adt <> 0.0 ) then
              Result := StrToInt(FieldByName('days').AsString )
           else
              Result := 0.0;
        end else
           Result := 0.0;
        if Active then
           Close;
     end;
  except
     on E : EDatabaseError do
     begin
        LogError( e.Message);
        Result := 0.0;
     end;
  end;
end;

function TRegDm.AddAnonRec( ProgName, CompName, MacAddr : String ) : String;
begin
   try
      with qryAnonInsert do
      begin
         ParamByName('cn').AsString := CompName;
         ParamByname('ma').AsString := MacAddr;
         ParamByName('prog').AsString := ProgName;
         ParamByName('dtst').AsString := DateToStr(Date);
         if not prepared then
            prepare;
         ExecSql;
         if Active then
            Close;
         Result := 'ok';
      end;
   except
      on E : EDatabaseError do
      begin
         LogError( e.Message);
         Result := 'error';
      end;
   end;
end;

function TRegDm.GetAnonId( ProgName, CompName, MacAddr : String ) : String;
begin
   try
      with qryAnon do
      begin
         ParamByName('co').AsString := CompName;
         ParamByName('mac').AsString := MacAddr;
         ParamByname('prog').AsString := ProgName;
         if not prepared then
            prepare;
      end;
      Result := GetCounter(qryAnon,'ANONY');
   except
      on E : EDatabaseError do LogError( e.Message);
   end;
end;

function TRegDm.GetRegString(RegId : String) : String;
var
  oQuery : TQuery;
  sCnter, sReturn  : String;
  iCntVal : integer;
begin
  sCnter := Copy(RegId,1,5);
  iCntVal := StrToInt(Copy(RegId,6,Length(RegId)-5));
  try
     oQuery := CounterQuery(sCnter, iCntVal);
     sReturn := RegId + ':';
     with oQuery do
     begin
        if (Active) and (not Eof) then
        begin
           sReturn := sReturn +  FieldByName('start_date').AsString;
           sReturn := sReturn + ':';
           sReturn := sReturn + FieldByName('days').AsString;
        end else
           sReturn :=  sReturn + 'INVALID';
        Result := StrToHex(sReturn);
        if Active then
           Close;
     end;
  except
     on E : EDatabaseError do LogError( e.Message);
  end;
end;

function StrToHex(sStr : String) : String;
var
  aStr : String;
  iIndex : integer;
begin
   for iIndex := 1 to Length(sStr) do
      aStr := aStr + IntTohex(Ord(sStr[iIndex]),2);
   result := aStr;
end;

function TRegDm.GetRegId( ProgName, Name, Address, Address2, City, State, Zip, Country,  Phone, Email : String ) : String;
begin
   prep(qryReg, ProgName, Name, Address, Address2, City, State, Zip, Country,  Phone, Email, '');
   Result := GetCounter(qryReg,'REGUS');
end;

function TRegDm.GetDloadId( ProgName, Name, Address, Address2, City, State, Zip, Country,  Phone, Email  : String ) : String;
begin
  prep(qryDownload, ProgName, Name, Address, Address2, City, State, Zip, Country,  Phone, Email, '');
  Result := GetCounter(qryDownload,'DLOAD');
end;

function TRegDm.AddDloadRec( ProgName, Name, Address, Address2, City, State, Zip, Country,  Phone, Email, MayContact : String ) : String;
begin
   prep(qryDloadInsert, ProgName, Name, Address, Address2, City, State, Zip, Country,  Phone, Email, MayContact);
   try
      qryDloadInsert.execSQL;
      qryDloadInsert.Close;
      Result := GetDloadId( ProgName, Name, Address, Address2, City, State, Zip, Country,  Phone, Email );
   except
      on E : EDatabaseError do LogError( e.Message);
   end;
end;

function TRegDm.GetId( ProgName, Name, Address, Address2, City, State, Zip, Country,  Phone, Email, MayContact : String ) : String;
begin
   Result := GetRegId( ProgName, Name, Address, Address2, City, State, Zip,
      Country, Phone, Email );
   if ( result = '' ) then
       Result := GetDloadId( ProgName, Name, Address, Address2, City, State, Zip,
         Country, Phone, Email );
   if ( result = '' ) then
       Result := AddDloadRec( ProgName, Name, Address, Address2, City, State, Zip,
         Country, Phone, Email, MayContact );
end;

Procedure TRegDm.prep( oQuery : TQuery;  ProgName, Name, Address, Address2, City, sState, Zip, Country,  Phone, Email, MayContact : String);
begin
   with oQuery do
   begin
      try
         ParamByName('prog').AsString := ProgName;
         ParamByName('nam').AsString := Name;
         ParamByName('ad1').AsString := Address;
         ParamByName('ad2').AsString := Address2;
         ParamByName('cit').AsString := City;
         ParamByName('sta').AsString := sState;
         ParamByName('zip').AsString := Zip;
         ParamByName('cou').AsString := Country;
         ParamByName('tel').AsString := Phone;
         ParamByName('ema').AsString := Email;
         if MayContact <> '' then
           ParamByName('may').AsString := MayContact;
         if not prepared then
            prepare;
      except
        on E : EDatabaseError do LogError( e.Message);
      end;
   end;
end;

Function TRegDm.GetCounter( oQuery : TQuery; sName : String ) : String;
var
  sRet : String;
begin
  with oQuery do
  begin
     try
        Open;
        if eof then
           Result := ''
        else
        begin
           sRet := '00000' + oQuery.FieldByName('counter').AsString;
           sRet := Copy(sRet,Length(sRet)-5,5);
           Result := sName + sRet;
        end;
        Close;
     except
        on E : EDatabaseError do LogError( e.Message);
     end;
  end;
end;

procedure TRegDm.LogError( sError : String );
var
   txtf : Textfile;
begin
   AssignFile(txtf,'C:\Errors.log');
   if FileExists('c:\Errors.log') then
      Append( txtf )
   else
      Rewrite( txtf );
   Writeln( txtf, DateToStr(Date) + ' : ' + sError );
   CloseFile(txtf);
end;

function TRegDm.GetTheAnonId( ProgName, CompName, MacAddr : String ) : String;
begin
   Result := GetAnonId( ProgName, CompName, MacAddr );
   if Result = '' then
   begin
      if AddAnonRec( ProgName, CompName, MacAddr ) = 'ok' then
         Result := GetAnonId( ProgName, CompName, MacAddr )
      else
         Result := '';
   end;
end;

procedure TRegDm.DataModuleCreate(Sender: TObject);
begin
   LogError('DataModuleCreate start');
   dbCjnoyessw.Connected := True;
   LogError('DataModuleCreated');
end;

initialization




end.
