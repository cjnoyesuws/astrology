unit setup;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Buttons;

type
  TCalcSetupForm = class(TForm)
    Label1: TLabel;
    edtLong: TEdit;
    Label2: TLabel;
    edtLatitude: TEdit;
    Label3: TLabel;
    edtGmt: TEdit;
    BitBtn1: TBitBtn;
    BitBtn2: TBitBtn;
    ckMidnight: TCheckBox;
    procedure BitBtn2Click(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure BitBtn1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  CalcSetupForm: TCalcSetupForm;

implementation

uses inheritedregistry;

{$R *.dfm}

procedure TCalcSetupForm.BitBtn1Click(Sender: TObject);
var
 oReg : TInheritedRegistry;
 str : string;
begin
  oReg := TInheritedRegistry.Create('');
  oReg.Open('InstCalc', true, false );
  oReg.WriteString('Longitude',edtLong.Text);
  oReg.WriteString('Latitude',edtLatitude.Text);
  oReg.WriteString('GmtOffset',edtGmt.Text);
  if ( ckMidnight.checked ) then
     str := 'Y'
  else
     str := 'N';
  oReg.WriteString('MidnightEphem',str);
  oReg.CloseKey;
  oReg.Destroy;
  Close;
end;

procedure TCalcSetupForm.FormShow(Sender: TObject);
var
 oReg : TInheritedRegistry;
 str : string;
begin
  oReg := TInheritedRegistry.Create('');
  oReg.Open('InstCalc', true, false );
  edtLong.Text := oReg.ReadString('Longitude','74W00');
  edtLatitude.Text := oReg.ReadString('Latitude','40N45');
  edtGmt.Text := oReg.ReadString('GmtOffset','5:0');
  str := oReg.ReadString('MidnightEphem','N');
  if ( str = 'Y' ) then
     ckMidnight.Checked := true
  else
     ckMidnight.Checked := false;
  oReg.CloseKey;
  oReg.Destroy;
end;

procedure TCalcSetupForm.BitBtn2Click(Sender: TObject);
begin
  Application.Terminate;
end;

end.
