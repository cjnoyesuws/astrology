unit expimp;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ADODB, DB, DBTables, ComCtrls, StdCtrls, Buttons;

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
    Function BirthExists( name, birth : String ) : boolean;
    function LocationExists ( country, state, location : string ) : boolean;
  end;

var
  ExpImpForm: TExpImpForm;

implementation

{$R *.dfm}

procedure TExpImpForm.FormShow(Sender: TObject);
var
  odbconf : TDbConfig;
begin
   odbconf := TDbConfig.Create('Astro For Windows');
   ADOConnection1.Provider := odbconf.Provider;
   ADOConnection1.ConnectionString := odbconf.Connect;
   ADOConnection1.Connected := True;
end;

procedure TExpImpForm.OkBtnClick(Sender: TObject);
begin
   tblPeople.DatabaseName := edExpertDir.Text;
   tblLocations.DatabaseName := edExpertDir.Text;
   if ckPeople.Checked then
      ImportBirths;
   if ckLocations.Checked then
      ImportLocs;
end;

procedure TExpImpForm.ImportBirths;
Begin
   with TblLocations do
   begin
      Open;
      ProgressBar1.Max  := RecordCount;
      While not Eof do
      begin
         if not BirthExists( FieldbyName('name').AsString,
              FieldByName('birth').AsString ) then
            AddLocs;
         Next;
         ProgressBar1.StepIt;
      end;
      Close;
   end;
end;


procedure TExpImpForm.ImportLocs;
Begin
   with TblPeople do
   begin
      Open;
      ProgressBar1.Max := RecordCount;
      While not Eof do
      begin
         if not LocationExists( FieldbyName('country').AsString,
              FieldByName('state').AsString, FieldByName('location').AsString ) then
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
Begin
  if longLat then
  begin
     sFmt := '%3.3d%s%2.2d'
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
  Result := FormatStr(sFmt, [deg,sDir,min] );
end;

Function TExpImpForm.BirthExists( name, birth : String ) : boolean;
Begin
   with AdoBirthQuery Do
   begin
       Parameters.Clear;
       Parameters.CreateParameter('nam',ftString,pdInput,-1,name);
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

function TExpImpForm.LocationExists ( country, state, location : string ) : boolean;
Begin
   with AdoLocQuery Do
   begin
       Parameters.Clear;
       Parameters.CreateParameter('co',ftString,pdInput,-1,name);
       Parameters.CreateParameter('st',ftString,pdInput,-1,name);
       Parameters.CreateParameter('lo',ftString,pdInput,-1,name);
       Prepared := True;
       Open;
       if Eof then
          Result := False
       else
          Result := True;
       Close;
   end;
end;

procedure AddBirths;
var
begin
end;

procedure AddLocs;
var
begin
end;

end.

