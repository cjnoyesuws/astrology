unit numchart;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, DBCtrls, StdCtrls, Buttons, ExtCtrls, ComCtrls;

type
  TNumChartForm = class(TForm)
    PageControl1: TPageControl;
    tsData: TTabSheet;
    tsChart: TTabSheet;
    Label1: TLabel;
    CbChartType: TComboBox;
    Label2: TLabel;
    edtChartName: TEdit;
    Label3: TLabel;
    edtChartComments: TEdit;
    Label4: TLabel;
    EdtFileName: TEdit;
    sbDialog: TSpeedButton;
    SaveDialog1: TSaveDialog;
    Label5: TLabel;
    Panel1: TPanel;
    BtnOk: TBitBtn;
    BitBtn1: TBitBtn;
    Label6: TLabel;
    DbLuCbListName: TDBLookupComboBox;
    edtListName: TEdit;
    Label7: TLabel;
    dtpBirth: TDateTimePicker;
    ckBirthInc: TCheckBox;
    Label8: TLabel;
    Label9: TLabel;
    edtBirthFirst: TEdit;
    Label10: TLabel;
    edtBirthMiddle: TEdit;
    Label11: TLabel;
    edtBirthLast: TEdit;
    ckBirthNameInclude: TCheckBox;
    Label12: TLabel;
    Label13: TLabel;
    edtCurFirst: TEdit;
    Label14: TLabel;
    edtCurMiddle: TEdit;
    Label15: TLabel;
    edtCurLast: TEdit;
    ckCurInclude: TCheckBox;
    Label16: TLabel;
    Label17: TLabel;
    edOpt1First: TEdit;
    Label18: TLabel;
    edOpt1Middle: TEdit;
    Label19: TLabel;
    edtOpt1Last: TEdit;
    CheckBox2: TCheckBox;
    Label20: TLabel;
    edtOpt2First: TEdit;
    Label21: TLabel;
    Label22: TLabel;
    edtOpt2Middle: TEdit;
    Label23: TLabel;
    edtOpt2Last: TEdit;
    edtOpt2Include: TCheckBox;
    procedure sbDialogClick(Sender: TObject);
    procedure edtBirthFirstChange(Sender: TObject);
    procedure edtCurFirstChange(Sender: TObject);
    procedure edOpt1FirstChange(Sender: TObject);
    procedure edtOpt2FirstChange(Sender: TObject);
    procedure dtpBirthChange(Sender: TObject);
    procedure DbLuCbListNameDropDown(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  NumChartForm: TNumChartForm;

implementation

uses numerocalc_TLB, DmNumerow;

{$R *.dfm}

procedure TNumChartForm.sbDialogClick(Sender: TObject);
begin
   With SaveDialog1 do
   begin
      if Execute then
         EdtFileName.Text := FileName;
   end;
end;

procedure TNumChartForm.edtBirthFirstChange(Sender: TObject);
begin
   if (Length(edtBirthFirst.Text)>0) or
         (Length(edtBirthMiddle.Text)>0) or
         (Length(edtBirthLast.Text)>0) then
      ckBirthNameInclude.Checked := True
   else
      ckBirthNameInclude.Checked := False;
end;

procedure TNumChartForm.edtCurFirstChange(Sender: TObject);
begin
   if (Length(edtCurFirst.Text)>0) or
         (Length(edtCurMiddle.Text)>0) or
         (Length(edtCurLast.Text)>0) then
      ckCurInclude.Checked := True
   else
      ckCurInclude.Checked := False;
end;

procedure TNumChartForm.edOpt1FirstChange(Sender: TObject);
begin
  if (Length(edtOpt1First.Text)>0) or
         (Length(edtOpt1Middle.Text)>0) or
         (Length(edtOpt1Last.Text)>0) then
      ckOpt1Include.Checked := True
   else
      ckOpt1Include.Checked := False;
end;

procedure TNumChartForm.edtOpt2FirstChange(Sender: TObject);
begin
  if (Length(edtOpt2First.Text)>0) or
         (Length(edtOpt2Middle.Text)>0) or
         (Length(edtOpt2Last.Text)>0) then
      ckOpt2Include.Checked := True
   else
      ckOpt2Include.Checked := False;
end;

procedure TNumChartForm.dtpBirthChange(Sender: TObject);
begin
   ckBirthInc.Checked := true;
end;

procedure TNumChartForm.DbLuCbListNameDropDown(Sender: TObject);
begin
   with DmNumerow.aDmNumerow.ADONumOne do
   begin
      Parameters.Clear;
      Parameters.CreateParameter('ListName',tsString,pdInput,-1);
      Open
      if not eof do
      begin
         edtListName.Text := DbLuCbListName.Text;
         dptBirth.date  := FieldByName('BirthDate').AsDateTime;
         edtBirthFirst.Text := FieldbyName('BirthFirst').AsString;
      end;
      Close;
   end
end;

end.
