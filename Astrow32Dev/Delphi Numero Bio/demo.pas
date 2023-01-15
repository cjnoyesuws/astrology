unit Demo;

interface

uses
  SysUtils, WinTypes, WinProcs, Messages, Classes, Graphics, Controls,
  Forms, Dialogs, StdCtrls, Buttons, ExtCtrls, inheritedregistry,
  dateutils;

type
  Tdemofrm = class(TForm)
    Timer1: TTimer;
    Label1: TLabel;
    BitBtn1: TBitBtn;
    Label2: TLabel;
    Label3: TLabel;
    procedure Timer1Timer(Sender: TObject);
    procedure BitBtn1Click(Sender: TObject);
    procedure FormShow(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

procedure DoDemoCheck(sApp : String);

var
  demofrm: Tdemofrm;
  DaysToTry : integer;
  formatValid :Boolean;

implementation

{$R *.DFM}

procedure Tdemofrm.Timer1Timer(Sender: TObject);
begin
Timer1.enabled := false;
BitBtn1Click(Sender);
end;

procedure Tdemofrm.BitBtn1Click(Sender: TObject);
begin
  if Timer1.enabled=True then
    exit
  else
    hide;
  MessageBeep(0);
  MessageBeep(0);
  if (DaysToTry <= 0) or (not formatValid) then
    Application.Terminate;
end;

procedure Tdemofrm.FormShow(Sender: TObject );
var
  tstr: string;
begin
  if not formatValid then
    tstr := 'Information in Registry isn''t Valid!'
  else if (DaysToTry > 0) then
    tstr := 'You Have '+IntToStr(DaysToTry) + ' Days left!'
  else
    tstr:= 'Sorry You Have Run Out of Trials!';
  label2.caption:=tstr;
  label2.alignment:=taCenter;
  Timer1.Enabled:= True;
  MessageBeep(0);
  MessageBeep(0);
end;


procedure DoDemoCheck(sApp : String);
var
   month, day, year, iPos : integer;
   str1: String;
   oReg : TInheritedRegistry;
begin
   oReg := TInheritedRegistry(sApp);
   if ( not oReg.Open('Shareware',false,false) ) then
   begin
      oReg.Destroy;
      exit;
   end;
   str1 := oReg.ReadString('Date','');
   if ( copy(str1,1,3)<>'AsT' ) then
      formatValid := false
   else
      begin
         day := StrToInt(copy(str1,4,5))-100;
         iPos := Pos('$',str1);
         if (iPos >= 6) and ( day > 0) and ( day < 32 ) then
         begin
            str1 := Copy(str1,iPos+1,length(str1)-iPos);
            year := StrToInt(str1)-1000;
            iPos := Pos('@', str1);
            if ( year > 2004) and ( year < 2010 )
                  and (iPos=5) then
            begin
               str1 := copy(str1,iPos+1,length(str1)-iPos);
               month := StrToInt(str1)- 500;
               if ( month < 0 ) or ( month > 12 ) or
                    (copy(str1,length(str1)-3,4) <> 'RoW') then
                  formatValid := False
               else
               begin
                  DaysToTry := 30 - DaysBetween(Date,EncodeDate(year,month,day));
                  formatValid := True;
               end;
            end
            else
             formatValid := false
         end
         else
            formatValid := False;
      end;
   demofrm := TDemofrm.Create(Application);
   demofrm.ShowModal;
   demofrm.Destroy;
   demofrm := nil;
end;

end.
