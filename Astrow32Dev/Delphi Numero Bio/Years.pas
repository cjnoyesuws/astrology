unit Years;

interface


uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Buttons;

type
  TfrmNameTrans = class(TForm)
    Label1: TLabel;
    Label2: TLabel;
    edtStart: TEdit;
    edtEnd: TEdit;
    btnCancel: TBitBtn;
    btnOk: TBitBtn;
    procedure FormCreate(Sender: TObject);
    procedure FormKeyPress(Sender: TObject; var Key: Char);
    procedure btnOkClick(Sender: TObject);
    procedure btnCancelClick(Sender: TObject);
    procedure edtStartChange(Sender: TObject);
    procedure edtEndChange(Sender: TObject);
  private
    { Private declarations }
    yBirth : SmallInt;
  public
    { Public declarations }
  procedure setBirth( y : SmallInt );
  Procedure GetYears( var st, ed : SmallInt );
  end;

var
  frmNameTrans: TfrmNameTrans;

implementation

{$R *.DFM}

procedure TfrmNameTrans.FormCreate(Sender: TObject);
var
  dt : TDateTime;
  m, d, y : Word;
  st : String;
begin
dt := Date;
DecodeDate(dt,y, m, d);
st := IntToStr(y);
edtStart.Text := st;
st := IntToStr(y+1);
edtEnd.Text := st;
end;

procedure TfrmNameTrans.FormKeyPress(Sender: TObject; var Key: Char);
begin
if Not (Key in ['0'..'9',#8] ) then
   begin
   Key := #0;
   MessageBeep(Word(-1));
   end;
end;

procedure TfrmNameTrans.btnOkClick(Sender: TObject);
begin
Hide;
end;

procedure TfrmNameTrans.btnCancelClick(Sender: TObject);
begin
Hide;
end;

procedure TfrmNameTrans.edtStartChange(Sender: TObject);
var
  v, r : Integer;
begin
Val( edtStart.Text, v, r );
if v = 0 then exit;
if edtStart.Text='' then Exit;
Val( edtStart.Text, v, r );
if (v < 10) or ( v > 2900 ) then
   begin
   edtStart.Text := IntToStr(yBirth);
   MessageBeep( Word(-1) );
   end;
end;

procedure TfrmNameTrans.edtEndChange(Sender: TObject);
var
  v, v2, r : Integer;
begin
Val( edtStart.Text, v, r );
Val( edtEnd.Text, v2, r );
if v2 = 0 then exit;
if ( v2 < 10 ) or ( v2 - v > 100 ) then
    begin
    MessageBeep(Word(-1));
    v2 := v + 10;
    edtEnd.Text := IntToStr(v2);
    end;
end;

procedure TfrmNameTrans.setBirth( y : SmallInt );
begin
ybirth := y;
end;

Procedure TfrmNameTrans.GetYears( var st, ed : SmallInt );
var
  r : integer;
begin
Val( edtStart.Text, st, r );
Val( edtEnd.Text, ed, r );
end;

end.
