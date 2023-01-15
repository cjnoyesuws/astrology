unit expimp;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ADODB, DB, DBTables, ComCtrls, StdCtrls, Buttons, dbconfig,
  strutils, dateutils;

type
  TExpImpForm = class(TForm)
    Label1: TLabel;
    edExpertDir: TEdit;
    btnSelect: TBitBtn;
    OpenDialog1: TOpenDialog;
    ckLocations: TCheckBox;
    ckPeople: TCheckBox;
    ProgressBar1: TProgressBar;
    Label2: TLabel;
    OkBtn: TBitBtn;
    CancelBtn: TBitBtn;
    tblPeople: TTable;
    tblLocations: TTable;
    ADOConnection1: TADOConnection;
    ADOLocQuery: TADOQuery;
    ADOBirthQuery: TADOQuery;
    ADOLocInsertQuery: TADOQuery;
    ADOBirthInsertQuery: TADOQuery;
    procedure CancelBtnClick(Sender: TObject);
    procedure btnSelectClick(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure OkBtnClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    procedure ImportBirths;
    procedure ImportLocs;
    procedure AddBirths;
    procedure AddLocs;
    function FormatLongLat(deg,min,dir : Integer; LongLat : boolean) : String;
    Function BirthExists( sName, birth : String ) : boolean;
    function LocationExists ( country, sState, location : string ) : boolean;
    procedure SetField( oQry : TAdoQuery; sName : String; oField : TField; fType : TFieldType );
    procedure SetStrField( oQry : TAdoQuery; sName, sValue : String );
    procedure SetIntField( oQry : TAdoQuery; sName : String; iValue : smallint );
    Procedure SplitTime( var hr, min : SmallInt; var ampm : Boolean );
  end;

var
  ExpImpForm: TExpImpForm;

const

StrSQL = 'insert into births (name,birthdate,hours, minutes, sex, country,state,location,longitude,latitude,timezone,specialcode,houroff,minoff,rect,AMPM) ' +
  'values(:nam,:bdt,:hour,:min,:sex,:co,:st,:lo,:lng,:lat,:tz,:sc,:hro,:mno,No,';

implementation

{$R *.dfm}

procedure TExpImpForm.FormShow(Sender: TObject);
var
  odbconf : TDbConfig;
begin
   ADOConnection1.Connected := False;
   odbconf := TDbConfig.Create('Astro For Windows');
   ADOConnection1.Provider := odbconf.Provider;
   ADOConnection1.ConnectionString := odbconf.Connect;
   ADOConnection1.Connected := True;
   if ( ParamCount > 0 ) and (ParamStr(1) = '-auto' ) and
        ( MessageDlg('Do You Want to Auto Import?', mtConfirmation, mbYesNo,0 )=mrYes) then
       OkBtnClick(sender);
end;

procedure TExpImpForm.OkBtnClick(Sender: TObject);
begin
   tblPeople.DatabaseName := edExpertDir.Text;
   tblLocations.DatabaseName := edExpertDir.Text;
   if ckPeople.Checked then
      ImportBirths;
   if ckLocations.Checked then
      ImportLocs;
   Application.Terminate;
end;

procedure TExpImpForm.ImportBirths;
Begin
   with TblPeople do
   begin
      Open;
      ProgressBar1.Max  := RecordCount;
      While not Eof do
      begin
         if not BirthExists( Trim(FieldbyName('First').AsString + ' ' +
              FieldbyName('Last').AsString),
              FieldByName('BirthDate').AsString ) then
            AddBirths;
         Next;
         ProgressBar1.StepIt;
      end;
      Close;
   end;
end;


procedure TExpImpForm.ImportLocs;
Begin
   with TblLocations do
   begin
      Open;
      ProgressBar1.Max := RecordCount;
      While not Eof do
      begin
         if not LocationExists( FieldbyName('Country').AsString,
              FieldByName('State').AsString, FieldByName('Location').AsString ) then
            AddLocs;
         Next;
         ProgressBar1.StepIt;
      end;
      Close;
   end;
end;

function TExpImpForm.FormatLongLat(deg,min,dir : Integer; LongLat : boolean) : String;
Var
  sFmt, sDir : String;
  pbuf : PChar;
Begin
  if longLat then
  begin
     sFmt := '%3.3d%s%2.2d';
     if dir > 0 then
       sDir := 'N'
     else
       sDir := 'S';
  end else
  begin
     sFmt := '%2.2d%s%2.2d';
     if dir > 0 then
       sDir := 'E'
     else
       sDir := 'W';
  end;
  pbuf := StrAlloc(12);
  Result := StrFmt(pbuf, PChar(sFmt), [deg,sDir,min]);
  strDispose(pbuf);
end;

Function TExpImpForm.BirthExists( sName, birth : String ) : boolean;
Begin
   with AdoBirthQuery Do
   begin
       Parameters.Clear;
       Parameters.CreateParameter('nam',ftString,pdInput,-1,sName);
       Parameters.CreateParameter('bdt',ftDate,pdInput,-1,StrToDate(birth));
       Prepared := True;
       Open;
       if Eof then
          Result := False
       else
          Result := True;
       Close;
   end;
end;

function TExpImpForm.LocationExists ( country, sState, location : string ) : boolean;
Begin
   with AdoLocQuery Do
   begin
       Parameters.Clear;
       Parameters.CreateParameter('co',ftString,pdInput,-1,country);
       Parameters.CreateParameter('st',ftString,pdInput,-1,sState);
       Parameters.CreateParameter('lo',ftString,pdInput,-1,location);
       Prepared := True;
       Open;
       if Eof then
          Result := False
       else
          Result := True;
       Close;
   end;
end;

procedure TExpImpForm.AddBirths;
var
  sFld, sSql : String;
  hour, min : Smallint;
  bPm: Boolean;
  bdt : TDateTime;
begin
  With AdoBirthInsertQuery do
  begin
     SplitTime(hour,min,bPm);
     sSql := strSql;
     if bPm then
        sSql := sSql + 'Yes)'
     else
        sSql := sSql  + 'No)';
     SQL.Clear;
     SQL.Add(sSQL);
     Parameters.Clear;
     Prepared := True;
     sFld := tblPeople.FieldByName('First').AsString + ' ' +
        tblPeople.FieldByName('Last').AsString;
     SetStrField(AdoBirthInsertQuery, 'nam', sFld );
     bdt := StrToDate(tblPeople.FieldbyName('BirthDate').AsString);
     Parameters.CreateParameter('bdt',ftDate,pdInput,-1,bdt);
     SetIntField(AdoBirthInsertQuery,'hour', hour );
     SetIntField(AdoBirthInsertQuery, 'min', min );
     SetIntField(AdoBirthInsertQuery,'sex',TblPeople.FieldbyName('Sex').AsInteger);
     SetField(AdoBirthInsertQuery,'co',tblPeople.FieldByName('Country'), ftString);
     SetField(AdoBirthInsertQuery,'st',tblPeople.FieldByName('State'), ftString);
     SetField(AdoBirthInsertQuery,'lo',tblPeople.FieldByName('Location'), ftString);
     SetStrField(AdoBirthInsertQuery,'lng',FormatLongLat(tblPeople.FieldByName('LonDeg').AsInteger,
        tblPeople.FieldByName('LonMin').AsInteger, tblPeople.FieldByName('EastWest').AsInteger, True) );
     SetStrField(AdoBirthInsertQuery,'lat',FormatLongLat(tblPeople.FieldByName('LatDeg').AsInteger,
        tblPeople.FieldByName('LatMin').AsInteger, tblPeople.FieldByName('NorthSouth').AsInteger, false) );
     SetField(AdoBirthInsertQuery,'tz',tblPeople.FieldByName('TimeZone'), ftSmallInt);
     SetField(AdoBirthInsertQuery,'sc',tblPeople.FieldByName('SpecialCode'), ftSmallInt);
     SetField(AdoBirthInsertQuery,'hro',tblPeople.FieldByName('GMT'), ftSmallInt);
     SetField(AdoBirthInsertQuery,'mno',tblPeople.FieldByName('GMTMin'), ftSmallInt);
     try
       ExecSQL;
     except
       On E: EDatabaseError do ShowMessage(E.Message);
     end;
     close;
  end;
end;

procedure TExpImpForm.AddLocs;
var
  sFld : String;
begin
   With AdoLocInsertQuery do
  begin
     Parameters.Clear;
     SetField(AdoLocInsertQuery,'co',tblLocations.FieldByName('Country'), ftString);
     SetField(AdoLocInsertQuery,'st',tblLocations.FieldByName('State'), ftString);
     SetField(AdoLocInsertQuery,'lo',tblLocations.FieldByName('Location'), ftString);
     SetStrField(AdoLocInsertQuery,'lng',FormatLongLat(tblLocations.FieldByName('LonDeg').AsInteger,
        tblLocations.FieldByName('LonMin').AsInteger, tblLocations.FieldByName('EastWest').AsInteger, True) );
          SetStrField(AdoLocInsertQuery,'lat',FormatLongLat(tblLocations.FieldByName('LatDeg').AsInteger,
        tblLocations.FieldByName('LatMin').AsInteger, tblLocations.FieldByName('NorthSouth').AsInteger, false) );
     SetField(AdoLocInsertQuery,'tz',tblLocations.FieldByName('TimeZone'), ftSmallInt);
     SetField(AdoLocInsertQuery,'sc',tblLocations.FieldByName('SpecialCode'), ftSmallInt);
     SetField(AdoLocInsertQuery,'hro',tblLocations.FieldByName('GMT'), ftSmallInt);
     SetField(AdoLocInsertQuery,'mno',tblLocations.FieldByName('GMTMin'), ftSmallInt);
     Prepared := True;
     try
       ExecSQL;
     except
       On E: EDatabaseError do ShowMessage(E.Message);
     end;
     close;
  end;
end;

procedure TExpImpForm.SetField( oQry : TAdoQuery; sName : String; oField : TField; fType : TFieldType );
var
  iVal : Integer;
begin
   if ftype = ftString then
      oQry.Parameters.CreateParameter(sName,ftString,pdInput,-1,oField.AsString)
   else if ftype = ftBoolean then
      oQry.Parameters.CreateParameter(sName,ftBoolean,pdInput,-1,oField.AsInteger<>0)
   else
   begin
      iVal := oField.AsInteger;
      if (iVal > 24) or (iVal < -24) then
         iVal := 0;
      oQry.Parameters.CreateParameter(sName,ftSmallint,pdInput,-1,iVal);
   end;
end;

procedure TExpImpForm.SetStrField( oQry : TAdoQuery; sName, sValue : String );
begin
   oQry.Parameters.CreateParameter(sName,ftString,pdInput,-1,sValue);
end;

procedure TExpImpForm.SetIntField( oQry : TAdoQuery; sName : String; iValue : smallint );
begin
    oQry.Parameters.CreateParameter(sName,ftSmallint,pdInput,-1,iValue);
end;

Procedure TExpImpForm.SplitTime( var hr, min : SmallInt; var ampm : Boolean );
var
  sTime : string;
  dtTime : TDateTime;
  hour, mins, sec, msec : Word;
begin
  sTime := tblPeople.FieldByName('BirthTime').AsString;
  if ( tblPeople.FieldByName('AM').AsInteger = 1 ) then
  begin
     sTime := sTime + ' AM';
     ampm := False;
     end else
  begin
     sTime := sTime + ' PM';
     ampm := True;
  end;
  dtTime := StrToTime(sTime);
  DecodeTime(dtTime,hour,mins,sec,msec);
  if ampm then
    hr := hour - 12
  else
    hr := hour;
  min := mins;
end;

procedure TExpImpForm.btnSelectClick(Sender: TObject);
var
   sDir : String;
   iPos : Integer;
begin
   OpenDialog1.InitialDir := edExpertDir.Text;
   if OpenDialog1.Execute then
   begin
      sDir := ReverseString(OpenDialog1.FileName);
      iPos := pos('\', sDir );
      sDir := OpenDialog1.FileName;
      sDir := LeftStr(sDir,Length(sDir)-iPos);
      edExpertDir.Text := sDir;
   end;
end;

procedure TExpImpForm.CancelBtnClick(Sender: TObject);
begin
   Application.Terminate;
end;

end.


