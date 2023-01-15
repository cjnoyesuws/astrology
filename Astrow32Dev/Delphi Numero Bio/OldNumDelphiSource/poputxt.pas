unit poputxt;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ComCtrls, Richedit, ldrched, Buttons;

type
  TfrmPopupText = class(TForm)
    btnClose: TBitBtn;
    RichEdit1: TRichEdit;
    procedure btnCloseClick(Sender: TObject);
    procedure FormKeyPress(Sender: TObject; var Key: Char);
  private
    { Private declarations }

  public
    { Public declarations }
  procedure SetTextCaption( txt, cap : string );
  end;

procedure DoClick( row, col : integer; caption : string );


var
  frmPopupText: TfrmPopupText;


implementation

uses numerocalc_TLB;

{$R *.DFM}

procedure TfrmPopupText.SetTextCaption( txt, cap : string );
begin
RichEdit1.Lines.Add(txt);
Caption := cap;
RichEdit1.Show;
end;

procedure TfrmPopupText.btnCloseClick(Sender: TObject);
begin
Hide;
end;

procedure TfrmPopupText.FormKeyPress(Sender: TObject; var Key: Char);
begin
if key <> #10 then key := #0
else beep;
end;

procedure DoClick( row, col : integer; caption : string );
var
  oText : ITextGetter;
  oTCText : TCTextGetter;
  res : TModalResult;
begin
  oTCText := TCTextGetter.Create(Application);
  oText := oTCText.DefaultInterface;
  oText.Row := row;
  oText.Col := col;
  frmPopupText := TfrmPopupText.Create(Application);
  frmPopupText.SetTextCaption(oText.Text,caption);
  oTCText.Disconnect;
  oTCText.Destroy;
  res := frmPopupText.ModalResult;
  frmPopupText.Destroy;
end;

end.
