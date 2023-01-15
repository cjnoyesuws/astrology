unit regchecksv;

interface

uses
  SysUtils, Classes, Graphics, Controls, Forms, Dialogs;

type
  TForm1 = class(TForm)
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

uses ComApp;

{$R *.DFM}

const
  CLASS_ComWebApp: TGUID = '{57100FD7-C8C8-4E02-8C6E-BF8E9DE21582}';

initialization
  TWebAppAutoObjectFactory.Create(Class_ComWebApp,
    'CoRegCheckService', 'CoRegCheckService Object');

end.
