unit doclck;

interface
{$IFDEF WIN32}

uses
  WinTypes, WinProcs, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Numdll, poputxt;

procedure doClick( key , id : SmallInt; title : string );

{$ELSE}
{$IFDEF RTF}
uses
  WinTypes, WinProcs, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Numdll31, popview;
{$ELSE}
uses
  WinTypes, WinProcs, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Numdll31, popviewm;
{$ENDIF}
procedure doClick( key , id : SmallInt; title : string ); export;
{$ENDIF}

implementation

procedure doClick( key , id : SmallInt; title : string );
const
f : FONT_AR = ((lfFaceName: 'Times New Roman'; lfHeight: 24;
                    lfWeight: FW_NORMAL; lfItalic: 0; lfUnderline: 0;
                    lfPitchandFamily: VARIABLE_PITCH+FF_ROMAN ),
                (lfFaceName: 'Times New Roman'; lfHeight: 24;
                    lfWeight: FW_BOLD; lfItalic: 0; lfUnderline: 0;
                    lfPitchandFamily: VARIABLE_PITCH+FF_ROMAN),
                (lfFaceName: 'Times New Roman'; lfHeight: 24;
                    lfWeight: FW_NORMAL; lfItalic: 1; lfUnderline: 0;
                    lfPitchandFamily: VARIABLE_PITCH+FF_ROMAN),
                (lfFaceName: 'Times New Roman'; lfHeight: 24;
                    lfWeight: FW_NORMAL; lfItalic: 0; lfUnderline: 1;
                    lfPitchandFamily: VARIABLE_PITCH+FF_ROMAN) );

c : COLOR_AR =  (0,$ff,$00ff,$0000ff);
begin
c[1] := 0;
if DoTextItem( PChar('tt.txt'), key, id  ) < 0 then
   begin
   Application.MessageBox( 'Text Could Not Be Accessed!', 'Error!', 1 );
   exit;
   end;
{$IFDEF RTF}
SetupRTFConvert( f, c, 10, 500, -1, 'test' );
{$ELSE}
SetupRTFConvert( f, c, 1, 600, 1, 'test' );
{$ENDIF}
ConvertToRTF( PChar('tt.txt'), PChar('tt.rtf') );
{$IFDEF WIN32}
frmPopupText.SetFileNameCaption( 'tt.rtf', title );
frmPopupText.show;
{$ELSE}
{$IFDEF RTF}
if FrmView = nil then FrmView := TFrmView.Create(Application);
{$ELSE}
if FrmView = nil then FrmView := TFrmViewm.Create(Application);
{$ENDIF}
FrmView.SetFileNameCaption( 'tt.rtf', title );
FrmView.show;
{$ENDIF}
end;



end.
