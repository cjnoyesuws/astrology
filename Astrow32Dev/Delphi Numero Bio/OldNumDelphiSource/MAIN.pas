unit Main;

interface

uses SysUtils, WinTypes, WinProcs, Messages, Classes, Graphics, Controls, Forms,
  Menus, Dialogs, Buttons, ExtCtrls, NumDll31,ViewTx31, ChildWin, birthdat,
  about, options, openf31, years, Udc_win, Udc_stat, inifiles, demo;

type
  TMainForm = class(TForm)
    MainMenu1: TMainMenu;
    File1: TMenuItem;
    FileCloseItem: TMenuItem;
    Window1: TMenuItem;
    Help1: TMenuItem;
    N1: TMenuItem;
    FileExitItem: TMenuItem;
    WindowCascadeItem: TMenuItem;
    WindowTileItem: TMenuItem;
    WindowArrangeItem: TMenuItem;
    FileSaveItem: TMenuItem;
    FileSaveAsItem: TMenuItem;
    Edit1: TMenuItem;
    CutItem: TMenuItem;
    CopyItem: TMenuItem;
    PasteItem: TMenuItem;
    WindowMinimizeItem: TMenuItem;
    SpeedPanel: TPanel;
    sbOpen: TSpeedButton;
    sbSave: TSpeedButton;
    NumerologyData1: TMenuItem;
    Utilities1: TMenuItem;
    ReadFileIntoData1: TMenuItem;
    Options1: TMenuItem;
    sbPrint: TSpeedButton;
    sbNumData: TSpeedButton;
    sbSaveAs: TSpeedButton;
    CompileJustData1: TMenuItem;
    FilePrintItem: TMenuItem;
    SaveDialog1: TSaveDialog;
    PrintDialog1: TPrintDialog;
    PrinterSetupDialog1: TPrinterSetupDialog;
    FileOpenItem: TMenuItem;
    Interactive: TMenuItem;
    HelpAboutItem: TMenuItem;
    FilePrintSetupItem: TMenuItem;
    NameTransitsData: TMenuItem;
    NameTransitsText: TMenuItem;
    CompileJustData2: TMenuItem;
    UdcStatusPanel1: TUdcStatusPanel;
    procedure FormCreate(Sender: TObject);
    procedure WindowCascadeItemClick(Sender: TObject);
    procedure UpdateMenuItems(Sender: TObject);
    procedure WindowTileItemClick(Sender: TObject);
    procedure WindowArrangeItemClick(Sender: TObject);
    procedure FileCloseItemClick(Sender: TObject);
    procedure FileExitItemClick(Sender: TObject);
    procedure FileSaveItemClick(Sender: TObject);
    procedure FileSaveAsItemClick(Sender: TObject);
    procedure CutItemClick(Sender: TObject);
    procedure CopyItemClick(Sender: TObject);
    procedure PasteItemClick(Sender: TObject);
    procedure WindowMinimizeItemClick(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure sbNumDataClick(Sender: TObject);
    procedure NumerologyData1Click(Sender: TObject);
    procedure HelpAboutItemClick(Sender: TObject);
    procedure Options1Click(Sender: TObject);
    procedure CompileJustData2Click(Sender: TObject);
    procedure CompileJustData1Click(Sender: TObject);
    procedure NameTransitsData1Click(Sender: TObject);
    procedure NameTransitsText1Click(Sender: TObject);
    procedure PrinterSetup1Click(Sender: TObject);
    procedure FileOpenItemClick(Sender: TObject);
    procedure ReadFileIntoData1Click(Sender: TObject);
    procedure Print1Click(Sender: TObject);
    procedure interactiveClick(Sender: TObject);
    procedure FormShow(Sender: TObject);
  private
    { Private declarations }
    procedure ShowHint(Sender: TObject);
  public
    { Public declarations }
  end;

var
  MainForm: TMainForm;
  {$IFDEF DEMO}demo_mode : integer;
  inifile :Tinifile;
  {$ENDIF DEMO}

implementation

{$R *.DFM}

{$IFDEF WIN32}
uses Birthdat, about, Options, Openf, Years;
{$lse}
uses Birthdat, about, Options, Openf31, Years;
{$ENDIF}
procedure TMainForm.FormCreate(Sender: TObject);
begin
  Application.OnHint := ShowHint;
  Screen.OnActiveFormChange := UpdateMenuItems;
end;

procedure TMainForm.ShowHint(Sender: TObject);
begin
if Application.Hint='' then UdcStatusPanel1.WriteMessage(ptPanel1, Application.Hint)
else UdcStatusPanel1.WriteMessage(ptMessagePanel, Application.Hint);
end;

procedure TMainForm.FileCloseItemClick(Sender: TObject);
begin
  if ActiveMDIChild <> nil then
    ActiveMDIChild.Close;
end;

procedure TMainForm.FileSaveItemClick(Sender: TObject);
var
Name : array [0..150] of char;
NewName : array [0..150] of char;
{ save current file (ActiveMDIChild points to the window) }
begin
    if ActiveMDIChild <> nil then
       begin
       StrPCopy( Name, TfrmViewText31(ActiveMDIChild).GetName );
       DoRTFSettings( 10, 700, 0 );
       with SaveDialog1 do
          begin
          Title := 'File Name To Save To';
          Filter := 'Text Files (*.txt)|*.txt|Document Files (*.doc)|*.doc|'+
            'Rich Text Files (*.rtf)|*.rtf|AMI Pro Files (*.sam)|*.sam|'+
            'WordPerfect Docs (*.wpd)|*.wpd|HTML Files (*.htm)|*.htm';
          if Execute then StrPCopy(NewName,FileName)
          else exit;
          end;
       UdcStatusPanel1.WriteMessage(ptMessagePanel, 'Converting.');
       ConvertToRTF( Name, NewName );
       MessageBeep(0);
       UdcStatusPanel1.WriteMessage(ptMessagePanel, 'Ready.');
       end;
end;

procedure TMainForm.FileSaveAsItemClick(Sender: TObject);
  { save current file under new name }
begin
FileSaveItemClick(Sender);
end;

procedure TMainForm.FileExitItemClick(Sender: TObject);
begin
  Close;
end;

procedure TMainForm.CutItemClick(Sender: TObject);
begin
  {cut selection to clipboard}
end;

procedure TMainForm.CopyItemClick(Sender: TObject);
begin
  {copy selection to clipboard}
end;

procedure TMainForm.PasteItemClick(Sender: TObject);
begin
  {paste from clipboard}
end;

procedure TMainForm.WindowCascadeItemClick(Sender: TObject);
begin
  Cascade;
end;

procedure TMainForm.WindowTileItemClick(Sender: TObject);
begin
  Tile;
end;

procedure TMainForm.WindowArrangeItemClick(Sender: TObject);
begin
  ArrangeIcons;
end;

procedure TMainForm.WindowMinimizeItemClick(Sender: TObject);
var
  I: Integer;
begin
  { Must be done backwards through the MDIChildren array }
  for I := MDIChildCount - 1 downto 0 do
    MDIChildren[I].WindowState := wsMinimized;
end;

procedure TMainForm.UpdateMenuItems(Sender: TObject);
begin
  FileCloseItem.Enabled := MDIChildCount > 0;
  FileSaveItem.Enabled := MDIChildCount > 0;
  FilePrintItem.Enabled := MDIChildCount > 0;
  FileSaveAsItem.Enabled := MDIChildCount > 0;
  CutItem.Enabled := MDIChildCount > 0;
  CopyItem.Enabled := MDIChildCount > 0;
  PasteItem.Enabled := MDIChildCount > 0;
  sbSave.Enabled := MDIChildCount > 0;
  sbPrint.Enabled := MDIChildCount > 0;
  sbSaveAs.Enabled := MDIChildCount > 0;
  WindowCascadeItem.Enabled := MDIChildCount > 0;
  WindowTileItem.Enabled := MDIChildCount > 0;
  WindowArrangeItem.Enabled := MDIChildCount > 0;
  WindowMinimizeItem.Enabled := MDIChildCount > 0;
end;

procedure TMainForm.FormDestroy(Sender: TObject);
begin
  Screen.OnActiveFormChange := nil;
end;

procedure TMainForm.sbNumDataClick(Sender: TObject);
begin
frmNumData.ShowModal;
end;

procedure TMainForm.NumerologyData1Click(Sender: TObject);
begin
frmNumData.ShowModal;
end;

procedure TMainForm.HelpAboutItemClick(Sender: TObject);
begin
AboutBox.showModal;
end;

procedure TMainForm.Options1Click(Sender: TObject);
begin
frmOptions.showModal;
end;

procedure TMainForm.CompileJustData2Click(Sender: TObject);
var
   fid : FILE_ID;
   name : string;
   ft : TFileType;
   cstr : array[0..150] of Char;
begin
UpdateDll;
frmOpenFile.SetMode( osmCreateFile );
frmOpenFile.SetInitial(NumerologyData.at_birth);
frmOpenFile.showModal;
if frmOpenFile.ModalResult<>mrOk then exit;
if frmOpenFile.GetSelection(name, fid, ft ) then
   begin
   SetFileInfo( fid );
   UdcStatusPanel1.WriteMessage(ptMessagePanel, 'Compiling.');
{$IFDEF DEMO }
   CompileReport( NUMERIC_FILE+demo_mode, StrPCopy(cstr,name) );
{$ELSE }
   CompileReport( NUMERIC_FILE, StrPCopy(cstr,name) );
{$ENDIF }
   MessageBeep(0);
   UdcStatusPanel1.WriteMessage(ptMessagePanel, 'Ready.');
   end
else
   exit;
end;

procedure TMainForm.CompileJustData1Click(Sender: TObject);
var
   fid : FILE_ID;
   name : string;
   ft : TFileType;
   cstr : array[0..150] of Char;
begin
UpdateDll;
frmOpenFile.SetMode( osmCreateFile );
frmOpenFile.SetInitial(NumerologyData.at_birth);
frmOpenFile.showModal;
if frmOpenFile.ModalResult<>mrOk then exit;
if frmOpenFile.GetSelection(name, fid, ft ) then
   begin
   SetFileInfo( fid );
   UdcStatusPanel1.WriteMessage(ptMessagePanel, 'Compiling.');
{$IFDEF DEMO }
   CompileReport( PERSON_FILE+demo_mode, StrPCopy(cstr,name) );
{$ELSE }
   CompileReport( PERSON_FILE, StrPCopy(cstr,name) );
{$ENDIF }
   MessageBeep(0);
   UdcStatusPanel1.WriteMessage(ptMessagePanel, 'Ready.');
   end
else
   exit;

end;

procedure TMainForm.NameTransitsData1Click(Sender: TObject);
var
   fid : FILE_ID;
   name : string;
   ft : TFileType;
   first, last : smallint;
   cstr : array[0..150] of Char;
begin
UpdateDll;
frmOpenFile.SetMode( osmCreateFile );
frmOpenFile.SetInitial(NumerologyData.at_birth);
frmOpenFile.showModal;
if frmOpenFile.ModalResult<>mrOk then exit;
if frmOpenFile.GetSelection(name, fid, ft ) then
   begin
   SetFileInfo( fid );
   frmNameTrans.SetBirth(NumerologyData.birth_date.year);
   frmNameTrans.ShowModal;
   if frmNameTrans.ModalResult<>mrOk then exit;
   frmNameTrans.GetYears(first,last);
   SetGroupStartEnd( first, last );
   UdcStatusPanel1.WriteMessage(ptMessagePanel, 'Compiling.');
{$IFDEF DEMO }
   CompileReport( NUMGRAPH_FILE+demo_mode, StrPCopy(cstr,name) );
{$ELSE }
   CompileReport( NUMGRAPH_FILE, StrPCopy(cstr,name) );
{$ENDIF }
   MessageBeep(0);
   UdcStatusPanel1.WriteMessage(ptMessagePanel, 'Ready.');
   end
else
   exit;
end;

procedure TMainForm.NameTransitsText1Click(Sender: TObject);
var
   fid : FILE_ID;
   name : string;
   ft : TFileType;
   first, last : smallint;
   cstr : array[0..150] of Char;
begin
UpdateDll;
frmOpenFile.SetMode( osmCreateFile );
frmOpenFile.SetInitial(NumerologyData.at_birth);
frmOpenFile.showModal;
if frmOpenFile.ModalResult<>mrOk then exit;
if frmOpenFile.GetSelection(name, fid, ft ) then
   begin
   SetFileInfo( fid );
   frmNameTrans.SetBirth(NumerologyData.birth_date.year);
   frmNameTrans.ShowModal;
   if frmNameTrans.ModalResult<>mrOk then exit;
   frmNameTrans.GetYears(first,last);
   SetGroupStartEnd( first, last );
   UdcStatusPanel1.WriteMessage(ptMessagePanel, 'Compiling.');
{$IFDEF DEMO }
   CompileReport( NAMEGRAPH_FILE+demo_mode, StrPCopy(cstr,name) );
{$ELSE }
   CompileReport( NAMEGRAPH_FILE, StrPCopy(cstr,name) );
{$ENDIF }
   MessageBeep(0);
   UdcStatusPanel1.WriteMessage(ptMessagePanel, 'Ready.');
   end
else
   exit;
end;

procedure TMainForm.PrinterSetup1Click(Sender: TObject);
begin
PrinterSetupDialog1.Execute;
end;

procedure TMainForm.FileOpenItemClick(Sender: TObject);
var
   fid : FILE_ID;
   name : string;
   ft : TFileType;
   vt: TfrmViewText31;
   icstr, ocstr : array[0..150] of Char;
begin
frmOpenFile.SetMode( osmOpenFile );
frmOpenFile.showModal;
if frmOpenFile.ModalResult<>mrOk then exit;
if frmOpenFile.GetSelection(name, fid, ft ) then
   begin
   vt := TfrmViewText31.Create(Application);
   DoRTFSettings( 10, 700, -1 );
   vt.SetFileNameCaption(name,name);
   vt.Show;
   UdcStatusPanel1.WriteMessage(ptMessagePanel, 'Ready.');
   end;
end;

procedure TMainForm.ReadFileIntoData1Click(Sender: TObject);
var
  name : string;
  ft : TFileType;
  fid : FILE_ID;
  id : array [0..5] of Char;
  r : integer;
  handle : integer;
begin
frmOpenFile.SetMode( osmOpenFile );
frmOpenFile.showModal;
if frmOpenFile.ModalResult<>mrOk then exit;
if Not frmOpenFile.GetSelection(name, fid, ft ) then exit;
if Not FileExists(name) then exit;
handle := FileOpen(name,fmOpenRead);
if handle < 0 then exit;
FileRead( handle, fid, SizeOf(fid) );
FileSeek( handle, fid.birth, 0 );
FileRead( handle, NumerologyData, SizeOf(NumerologyData) );
frmNumData.PutNum( NumerologyData );
FileClose(handle);
MessageBeep(0);
UdcStatusPanel1.WriteMessage(ptMessagePanel, 'Ready.');
end;

procedure TMainForm.Print1Click(Sender: TObject);
begin
  if ActiveMDIChild <> nil then
    TfrmViewText31(ActiveMDIChild).Print;
MessageBeep(0);
UdcStatusPanel1.WriteMessage(ptMessagePanel, 'Ready.');
end;

procedure TMainForm.interactiveClick(Sender: TObject);
begin
WinExec('Intercal.exe', SW_SHOW );
end;

procedure TMainForm.FormShow(Sender: TObject);
var
  ifn, s : string;
begin
{$IFDEF DEMO}
GetDir(0,ifn);
if ifn[length(ifn)-1]<> '\' then ifn := ifn + '\';
ifn := ifn + 'NUMERO.INI';
if iniFile = nil then iniFile := TIniFile.Create(ifn);
s := iniFile.ReadString('Shareware','Reg','0');
if s = '1&Numbers&9' then demo_mode := 0
   else demo_mode := 100;
if demo_mode = 100 then demofrm.Show;
{$ENDIF}
end;

end.
