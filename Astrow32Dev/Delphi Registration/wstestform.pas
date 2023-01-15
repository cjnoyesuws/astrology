unit wstestform;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Buttons, Rio, SOAPHTTPClient;

type
  TForm1 = class(TForm)
    Label1: TLabel;
    edProgram: TEdit;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    BitBtn1: TBitBtn;
    HTTPRIO1: THTTPRIO;
    Label10: TLabel;
    Label11: TLabel;
    Button1: TButton;
    Label12: TLabel;
    edName: TEdit;
    Label13: TLabel;
    edAddress: TEdit;
    Label14: TLabel;
    EdAddress2: TEdit;
    Label15: TLabel;
    edCity: TEdit;
    Label16: TLabel;
    edState: TEdit;
    Label17: TLabel;
    edZip: TEdit;
    Label18: TLabel;
    edCountry: TEdit;
    Label19: TLabel;
    edPhone: TEdit;
    Label20: TLabel;
    edEmail: TEdit;
    procedure BitBtn1Click(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure HTTPRIO1BeforeExecute(const MethodName: String;
      var SOAPRequest: WideString);
    procedure HTTPRIO1AfterExecute(const MethodName: String;
      SOAPResponse: TStream);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

uses RegCheckServiceIntf;

{$R *.dfm}

procedure TForm1.BitBtn1Click(Sender: TObject);
var
  oRegCheck : IRegCheckService;
  sId : String;
begin
   oRegCheck := HTTPRIO1 as IRegCheckService;
   sId := oRegCheck.GetRegistrationId(edProgram.Text, edName.Text, edAddress.Text, edAddress2.Text, edCity.Text, edState.Text, edZip.Text, edCountry.Text, edPhone.Text, edEmail.Text,'Y');
   Label11.Caption := sid;
   Label3.Caption := oRegCheck.GetRegistrationStatus(sId);
   Label9.Caption := oRegCheck.GetRegistrationCodeStr(sId);
   label5.Caption := DateToStr(oRegCheck.GetRegStartDate(sId));
   Label7.Caption := DateToStr(oRegCheck.GetRegEndDate(sId));
end;

procedure TForm1.Button1Click(Sender: TObject);
var
  oRegCheck : IRegCheckService;
  sId : String;
begin
   oRegCheck := HTTPRIO1 as IRegCheckService;
   try
   sId := oRegCheck.GetRegistrationIdByCompName(edProgram.Text,edName.Text,edAddress.Text);
   except
     sId := oRegCheck.GetRegistrationIdByCompName(edProgram.Text,edName.Text,edAddress.Text);
   end;

   Label11.Caption := sid;
   Label3.Caption := oRegCheck.GetRegistrationStatus(sId);
   Label9.Caption := oRegCheck.GetRegistrationCodeStr(sId);
   label5.Caption := DateToStr(oRegCheck.GetRegStartDate(sId));
   Label7.Caption := DateToStr(oRegCheck.GetRegEndDate(sId));
end;

procedure TForm1.HTTPRIO1BeforeExecute(const MethodName: String;
  var SOAPRequest: WideString);
begin
  ShowMessage(SoapRequest);
  ShowMessage(methodName);
end;

procedure TForm1.HTTPRIO1AfterExecute(const MethodName: String;
  SOAPResponse: TStream);
var
  buf : array [0..200] of Char;
  str : String;
begin
  SoapResponse.Read(buf,200);
  str := buf;
  ShowMessage(str);
end;

end.
