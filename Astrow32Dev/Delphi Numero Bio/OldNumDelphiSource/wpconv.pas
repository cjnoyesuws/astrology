unit wpconv;

interface

uses
  Windows, Messages, SysUtils, Classes, oleauto;

procedure Initialize;
procedure DoSaveDlg;
procedure InsHardRet;
procedure InsText( txt : PChar );
procedure InsTabChar;
procedure ClearTabs;
Procedure SetTab( v : Pchar );
procedure HeadFont( name : PChar, size : smallint );
procedure RegFont( name : PChar, size : smallint );
procedure ItalFont( name : PChar, size : smallint );
procedure BoldFont( name : PChar, size : smallint );
procedure Close;

var
  objWP : Variant;

implementation

procedure Initialize;
begin
objWP := CreateOleObject( 'WordPerfect.PerfectScript');
end;

procedure DoSaveDlg;
begin
objWP.FileSaveAsDlg;
end;

procedure InsHardRet;
begin
objWP.HardReturnInsert;
end;

procedure InsText( txt : PChar );
begin
objWP.KeyType(txt);
end;

procedure InsTabChar;
begin
objWP.TabKey;
end;

procedure ClearTabs;
begin
objWP.TabClearAll;
end;

Procedure SetTab( v : Pchar );
begin
objWP.TabSet(0, v, 0);
end.

procedure HeadFont( name : PChar, size : smallint );
begin
objWP.Font(name,, 0, 144, 112, , 139, 0);
objWP.FontSize(size);
end;

procedure RegFont( name : PChar, size : smallint );
begin
objWP.Font(name,, 0, 104, 112,, 139, 0);
objWP.FontSize(size);
end;

procedure ItalFont( name : PChar, size : smallint );
begin
objWP.Font(name,, 1, 104, 112,, 139, 0);
objWP.FontSize(size);
end;

procedure BoldFont( name : PChar, size : smallint );
begin
objWP.Font('Times New Roman',, 0, 144, 112,, 139, 0);
objWP.FontSize(12);
end;

procedure Close;
begin
end;

end.



