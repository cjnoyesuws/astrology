unit View;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ComCtrls;

type
  TfrmView = class(TForm)
    RichEdit1: TRichEdit;
  private
    { Private declarations }
  FileName : String;
  public
    { Public declarations }
  end;

var
  frmView: TfrmView;

implementation

{$R *.DFM}


end.
