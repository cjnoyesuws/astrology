unit Txtpop31;

interface

uses
  SysUtils, WinTypes, WinProcs, Messages, Classes, Graphics, Controls,
  Forms, Dialogs, StdCtrls, Buttons;


type
  TfrmTxtPop31 = class(TForm)
    closeBtn: TBitBtn;
    procedure FormKeyPress(Sender: TObject; var Key: Char);
    procedure closeBtnClick(Sender: TObject);
  private
    { Private declarations }
  public
  procedure SetFileNameCaption( fn, cap : string );
    { Public declarations }
  end;

var
  frmPopupText: TfrmTxtPop31;

implementation

{$R *.DFM}

procedure TfrmTxtPop31.FormKeyPress(Sender: TObject; var Key: Char);
begin
if key <> #10 then key := #0;
end;

procedure TfrmTxtPop31.closeBtnClick(Sender: TObject);
begin
hide;
end;

procedure TfrmTxtPop31.SetFileNameCaption( fn, cap : string );
var
  st : string;
begin
if Not FileExists( fn ) then
   begin
   st := Format( '%s Does Not Exist!', [fn] );
   MessageDlg( st, mtError, [mbOk], 0 );
   exit;
   end;
Caption := cap;
end;

end.
