;	Static Name Aliases
;
	TITLE   domiscca.c
	NAME    domiscca

	.8087
DOMISCA_TEXT     SEGMENT  WORD PUBLIC 'CODE'
DOMISCA_TEXT     ENDS
_DATA	SEGMENT  WORD PUBLIC 'DATA'
_DATA	ENDS
CONST	SEGMENT  WORD PUBLIC 'CONST'
CONST	ENDS
_BSS	SEGMENT  WORD PUBLIC 'BSS'
_BSS	ENDS
DGROUP	GROUP	CONST, _BSS, _DATA
	ASSUME  CS: DOMISCA_TEXT, DS: DGROUP, SS: NOTHING
EXTRN	__acrtused:ABS
EXTRN   _house_cusp_intercept:FAR
EXTRN   _is_sign_intercept:FAR
EXTRN   _tropical_2_sidereal:FAR
EXTRN   _sign_cusp:FAR
EXTRN	__aFNalrem:FAR
EXTRN   _adjust_mins:FAR
EXTRN   _flip_mins:FAR
EXTRN   _house_number:FAR
EXTRN   _house_cusps:BYTE
DOMISCA_TEXT      SEGMENT
	ASSUME  CS: DOMISCA_TEXT

	; int critical_degree( int deg, int sign )
	; edited for speed by cjn, 10/16/89
	; extracted from docalc.c
	PUBLIC  _critical_degree
_critical_degree	PROC FAR
	push	bp
	mov	bp,sp
;       int deg = 6
;       int sign = 8
	mov     ax,WORD PTR ss:[bp+8] ; load sign
	cmp     ax,0               ; test sign against 0
	je      $I697              ; yes jump, no continue
	cmp     ax,3               ; test sign against 3
	je      $I697              ; yes jump, no continue
	cmp     ax,6               ; test sign against 6
	je      $I697              ; yes jump, no continue
	cmp     ax,9               ; test sign against 9
	jne     $I696              ; no continue below, yes continue next
$I697:
	mov     ax,WORD PTR ss:[bp+6] ; load deg
	cmp     ax,0               ; test deg against 0
	je      $I699              ; yes jump, no continue
	cmp     ax,13              ; test deg against 13
	je      $I699              ; yes jump, no continue
	cmp     ax,26              ; test deg against 26
$L20014:
	jne     $I698              ; yes return 1, no return 0
$I699:
	mov     ax,1
	pop	bp
	ret	
$I698:
	sub     ax,ax
	pop	bp
	ret	
$I696:
	cmp     ax,1               ; test sign against 1
	je      $I703              ; yes jump, no continue
	cmp     ax,4               ; test sign against 4
	je      $I703              ; yes jump, no continue
	cmp     ax,7               ; test sign against 7
	je      $I703              ; yes jump, no continue
	cmp     ax,10              ; test sign against 10
	jne     $I702              ; no jump, yes continue
$I703:
	mov     ax,WORD PTR ss:[bp+6]  ; load deg into register
	cmp     ax,9                ; test deg against 9
	je      $I699               ; yes jump, no continue
	cmp     ax,21               ; test deg against 21
	jmp	SHORT $L20014
$I702:
	cmp     ax,2                ; test sign against 2
	je      $I709               ; yes jump, no continue
	cmp     ax,5                ; test sign against 5
	je      $I709               ; yes jump, no continue
	cmp     ax,8                ; test sign against 8
	je      $I709               ; yes jump, no continue
	cmp     ax,11               ; test sign against 11
	jne     $I698               ; no return 0, yes continue
$I709:
	mov     ax,WORD PTR ss:[bp+6]  ; load deg into register
	cmp     ax,4                ; test deg against 9
	je      $I699               ; yes jump, no continue
	cmp     ax,17               ; test deg against 9
	jmp     SHORT $L20014       ; yes jump, no continue
_critical_degree        ENDP



	; void misc_calc( AS_INF *ptr, BITS (unsigned) mode, short year )
	; edited for speed by cjn, 10/17/89
	; extracted from docalc.c
	PUBLIC  _misc_calc
