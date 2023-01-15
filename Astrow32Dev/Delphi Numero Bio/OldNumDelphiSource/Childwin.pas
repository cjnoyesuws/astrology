unit Childwin;

interface

uses Windows, Classes, Graphics, Forms, Controls;

type
  TfrmMDIChild = class(TForm)
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  frmMdiChild : TfrmMDIChild;

implementation

{$R *.DFM}


procedure TfrmMDIChild.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  Action := caFree;
end;

procedure TfrmMDIChild.FormCreate(Sender: TObject);
begin
FormStyle := fsMDIChild
end;

end.
