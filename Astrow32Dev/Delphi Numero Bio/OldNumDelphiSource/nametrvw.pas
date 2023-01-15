unit NameTrVw;

interface

uses
  Windows,
  Messages,
  SysUtils,
  Classes,
  Graphics,
  Controls,
  Forms,
  Dialogs,
  StdCtrls,
  Spin;

type
  TfrmNameTrVw = class(TForm)
    Label1: TLabel;
    ComboWhich: TComboBox;
    Label2: TLabel;
    SpinYear: TSpinEdit;
    Label3: TLabel;
    SpinAge: TSpinEdit;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    EditFirst: TEdit;
    EditFirstVal: TEdit;
    Label8: TLabel;
    EditLast: TEdit;
    EditLastVal: TEdit;
    Label9: TLabel;
    EditMiddle: TEdit;
    EditMiddleVal: TEdit;
    Label10: TLabel;
    Label11: TLabel;
    EditEssence: TEdit;
    Label12: TLabel;
    EditPYear: TEdit;
    Label13: TLabel;
    EditUYear: TEdit;
    Label14: TLabel;
    EditPinn: TEdit;
    Label15: TLabel;
    EditLife: TEdit;
    ButtonClose: TButton;
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  frmNameTrVw: TfrmNameTrVw;

implementation

{$R *.DFM}

end.
