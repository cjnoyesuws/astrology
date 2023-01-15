unit doclck;

interface
{$IFDEF WIN32}
uses
  WinTypes, WinProcs, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Numdll, poputxt;
{$ELSE}
uses
  WinTypes, WinProcs, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, Numdll31, txtpop31;

{$ENDIF}

procedure doClick( key , id : SmallInt; title : string );

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
if DoTextItem( 'tt.txt', key, id  ) < 0 then
   begin
   Application.MessageBox( 'Text Could Not Be Accessed!', 'Error!', 1 );
   exit;
   end;
SetupRTFConvert( f, c, 10, 500 );
ConvertToRTF( 'tt.txt', 'tt.rtf' );
frmPopupText.SetFileNameCaption( 'tt.rtf', title );
frmPopupText.Show;
end;

end.
 