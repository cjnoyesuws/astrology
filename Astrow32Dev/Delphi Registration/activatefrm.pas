unit activatefrm;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Buttons, Rio, SOAPHTTPClient, Windows;

type
  TActivateForm = class(TForm)
    ckPrivate: TCheckBox;
    Label1: TLabel;
    edName: TEdit;
    Label2: TLabel;
    edAddress: TEdit;
    edAddress2: TEdit;
    Label3: TLabel;
    edCity: TEdit;
    Label4: TLabel;
    edState: TEdit;
    Label5: TLabel;
    edZip: TEdit;
    Label6: TLabel;
    edCountry: TEdit;
    Label7: TLabel;
    edTelephone: TEdit;
    Label8: TLabel;
    edEmail: TEdit;
    btnOk: TBitBtn;
    btnClose: TBitBtn;
    lblActivateTitle: TLabel;
    lblRegActivate: TLabel;
    Rio1: THTTPRIO;
    procedure ckPrivateClick(Sender: TObject);
    procedure edNameExit(Sender: TObject);
    procedure btnOkClick(Sender: TObject);
    procedure btnCloseClick(Sender: TObject);
    procedure edNameEnter(Sender: TObject);
  private
    { Private declarations }
  public
    sProgram : String;
    sRegType : String;
    IsValid  : Boolean;
    function Validate : Boolean;
    function ValidateField(fld : TObject) : Boolean;
    function ComputerName : String;
    function MacAddress : String;
    { Public declarations }
  end;

var
  ActivateForm: TActivateForm;

implementation

{$R *.dfm}

procedure TActivateForm.ckPrivateClick(Sender: TObject);
begin
   if ckPrivate.Checked then
   begin
      edTelephone.Enabled:= false;
      edZip.Enabled := false;
      edState.Enabled := False;
      edEmail.Enabled := False;
      edCity.Enabled := false;
      edAddress.Enabled := False;
      edAddress2.Enabled := False;
      edName.Enabled := False;
      edCountry.Enabled := False;
   end else
   begin
      edTelephone.Enabled:= True;
      edZip.Enabled := True;
      edState.Enabled := True;
      edEmail.Enabled := True;
      edCity.Enabled := True;
      edAddress.Enabled := True;
      edAddress2.Enabled := True;
      edName.Enabled := True;
      edCountry.Enabled := True;
   end;
end;

procedure TActivateForm.edNameExit(Sender: TObject);
begin
   if Sender is TEdit then
   begin
      if TEdit(Sender).Enabled and (Length(TEdit(Sender).Text) = 0) then
      begin
         ShowMessage('This Field Is Required');
         ActiveControl :=  TWinControl(Sender);
         isValid := False;
         TEdit(Sender).Color := clRed;
      end else
         IsValid := True;
   end;
end;

function TActivateForm.Validate : Boolean;
begin
   Result := ValidateField(edName);
   if Result then
      Result := ValidateField(edAddress);
   if Result then
      Result := ValidateField(edCity);
   if Result then
      Result := ValidateField(edZip);
   if Result then
      Result := ValidateField(edCountry);
end;

function TActivateForm.ValidateField(fld : TObject) : Boolean;
begin
   edNameExit(fld);
   Result := IsValid;
end;

procedure TActivateForm.btnOkClick(Sender: TObject);
begin
   if not Validate then
      exit;

end;



procedure TActivateForm.edNameEnter(Sender: TObject);
begin
   If TEdit(Sender).Color = clRed then
      TEdit(Sender).Color := clWindow;
end;

function ComputerName : String;
var
  pBuf : PChar;
  nSize : integer;
begin
  pBuf := StrAlloc(100);
  nSize := 99;
  if GetComputerName(pBuf, nSize) <> 0 )
  Begin
     Result := pBuf;
     strDispose(pBuf);
  end else
     Result := '';
end;


function MacAddress : String;
begin
end;

end.
