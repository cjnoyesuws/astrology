#ifndef _MENUUTL_HPP_
#define _MENUUTL_HPP_

extern int enableMenuItems( zMenu *pm, int idf, int idl=0 );
extern int disableMenuItems( zMenu *pm, int idf, int idl=0 );
extern int enableMenuItems( zMenu *pm, int *ids );
extern int disableMenuItems( zMenu *pm, int *ids );
extern int getMenuItemPos( zMenu *pm, unsigned id, HMENU &sub, int topPos=0 );

#pragma warning( once : 4135; once : 4136; once : 4100; once : 4309; disable : 4505 )
#endif /* _MENUUTL_HPP_ */
