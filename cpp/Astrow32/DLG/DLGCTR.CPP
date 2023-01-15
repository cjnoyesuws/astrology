#include <zapp.hpp>
#pragma hdrstop("\WPRO\ZAPP.PCH")
#include <zapph\mdi.hpp>

#pragma warning( once : 4135; once : 4136; once : 4100; once : 4309; disable : 4505 )

int centerDialog( zFrameWin *fw )
{
  zRect pdim, edim, idim;
  int x, y, w;

  app->rootWindow()->getExterior(pdim);
  fw->getExterior(edim);
  fw->getInterior(idim);
  x = ((pdim.width() - edim.width())/2)+pdim.left();
  y = ((pdim.height() - edim.height())/2)+pdim.top();
  if ( x < 0 )
     x = 0;
  if ( y < 0 )
     y = 0;
  zSystemInfo *si = new zSystemInfo();
  if ( x + edim.width() > si->pixWidth() )
     x = si->pixWidth() - edim.width();
  if ( y + edim.height() > si->pixHeight() )
     y = si->pixHeight() - edim.height();
  delete si;
  zRect re(x,y,edim.width()+x,edim.height()+y);
  fw->move(&re);
  return( 1 );
}
