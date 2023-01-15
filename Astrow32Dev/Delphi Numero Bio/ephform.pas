unit ephform;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, Grids, StdCtrls, ComCtrls,
  {$IFNDEF DEBUG}
   _instcalc_TLB, CustomizeDlg;
{$ELSE}
   instcalc_TLB;
{$ENDIF}


type
  TEphemForm = class(TForm)
    Label1: TLabel;
    dtpStart: TDateTimePicker;
    ckMidnightEphem: TCheckBox;
    sgPositions: TStringGrid;
    Label2: TLabel;
    CustomizeDlg1: TCustomizeDlg;
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure dtpStartChange(Sender: TObject);
    procedure ckMidnightEphemClick(Sender: TObject);
  private
   { Private declarations }
       calc : IAstInstCalc;
{$IFNDEF DEBUG}
    coclass : TCAstInstCalc;
{$ENDIF }
    procedure FillHeader;
    procedure FillGrid;
    Procedure DoGridRow( iRow : Integer );

  public
    { Public declarations }
  end;

  TPlanNames = array[1..11] of ShortString;

const
  PlanNames: TPlanNames = ( 'Sun', 'Moon',
     'Mercury', 'Venus', 'Mars', 'Jupiter', 'Saturn',
     'Uranus', 'Neptune', 'Pluto', 'N Node');

var
  EphemForm: TEphemForm;


implementation

{$R *.dfm}

procedure TEphemForm.FormCreate(Sender: TObject);
begin
   {$IFNDEF DEBUG }
   coclass := TCAstInstCalc.Create(Self);
   calc := coclass.DefaultInterface;
{$ELSE}
   Calc := CoAstInstCalc.Create;
{$ENDIF}
end;

procedure TEphemForm.FormDestroy(Sender: TObject);
begin
{$IFNDEF DEBUG}
   coclass.Disconnect;
   coclass.Destroy;
{$ENDIF}
end;

procedure TEphemForm.FillHeader;
var
  i : Integer;
begin
  for i := 1 to 12 do
  begin
    sgPositions.Cells[i,0] := PlanNames[i];
  end;
end;

procedure TEphemForm.FillGrid;
var
  i : Integer;
begin
  for i:= 1 to 31 do
  begin
    DoGridRow( i );
  end;
end;

Procedure TEphemForm.DoGridRow( iRow : Integer );
var
   dtRow : TDateTime;
   iCol, hour, year, month, day : Word;
begin
   dtRow := dtpStart.Date + (iRow -1);
   DecodeDate(dtRow, year, month, day );
   if ckMidnightEphem.Checked then
     hour := 0
   else
     hour := 144;
   calc.StartAt(month,day,year,hour);
   sgPositions.Cells[0,iRow] := dateToStr(dtRow);
   for icol := 1 to 12 do
   begin
      calc.Index := iCol;
      sgPositions.Cells[iCol,iRow] := calc.Value + 'R';
   end;
end;

procedure TEphemForm.FormShow(Sender: TObject);
begin
   FillHeader;
   FillGrid;
end;

procedure TEphemForm.dtpStartChange(Sender: TObject);
begin
   FillGrid;
end;

procedure TEphemForm.ckMidnightEphemClick(Sender: TObject);
begin
   FillGrid;
end;

end.
