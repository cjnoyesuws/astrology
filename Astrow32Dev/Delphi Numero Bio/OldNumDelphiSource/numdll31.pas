unit Numdll31;

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
  VARIABLE_PITCH = 2;
  { Font Families }
  FF_DONTCARE   = (0 shl 4);     { Don't care or don't know. }
  FF_ROMAN      = (1 shl 4);     { Variable stroke width, serifed. }
                                 { Times Roman, Century Schoolbook, etc. }
  FF_SWISS      = (2 shl 4);     { Variable stroke width, sans-serifed. }
                                 { Helvetica, Swiss, etc. }

procedure SetFileInfo( var p : FILE_ID );
procedure SetChartInfoData( var h : CHART_INFO );
function CompileReport( rep : integer; n1_file : PCHAR ) : Integer ;
function ConvertToRTF( fin, fout : PCHAR ) : integer;
procedure SetupRTFConvert( var pFnt : FONT_AR; var pClr : COLOR_AR; lft, wdt, cvt : integer; dev : PChar );
function DoTextItem( filen : PChar; row, col : smallint ) : integer;
procedure SetGroupStartEnd( start, endd : smallint );
procedure SetWYVowel( s : smallint );
implementation


procedure SetFileInfo( var p : FILE_ID );
   external 'NUMDLL' index 3;
procedure SetChartInfoData( var h : CHART_INFO );
   external 'NUMDLL' index 4;
function CompileReport( rep : integer; n1_file : PCHAR ) : Integer ;
   external 'NUMDLL' index 10;
function ConvertToRTF( fin, fout : PCHAR ) : integer;
   external 'NUMDLL' index 9;
procedure SetupRTFConvert( var pFnt : FONT_AR; var pClr : COLOR_AR; lft, wdt, cvt : integer; dev : PChar );
   external 'NUMDLL' index 2;
function DoTextItem( filen : PChar; row, col : smallint ) : integer;
   external 'NUMDLL' index 11;
procedure SetGroupStartEnd( start, endd : smallint );
   external 'NUMDLL' index 5;
procedure SetWYVowel( s : smallint );
   external 'NUMDLL' index 8;
end.
