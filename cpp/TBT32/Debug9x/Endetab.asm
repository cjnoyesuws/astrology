; Listing generated by Microsoft (R) Optimizing Compiler Version 13.10.3077 

	TITLE	.\Endetab.cpp
	.386P
include listing.inc
if @Version gt 510
.model FLAT
else
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
_BSS	SEGMENT DWORD USE32 PUBLIC 'BSS'
_BSS	ENDS
$$SYMBOLS	SEGMENT BYTE USE32 'DEBSYM'
$$SYMBOLS	ENDS
$$TYPES	SEGMENT BYTE USE32 'DEBTYP'
$$TYPES	ENDS
_TLS	SEGMENT DWORD USE32 PUBLIC 'TLS'
_TLS	ENDS
;	COMDAT ??_C@_08KMDLBENF@?$FO?$FL?$FN?$HL?$HN?$DM?$DO?$HO?$AA@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_C@_0CB@LICAEBEI@c?3?2astrow32dev?2tbt32?2endetab?4cpp@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ??_C@_0O@NDPOADHB@len?5?$DM?5max_len?$AA@
CONST	SEGMENT DWORD USE32 PUBLIC 'CONST'
CONST	ENDS
;	COMDAT ?space_out@@YAPADPAHH0PAD@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?entab_buf@@YAHPBDPADH@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?detab_buf@@YAHPBDHPAD@Z
_TEXT	SEGMENT PARA USE32 PUBLIC 'CODE'
_TEXT	ENDS
;	COMDAT ?__LINE__Var@?1??detab_buf@@YAHPBDHPAD@Z@4JA
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
;	COMDAT ?__LINE__Var@?1??entab_buf@@YAHPBDPADH@Z@4JA
_DATA	SEGMENT DWORD USE32 PUBLIC 'DATA'
_DATA	ENDS
sxdata	SEGMENT DWORD USE32 'SXDATA'
sxdata	ENDS
FLAT	GROUP _DATA, CONST, _BSS
	ASSUME	CS: FLAT, DS: FLAT, SS: FLAT
endif

INCLUDELIB LIBCMTD
INCLUDELIB OLDNAMES

PUBLIC	?space_out@@YAPADPAHH0PAD@Z			; space_out
EXTRN	__RTC_InitBase:NEAR
EXTRN	__RTC_Shutdown:NEAR
;	COMDAT rtc$IMZ
; File c:\astrow32dev\tbt32\endetab.cpp
rtc$IMZ	SEGMENT
__RTC_InitBase.rtc$IMZ DD FLAT:__RTC_InitBase
rtc$IMZ	ENDS
;	COMDAT rtc$TMZ
rtc$TMZ	SEGMENT
__RTC_Shutdown.rtc$TMZ DD FLAT:__RTC_Shutdown
; Function compile flags: /Odt /RTCcsu /ZI
rtc$TMZ	ENDS
;	COMDAT ?space_out@@YAPADPAHH0PAD@Z
_TEXT	SEGMENT
tv70 = -220						; size = 4
_dst$ = -20						; size = 4
_sc$ = -8						; size = 4
_space_cnt$ = 8						; size = 4
_col$ = 12						; size = 4
_len$ = 16						; size = 4
_buf$ = 20						; size = 4
?space_out@@YAPADPAHH0PAD@Z PROC NEAR			; space_out, COMDAT

