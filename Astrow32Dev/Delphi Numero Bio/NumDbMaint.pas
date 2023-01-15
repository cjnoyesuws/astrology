unit NumDbMaint;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, DBCtrls, Mask, ExtCtrls, Buttons;

type
  TNumDBMaintForm = class(TForm)
    DBNavigator1: TDBNavigator;
    Label1: TLabel;
    DBEdListName: TDBEdit;
    Label2: TLabel;
    DBEdBirthDate: TDBEdit;
    DBCkbdtInclude: TDBCheckBox;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    DBEdBirthFirst: TDBEdit;
    DBEdBirthMid: TDBEdit;
    DBEdBirthLast: TDBEdit;
    DBCkBirthInclude: TDBCheckBox;
    Label7: TLabel;
    DBEdCurrFirst: TDBEdit;
    Label9: TLabel;
    DBEdCurrMid: TDBEdit;
    Label10: TLabel;
    DBEdCurrLast: TDBEdit;
    DBCkCurInc: TDBCheckBox;
    Label11: TLabel;
    Label8: TLabel;
    Label12: TLabel;
    DBEdOpt1First: TDBEdit;
    Label13: TLabel;
    DBEdOpt1Mid: TDBEdit;
    Label14: TLabel;
    DbEdOpt1Last: TDBEdit;
    DBCkOpt1Include: TDBCheckBox;
    Label15: TLabel;
    Label16: TLabel;
    Label17: TLabel;
    Label18: TLabel;
    DBEdOpt2First: TDBEdit;
    DBEdOpt2Mid: TDBEdit;
    DBEdOpt2Last: TDBEdit;
    DBCkOpt2Include: TDBCheckBox;
    OkBtn: TBitBtn;
    CancelBtn: TBitBtn;
    procedure FormShow(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  NumDBMaintForm: TNumDBMaintForm;

implementation

uses DmNumerow;

{$R *.dfm}


procedure TNumDBMaintForm.FormShow(Sender: TObject);
begin
   if not DmNumerow.aDmNumerow.ADONumLst.Active then
      DmNumerow.aDmNumerow.ADONumLst.Open;
end;

end.
