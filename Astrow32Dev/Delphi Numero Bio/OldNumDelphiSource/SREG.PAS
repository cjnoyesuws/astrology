unit Sreg;

interface

uses
  SysUtils, WinTypes, WinProcs, Messages, Classes, Graphics, Controls,
  Forms, Dialogs, StdCtrls, inifiles;

type
  TfrmSReg = class(TForm)
    Button1: TButton;
    Label1: TLabel;
    Label2: TLabel;
    edtUser: TEdit;
    edtRegCode: TEdit;
    Button2: TButton;
    Label3: TLabel;
    procedure Button1Click(Sender: TObject);
    procedure edtUserChange(Sender: TObject);
    procedure edtRegCodeChange(Sender: TObject);
    procedure Button2Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  frmSReg: TfrmSReg;
  reg_code : string;
  user: string;

implementation

{$R *.DFM}

procedure TfrmSReg.Button1Click(Sender: TObject);
var
  ifn : string;
  inif : Tinifile;
begin
GetDir(0,ifn);
if ifn[length(ifn)-1]<> '\' then ifn := ifn + '\';
ifn := ifn + 'NUMERO.INI';
inif := TIniFile.Create(ifn);
inif.WriteString('Shareware','Reg',reg_code);
inif.WriteString('Shareware','User',user);
close;
end;

procedure TfrmSReg.edtUserChange(Sender: TObject);
begin
user := edtUser.Text;
end;

procedure TfrmSReg.edtRegCodeChange(Sender: TObject);
begin
reg_code := edtRegCode.Text;
end;

procedure TfrmSReg.Button2Click(Sender: TObject);
begin
Close;
end;

end.
