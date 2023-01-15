unit dbmaint;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Buttons, Mask, DBCtrls, DB, ADODB, ExtCtrls;

type
  TDbMaintForm = class(TForm)
    DBNavigator1: TDBNavigator;
    ADOConnection1: TADOConnection;
    nameDataSource: TDataSource;
    ADOTable1: TADOTable;
    dbName: TDBEdit;
    dbDate: TDBEdit;
    Label1: TLabel;
    Label2: TLabel;
    btnOk: TBitBtn;
    btnCancel: TBitBtn;
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  DbMaintForm: TDbMaintForm;

implementation

uses DBConfig, inheritedregistry;

{$R *.dfm}

procedure TDbMaintForm.FormCreate(Sender: TObject);
var
   oDbConf : TDBConfig;
begin
   oDbConf := TDbConfig.Create('Biorythms');
   AdoConnection1.Provider := oDbconf.Provider;
   AdoConnection1.ConnectionString := oDbConf.Connect;
   AdoConnection1.Connected := True;
   AdoTable1.Open;
end;

end.
