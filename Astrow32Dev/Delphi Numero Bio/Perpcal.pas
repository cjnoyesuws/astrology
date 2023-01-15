unit PerpCal;

interface
{ pepetia;[lookup[year-1700]][month] contains .start of week, and
   .days per month }

type
  CalData = Record
    start : ShortInt;
    days  : ShortInt;
    end;

type Select = ( A , B, C, D, E, F, G, H, I, J, K, L, M, N );

const
perpetual : array [A..N,1..12] of CalData = (
   ((start:3;days:31), (start:6;days:28), (start:6;days:31),
   (start:2;days:30), (start:4;days:31), (start:0;days:30),
   (start:2;days:31), (start:5;days:31), (start:1;days:30),
   (start:3;days:31), (start:6;days:30), (start:1;days:31)),
   ((start:4;days:31), (start:0;days:28), (start:0;days:31),
   (start:3;days:30), (start:5;days:31), (start:1;days:30),
   (start:3;days:31), (start:6;days:31), (start:2;days:30),
   (start:4;days:31), (start:0;days:30), (start:2;days:31)),
   ((start:5;days:31), (start:1;days:29), (start:2;days:31),
   (start:5;days:30), (start:0;days:31), (start:3;days:30),
   (start:5;days:31), (start:1;days:31), (start:4;days:30),
   (start:6;days:31), (start:2;days:30), (start:4;days:31)),
   ((start:0;days:31), (start:4;days:28), (start:3;days:31),
   (start:6;days:30), (start:1;days:31), (start:4;days:30),
   (start:6;days:31), (start:2;days:31), (start:5;days:30),
   (start:0;days:31), (start:3;days:30), (start:5;days:31)),
   ((start:1;days:31), (start:4;days:28), (start:4;days:31),
   (start:0;days:30), (start:2;days:31), (start:5;days:30),
   (start:0;days:31), (start:3;days:31), (start:6;days:30),
   (start:1;days:31), (start:4;days:30), (start:6;days:31)),
   ((start:2;days:31), (start:5;days:28), (start:5;days:31),
   (start:1;days:30), (start:3;days:31), (start:6;days:30),
   (start:1;days:31), (start:4;days:31), (start:0;days:30),
   (start:2;days:31), (start:5;days:30), (start:0;days:31)),
   ((start:3;days:31), (start:6;days:29), (start:0;days:31),
   (start:3;days:30), (start:5;days:31), (start:1;days:30),
   (start:3;days:31), (start:6;days:31), (start:2;days:30),
   (start:4;days:31), (start:0;days:30), (start:2;days:31)),
   ((start:5;days:31), (start:1;days:28), (start:1;days:31),
   (start:4;days:30), (start:6;days:31), (start:2;days:30),
   (start:4;days:31), (start:0;days:31), (start:3;days:30),
   (start:5;days:31), (start:1;days:30), (start:3;days:31)),
   ((start:6;days:31), (start:2;days:28), (start:2;days:31),
   (start:5;days:30), (start:0;days:31), (start:3;days:30),
   (start:5;days:31), (start:1;days:31), (start:4;days:30),
   (start:6;days:31), (start:2;days:30), (start:4;days:31)),
   ((start:1;days:31), (start:4;days:29), (start:5;days:31),
   (start:1;days:30), (start:3;days:31), (start:6;days:30),
   (start:1;days:31), (start:4;days:31), (start:0;days:30),
   (start:2;days:31), (start:5;days:30), (start:0;days:31)),
   ((start:6;days:31), (start:2;days:29), (start:3;days:31),
   (start:6;days:30), (start:1;days:31), (start:4;days:30),
   (start:6;days:31), (start:2;days:31), (start:5;days:30),
   (start:0;days:31), (start:3;days:30), (start:5;days:31)),
   ((start:0;days:31), (start:3;days:29), (start:4;days:31),
   (start:0;days:30), (start:2;days:31), (start:5;days:30),
   (start:0;days:31), (start:3;days:31), (start:6;days:30),
   (start:1;days:31), (start:4;days:30), (start:6;days:31)),
   ((start:2;days:31), (start:5;days:29), (start:6;days:31),
   (start:2;days:30), (start:4;days:31), (start:0;days:30),
   (start:2;days:31), (start:5;days:31), (start:1;days:30),
   (start:3;days:31), (start:6;days:30), (start:1;days:31)),
   ((start:4;days:31), (start:0;days:29), (start:1;days:31),
   (start:4;days:30), (start:6;days:31), (start:2;days:30),
   (start:4;days:31), (start:1;days:31), (start:3;days:30),
   (start:5;days:31), (start:1;days:30), (start:3;days:31)));
{ index to table above }
lookup : array [0..408] of select = (
      H, I, D, E, M, B, H, I, L, F, A, B, C, D,
      E, F, G, H, I, D, J, A, B, H, K, E, F, A,
      N, I, D, E, M, B, H, I, L, F, A, B, C, D,
      E, F, G, H, I, D, J, A, B, H, K, E, F, A,
      N, I, D, E, M, B, H, I, L, F, A, B, C, D,
      E, F, G, H, I, D, J, A, B, H, K, E, F, A,
      N, I, D, E, M, B, H, I, L, F, A, B, C, D,
      E, F, A, B, H, I, L, F, A, B, C, D, E, F,
      G, H, I, D, J, A, B, H, K, E, F, A, N, I,
      D, E, M, B, H, I, L, F, A, B, C, D, E, F,
      G, H, I, D, J, A, B, H, K, E, F, A, N, I,
      D, E, M, B, H, I, L, F, A, B, C, D, E, F,
      G, H, I, D, J, A, B, H, K, E, F, A, N, I,
      D, E, M, B, H, I, L, F, A, B, C, D, E, F,
      G, H, I, D, E, F, A, B, C, D, E, F, G, H,
      I, D, J, A, B, H, K, E, F, A, N, I, D, E,
      M, B, H, I, L, F, A, B, C, D, E, F, G, H,
      I, D, J, A, B, H, K, E, F, A, N, I, D, E,
      M, B, H, I, L, F, A, B, C, D, E, F, G, H,
      I, D, J, A, B, H, K, E, F, A, N, I, D, E,
      M, B, H, I, L, F, A, B, C, D, E, F, G, H,
      I, D, J, A, B, H, K, E, F, A, N, I, D, E,
      M, B, H, I, L, F, A, B, C, D, E, F, G, H,
      I, D, J, A, B, H, K, E, F, A, N, I, D, E,
      M, B, H, I, L, F, A, B, C, D, E, F, G, H,
      I, D, J, A, B, H, K, E, F, A, N, I, D, E,
      M, B, H, I, L, F, A, B, C, D, E, F, G, H,
      I, D, J, A, B, H, K, E, F, A, N, I, D, E,
      M, B, H, I, L, F, A, B, H, I, D, E, M, B,
      H, I, L );

function PerpetualCalendar( y, m : Word ) : CalData;

Implementation

{ function to get data from arrays and structures }

function PerpetualCalendar( y, m : Word ) : CalData;
var
  cd : CalData;
  sel : Select;
begin
 if (y > 2105 ) or ( y < 0 ) then y := 0;
 sel := lookup[y-1700];
 cd := perpetual[sel][m];
 PerpetualCalendar := cd;
end;

end.