; 7    : {

	push	ebp
	mov	ebp, esp
	sub	esp, 220				; 000000dcH
	push	ebx
	push	esi
	push	edi
	lea	edi, DWORD PTR [ebp-220]
	mov	ecx, 55					; 00000037H
	mov	eax, -858993460				; ccccccccH
	rep stosd

; 8    :  int sc;
; 9    :  char *dst = buf;

	mov	eax, DWORD PTR _buf$[ebp]
	mov	DWORD PTR _dst$[ebp], eax

; 10   : 
; 11   :  sc = *space_cnt;

	mov	eax, DWORD PTR _space_cnt$[ebp]
	mov	ecx, DWORD PTR [eax]
	mov	DWORD PTR _sc$[ebp], ecx

; 12   :  if ( sc > 1 && (col%5==0) ) {

	cmp	DWORD PTR _sc$[ebp], 1
	jle	SHORT $L92959
	mov	eax, DWORD PTR _col$[ebp]
	cdq
	mov	ecx, 5
	idiv	ecx
	test	edx, edx
	jne	SHORT $L92959

; 13   :     *dst++ = '\t';

	mov	eax, DWORD PTR _dst$[ebp]
	mov	BYTE PTR [eax], 9
	mov	ecx, DWORD PTR _dst$[ebp]
	add	ecx, 1
	mov	DWORD PTR _dst$[ebp], ecx

; 14   :     (*len)++;

	mov	eax, DWORD PTR _len$[ebp]
	mov	ecx, DWORD PTR [eax]
	add	ecx, 1
	mov	edx, DWORD PTR _len$[ebp]
	mov	DWORD PTR [edx], ecx

; 15   :     }
; 16   :  else {

	jmp	SHORT $L92957
$L92959:

; 17   :     while ( sc-- ) {

	mov	eax, DWORD PTR _sc$[ebp]
	mov	DWORD PTR tv70[ebp], eax
	mov	ecx, DWORD PTR _sc$[ebp]
	sub	ecx, 1
	mov	DWORD PTR _sc$[ebp], ecx
	cmp	DWORD PTR tv70[ebp], 0
	je	SHORT $L92957

; 18   : 	  *dst++ = ' ';

	mov	eax, DWORD PTR _dst$[ebp]
	mov	BYTE PTR [eax], 32			; 00000020H
	mov	ecx, DWORD PTR _dst$[ebp]
	add	ecx, 1
	mov	DWORD PTR _dst$[ebp], ecx

; 19   : 	  (*len)++;

	mov	eax, DWORD PTR _len$[ebp]
	mov	ecx, DWORD PTR [eax]
	add	ecx, 1
	mov	edx, DWORD PTR _len$[ebp]
	mov	DWORD PTR [edx], ecx

; 20   : 	  }

	jmp	SHORT $L92959
$L92957:

; 21   :     }
; 22   :  *space_cnt = 0;

	mov	eax, DWORD PTR _space_cnt$[ebp]
	mov	DWORD PTR [eax], 0

; 23   :  return( dst );

	mov	eax, DWORD PTR _dst$[ebp]

; 24   : }

	pop	edi
	pop	esi
	pop	ebx
	mov	esp, ebp
	pop	ebp
	ret	0
?space_out@@YAPADPAHH0PAD@Z ENDP			; space_out
_TEXT	ENDS
PUBLIC	?entab_buf@@YAHPBDPADH@Z			; entab_buf
PUBLIC	??_C@_08KMDLBENF@?$FO?$FL?$FN?$HL?$HN?$DM?$DO?$HO?$AA@ ; `string'
PUBLIC	?__LINE__Var@?1??entab_buf@@YAHPBDPADH@Z@4JA	; `entab_buf'::`2'::__LINE__Var
PUBLIC	??_C@_0CB@LICAEBEI@c?3?2astrow32dev?2tbt32?2endetab?4cpp@ ; `string'
PUBLIC	??_C@_0O@NDPOADHB@len?5?$DM?5max_len?$AA@	; `string'
EXTRN	_strlen:NEAR
EXTRN	__assert:NEAR
EXTRN	_strchr:NEAR
EXTRN	@_RTC_CheckStackVars@8:NEAR
EXTRN	__RTC_CheckEsp:NEAR
;	COMDAT ??_C@_08KMDLBENF@?$FO?$FL?$FN?$HL?$HN?$DM?$DO?$HO?$AA@
CONST	SEGMENT
??_C@_08KMDLBENF@?$FO?$FL?$FN?$HL?$HN?$DM?$DO?$HO?$AA@ DB '^[]{}<>~', 00H ; `string'
CONST	ENDS
;	COMDAT ?__LINE__Var@?1??entab_buf@@YAHPBDPADH@Z@4JA
_DATA	SEGMENT
?__LINE__Var@?1??entab_buf@@YAHPBDPADH@Z@4JA DD 01fH	; `entab_buf'::`2'::__LINE__Var
_DATA	ENDS
;	COMDAT ??_C@_0CB@LICAEBEI@c?3?2astrow32dev?2tbt32?2endetab?4cpp@
CONST	SEGMENT
??_C@_0CB@LICAEBEI@c?3?2astrow32dev?2tbt32?2endetab?4cpp@ DB 'c:\astrow32'
	DB	'dev\tbt32\endetab.cpp', 00H			; `string'
CONST	ENDS
;	COMDAT ??_C@_0O@NDPOADHB@len?5?$DM?5max_len?$AA@
CONST	SEGMENT
??_C@_0O@NDPOADHB@len?5?$DM?5max_len?$AA@ DB 'len < max_len', 00H ; `string'
; Function compile flags: /Odt /RTCcsu /ZI
CONST	ENDS
;	COMDAT ?entab_buf@@YAHPBDPADH@Z
_TEXT	SEGMENT
tv67 = -256						; size = 4
_dst$ = -56						; size = 4
_src$ = -44						; size = 4
_len$ = -32						; size = 4
_space_cnt$ = -20					; size = 4
_col$ = -8						; size = 4
_buf$ = 8						; size = 4
_out$ = 12						; size = 4
_max_len$ = 16						; size = 4
?entab_buf@@YAHPBDPADH@Z PROC NEAR			; entab_buf, COMDAT

