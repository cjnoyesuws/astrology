;       Static Name Aliases
;
	TITLE   midpt.ASM
	NAME    midpt

;
;######################################################################
;#########  Source For These Routines Is Found In MIDPOINT.C  #########
;######################################################################
;

	.8087
MIDPT_TEXT   SEGMENT  WORD PUBLIC 'CODE'
MIDPT_TEXT   ENDS
_DATA	SEGMENT  WORD PUBLIC 'DATA'
_DATA	ENDS
CONST	SEGMENT  WORD PUBLIC 'CONST'
CONST	ENDS
_BSS	SEGMENT  WORD PUBLIC 'BSS'
_BSS	ENDS
DGROUP	GROUP	CONST, _BSS, _DATA
	ASSUME  CS: MIDPT_TEXT, DS: DGROUP, SS: DGROUP
EXTRN	__acrtused:ABS
EXTRN	_sign_cusp:FAR
EXTRN	_adjust_mins:FAR
EXTRN	_house_number:FAR
EXTRN	_free:FAR
EXTRN	_malloc:FAR
EXTRN   _house_cusp_intercept:FAR
EXTRN   _is_sign_intercept:FAR
EXTRN	_realloc:FAR
EXTRN	_find_aspect:FAR
EXTRN	_house_cusps:BYTE
EXTRN	_errno:WORD
EXTRN	_max_asp:WORD
MIDPT_TEXT      SEGMENT
	ASSUME  CS: MIDPT_TEXT
; Line 11
	; int midpoint( int min1, int min2 )
	; edited for speed by cjn 10/14/89
	PUBLIC  _midpoint
_midpoint   PROC FAR
	push    bp
	mov bp,sp
;   min1 = 6
;   min2 = 8
	mov     ax,WORD PTR ss:[bp+8]   ; load min2 into register
	mov     bx,WORD PTR ss:[bp+6]   ; load min1 into register
	cmp     bx,ax                   ; check to see which is bigger
	jge     $I514                   ; if ax is lesser, jump and sw
	xchg    ax, bx                  ; swap ax, and bx
$I514:
	mov     cx, ax                  ; save ax
	mov     dx, bx                  ; save larger just in case
	sub     bx, ax                  ; create difference
	xchg    ax, bx                  ; swap
	cmp     ax, 10800               ; is difference greater than 180 deg
	jb      no180
	mov     bx, 21600               ; 360 deg into bx and
	sub     bx, ax                  ; subtract
	xchg    ax, bx                  ; swap
	sar     ax, 1                   ; divide by two
	add     ax, dx                  ; add to greater
	jmp     short chkwrp
no180:
	sar     ax, 1                   ; divide by two
	add     ax,cx                   ; add to minimum
chkwrp:
	cmp     ax, 21600               ; check against 360 deg
	jb      ok                      ; ok to leave
	sub     ax, 21600               ; else subtract 360 deg
ok:
	pop     bp                      ; return ax
	ret
_midpoint       ENDP


; Line 33
	; mid_misc_calc( MIDPT *ptr )
	; edited for speed by cjn by 10/21/89
	PUBLIC  _mid_misc_calc
_mid_misc_calc   PROC FAR
	push	bp
	mov	bp,sp
	push	si
;	ptr = 6
	les     bx,DWORD PTR ss:[bp+6]  ;loax ptr
	mov     si,WORD PTR es:[bx]     ; load ptr->total_minutes
	mov     ax,si
	cwd
	mov     cx,60                   ; load divisor
	idiv    cx                      ; divide
	mov     WORD PTR es:[bx+6],dx   ; save ptr->minor_minutes
	cwd
	mov     cx,30                   ; load divisor
	idiv    cx                      ; divide
	mov     WORD PTR es:[bx+2],ax   ; save ptr->sign
	mov     WORD PTR es:[bx+4],dx   ; save ptr->minor_degrees
	push    ax                      ; push ptr->sign
	push    WORD PTR es:[bx+6]      ; push ptr->minor_minutes
	push    dx                      ; push ptr->minor_degrees
	call    FAR PTR _sign_cusp
	add	sp,6
	les     bx,DWORD PTR ss:[bp+6]  ; load ptr
	mov     WORD PTR es:[bx+8],ax   ; save ptr->cusp
; Line 38
	push    si                      ; push ptr->total_minutes
	call    FAR PTR _house_number
	add     sp,2
	les     bx,DWORD PTR ss:[bp+6]  ; load ptr
	mov     WORD PTR es:[bx+10],ax  ; save ptr->house_number
; Line 39
	push    ax                      ; push ptr->house_number
	push    si                      ; ptr->total_minutes
	call	FAR PTR _house_cusp_intercept
	add	sp,4
	les     bx,DWORD PTR ss:[bp+6]  ; load ptr
	mov     WORD PTR es:[bx+12],ax  ; save ptr->house_cusp
; Line 40
	push    WORD PTR es:[bx+2]      ; save ptr->sign
	call    FAR PTR _is_sign_intercept
	add     sp,2
	les     bx,DWORD PTR ss:[bp+6]  ; load ptr
	mov     WORD PTR es:[bx+14],ax  ; save ptr->intercepted
	sub     ax,ax
	mov     WORD PTR es:[bx+18],ax
	mov     WORD PTR es:[bx+22],ax
	mov     WORD PTR es:[bx+20],ax
	pop     si
	pop	bp
	ret	
_mid_misc_calc   ENDP
MIDPT_TEXT   ENDS
END
