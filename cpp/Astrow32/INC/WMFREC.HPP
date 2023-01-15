#ifndef _WMFREC___HPP_
#define _WMFREC___HPP_



#pragma pack(1)
#define WMF_REC_BkMode          0x102   /* ^ p1  */
#define WMF_REC_MapMode         0x103   /* ## p1  */
#define WMF_REC_Rop2            0x104   /* ^  p1  */
#define WMF_REC_SelectObj       0x12d   /* ^  p1  */
#define WMF_REC_TextAlign       0x12e   /* ^  p1  */
#define WMF_REC_DeleteObj       0x1f0   /* ^  p1  */
#define WMF_REC_BkColor         0x201   /* ^  cr  */
#define WMF_REC_TextColor       0x209   /* ^  cr  */
#define WMF_REC_WinOrg          0x20b   /* ## yx  */
#define WMF_REC_WinExt          0x20c   /* ## yx  */
#define WMF_REC_LineTo          0x213   /*  yx  */
#define WMF_REC_MoveTo          0x214   /*  yx  */
#define WMF_REC_CreatePenInd    0x2fa   /* ^  crpn */
#define WMF_REC_CreateFontInd   0x2fb   /* ^  crfn */
#define WMF_REC_CreateBrushInd  0x2fc   /* ^  crbr */
#define WMF_REC_Elipse          0x418   /*  rect */
#define WMF_REC_TextOut         0x521   /*  txtout */
#define WMF_REC_PatBlt          0x61d   /*  pblt   */
#define WMF_REC_XX              0x325   /*  ????   */
#define WMF_REC_00              0x0     /*  ????   */


typedef struct WMFPlaceHead {
	unsigned long id;
	unsigned short  unused;
	unsigned short  topx;
	unsigned short  topy;
	unsigned short  botx;
	unsigned short  boty;
	unsigned short  scale;
	unsigned long unused2;
	unsigned short  checksum;
	void setup( short x, short y, short sc );
	void getChecksum();
	} WMFPlaceHead;


typedef struct WMFHead {
	unsigned short type;
	unsigned short sizehead;
	unsigned short version;
	unsigned long  fsize;
	unsigned short obj_handles;
	unsigned long  largest_rec;
	unsigned short noparam;
	} WMFHead;


typedef struct WMFItem {
	unsigned long size;
	short  code;
	} WMFItem;

typedef struct WMF1Parm {
	WMFItem header;
	unsigned short parm;
	} WMF1Parm;

typedef struct WMFYXParm {
	WMFItem header;
	short y;
	short x;
	} WMFYXParm;

typedef struct WMFRectParm {
	WMFItem header;
	short y1;
	short x1;
	short y2;
	short x2;
	} WMFRectParm;

typedef struct WMFPBlt {
	WMFItem header;
	unsigned long op;
	unsigned short ht;
	unsigned short wd;
	short y;
	short x;
	} WMFPBlt;

typedef struct WMFTxtOut {
	WMFItem header;
	short length;
	char text[];
	} WMFTxtOut;

typedef struct WMFTxtOutXY {
	short x;
	short y;
	} WMFTxtOutXY;

#pragma pack()
#endif /*  _WMFREC___HPP_  */
