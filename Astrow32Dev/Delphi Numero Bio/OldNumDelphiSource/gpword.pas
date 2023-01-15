unit Gpword;

interface

uses
  SysUtils, WinTypes, WinProcs, Messages, Classes, Graphics, Controls,
  Forms, Dialogs, StdCtrls;

type
  TPword = class(TForm)
    Edit1: TEdit;
    Label1: TLabel;
    Button1: TButton;
    procedure Button1Click(Sender: TObject);
  private
    Password : string;
    { Private declarations }
  public
    { Public declarations }
  Procedure setPassword( pw : string );
  end;

var
  Pword: TPword;

implementation

{$R *.DFM}

procedure TPword.Button1Click(Sender: TObject);
begin
if Password = Edit1.text then ModalResult := mrOK;
   else Beep;
end;

Procedure TPword.setPassword( pw : string );
begin
Password := pw;
end;

end.
