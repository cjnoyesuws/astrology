;       Static Name Aliases
;
;       $S564_m EQU     m
;       $S565_y EQU     y
;       $S584_signs     EQU     signs
;       $S601_planets   EQU     planets
;       $S636_numbers   EQU     numbers
;       $S654_aspects   EQU     aspects
;       $S668_signs     EQU     signs
	TITLE   astmisc.c
	NAME    astmisc
.8087
ASTXMISC_TEXT    SEGMENT  WORD PUBLIC 'CODE'
ASTXMISC_TEXT    ENDS
_DATA   SEGMENT  WORD PUBLIC 'DATA'
_DATA   ENDS
CONST   SEGMENT  WORD PUBLIC 'CONST'
CONST   ENDS
_BSS    SEGMENT  WORD PUBLIC 'BSS'
_BSS    ENDS
DGROUP  GROUP   CONST, _BSS, _DATA
	ASSUME  CS: ASTXMISC_TEXT, DS: DGROUP, SS: NOTHING
EXTRN   __acrtused:ABS
EXTRN   _sprintf:FAR
EXTRN   _fprintf:FAR
EXTRN   __aFNalmul:FAR
EXTRN   __aFNaldiv:FAR
EXTRN   _ERROR2:BYTE
_DATA      SEGMENT
$MODE   DW      00H
$S564_m DW      00H
$S565_y DW      00H
_DATA      ENDS
ASTXMISC_TEXT      SEGMENT
	ASSUME  CS: ASTXMISC_TEXT
	; void set_mode( int m );
	PUBLIC  _set_mode_flags
 _set_mode_flags    PROC FAR
	push    bp
	mov     bp,sp
	sub     sp,4
;       m = 6
	mov     ax,WORD PTR ss:[bp+6]
	mov     $MODE, ax
	mov     sp, bp
	pop     bp
	ret
_set_mode_flags     ENDP

; Line 14
	; int tropical_2_sidereal( int minutes, int year )
	; edited for speed cjn 10/10/1989
	PUBLIC  _tropical_2_sidereal
_tropical_2_sidereal	PROC FAR
	push	bp
	mov	bp,sp
	sub	sp,4
;	minutes = 6
;	year = 8
;	min = -4
; Line 17
	mov     ax,$S565_y              ; if ( y != year ) no need to recalc
	cmp     WORD PTR ss:[bp+8],ax   ;
	je	$I604
; Line 18
	mov     ax,WORD PTR ss:[bp+8]   ; recalculate adjustment see astmisc.c
	sub     ax,221                  ; year offset of 221 ad
; Line 19
	mov     bx,50
	imul    bx  ;min
; Line 20
	mov     bx,60
	idiv    bx
; Line 21
	mov     $S564_m,ax
; Line 22
	mov     ax,WORD PTR ss:[bp+8]   ;year
	mov     $S565_y,ax
; Line 23
; Line 24
$I604:
	mov     ax, WORD PTR ss:[bp+6]  ; load to reduce accesses
	sub     ax, $S564_m             ; min -= m
; Line 25
	cmp     ax, 0                   ; if ( min < 0 )
	jge     $I605
	add     ax, 21600               ; add 360 degrees
$I605:  cmp     ax, 21599               ; if min >= 360 degrees
	jle     $I606
	sub     ax, 21600               ; subtract 360 degrees
$I606:  mov     sp, bp                  ; return min
	pop     bp
	ret	
	nop	

_tropical_2_sidereal	ENDP

; Line 33
	; int sign_cusp( int minor_degree, int minor_minutes, int sign )
	; edited for speed, cjn 10/10/1989

	PUBLIC  _sign_cusp
_sign_cusp	PROC FAR
	push	bp
	mov	bp,sp
;	minor_degree = 6
;	minor_minutes = 8
;	sign = 10
; Line 35
	mov     ax, $MODE
	and     ax, 8000H
	jnz     $L20004
	mov     ax, WORD PTR ss:[bp+6]  ; load minor degree (reduce rednd acc)
	cmp     ax,2                    ; test lower range limit
	jle     $I609
	cmp     ax,29                   ; test upper range limit
	jge	$I609
; Line 36
$L20004:
	mov     ax,-1                   ; return -1 not on a cusp
	pop	bp
	ret	
$I609:
; Line 37
	cmp     ax,2                    ; test for 2d31m edge
	jne     $I611                   ; ok
	cmp     WORD PTR ss:[bp+8],31   ; test minutes
	jl      $L20004                 ; not on a cusp return -1
$I611:
	mov     bx, WORD PTR ss:[bp+10] ; load to reduce redundant accesses
	cmp     ax,3                    ; if ( minor_degree < 3 &&
	jge	$I612
	cmp     bx,0                    ; Sign > ARIES )
	jle	$I612
; Line 40
	mov     ax,bx                   ; return sign -1
	dec	ax
	pop	bp
	ret	
$I612:
; Line 41
	cmp     ax,3                    ; else if ( minor_degree < 3 )
	jge	$I614
; Line 42
	mov     ax,11                   ; return PISCES
	pop	bp
	ret	
	nop	
$I614:
; Line 43
	cmp     bx,11                   ; is it PISCES
	jne	$I616
; Line 44
	sub     ax,ax                   ; return ARIES
	pop	bp
	ret	
$I616:
; Line 46
	mov     ax,bx                   ; else return SIGN + 1
	inc	ax
	pop	bp
	ret	
_sign_cusp      ENDP
ASTXMISC_TEXT    ENDS
END
