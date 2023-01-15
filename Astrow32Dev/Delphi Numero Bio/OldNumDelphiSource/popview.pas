unit Popview;

interface

uses
  SysUtils, WinTypes, WinProcs, Messages, Classes, Graphics, Controls,
  Forms, Dialogs, Udc_win, Udc_wrp1, Udc_mwps, StdCtrls, Buttons;

type
  TFrmView = class(TForm)
    BitBtn1: TBitBtn;
    UdcMWPStandard1: TUdcMWPStandard;
    procedure BitBtn1Click(Sender: TObject);
    procedure FormKeyPress(Sender: TObject; var Key: Char);
  private
    { Private declarations }
  public
    { Public declarations }
  procedure SetFileNameCaption( fn, cap : string );
  end;

var
  FrmView: TFrmView;

implementation

{$R *.DFM}

procedure TFrmView.BitBtn1Click(Sender: TObject);
begin
hide;
end;

procedure TFrmView.SetFileNameCaption( fn, cap : string );
var
  st : string;
begin
if Not FileExists( fn ) then
   begin
   st := Format( '%s Does Not Exist!', [fn] );
   MessageDlg( st, mtError, [mbOk], 0 );
   exit;
   end;
UdcMWPStandard1.SelectAll;
UdcMWPStandard1.Clear;
{$IFDEF DEMO }
UdcMWPStandard1.CurrentStyle:= [afsBold];
UdcMWPStandard1.CurrentSize:=14;
UdcMWPStandard1.InsertLine('This is a Shareware Demo Version! Please Register It!');
{$ENDIF }
UdcMWPStandard1.LoadFromFile(fn);
Caption := cap;
end;


procedure TFrmView.FormKeyPress(Sender: TObject; var Key: Char);
begin
if key <> #10 then key := #0;
end;

end.