_misc_calc	PROC FAR
	push	bp
	mov	bp,sp
	push    di
	push    si
;	ptr = 6
;	code = 8
;	year = 10
; Line 102
	mov     bx,WORD PTR ss:[bp+6]   ; load ptr in reg
	mov     di,bx                   ; save in di to keep for calls
	mov     ax,WORD PTR [bx]        ; load total minutes
	test    BYTE PTR ss:[bp+8],1    ; test against code
	je      $I718                   ; not set skip around
; Line 103
	push    WORD PTR ss:[bp+10]     ; push year
	push    ax                      ; push total minutes
	call	FAR PTR _tropical_2_sidereal
	add     sp,4                    ; readjust stack
	mov     bx,di                   ; reload ptr
	mov     WORD PTR [bx],ax        ; save new total minutes
; Line 104
$I718:
	cwd
	mov     cx,60
	idiv    cx                      ; signed divide
	mov     WORD PTR [bx+8],dx      ; remainder is minor minutes
; Line 105
	cwd                             ; prepare for division
	mov     cx,30                   ; load divisor
	idiv    cx                      ; signed divide
	mov     WORD PTR [bx+6],dx      ; remainder is minor degrees
	mov     WORD PTR [bx+2],ax      ; remainder is sign
; Line 107
	push    ax                      ; push sign
	push    WORD PTR [bx+8]         ; push minor minutes
	push    dx                      ; push minor degrees
	call    FAR PTR _sign_cusp
	add     sp,6                    ; readjust stack
	mov     bx,di                   ; reload ptr
	mov     WORD PTR [bx+4],ax      ; save cusp
; Line 108
	test    WORD PTR ss:[bp+8],512  ; test against code
	je      $I719                   ; not set skip around
; Line 109
	mov     ax,WORD PTR [bx+6]      ; load minor degrees
	cwd                             ; prepare for division
	mov     cx,10                   ; load divisor
	idiv    cx                      ; signed divide
	inc     ax                      ; add 1
	mov     WORD PTR [bx+18],ax     ; save in decan
; Line 110
$I719:
	test    BYTE PTR ss:[bp+8],32   ; test against code
	je      $I720                   ; not set skip around
; Line 111
	mov     si,WORD PTR [bx]        ; load si with total minutes
	push    si                      ; push for call
	call	FAR PTR _house_number
	add     sp,2                    ; readjust stack
	mov     bx,di                   ; reload ptr
	mov     WORD PTR [bx+10],ax     ; save in house number
; Line 112
	push    ax                      ; push house
	push    si                      ; push total minutes
	call	FAR PTR _house_cusp_intercept
	add     sp,4                    ; readjust stack
	mov     bx,di                   ; reload ptr
	mov     WORD PTR [bx+12],ax     ; save house_cusp
; Line 113
; Line 114
$I720:
	test    WORD PTR ss:[bp+8],512  ; test against code
	je      $I723                   ; not set skip around
; Line 115
	mov     bx,di                   ; reload ptr
	cmp     WORD PTR [bx+6],28      ; is minor minutes anaretic degree
	jle     $I722                   ; no jump
; Line 116
	or      BYTE PTR [bx+18],8      ; yes set bit
; Line 117
$I722:
	push    WORD PTR [bx+2]         ; push sign
	push    WORD PTR [bx+6]         ; push minor degree
	call    FAR PTR _critical_degree
	add     sp,4                    ; readjust stack
	or      ax,ax                   ; is ax == 0
	je      $I723                   ; yes jump
; Line 118
	mov     bx,di                   ; reload ptr
	or      BYTE PTR [bx+18],4      ; set bit
; Line 119
$I723:
	push    WORD PTR [bx+2]         ; push sign
	call    FAR PTR _is_sign_intercept
	add     sp,2                    ; readjust stack
	mov     bx, di                  ; reload ptr
	mov     [bx+14], ax             ; save intercepted
; Line 120
	pop     si                      ; return to caller
	pop     di
	pop     bp
	ret	

_misc_calc	ENDP
DOMISCA_TEXT     ENDS
END