; 31   : {

	push	ebp
	mov	ebp, esp
	sub	esp, 256				; 00000100H
	push	ebx
	push	esi
	push	edi
	lea	edi, DWORD PTR [ebp-256]
	mov	ecx, 64					; 00000040H
	mov	eax, -858993460				; ccccccccH
	rep stosd

; 32   :  int col = 0, space_cnt = 0, len = 0;

	mov	DWORD PTR _col$[ebp], 0
	mov	DWORD PTR _space_cnt$[ebp], 0
	mov	DWORD PTR _len$[ebp], 0

; 33   :  const char *src = buf;

	mov	eax, DWORD PTR _buf$[ebp]
	mov	DWORD PTR _src$[ebp], eax

; 34   :  char *dst = out;

	mov	eax, DWORD PTR _out$[ebp]
	mov	DWORD PTR _dst$[ebp], eax
$L92972:

; 35   : 
; 36   :  while ( *src ) {

	mov	eax, DWORD PTR _src$[ebp]
	movsx	ecx, BYTE PTR [eax]
	test	ecx, ecx
	je	$L92973

; 37   :        switch( *src ) {

	mov	eax, DWORD PTR _src$[ebp]
	mov	cl, BYTE PTR [eax]
	mov	BYTE PTR tv67[ebp], cl
	cmp	BYTE PTR tv67[ebp], 10			; 0000000aH
	je	$L92984
	cmp	BYTE PTR tv67[ebp], 32			; 00000020H
	je	SHORT $L92978
	cmp	BYTE PTR tv67[ebp], 126			; 0000007eH
	je	SHORT $L92980
	jmp	$L92985
$L92978:

; 38   : 	     case ' ' :
; 39   : 		  space_cnt++;

	mov	eax, DWORD PTR _space_cnt$[ebp]
	add	eax, 1
	mov	DWORD PTR _space_cnt$[ebp], eax

; 40   : 		  col++;

	mov	eax, DWORD PTR _col$[ebp]
	add	eax, 1
	mov	DWORD PTR _col$[ebp], eax

; 41   : 		  if ( col%5==0 )

	mov	eax, DWORD PTR _col$[ebp]
	cdq
	mov	ecx, 5
	idiv	ecx
	test	edx, edx
	jne	SHORT $L92979

; 42   : 		     dst = space_out( &space_cnt, col, &len, dst );

	mov	eax, DWORD PTR _dst$[ebp]
	push	eax
	lea	ecx, DWORD PTR _len$[ebp]
	push	ecx
	mov	edx, DWORD PTR _col$[ebp]
	push	edx
	lea	eax, DWORD PTR _space_cnt$[ebp]
	push	eax
	call	?space_out@@YAPADPAHH0PAD@Z		; space_out
	add	esp, 16					; 00000010H
	mov	DWORD PTR _dst$[ebp], eax
$L92979:

; 43   : 		  break;

	jmp	$L92975
$L92980:

; 44   : 	     case '~' :
; 45   : 		  dst = space_out( &space_cnt, col, &len, dst );

	mov	eax, DWORD PTR _dst$[ebp]
	push	eax
	lea	ecx, DWORD PTR _len$[ebp]
	push	ecx
	mov	edx, DWORD PTR _col$[ebp]
	push	edx
	lea	eax, DWORD PTR _space_cnt$[ebp]
	push	eax
	call	?space_out@@YAPADPAHH0PAD@Z		; space_out
	add	esp, 16					; 00000010H
	mov	DWORD PTR _dst$[ebp], eax

; 46   : 		  src++;

	mov	eax, DWORD PTR _src$[ebp]
	add	eax, 1
	mov	DWORD PTR _src$[ebp], eax

; 47   : 		  if ( strchr("^[]{}<>~", *src) != NULL )  {

	mov	eax, DWORD PTR _src$[ebp]
	movsx	ecx, BYTE PTR [eax]
	push	ecx
	push	OFFSET FLAT:??_C@_08KMDLBENF@?$FO?$FL?$FN?$HL?$HN?$DM?$DO?$HO?$AA@
	call	_strchr
	add	esp, 8
	test	eax, eax
	je	SHORT $L92981

; 48   : 		     *dst++ = '~';

	mov	eax, DWORD PTR _dst$[ebp]
	mov	BYTE PTR [eax], 126			; 0000007eH
	mov	ecx, DWORD PTR _dst$[ebp]
	add	ecx, 1
	mov	DWORD PTR _dst$[ebp], ecx

; 49   : 		     *dst++ = *src;

	mov	eax, DWORD PTR _dst$[ebp]
	mov	ecx, DWORD PTR _src$[ebp]
	mov	dl, BYTE PTR [ecx]
	mov	BYTE PTR [eax], dl
	mov	eax, DWORD PTR _dst$[ebp]
	add	eax, 1
	mov	DWORD PTR _dst$[ebp], eax

; 50   : 		     }
; 51   : 		  else

	jmp	SHORT $L92983
$L92981:

; 52   : 		     *dst++ = *src;

	mov	eax, DWORD PTR _dst$[ebp]
	mov	ecx, DWORD PTR _src$[ebp]
	mov	dl, BYTE PTR [ecx]
	mov	BYTE PTR [eax], dl
	mov	eax, DWORD PTR _dst$[ebp]
	add	eax, 1
	mov	DWORD PTR _dst$[ebp], eax
$L92983:

; 53   : 		  col++;

	mov	eax, DWORD PTR _col$[ebp]
	add	eax, 1
	mov	DWORD PTR _col$[ebp], eax

; 54   : 		  len++;

	mov	eax, DWORD PTR _len$[ebp]
	add	eax, 1
	mov	DWORD PTR _len$[ebp], eax

; 55   : 		  break;

	jmp	$L92975
$L92984:

; 56   : 	     case '\n':
; 57   : 		  dst = space_out( &space_cnt, col, &len, dst );

	mov	eax, DWORD PTR _dst$[ebp]
	push	eax
	lea	ecx, DWORD PTR _len$[ebp]
	push	ecx
	mov	edx, DWORD PTR _col$[ebp]
	push	edx
	lea	eax, DWORD PTR _space_cnt$[ebp]
	push	eax
	call	?space_out@@YAPADPAHH0PAD@Z		; space_out
	add	esp, 16					; 00000010H
	mov	DWORD PTR _dst$[ebp], eax

; 58   : 		  len++;

	mov	eax, DWORD PTR _len$[ebp]
	add	eax, 1
	mov	DWORD PTR _len$[ebp], eax

; 59   : 		  *dst++ = *src;

	mov	eax, DWORD PTR _dst$[ebp]
	mov	ecx, DWORD PTR _src$[ebp]
	mov	dl, BYTE PTR [ecx]
	mov	BYTE PTR [eax], dl
	mov	eax, DWORD PTR _dst$[ebp]
	add	eax, 1
	mov	DWORD PTR _dst$[ebp], eax

; 60   : 		  col = 0;

	mov	DWORD PTR _col$[ebp], 0

; 61   : 		  break;

	jmp	SHORT $L92975
$L92985:

; 62   : 	     default :
; 63   : 		  dst = space_out( &space_cnt, col, &len, dst );

	mov	eax, DWORD PTR _dst$[ebp]
	push	eax
	lea	ecx, DWORD PTR _len$[ebp]
	push	ecx
	mov	edx, DWORD PTR _col$[ebp]
	push	edx
	lea	eax, DWORD PTR _space_cnt$[ebp]
	push	eax
	call	?space_out@@YAPADPAHH0PAD@Z		; space_out
	add	esp, 16					; 00000010H
	mov	DWORD PTR _dst$[ebp], eax

; 64   : 		  *dst++ = *src;

	mov	eax, DWORD PTR _dst$[ebp]
	mov	ecx, DWORD PTR _src$[ebp]
	mov	dl, BYTE PTR [ecx]
	mov	BYTE PTR [eax], dl
	mov	eax, DWORD PTR _dst$[ebp]
	add	eax, 1
	mov	DWORD PTR _dst$[ebp], eax

; 65   : 		  len++;

	mov	eax, DWORD PTR _len$[ebp]
	add	eax, 1
	mov	DWORD PTR _len$[ebp], eax

; 66   : 		  col++;

	mov	eax, DWORD PTR _col$[ebp]
	add	eax, 1
	mov	DWORD PTR _col$[ebp], eax
$L92975:

; 67   : 		  break;
; 68   : 	     }
; 69   :        assert( len < max_len );

	mov	eax, DWORD PTR _len$[ebp]
	cmp	eax, DWORD PTR _max_len$[ebp]
	jl	SHORT $L93049
	mov	ecx, DWORD PTR ?__LINE__Var@?1??entab_buf@@YAHPBDPADH@Z@4JA
	add	ecx, 38					; 00000026H
	push	ecx
	push	OFFSET FLAT:??_C@_0CB@LICAEBEI@c?3?2astrow32dev?2tbt32?2endetab?4cpp@
	push	OFFSET FLAT:??_C@_0O@NDPOADHB@len?5?$DM?5max_len?$AA@
	call	__assert
	add	esp, 12					; 0000000cH
$L93049:

; 70   :        if ( len >= max_len ) {

	mov	eax, DWORD PTR _len$[ebp]
	cmp	eax, DWORD PTR _max_len$[ebp]
	jl	SHORT $L92990

; 71   : 	  *dst++ = '\0';

	mov	eax, DWORD PTR _dst$[ebp]
	mov	BYTE PTR [eax], 0
	mov	ecx, DWORD PTR _dst$[ebp]
	add	ecx, 1
	mov	DWORD PTR _dst$[ebp], ecx

; 72   : 	  *dst++ = '\0';

	mov	eax, DWORD PTR _dst$[ebp]
	mov	BYTE PTR [eax], 0
	mov	ecx, DWORD PTR _dst$[ebp]
	add	ecx, 1
	mov	DWORD PTR _dst$[ebp], ecx

; 73   : 	  return( len );

	mov	eax, DWORD PTR _len$[ebp]
	jmp	SHORT $L92965
$L92990:

; 74   : 	  }
; 75   :        src++;

	mov	eax, DWORD PTR _src$[ebp]
	add	eax, 1
	mov	DWORD PTR _src$[ebp], eax

; 76   :        }

	jmp	$L92972
$L92973:

; 77   :  if ( *(dst-1) != '\n' )

	mov	eax, DWORD PTR _dst$[ebp]
	movsx	ecx, BYTE PTR [eax-1]
	cmp	ecx, 10					; 0000000aH
	je	SHORT $L92991

; 78   :     *dst++ = '\n';

	mov	eax, DWORD PTR _dst$[ebp]
	mov	BYTE PTR [eax], 10			; 0000000aH
	mov	ecx, DWORD PTR _dst$[ebp]
	add	ecx, 1
	mov	DWORD PTR _dst$[ebp], ecx
$L92991:

; 79   :  *dst++ = '\0';

	mov	eax, DWORD PTR _dst$[ebp]
	mov	BYTE PTR [eax], 0
	mov	ecx, DWORD PTR _dst$[ebp]
	add	ecx, 1
	mov	DWORD PTR _dst$[ebp], ecx

; 80   :  *dst++ = '\0';

	mov	eax, DWORD PTR _dst$[ebp]
	mov	BYTE PTR [eax], 0
	mov	ecx, DWORD PTR _dst$[ebp]
	add	ecx, 1
	mov	DWORD PTR _dst$[ebp], ecx

; 81   :  return( strlen(out) );

	mov	eax, DWORD PTR _out$[ebp]
	push	eax
	call	_strlen
	add	esp, 4
$L92965:

; 82   : }

	push	edx
	mov	ecx, ebp
	push	eax
	lea	edx, DWORD PTR $L93053
	call	@_RTC_CheckStackVars@8
	pop	eax
	pop	edx
	pop	edi
	pop	esi
	pop	ebx
	add	esp, 256				; 00000100H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
