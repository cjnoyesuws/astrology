unit biochart;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls, TeeProcs, TeEngine, Chart, ComCtrls, StdCtrls,
  Series, biocalc_TLB, Grids, Menus, DB, DBCtrls, ADODB, ImgList, ToolWin,
  Buttons, demo, AppEvnts, Inifiles, jpeg;

type
  TBioForm = class(TForm)
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
    Open1: TMenuItem;
    miSave: TMenuItem;
    miExport: TMenuItem;
    miExit: TMenuItem;
    OpenDialog1: TOpenDialog;
    TextDialog: TSaveDialog;
    ADOConnection1: TADOConnection;
    DateQuery: TADOQuery;
    nameDataSource: TDataSource;
    SaveQuery: TADOQuery;
    ToolBar1: TToolBar;
    ToolButton1: TToolButton;
    ToolButton2: TToolButton;
    ToolButton3: TToolButton;
    ImageList1: TImageList;
    edtName: TEdit;
    DBComboBox1: TDBLookupComboBox;
    Print1: TMenuItem;
    ToolButton4: TToolButton;
    Database1: TMenuItem;
    Maintenance1: TMenuItem;
    BmpDialog: TSaveDialog;
    SaveDialog1: TSaveDialog;
    NameQuery: TADOQuery;
    RecCheckQuery: TADOQuery;
    procedure FormCreate(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure PageControl1Change(Sender: TObject);
    procedure PageControl1Changing(Sender: TObject;
      var AllowChange: Boolean);
    procedure miSaveClick(Sender: TObject);
    procedure miExportClick(Sender: TObject);
    procedure miExitClick(Sender: TObject);
    procedure Open1Click(Sender: TObject);
    procedure DBComboBox1Exit(Sender: TObject);
    procedure edtNameChange(Sender: TObject);
    procedure DBComboBox1Change(Sender: TObject);
    procedure Print1Click(Sender: TObject);
    procedure Maintenance1Click(Sender: TObject);
  private
    tsPrev: TTabSheet;
    LineSeries1 : TLineSeries;
    LineSeries2 : TLineSeries;
    LineSeries3 : TLineSeries;
    LineSeries4 : TLineSeries;
    ICalc : IBioDataCalc;
    RecAdded : Boolean;
    auto : Boolean;
    autocnf : TIniFile;
    autofile : String;
    autoname : String;
    autocss : String;
    autobirth : TDateTime;
    autostart : TDateTime;
    Procedure Calc;
    procedure Automate;
    Procedure OpenAutoFile;
    procedure ExportAuto;
    { Private declarations }
  public
    { Public declarations }
  end;

var
  BioForm: TBioForm;

implementation

uses DBConfig, inheritedregistry, dbmaint;


{$R *.dfm}

procedure TBioForm.FormCreate(Sender: TObject);
var
   oDbConf : TDBConfig;
   month, day, year : word;
begin
   if (ParamCount > 1) and (paramStr(1)='auto') then
   begin
      auto := true;
      autofile := paramStr(2);
      autocnf := TIniFile.Create(ParamStr(2));
      autoname := autocnf.ReadString('chart', 'name', 'My Name');
      autobirth := StrToDate(autocnf.ReadString('chart', 'birth', datetoStr(date)));
      autostart := StrToDate(autocnf.ReadString('chart', 'start', datetoStr(date)));
      autocss := autocnf.ReadString('chart', 'css', '');
   end else begin
      AdoConnection1.Connected := False;
      oDbConf := TDbConfig.Create('Biorythms');
      AdoConnection1.Provider := oDbconf.Provider;
      AdoConnection1.ConnectionString := oDbConf.Connect;
      AdoConnection1.Connected := True;
      NameQuery.Open;
   end;
   ICalc := CoCBioDataCalc.Create;
   LineSeries1 := TLineSeries.Create(Chart1);
   LineSeries1.ParentChart := Chart1;
   LineSeries1.Title := 'Physical';
   LineSeries1.LinePen.Color := clRed;
   LineSeries1.AreaColor := clRed;
   LineSeries1.SeriesColor := clRed;
   LineSeries1.LinePen.Style := psSolid;
   LineSeries1.LinePen.Width := 2;

   LineSeries2 := TLineSeries.Create(Chart1);
   LineSeries2.ParentChart := Chart1;
   LineSeries2.Title := 'Emotional';
   LineSeries2.LinePen.Color := clBlue;
   LineSeries2.AreaColor := clBlue;
   LineSeries2.SeriesColor := clBlue;
   LineSeries2.LinePen.Style := psSolid;
   LineSeries2.LinePen.Width := 2;

   LineSeries3 := TLineSeries.Create(Chart1);
   LineSeries3.ParentChart := Chart1;
   LineSeries3.Title := 'Intellectual';
   LineSeries3.LinePen.Color := clGreen;
   LineSeries3.AreaColor := clGreen;
   LineSeries3.SeriesColor := clGreen;
   LineSeries3.LinePen.Style := psSolid;
   LineSeries3.LinePen.Width := 2;

   LineSeries4 := TLineSeries.Create(Chart1);
   LineSeries4.ParentChart := Chart1;
   LineSeries4.Title := 'Critical';
   LineSeries4.LinePen.Color := clYellow;
   LineSeries4.AreaColor := clYellow;
   LineSeries4.SeriesColor := clYellow;
   LineSeries4.LinePen.Style := psSolid;
   LineSeries4.LinePen.Width := 2;
   DecodeDate(Date,year,month,day);
   dtpStart.Date := EncodeDate(year,month,1);
   dtpBirth.Date := Date;

   {$IFDEF DEMO}
   doDemoCheck('Biorythms');
   {$ENDIF}
end;

procedure TBioForm.FormShow(Sender: TObject);
begin
   PageControl1.ActivePage := tsData;
   sgText.Cells[1,0] := 'Physical';
   sgText.Cells[2,0] := 'Emotional';
   sgText.Cells[3,0] := 'Intellectual';
   sgText.Cells[4,0] := 'Critical';
   if auto then
      automate;
end;

procedure TBioForm.Calc;
var
  dtdate : TDateTime;
  index  : integer;
  bUpdate : Boolean;
begin
  if (not auto) then
  begin
    NameQuery.Close;
    ICalc.PersName := edtName.Text;
    ICalc.BirthDate := dtpBirth.Date;
    ICalc.StartDate := dtpStart.Date;
  end else
  begin
    ICalc.PersName := autoname;
    ICalc.BirthDate := autobirth;
    ICalc.StartDate := autostart;
  end;
  ICalc.Calc;
  if (not auto) then
  begin
    bUpdate := not RecAdded;
    if not bUpdate then
    begin
       with RecCheckQuery do
       begin
          Parameters.Clear;
          Parameters.CreateParameter('name',ftString,pdInput,-1,edtName.Text);
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
         SQL.Add('UPDATE biorythms set BirthDate = :date where Name = :name');
         Parameters.Clear;
         Parameters.CreateParameter('date',ftString,pdInput,-1,DateToStr(dtpBirth.Date));
         Parameters.CreateParameter('name',ftString,pdInput,-1,edtName.Text);
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
         Parameters.CreateParameter('date',ftString,pdInput,-1,DateToStr(dtpBirth.Date));
         Parameters.CreateParameter('name',ftString,pdInput,-1,edtName.Text);
         ExecSQL;
         Close;
      end;
    end;
  end;
  LineSeries1.Clear;
  LineSeries2.Clear;
  LineSeries3.Clear;
  LineSeries4.Clear;
  Chart1.Title.Text.Clear;
  Chart1.Title.Text.Add('Biorythms Graph');
  if not auto then
  begin
    Chart1.Title.Text.Add('Name: ' + edtName.Text);
    Chart1.Title.Text.Add('Birth Date: ' + DateToStr(dtpBirth.Date) + ' Start Date: ' +
       DateToStr(dtpStart.Date));
  end else
    Chart1.Title.Text.Add('Name: ' + autoname);
    Chart1.Title.Text.Add('Birth Date: ' + DateToStr(autobirth) + ' Start Date: ' +
       DateToStr(autostart));
  begin
  end;
  Chart1.BottomAxis.Maximum := ICalc.Days;
  for index := 1 to ICalc.Days do
  begin
     dtDate := dtpStart.Date + (index-1.0);
     ICalc.Index := index-1;
     sgText.Cells[0,index] := DateToStr(dtDate);
     sgText.Cells[1,Index] := ICalc.PhysicalDesc;
     sgText.Cells[2,Index] := ICalc.EmotionalDesc;
     sgText.Cells[3,Index] := ICalc.IntellectualDesc;
     sgText.Cells[4,Index] := ICalc.CriticalDesc;
     LineSeries1.AddXY(Index,Icalc.Physical * 100.0);
     LineSeries2.AddXY(Index,Icalc.Emotional * 100.0);
     LineSeries3.AddXY(Index,ICalc.Intellectual * 100.0);
     LineSeries4.AddXY(Index,Icalc.Critical * 100.0);
  end;
  LineSeries1.Active := True;
  LineSeries2.Active := True;
  LineSeries3.Active := True;
  LineSeries4.Active := True;
  If not auto then
     NameQuery.Open;
end;


procedure TBioForm.PageControl1Change(Sender: TObject);
begin
   if (PageControl1.ActivePage <> tsData) and (tsPrev=tsData) then
      Calc;
   if PageControl1.ActivePage=tsGraph then
      Print1.Enabled := true
   else
      Print1.Enabled := false;
   if PageControl1.ActivePage = tsData then
      miExport.Enabled := False
   else
      miExport.Enabled := True;
end;

procedure TBioForm.PageControl1Changing(Sender: TObject;
  var AllowChange: Boolean);
begin
  if (Length(edtName.Text) = 0) and (not auto) then
  begin
    ShowMessage('You Must Select or Enter a Name');
    Allowchange := False;
    exit;
  end;
  tsPrev := PageControl1.ActivePage;
  AllowChange := True;
end;

procedure TBioForm.miSaveClick(Sender: TObject);
begin
   With SaveDialog1 do
      begin
         if Execute then
         begin
            ICalc.PersName := edtName.Text;
            ICalc.BirthDate := dtpBirth.Date;
            ICalc.StartDate := dtpStart.Date;
            ICalc.SaveData(FileName);
         end;
     end;
end;

procedure TBioForm.miExportClick(Sender: TObject);
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
   end else
   begin
      With TextDialog do
      begin
         if Execute then
         begin
            ICalc.PersName := edtName.Text;
            ICalc.BirthDate := dtpBirth.Date;
            ICalc.StartDate := dtpStart.Date;
            ICalc.Calc;
            ICalc.Export(FileName);
         end;
      end;
   end;
end;

procedure TBioForm.miExitClick(Sender: TObject);
begin
   Application.Terminate;
end;

procedure TBioForm.Open1Click(Sender: TObject);
begin
   With OpenDialog1 do
   begin
      if Execute then
      begin
         ICalc.LoadData(FileName);
         edtName.Text := ICalc.PersName;
         dtpBirth.Date := ICalc.BirthDate;
         dtpStart.Date := ICalc.StartDate;
         ICalc.Calc;
      end;
   end;
end;

procedure TBioForm.DBComboBox1Exit(Sender: TObject);
begin
  //
end;

procedure TBioForm.edtNameChange(Sender: TObject);
begin
   RecAdded := True;
end;

procedure TBioForm.DBComboBox1Change(Sender: TObject);
begin
   if ( not auto ) then
   begin
     edtName.Text := DbComboBox1.Text;
     with DateQuery do
     begin
        Parameters.Clear;
        Parameters.CreateParameter('name1',ftString,pdInput,-1,DBComboBox1.Text);
        Parameters.CreateParameter('name2',ftString,pdInput,-1,DBComboBox1.Text);
        Open;
        if not Eof then
        begin
         dtpBirth.Date := FieldByName('BirthDate').AsDateTime;
         RecAdded := False;
        end;
        Close;
     end;
   end;
end;

procedure TBioForm.Print1Click(Sender: TObject);
begin
   if PageControl1.ActivePage=tsGraph then
      Chart1.Print;
end;

procedure TBioForm.Maintenance1Click(Sender: TObject);
begin
   with  TDBMaintForm.Create(Application) do
   begin
      ShowModal;
      Close;
      Free;
   End;
end;

procedure TBioForm.Automate;
begin
   OpenAutoFile;
   ExportAuto;
end;

Procedure TBioForm.OpenAutoFile;
begin
   Calc;
end;

procedure TBioForm.ExportAuto;
var
  FileName : String;
  ipos : integer;
  jpeg: TJpegImage;
  bmp: TBitmap;
begin
   if copy(autofile,1,1)='.' then
      ipos := pos('.',copy(autofile,2,length(autofile)-1))+1
   else
      ipos := pos('.',autofile);
   FileName := copy(autofile,1,ipos-1);
   PageControl1.ActivePage:=tsGraph;
   Chart1.SaveToBitmapFile(FileName+'.bmp');
   bmp := TBitmap.Create;
   bmp.LoadFromFile(FileName+'.bmp');
   jpeg := TJpegImage.Create;
   jpeg.Assign(bmp);
   jpeg.CompressionQuality := 50;
   jpeg.SaveToFile(FileName+'.jpg');
   bmp.Free;
   jpeg.Free;
   DeleteFile(FileName+'.bmp');
   PageControl1.ActivePage:=tsData;
   ICalc.PersName := autoname;
   ICalc.BirthDate := autobirth;
   ICalc.StartDate := autostart;
   if (length(autocss)>0) then
      ICalc.CSS := autocss;
   ICalc.Calc;
   ICalc.Export(FileName+'.csv');
   ICalc.Export(FileName+'.html');
   Application.Terminate;
end;

end.
