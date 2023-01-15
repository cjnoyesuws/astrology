;	Static Name Aliases
;
;	$S508_maxorb	EQU	maxorb
;	$S509_aspptr	EQU	aspptr
	TITLE   aspec.asm
	NAME    aspec
;
;#######################################################################
;####  The C Source for these routines are found in ASPECTS.C  #########
;#######################################################################
;
	.8087
ASPEC_TEXT    SEGMENT  WORD PUBLIC 'CODE'
ASPEC_TEXT    ENDS
_DATA	SEGMENT  WORD PUBLIC 'DATA'
_DATA	ENDS
CONST	SEGMENT  WORD PUBLIC 'CONST'
CONST	ENDS
_BSS	SEGMENT  WORD PUBLIC 'BSS'
_BSS	ENDS
DGROUP	GROUP	CONST, _BSS, _DATA
	ASSUME  CS: ASPEC_TEXT, DS: DGROUP, SS: DGROUP
EXTRN   __acrtused:ABS
EXTRN   _house_cusps:BYTE
EXTRN   _aspect_def:BYTE
_BSS      SEGMENT
COMM NEAR	_max_asp:	BYTE:	 2
_BSS      ENDS
_DATA      SEGMENT
;_aspect_def     DW      00H
;        DW      00H
;        DW      01a4H
;        DW      01H
;        DW      0e10H
;        DW      01a4H
;        DW      02H
;        DW      01c20H
;        DW      01a4H
;        DW      03H
;        DW      02a30H
;        DW      01a4H
;        DW      04H
;        DW      01518H
;        DW      01a4H
;        DW      05H
;        DW      0708H
;        DW      078H
;        DW      06H
;        DW      0a8cH
;        DW      078H
;        DW      07H
;        DW      01fa4H
;        DW      078H
_maxorb DW      0
_DATA      ENDS
_BSS      SEGMENT
_BSS      ENDS
ASPEC_TEXT      SEGMENT
	ASSUME  CS: ASPEC_TEXT
; Was a C function, but it is only called by find aspect.
; It is now a near assembly language function
; Rewrote for speed by cjn 10/14/89
; CALLED WITH:
;       abs_difference   ax   also returns value
;       aspptr bx   stable
; USES:
;       orb  di     register pushed when entering
; RETURNS:
;       result ax
test_aspect    PROC NEAR
	push    di                   ; save di reg
	cmp     ax,11280             ; is dif greater than 188 degrees
	jle     le188d               ; no jump
	mov     di,21600             ; di is temp reg
	sub     di,ax                ; 360 degrees - dif
	mov     ax,di                ; back into dif
le188d: sub     ax,WORD PTR [bx+2]   ; check agains ptr->degs
	jns     negdif               ; if less than 0 jump
	neg     ax                   ; make positive
negdif: cmp     WORD PTR _maxorb,0   ; check maxorb for 0
	jne     monot0               ; no jump
	mov     di,WORD PTR [bx+4]   ; move ptr->maxorb into orb
	jmp     SHORT tst
monot0: mov     di,_maxorb           ; else move _maxorb into orb
tst:    cmp     ax, di               ; compare orb against dif
	jg      noaspect             ; too big return NOASPECT
	pop     di
	ret
noaspect:
	mov     ax,-999              ; NOASPECT = -999
	pop     di
	ret
test_aspect    ENDP




; Line 61
	; int find_aspect( int deg1, int deg2, int *aspect, int maxiorb )
	; edited for speed by cjn 10/14/89
	PUBLIC  _find_aspect
_find_aspect	PROC FAR
	push	bp
	mov	bp,sp
;       deg1 = 6
;	deg2 = 8
;	aspect = 10
;	maxiorb = 14
; Line 64
	mov     cx,WORD PTR ss:[bp+14]  ; load maxiorb in cx for loop
	mov     _maxorb, cx             ; save it
	mov     ax, ss:[bp+6]           ; load deg1 in ax for call
	mov     dx, ss:[bp+8]           ; load deg2 in dx for call
	sub     ax, dx                  ; sub dx
	or      ax, ax                  ; is it 0
	jge     gt0                     ; greater than 0 jmp
; Line 42
	neg     ax                      ; change sign
gt0:    mov     dx,ax                   ; save it in dx
	mov     bx,OFFSET DGROUP:_aspect_def  ; load ptr to aspect_deg
	mov     cx,WORD PTR _max_asp    ; load _max_asp
test_a: mov     ax,dx                   ; copy from dx
	call    NEAR PTR test_aspect    ; call loop
	cmp     ax, -999                ; if result is not -999 jump
	jne     asp_ok                  ; got an aspect
	add     bx,6                    ; increment pointer
	loop    test_a                  ; continue loop
	les     bx,DWORD PTR ss:[bp+10] ; load aspect pointer
	mov     WORD PTR es:[bx],-1     ; -1 to represent no aspect
	mov     sp,bp                   ; go home
	pop     bp
	ret
asp_ok: mov cx, WORD PTR [bx]           ; get aspect number
	les     bx,DWORD PTR ss:[bp+10] ; load aspect pointer
	mov     WORD PTR es:[bx],cx     ; save aspect number
	mov     sp,bp                   ; go home
	pop     bp
	ret
_find_aspect	ENDP


ASPEC_TEXT    ENDS
END
