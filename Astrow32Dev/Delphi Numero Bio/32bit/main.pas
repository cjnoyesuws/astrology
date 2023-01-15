unit Main;

interface

uses Windows, SysUtils, Classes, Graphics, Forms, Controls, Menus,
  StdCtrls, Dialogs, Buttons, Messages, ExtCtrls, ComCtrls, numdll, viewtxt;

type
  TMainForm = class(TForm)
    MainMenu1: TMainMenu;
    File1: TMenuItem;
    FileNewItem: TMenuItem;
    FileOpenItem: TMenuItem;
    FileCloseItem: TMenuItem;
    Window1: TMenuItem;
    Help1: TMenuItem;
    N1: TMenuItem;
    FileExitItem: TMenuItem;
    WindowCascadeItem: TMenuItem;
    WindowTileItem: TMenuItem;
    WindowArrangeItem: TMenuItem;
    HelpAboutItem: TMenuItem;
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
    StatusBar: TStatusBar;
    Data: TMenuItem;
    NumerologyData1: TMenuItem;
    Utilities1: TMenuItem;
    interactive: TMenuItem;
    ReadFileIntoData1: TMenuItem;
    Options1: TMenuItem;
    sbPrint: TSpeedButton;
    sbNumData: TSpeedButton;
    sbSaveAs: TSpeedButton;
    CompileJustData1: TMenuItem;
    NameTransitsData1: TMenuItem;
    NameTransitsText1: TMenuItem;
    CompileJustData2: TMenuItem;
    Print1: TMenuItem;
    PrinterSetup1: TMenuItem;
    PrintDialog1: TPrintDialog;
    PrinterSetupDialog1: TPrinterSetupDialog;
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
  private
    { Private declarations }
    procedure CreateMDIChild(const Name: string);
    procedure ShowHint(Sender: TObject);
  public
    { Public declarations }
  end;

var
  MainForm: TMainForm;

implementation

{$R *.DFM}

uses ChildWin, Birthdat, about, Options, Openf, Years;

procedure TMainForm.FormCreate(Sender: TObject);
begin
  Application.OnHint := ShowHint;
  Screen.OnActiveFormChange := UpdateMenuItems;
end;

procedure TMainForm.ShowHint(Sender: TObject);
begin
  StatusBar.SimpleText := Application.Hint;
end;

procedure TMainForm.CreateMDIChild(const Name: string);
var
  Child: TfrmViewText;
begin
  { create a new MDI child window }
  Child := TfrmViewText.Create(Application);
  Child.Caption := Name;
end;

procedure TMainForm.FileCloseItemClick(Sender: TObject);
begin
  if ActiveMDIChild <> nil then
    ActiveMDIChild.Close;
end;

procedure TMainForm.FileSaveItemClick(Sender: TObject);
begin
  { save current file (ActiveMDIChild points to the window) }
end;

procedure TMainForm.FileSaveAsItemClick(Sender: TObject);
begin
  { save current file under new name }
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
  FileSaveAsItem.Enabled := MDIChildCount > 0;
  CutItem.Enabled := MDIChildCount > 0;
  CopyItem.Enabled := MDIChildCount > 0;
  PasteItem.Enabled := MDIChildCount > 0;
  sbSave.Enabled := MDIChildCount > 0;
  sbPrint.Enabled := MDIChildCount > 0;
  Print1.Enabled := MDIChildCount > 0;
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
frmNumData.Show;
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
begin
UpdateDll;
frmOpenFile.SetInitial(NumerologyData.at_birth);
frmOpenFile.SetMode( osmCreateFile );
frmOpenFile.showModal;
if frmOpenFile.ModalResult<>mrOk then exit;
if frmOpenFile.GetSelection(name, fid, ft ) then
   begin
   SetFileInfo( fid );
   CompileReport( NUMERIC_FILE, PChar(name) );
   end
else
   exit;
end;

procedure TMainForm.CompileJustData1Click(Sender: TObject);
var
   fid : FILE_ID;
   name : string;
   ft : TFileType;
begin
UpdateDll;
frmOpenFile.SetInitial(NumerologyData.at_birth);
frmOpenFile.SetMode( osmCreateFile );
frmOpenFile.showModal;
if frmOpenFile.ModalResult<>mrOk then exit;
if frmOpenFile.GetSelection(name, fid, ft ) then
   begin
   SetFileInfo( fid );
   CompileReport( PERSON_FILE, PChar(name) );
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
begin
UpdateDll;
frmOpenFile.SetInitial(NumerologyData.at_birth);
frmOpenFile.SetMode( osmCreateFile );
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
   CompileReport( NUMGRAPH_FILE, PChar(name) );
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
begin
UpdateDll;
frmOpenFile.SetInitial(NumerologyData.at_birth);
frmOpenFile.SetMode( osmCreateFile );
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
   CompileReport( NAMEGRAPH_FILE, PChar(name) );
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
   vt: TfrmViewText;
begin
frmOpenFile.SetMode( osmOpenFile );
frmOpenFile.showModal;
if frmOpenFile.ModalResult<>mrOk then exit;
if frmOpenFile.GetSelection(name, fid, ft ) then
   begin
   vt := TfrmViewText.Create(Application);
   DoRTFSettings( 10, 700 );
   vt.SetFileNameCaption(name,name);
   vt.Show;
   end;
end;

procedure TMainForm.ReadFileIntoData1Click(Sender: TObject);
var
  name : string;
  ft : TFileType;
  fid : FILE_ID;
  id : array [0..5] of Char;
  r : integer;
  f : file of Char;
begin
frmOpenFile.SetMode( osmOpenFile );
frmOpenFile.showModal;
if frmOpenFile.ModalResult<>mrOk then exit;
if Not frmOpenFile.GetSelection(name, fid, ft ) then exit;
if Not FileExists(name) then exit;
AssignFile( f, name );
Reset(f);
BlockRead( f, fid, SizeOf(fid), r );
Seek( f, fid.birth );
BlockRead( f, NumerologyData, SizeOf(NumerologyData), r );
frmNumData.PutNum( NumerologyData );
CloseFile(f);
end;

procedure TMainForm.Print1Click(Sender: TObject);
begin
  if ActiveMDIChild <> nil then
    TfrmViewText(ActiveMDIChild).Print;
end;

procedure TMainForm.interactiveClick(Sender: TObject);
begin
WinExec('Intercal.exe', SW_SHOW );
end;

end.
