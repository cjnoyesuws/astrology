unit Numbers;

interface
function reduceMasterNum( n : SmallInt ) : SmallInt;
function reduceNum( n : SmallInt ) : SmallInt;
function universalDay( y, m, d : SmallInt ) : SmallInt;
function universalMonth( m : SmallInt ) : SmallInt;
function universalYear( y : SmallInt ) : SmallInt;
function personalYear( bm, bd, y : SmallInt ) : SmallInt ;
function personalMonth( bm, bd, y, m : SmallInt ) : SmallInt ;
function personalDay( bm, bd, y, m, d : SmallInt ) : SmallInt ;

Const
  reduce : array [10..38] of ShortInt = (1, 11, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 22, 5, 6, 7, 8, 9, 1, 11,
     3, 4, 5, 6, 7, 8, 9, 1, 11  );

const
  PERS_YEAR  = 13;
  PERS_MONTH = 14;
  UNIV_YEAR  = 15;
  UNIV_MONTH = 16;
  PERS_DAY   = 17;
  UNIV_DAY   = 18;


implementation

function reduceMasterNum( n : SmallInt ) : SmallInt;
begin
if n = 11 then reduceMasterNum := 2
   else if n = 22 then reduceMasterNum := 4
        else reduceMasterNum := n
end;

function reduceNum( n : SmallInt ) : SmallInt;
var
   cent, r, x : SmallInt;
begin
cent := 0;
r := 0;
if n in [0..9,11,22] then r := n
else if n <= 38 then r := reduce[n]
else if n < 100 then
    begin
    r := (n mod 10)+ (n div 10);
    if n <= 38 then r := reduce[n];
    if not r in [0..9,11,22] then r := reduceNum(r);
    end
else
    begin
    cent := 0;
    if n >= 2100 then
       begin;
       cent := 3;
       n := n - 2100;
       end
    else if n >= 2000 then
       begin
       cent := 2;
       n := n - 2000;
       end
    else if n >= 1900 then
       begin
       cent := 1;
       n := n - 1900;
       end
    else if n >= 1800 then
       begin
       cent := 9;
       n := n - 1800;
       end;
    n := n + cent;
    if n in [0..9,11,22] then r := n
    else if n <= 38 then r := reduce[n]
    else if n >= 100 then
       begin
       x := n mod 100;
       r := (n div 100) + (x mod 10) + (x div 10);
       r := reduceNum(r);
       end
    else
       begin
       r := (n mod 10)+ (n div 10);
       r := reduceNum(r);
       end;
    end;
reduceNum := r;
end;

function universalDay( y, m, d : SmallInt ) : SmallInt;
begin
universalDay := reduceNum(reduceNum(y)+reduceNum(m)+reduceNum(d));
end;

function universalMonth( m : SmallInt ) : SmallInt;
begin
universalMonth := reduceNum( m );
end;

function universalYear( y : SmallInt ) : SmallInt;
begin
universalYear := reduceNum( y );
end;

function personalYear( bm, bd, y : SmallInt ) : SmallInt;
var
   r : SmallInt;
begin
r := reduceNum(y);
r := r +reduceNum(bm);
r := reduceNum(r);
r := r + reduceNum(bd);
personalYear := reduceNum(r);
end;

function personalMonth( bm, bd, y, m : SmallInt ) : SmallInt;
var
  r : Word;
begin
r := personalYear(bm,bd,y);
r := r + reduceNum(m);
personalMonth := reduceNum( r );
end;

function personalDay( bm, bd, y, m, d : SmallInt ) : SmallInt;
var
  r : Word;
begin
r := personalYear(bm,bd,y);
r := r + reduceNum(m);
r := reduceNum(r);
r := r + reduceNum(d);
personalDay := reduceNum( r );
end;

end.
