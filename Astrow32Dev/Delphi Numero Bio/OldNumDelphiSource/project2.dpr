program Project2;

uses
  Forms,
  Txtpop31 in 'TXTPOP31.PAS' {frmTxtPop31},
  Viewtx31 in 'VIEWTX31.PAS' {frmViewText31};

{$R *.RES}

begin
  Application.CreateForm(TfrmViewText31, frmViewText31);
  Application.Run;
end.