$L93053:
	DD	2
	DD	$L93052
$L93052:
	DD	-20					; ffffffecH
	DD	4
	DD	$L93050
	DD	-32					; ffffffe0H
	DD	4
	DD	$L93051
$L93051:
	DB	108					; 0000006cH
	DB	101					; 00000065H
	DB	110					; 0000006eH
	DB	0
$L93050:
	DB	115					; 00000073H
	DB	112					; 00000070H
	DB	97					; 00000061H
	DB	99					; 00000063H
	DB	101					; 00000065H
	DB	95					; 0000005fH
	DB	99					; 00000063H
	DB	110					; 0000006eH
	DB	116					; 00000074H
	DB	0
?entab_buf@@YAHPBDPADH@Z ENDP				; entab_buf
_TEXT	ENDS
PUBLIC	?detab_buf@@YAHPBDHPAD@Z			; detab_buf
PUBLIC	?__LINE__Var@?1??detab_buf@@YAHPBDHPAD@Z@4JA	; `detab_buf'::`2'::__LINE__Var
;	COMDAT ?__LINE__Var@?1??detab_buf@@YAHPBDHPAD@Z@4JA
_DATA	SEGMENT
?__LINE__Var@?1??detab_buf@@YAHPBDHPAD@Z@4JA DD 05bH	; `detab_buf'::`2'::__LINE__Var
; Function compile flags: /Odt /RTCcsu /ZI
_DATA	ENDS
;	COMDAT ?detab_buf@@YAHPBDHPAD@Z
_TEXT	SEGMENT
tv75 = -292						; size = 4
tv69 = -292						; size = 4
_dst$ = -92						; size = 4
_src$ = -80						; size = 4
_len$ = -68						; size = 4
_h$ = -56						; size = 4
_u$ = -44						; size = 4
_b$ = -32						; size = 4
_ts$ = -20						; size = 4
_col$ = -8						; size = 4
_buffer$ = 8						; size = 4
_max_len$ = 12						; size = 4
_nbuf$ = 16						; size = 4
?detab_buf@@YAHPBDHPAD@Z PROC NEAR			; detab_buf, COMDAT

