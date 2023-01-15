;	Static Name Aliases
;
	TITLE   splitdeg.c
	NAME    splitdeg

	.8087
SPLITDEG_TEXT     SEGMENT  WORD PUBLIC 'CODE'
SPLITDEG_TEXT     ENDS
_DATA	SEGMENT  WORD PUBLIC 'DATA'
_DATA	ENDS
CONST	SEGMENT  WORD PUBLIC 'CONST'
CONST	ENDS
_BSS	SEGMENT  WORD PUBLIC 'BSS'
_BSS	ENDS
DGROUP	GROUP	CONST, _BSS, _DATA
	ASSUME  CS: SPLITDEG_TEXT, DS: DGROUP, SS: DGROUP
EXTRN	__acrtused:ABS
EXTRN	_sign_cusp:FAR
SPLITDEG_TEXT      SEGMENT
	ASSUME  CS: SPLITDEG_TEXT
	; void do_house_sign( int minutes, int *minor, int *sign, int *cusp )
	; edited for speed by cjn 10/16/89
	; derived from do_house_sign() in prnres.c
	PUBLIC  _do_house_sign
_do_house_sign	PROC FAR
	push	bp
	mov	bp,sp
;       stack parameters
;       int minutes = 6
;       int *minor = 8
;       int *sign = 12
;       int *cusp = 16
	mov     ax,WORD PTR ss:[bp+6]   ; load minutes in register
	cwd	
	mov     cx,60                   ; load divisor
	idiv    cx                      ; divide
	mov     bx,dx                   ; bx is minor minutes
	cwd
	mov     cx,30                   ; load next divisor
	idiv    cx                      ; divide
	push    ax                      ; push sign
	push    bx                      ; push minor minutes
	push    dx                      ; push minor degrees
	les     bx,DWORD PTR ss:[bp+8]  ; load pointer for minor degrees
	mov     WORD PTR es:[bx],dx     ; save minor degrees
	les     bx,DWORD PTR ss:[bp+12] ; load pointer for sign
	mov     WORD PTR es:[bx],ax     ; save sign
	call    FAR PTR _sign_cusp      ; get sign_cusp
	add     sp,6                    ; readjust stack
	les     bx,DWORD PTR ss:[bp+16] ; load pointer for cusp
	mov     WORD PTR es:[bx],ax     ; save cusp
	pop     bp                      ; return
	ret	
_do_house_sign  ENDP
SPLITDEG_TEXT     ENDS
END
