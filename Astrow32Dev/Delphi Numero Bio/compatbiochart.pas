unit compatbiochart;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls, TeeProcs, TeEngine, Chart, ComCtrls, StdCtrls,
  Series, biocalc_TLB, Grids, Menus, DB, DBCtrls, ADODB, ImgList, ToolWin,
  Buttons, demo;

type
  TCompatBioForm = class(TForm)
    Label1: TLabel;
    Label2: TLabel;
    dtpBirth: TDateTimePicker;
    dtpStart: TDateTimePicker;
    Chart1: TChart;
    Label3: TLabel;
    PageControl1: TPageControl;
    tsData: TTabSheet;
    tsGraph: TTabSheet;
    tsInterp: TTabSheet;
    sgText: TStringGrid;
    MainMenu1: TMainMenu;
    miOpen: TMenuItem;
    miExport: TMenuItem;
    miExit: TMenuItem;
    TextDialog: TSaveDialog;
    ADOConnection1: TADOConnection;
    DateQuery: TADOQuery;
    nameDataSource: TDataSource;
    SaveQuery: TADOQuery;
    ToolBar1: TToolBar;
    ToolButton3: TToolButton;
    ImageList1: TImageList;
    edtName: TEdit;
    Print1: TMenuItem;
    ToolButton4: TToolButton;
    Database1: TMenuItem;
    Maintenance1: TMenuItem;
    BmpDialog: TSaveDialog;
    SaveDialog1: TSaveDialog;
    Label4: TLabel;
    Label5: TLabel;
    dtpBirth2: TDateTimePicker;
    DBComboBox1: TDBLookupComboBox;
    DBComboBox2: TDBLookupComboBox;
    EdtName2: TEdit;
    ADOQuery1: TADOQuery;
    RecCheckQuery: TADOQuery;
    procedure FormCreate(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure PageControl1Change(Sender: TObject);
    procedure PageControl1Changing(Sender: TObject;
      var AllowChange: Boolean);
    procedure miExportClick(Sender: TObject);
    procedure miExitClick(Sender: TObject);
    procedure DBComboBox1Exit(Sender: TObject);
    procedure edtNameChange(Sender: TObject);
    procedure DBComboBox1Change(Sender: TObject);
    procedure Print1Click(Sender: TObject);
    procedure Maintenance1Click(Sender: TObject);
    procedure DBComboBox2CloseUp(Sender: TObject);
    procedure EdtName2Change(Sender: TObject);
  private
    tsPrev: TTabSheet;
    LineSeries1 : TLineSeries;
    LineSeries2 : TLineSeries;
    LineSeries3 : TLineSeries;
    LineSeries4 : TLineSeries;
    LineSeries5 : TLineSeries;
    LineSeries6 : TLineSeries;
    LineSeries7 : TLineSeries;
    LineSeries8 : TLineSeries;
    coclass : TCBioDataCalc;
    ICalc : IBioDataCalc;
    bRec1New : Boolean;
    bRec2New : Boolean;
    Procedure Calc;
    Procedure DbUpdate( sName : String; BDate : TDate; bAdd : Boolean);

    { Private declarations }
  public
    { Public declarations }
  end;

var
  CompatBioForm: TCompatBioForm;

implementation

uses DBConfig, inheritedregistry, dbmaint;


{$R *.dfm}

procedure TCompatBioForm.FormCreate(Sender: TObject);
var
   oDbConf : TDBConfig;
   mo, day, yr : Word;
begin
   oDbConf := TDbConfig.Create('Biorythms');
   AdoConnection1.Connected := False;
   AdoConnection1.Provider := oDbconf.Provider;
   AdoConnection1.ConnectionString := oDbConf.Connect;
   AdoConnection1.Connected := True;
   AdoQuery1.Open;
   coclass := TCBioDataCalc.Create(Application);
   ICalc := coclass.DefaultInterface;
   LineSeries1 := TLineSeries.Create(Chart1);
   LineSeries1.ParentChart := Chart1;
   LineSeries1.Title := 'First Person Physical';
   LineSeries1.LinePen.Color := clRed;
   LineSeries1.AreaColor := clRed;
   LineSeries1.SeriesColor := clRed;
   LineSeries1.LinePen.Style := psSolid;
   LineSeries1.LinePen.Width := 2;

   LineSeries2 := TLineSeries.Create(Chart1);
   LineSeries2.ParentChart := Chart1;
   LineSeries2.Title := 'First Person Emotional';
   LineSeries2.LinePen.Color := clBlue;
   LineSeries2.AreaColor := clBlue;
   LineSeries2.SeriesColor := clBlue;
   LineSeries2.LinePen.Style := psSolid;
   LineSeries2.LinePen.Width := 2;

   LineSeries3 := TLineSeries.Create(Chart1);
   LineSeries3.ParentChart := Chart1;
   LineSeries3.Title := 'First Person Intellectual';
   LineSeries3.LinePen.Color := clGreen;
   LineSeries3.AreaColor := clGreen;
   LineSeries3.SeriesColor := clGreen;
   LineSeries3.LinePen.Style := psSolid;
   LineSeries3.LinePen.Width := 2;

   LineSeries4 := TLineSeries.Create(Chart1);
   LineSeries4.ParentChart := Chart1;
   LineSeries4.Title := 'First Person Critical';
   LineSeries4.LinePen.Color := clYellow;
   LineSeries4.AreaColor := clYellow;
   LineSeries4.SeriesColor := clYellow;
   LineSeries4.LinePen.Style := psSolid;
   LineSeries4.LinePen.Width := 2;

   LineSeries5 := TLineSeries.Create(Chart1);
   LineSeries5.ParentChart := Chart1;
   LineSeries5.Title := 'Second Person Physical';
   LineSeries5.LinePen.Color := clAqua;
   LineSeries5.AreaColor := clAqua;
   LineSeries5.SeriesColor := clAqua;
   LineSeries5.LinePen.Style := psSolid;
   LineSeries5.LinePen.Width := 2;

   LineSeries6 := TLineSeries.Create(Chart1);
   LineSeries6.ParentChart := Chart1;
   LineSeries6.Title := 'Second Person Emotional';
   LineSeries6.LinePen.Color := clLime;
   LineSeries6.AreaColor := clLime;
   LineSeries6.SeriesColor := clLime;
   LineSeries6.LinePen.Style := psSolid;
   LineSeries6.LinePen.Width := 2;

   LineSeries7 := TLineSeries.Create(Chart1);
   LineSeries7.ParentChart := Chart1;
   LineSeries7.Title := 'Second Person Intellectual';
   LineSeries7.LinePen.Color := clFuchsia;
   LineSeries7.AreaColor := clFuchsia;
   LineSeries7.SeriesColor := clFuchsia;
   LineSeries7.LinePen.Style := psSolid;
   LineSeries7.LinePen.Width := 2;

   LineSeries8 := TLineSeries.Create(Chart1);
   LineSeries8.ParentChart := Chart1;
   LineSeries8.Title := 'Second Person Critical';
   LineSeries8.LinePen.Color := clTeal;
   LineSeries8.AreaColor := clTeal;
   LineSeries8.SeriesColor := clTeal;
   LineSeries8.LinePen.Style := psSolid;
   LineSeries8.LinePen.Width := 2;
   DecodeDate(Date,yr,mo,day);
   dtpStart.Date := EncodeDate(yr,mo,1);
   dtpBirth.Date := Date;
   dtpBirth2.Date := Date;
   {$IFDEF DEMO}
   DoDemoCheck('Biorythms');
   {$ENDIF}
end;

procedure TCompatBioForm.FormShow(Sender: TObject);
begin
   PageControl1.ActivePage := tsData;
   sgText.Cells[1,0] := 'Physical #1';
   sgText.Cells[3,0] := 'Emotional #1';
   sgText.Cells[5,0] := 'Intellectual #1';
   sgText.Cells[7,0] := 'Critical #1';
   sgText.Cells[2,0] := 'Physical #2';
   sgText.Cells[4,0] := 'Emotional #2';
   sgText.Cells[6,0] := 'Intellectual #2';
   sgText.Cells[8,0] := 'Critical #2';
end;

procedure TCompatBioForm.Calc;
var
  dtdate : TDateTime;
  index  : integer;
begin
  ICalc.PersName := edtName.Text;
  ICalc.BirthDate := dtpBirth.Date;
  ICalc.StartDate := dtpStart.Date;
  ICalc.Calc;
  DbUpdate(edtName.Text,dtpBirth.Date, bRec1New);
  LineSeries1.Clear;
  LineSeries2.Clear;
  LineSeries3.Clear;
  LineSeries4.Clear;
  Chart1.Title.Text.Clear;
  Chart1.Title.Text.Add('Biorythms Graph');
  Chart1.Title.Text.Add('Name: ' + edtName.Text + ' and ' + edtName2.Text);
  Chart1.Title.Text.Add('Birth Date: ' + DateToStr(dtpBirth.Date) + ' and ' +
     DateToStr(dtpBirth2.Date) + ' Start Date: ' + DateToStr(dtpStart.Date));
  Chart1.BottomAxis.Maximum := ICalc.Days;
  for index := 1 to ICalc.Days do
  begin
     dtDate := dtpStart.Date + (index-1.0);
     ICalc.Index := index-1;
     sgText.Cells[0,index] := DateToStr(dtDate);
     sgText.Cells[1,Index] := ICalc.PhysicalDesc;
     sgText.Cells[3,Index] := ICalc.EmotionalDesc;
     sgText.Cells[5,Index] := ICalc.IntellectualDesc;
     sgText.Cells[7,Index] := ICalc.CriticalDesc;
     LineSeries1.AddXY(Index,Icalc.Physical * 100.0);
     LineSeries2.AddXY(Index,Icalc.Emotional * 100.0);
     LineSeries3.AddXY(Index,ICalc.Intellectual * 100.0);
     LineSeries4.AddXY(Index,Icalc.Critical * 100.0);
  end;
  ICalc.PersName := edtName2.Text;
  ICalc.BirthDate := dtpBirth2.Date;
  ICalc.StartDate := dtpStart.Date;
  ICalc.Calc;
  DbUpdate(edtName2.Text,dtpBirth2.Date,bRec1New);
  LineSeries5.Clear;
  LineSeries6.Clear;
  LineSeries7.Clear;
  LineSeries8.Clear;
  for index := 1 to ICalc.Days do
  begin
     ICalc.Index := index-1;
     sgText.Cells[2,Index] := ICalc.PhysicalDesc;
     sgText.Cells[4,Index] := ICalc.EmotionalDesc;
     sgText.Cells[6,Index] := ICalc.IntellectualDesc;
     sgText.Cells[8,Index] := ICalc.CriticalDesc;
     LineSeries5.AddXY(Index,Icalc.Physical * 100.0);
     LineSeries6.AddXY(Index,Icalc.Emotional * 100.0);
     LineSeries7.AddXY(Index,ICalc.Intellectual * 100.0);
     LineSeries8.AddXY(Index,Icalc.Critical * 100.0);
  end;
end;


procedure TCompatBioForm.PageControl1Change(Sender: TObject);
begin
   if PageControl1.ActivePage=tsGraph then
      Print1.Enabled := true
   else
      Print1.Enabled := false;
   if PageControl1.ActivePage = tsGraph then
      miExport.Enabled := True
   else
      miExport.Enabled := False;
   if (PageControl1.ActivePage <> tsData) and (tsPrev=tsData) then
      Calc;
end;

procedure TCompatBioForm.PageControl1Changing(Sender: TObject;
  var AllowChange: Boolean);
begin
  if length(edtName.Text)=0 then
  begin
     ShowMessage('You Must Fill in or Select Name 1');
     AllowChange := False;
     exit;
  end;
  if length(edtName2.Text)=0 then
  begin
     ShowMessage('You Must Fill in or Select Name 2');
     AllowChange := False;
     Exit;
  end;
  tsPrev := PageControl1.ActivePage;
  AllowChange := True;
end;


procedure TCompatBioForm.miExportClick(Sender: TObject);
begin
   if PageControl1.ActivePage=tsGraph then
   begin
      with BmpDialog do
      begin
         if Execute then
         begin
            Chart1.SaveToBitmapFile(FileName);
         end;
      end;
   end;
end;

procedure TCompatBioForm.miExitClick(Sender: TObject);
begin
   Application.Terminate;
end;


procedure TCompatBioForm.DBComboBox1Exit(Sender: TObject);
begin
  //
end;

procedure TCompatBioForm.edtNameChange(Sender: TObject);
begin
   bRec1New := TRUE;
   //DbComboBox1.index := DBComboBox1.Items.IndexOf(EdtName.Text);
end;

procedure TCompatBioForm.DBComboBox1Change(Sender: TObject);
begin
   edtName.Text := DbComboBox1.Text;
   with DateQuery do
   begin
      Parameters.ParamByName('name1').Value := DbComboBox1.Text;
      Parameters.ParamByName('name2').Value := DbComboBox1.Text;
      Open;
      if not Eof then
      begin
         dtpBirth.Date := FieldByName('BirthDate').AsDateTime;
         bRec1New := False;
      end;
      Close;
   end;
end;

procedure TCompatBioForm.Print1Click(Sender: TObject);
begin
   if PageControl1.ActivePage=tsGraph then
      Chart1.Print;
end;

procedure TCompatBioForm.Maintenance1Click(Sender: TObject);
begin
   with  TDBMaintForm.Create(Application) do
   begin
      ShowModal;
      Close;
      Free;
   End;
end;


procedure TCompatBioForm.DBComboBox2CloseUp(Sender: TObject);
begin
   edtName2.Text := DbComboBox2.Text;
   with DateQuery do
   begin
      Parameters.ParamByName('name1').Value := DbComboBox2.Text;
      Parameters.ParamByName('name2').Value := DbComboBox2.Text;
      Open;
      if not Eof then
      begin
         dtpBirth2.Date := FieldByName('BirthDate').AsDateTime;
         bRec2New := False;
      end;
      Close;
   end;
end;

procedure TCompatBioForm.DbUpdate( sName : String; BDate : TDate; bAdd : Boolean);
var
  bUpdate : Boolean;
begin
  AdoQuery1.Close;
  bUpdate := not bAdd;
  if not bUpdate then
  begin
     with DateQuery do
     begin
       Parameters.ParamByName('name').Value := edtName.Text;
       Open;
       if not Eof then
         bUpdate := True
       else
         bUpdate := False;
       Close;
     end;
  end;
  if bUpdate then
  begin
    With SaveQuery do
    begin
       SQL.Clear;
       SQL.Add('UPDATE biorythms set BirthDate = :date where Name = :date');
       Parameters.Clear;
       Parameters.CreateParameter('date',ftString,pdInput,-1,DateToStr(bDate));
       Parameters.CreateParameter('name',ftString,pdInput,-1,sName);
       Prepared := True;
       ExecSQL;
       Close
    end;
  end else
  begin
    With SaveQuery do
    begin
       SQL.Clear;
       SQL.Add('INSERT INTO biorythms(BirthDate,Name) VALUES(:date,:name)');
       Parameters.Clear;
       Parameters.CreateParameter('date',ftString,pdInput,-1,DateToStr(bDate));
       Parameters.CreateParameter('name',ftString,pdInput,-1,sName);
       Prepared := True;
       ExecSQL;
       Close;
    end;
  end;
  AdoQuery1.Open;
end;

procedure TCompatBioForm.EdtName2Change(Sender: TObject);
begin
   bRec2New := True;
end;

end.