; 91   : {

	push	ebp
	mov	ebp, esp
	sub	esp, 292				; 00000124H
	push	ebx
	push	esi
	push	edi
	lea	edi, DWORD PTR [ebp-292]
	mov	ecx, 73					; 00000049H
	mov	eax, -858993460				; ccccccccH
	rep stosd

; 92   :  int col = 1, ts, b = 0, u = 0, h = 0;

	mov	DWORD PTR _col$[ebp], 1
	mov	DWORD PTR _b$[ebp], 0
	mov	DWORD PTR _u$[ebp], 0
	mov	DWORD PTR _h$[ebp], 0

; 93   :  int len = strlen( buffer );

	mov	eax, DWORD PTR _buffer$[ebp]
	push	eax
	call	_strlen
	add	esp, 4
	mov	DWORD PTR _len$[ebp], eax

; 94   :  const char *src = buffer;

	mov	eax, DWORD PTR _buffer$[ebp]
	mov	DWORD PTR _src$[ebp], eax

; 95   :  char *dst = nbuf;

	mov	eax, DWORD PTR _nbuf$[ebp]
	mov	DWORD PTR _dst$[ebp], eax

; 96   : 
; 97   :  len = 0;

	mov	DWORD PTR _len$[ebp], 0
$L93006:

; 98   :  while ( *src ) {

	mov	eax, DWORD PTR _src$[ebp]
	movsx	ecx, BYTE PTR [eax]
	test	ecx, ecx
	je	$L93007

; 99   :        switch( *src ) {

	mov	eax, DWORD PTR _src$[ebp]
	mov	cl, BYTE PTR [eax]
	mov	BYTE PTR tv69[ebp], cl
	cmp	BYTE PTR tv69[ebp], 9
	je	SHORT $L93013
	cmp	BYTE PTR tv69[ebp], 10			; 0000000aH
	je	SHORT $L93012
	jmp	$L93017
$L93012:

; 100  : 	     case '\n' :
; 101  : 		  *dst++ = *src;

	mov	eax, DWORD PTR _dst$[ebp]
	mov	ecx, DWORD PTR _src$[ebp]
	mov	dl, BYTE PTR [ecx]
	mov	BYTE PTR [eax], dl
	mov	eax, DWORD PTR _dst$[ebp]
	add	eax, 1
	mov	DWORD PTR _dst$[ebp], eax

; 102  : 		  len++;

	mov	eax, DWORD PTR _len$[ebp]
	add	eax, 1
	mov	DWORD PTR _len$[ebp], eax

; 103  : 		  col = 0;

	mov	DWORD PTR _col$[ebp], 0

; 104  : 		  break;

	jmp	$L93009
$L93013:

; 105  : 	     case '\t' :
; 106  : 		  ts = 5-(col % 5);

	mov	eax, DWORD PTR _col$[ebp]
	cdq
	mov	ecx, 5
	idiv	ecx
	mov	eax, 5
	sub	eax, edx
	mov	DWORD PTR _ts$[ebp], eax
$L93015:

; 107  : 		  while ( ts-- ) {

	mov	eax, DWORD PTR _ts$[ebp]
	mov	DWORD PTR tv75[ebp], eax
	mov	ecx, DWORD PTR _ts$[ebp]
	sub	ecx, 1
	mov	DWORD PTR _ts$[ebp], ecx
	cmp	DWORD PTR tv75[ebp], 0
	je	SHORT $L93016

; 108  : 			*dst++ = ' ';

	mov	eax, DWORD PTR _dst$[ebp]
	mov	BYTE PTR [eax], 32			; 00000020H
	mov	ecx, DWORD PTR _dst$[ebp]
	add	ecx, 1
	mov	DWORD PTR _dst$[ebp], ecx

; 109  : 			col++;

	mov	eax, DWORD PTR _col$[ebp]
	add	eax, 1
	mov	DWORD PTR _col$[ebp], eax

; 110  : 			len++;

	mov	eax, DWORD PTR _len$[ebp]
	add	eax, 1
	mov	DWORD PTR _len$[ebp], eax

; 111  : 			}

	jmp	SHORT $L93015
$L93016:

; 112  : 		  break;

	jmp	$L93009
$L93017:

; 113  : 	     default :
; 114  : 		  if ( !isascii( *src ) ) {

	mov	eax, DWORD PTR _src$[ebp]
	movsx	ecx, BYTE PTR [eax]
	cmp	ecx, 128				; 00000080H
	jb	$L93019

; 115  : 		     *dst++ = '~';

	mov	eax, DWORD PTR _dst$[ebp]
	mov	BYTE PTR [eax], 126			; 0000007eH
	mov	ecx, DWORD PTR _dst$[ebp]
	add	ecx, 1
	mov	DWORD PTR _dst$[ebp], ecx

; 116  : 		     *dst++ = *src;

	mov	eax, DWORD PTR _dst$[ebp]
	mov	ecx, DWORD PTR _src$[ebp]
	mov	dl, BYTE PTR [ecx]
	mov	BYTE PTR [eax], dl
	mov	eax, DWORD PTR _dst$[ebp]
	add	eax, 1
	mov	DWORD PTR _dst$[ebp], eax

; 117  : 		     col++;

	mov	eax, DWORD PTR _col$[ebp]
	add	eax, 1
	mov	DWORD PTR _col$[ebp], eax

; 118  : 		     len++;

	mov	eax, DWORD PTR _len$[ebp]
	add	eax, 1
	mov	DWORD PTR _len$[ebp], eax

; 119  : 		     len++;

	mov	eax, DWORD PTR _len$[ebp]
	add	eax, 1
	mov	DWORD PTR _len$[ebp], eax

; 120  : 		     if ( *(src+1) == ' ' ) {

	mov	eax, DWORD PTR _src$[ebp]
	movsx	ecx, BYTE PTR [eax+1]
	cmp	ecx, 32					; 00000020H
	jne	SHORT $L93020

; 121  : 			*dst++ = '~';

	mov	eax, DWORD PTR _dst$[ebp]
	mov	BYTE PTR [eax], 126			; 0000007eH
	mov	ecx, DWORD PTR _dst$[ebp]
	add	ecx, 1
	mov	DWORD PTR _dst$[ebp], ecx

; 122  : 			*dst++ = ' ';

	mov	eax, DWORD PTR _dst$[ebp]
	mov	BYTE PTR [eax], 32			; 00000020H
	mov	ecx, DWORD PTR _dst$[ebp]
	add	ecx, 1
	mov	DWORD PTR _dst$[ebp], ecx

; 123  : 			src++;

	mov	eax, DWORD PTR _src$[ebp]
	add	eax, 1
	mov	DWORD PTR _src$[ebp], eax

; 124  : 			col++;

	mov	eax, DWORD PTR _col$[ebp]
	add	eax, 1
	mov	DWORD PTR _col$[ebp], eax

; 125  : 			len++;

	mov	eax, DWORD PTR _len$[ebp]
	add	eax, 1
	mov	DWORD PTR _len$[ebp], eax

; 126  : 			len++;

	mov	eax, DWORD PTR _len$[ebp]
	add	eax, 1
	mov	DWORD PTR _len$[ebp], eax
$L93020:

; 127  : 			}
; 128  : 		     }
; 129  : 		  else {

	jmp	SHORT $L93009
$L93019:

; 130  : 		     *dst++ = *src;

	mov	eax, DWORD PTR _dst$[ebp]
	mov	ecx, DWORD PTR _src$[ebp]
	mov	dl, BYTE PTR [ecx]
	mov	BYTE PTR [eax], dl
	mov	eax, DWORD PTR _dst$[ebp]
	add	eax, 1
	mov	DWORD PTR _dst$[ebp], eax

; 131  : 		     col++;

	mov	eax, DWORD PTR _col$[ebp]
	add	eax, 1
	mov	DWORD PTR _col$[ebp], eax

; 132  : 		     len++;

	mov	eax, DWORD PTR _len$[ebp]
	add	eax, 1
	mov	DWORD PTR _len$[ebp], eax
$L93009:

; 133  : 		     }
; 134  : 		  break;
; 135  : 	     }
; 136  :        src++;

	mov	eax, DWORD PTR _src$[ebp]
	add	eax, 1
	mov	DWORD PTR _src$[ebp], eax

; 137  :        assert( len < max_len );

	mov	eax, DWORD PTR _len$[ebp]
	cmp	eax, DWORD PTR _max_len$[ebp]
	jl	SHORT $L93058
	mov	ecx, DWORD PTR ?__LINE__Var@?1??detab_buf@@YAHPBDHPAD@Z@4JA
	add	ecx, 46					; 0000002eH
	push	ecx
	push	OFFSET FLAT:??_C@_0CB@LICAEBEI@c?3?2astrow32dev?2tbt32?2endetab?4cpp@
	push	OFFSET FLAT:??_C@_0O@NDPOADHB@len?5?$DM?5max_len?$AA@
	call	__assert
	add	esp, 12					; 0000000cH
$L93058:

; 138  :        }

	jmp	$L93006
$L93007:

; 139  :  if ( *(dst-1) != '\n' )

	mov	eax, DWORD PTR _dst$[ebp]
	movsx	ecx, BYTE PTR [eax-1]
	cmp	ecx, 10					; 0000000aH
	je	SHORT $L93024

; 140  :     *dst++ = '\n';

	mov	eax, DWORD PTR _dst$[ebp]
	mov	BYTE PTR [eax], 10			; 0000000aH
	mov	ecx, DWORD PTR _dst$[ebp]
	add	ecx, 1
	mov	DWORD PTR _dst$[ebp], ecx
$L93024:

; 141  :  *dst++ = '\0';

	mov	eax, DWORD PTR _dst$[ebp]
	mov	BYTE PTR [eax], 0
	mov	ecx, DWORD PTR _dst$[ebp]
	add	ecx, 1
	mov	DWORD PTR _dst$[ebp], ecx

; 142  :  *dst++ = '\0';

	mov	eax, DWORD PTR _dst$[ebp]
	mov	BYTE PTR [eax], 0
	mov	ecx, DWORD PTR _dst$[ebp]
	add	ecx, 1
	mov	DWORD PTR _dst$[ebp], ecx

; 143  :  len = strlen( nbuf );

	mov	eax, DWORD PTR _nbuf$[ebp]
	push	eax
	call	_strlen
	add	esp, 4
	mov	DWORD PTR _len$[ebp], eax

; 144  :  return( len );

	mov	eax, DWORD PTR _len$[ebp]

; 145  : }

	pop	edi
	pop	esi
	pop	ebx
	add	esp, 292				; 00000124H
	cmp	ebp, esp
	call	__RTC_CheckEsp
	mov	esp, ebp
	pop	ebp
	ret	0
?detab_buf@@YAHPBDHPAD@Z ENDP				; detab_buf
_TEXT	ENDS
END
