unit NumDll;

interface

type
  NAME_REC = record
  first : array [0..79] of char;
  middle : array [0..79] of char;
  last : array [0..79] of char;
  include : smallint;
  end;

type
  DATES = record
  month, day, year : smallint;
  include : smallint;
  end;


type
  CHART_INFO = record
  id : array [0..5] of char;
  birth_date : DATES ;
  at_birth, current, opt1, opt2 : NAME_REC;
  end;


type FILE_ID = record
  id : array [0..5] of char;
  fType : array [0..29] of char;
  comment : array [0..79] of char;
  text, birth, data : longint;
  end;

const
 PERSON_FILE = 1;
 NUMERIC_FILE = 2;
 NAMEGRAPH_FILE = 3;
 NUMGRAPH_FILE = 4;


type
   FONT = record
   lfFaceName : array [0..39] of char;
   lfHeight : smallint;
   lfWeight : smallint;
   lfItalic : smallint;
   lfUnderline : smallint;
   lfPitchAndFamily : word ;
   end;

type
  FONT_AR = array [0..3] of FONT;

type
  COLOR_AR = array [0..3] of Longint;


const
 _REG_ = 0;
 _HEAD_ = 1;
 _BOLD_ = 2;
 _UITAL_ = 3;

const
  PERS_YEAR  = 13;
  PERS_MONTH = 14;
  UNIV_YEAR  = 15;
  UNIV_MONTH = 16;
  PERS_DAY   = 17;
  UNIV_DAY   = 18;

procedure SetGroupStartEnd( start, endd : smallint );  cdecl;
procedure SetWYVowel( s : smallint );  cdecl;
procedure SetFileInfo( var p : FILE_ID );  cdecl;
procedure SetChartInfoData( var h : CHART_INFO );  cdecl;
function CompileReport( rep : integer; n1_file : PCHAR ) : Integer ;  cdecl;
function ConvertToRTF( fin, fout : PCHAR ) : integer;  cdecl;
procedure SetupRTFConvert( var pFnt : FONT_AR ; var pClr : COLOR_AR; lft, wdt, cvt : integer; dev : PChar );  cdecl;
function DoTextItem( filen : PChar; row, col : smallint ) : integer;  cdecl;
implementation

procedure SetGroupStartEnd( start, endd : smallint ); cdecl;
   external 'Numdll' index 6;
procedure SetWYVowel( s : smallint ); cdecl;
   external 'Numdll' index 7;
procedure SetFileInfo( var p : FILE_ID ); cdecl;
   external 'Numdll' index 5;
procedure SetChartInfoData( var h : CHART_INFO ); cdecl;
   external 'Numdll' index 4;
function CompileReport( rep : integer; n1_file : PCHAR ) : Integer ; cdecl;
   external 'Numdll' index 1;
function ConvertToRTF( fin, fout : PCHAR ) : integer; cdecl;
   external 'Numdll' index 2;
procedure SetupRTFConvert( var pFnt : FONT_AR ; var pClr : COLOR_AR; lft, wdt, cvt : integer; dev : PChar );  cdecl;
   external 'Numdll' index 8;
function DoTextItem( filen : PChar; row, col : smallint ) : integer; cdecl;
   external 'Numdll' index 3;
end.
