unit text;

interface

uses
  WinTypes, WinProcs, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls;

const
     PERS_YEAR  =  13;
     PERS_MONTH =  14;
     UNIV_YEAR  =  15;
     UNIV_MONTH =  16;
     PERS_DAY   =  17;
     UNIV_DAY   =  18;

type
  TfrmText = class(TForm)
    Memo1: TMemo;
    btnClose: TButton;
    procedure btnCloseClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    procedure SetCaption( s : String );
    procedure SetItem( r, c : SmallInt );
    procedure DoText;
  end;

var
  frmText: TfrmText;
  itemrow, itemcol : SmallInt;

implementation

{$R *.DFM}

procedure TfrmText.btnCloseClick(Sender: TObject);
begin
Hide;
end;

procedure TfrmText.SetCaption( s : String );
begin
    Caption := s;
end;

procedure TfrmText.SetItem( r, c : SmallInt );
begin
itemrow := r;
itemcol := c;
end;


procedure TfrmText.DoText;
begin
end;

end.
