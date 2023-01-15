unit birtnum;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Buttons, ExtCtrls, ComCtrls, Tabnotbk;

type
  TfrmBirthNum = class(TForm)
    TabbedNotebook1: TTabbedNotebook;
    Panel1: TPanel;
    btnClose: TBitBtn;
    Label1: TLabel;
    edt1No: TEdit;
    Label2: TLabel;
    edt1Yr: TEdit;
    Label3: TLabel;
    edt2No: TEdit;
    Label4: TLabel;
    edt2Yr: TEdit;
    Label5: TLabel;
    edt3No: TEdit;
    Label6: TLabel;
    edt3Yr: TEdit;
    Label7: TLabel;
    edt4No: TEdit;
    Label8: TLabel;
    edt4Yr: TEdit;
    Label9: TLabel;
    Label10: TLabel;
    Year: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    Label13: TLabel;
    Label14: TLabel;
    Label15: TLabel;
    Label16: TLabel;
    Label27: TLabel;
    Label30: TLabel;
    Label19: TLabel;
    edtC1No: TEdit;
    Label28: TLabel;
    Label21: TLabel;
    edtC2No: TEdit;
    Label31: TLabel;
    Label29: TLabel;
    Label32: TLabel;
    Label23: TLabel;
    edtC3No: TEdit;
    Label17: TLabel;
    Label18: TLabel;
    Label20: TLabel;
    Second: TLabel;
    Label22: TLabel;
    edtL1No: TEdit;
    edtL2No: TEdit;
    edtL3No: TEdit;
    Label24: TLabel;
    Label25: TLabel;
    edtL1Yr: TEdit;
    edtL2Yr: TEdit;
    edtL3Yr: TEdit;
    Label26: TLabel;
    Label33: TLabel;
    Label34: TLabel;
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  frmBirthNum: TfrmBirthNum;

implementation

{$R *.DFM}

end.
