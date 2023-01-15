	TITLE   house.c
	NAME    house
HOUSE_TEXT	SEGMENT  WORD PUBLIC 'CODE'
HOUSE_TEXT	ENDS
_DATA	SEGMENT  WORD PUBLIC 'DATA'
_DATA	ENDS
CONST	SEGMENT  WORD PUBLIC 'CONST'
CONST	ENDS
_BSS	SEGMENT  WORD PUBLIC 'BSS'
_BSS	ENDS
DGROUP	GROUP	CONST, _BSS, _DATA
	ASSUME  CS: HOUSE_TEXT, DS: DGROUP, SS: NOTHING
EXTRN   __acrtused:ABS
EXTRN   $MODE:WORD
_BSS      SEGMENT
COMM NEAR	_house_cusps:	BYTE:	 26
COMM NEAR	_alt_cusps:	BYTE:	 26
_BSS      ENDS
HOUSE_TEXT      SEGMENT
	ASSUME	CS: HOUSE_TEXT
; Line 15

	; int adjust_mins(int mins )
	; edited for speed by cjn 9/9/1989
	PUBLIC  _adjust_mins
_adjust_mins	PROC FAR
	push	bp
	mov	bp,sp
	sub	sp,2
;       mins = 6
; Line 18
	mov     ax,WORD PTR ss:[bp+6]   ;load mins
	cmp     ax,0                    ;see if it's less than 0
	jge     $I528                   ;if plus jmp
; Line 19

	add     ax,21600                ; neg make pos
	mov     sp,bp                   ; exit
	pop     bp
	ret
	nop

$I528:
; Line 21
	cmp     ax, 21600               ; see if it's too big
	jb      $I531                   ; no, return the value
; Line 23
	sub     ax,21600                ; too big sub, bring in range
$I531:  mov     sp,bp                   ; exit
	pop	bp
	ret	
	nop	

_adjust_mins	ENDP


	; int flip_mins( int mins, char dir )
	; edited for speed by cjn 9/9/1989
; Line 31
	PUBLIC	_flip_mins
_flip_mins	PROC FAR
	push	bp
	mov	bp,sp
	sub	sp,2
;       mins = 6
;	dir = 8

; Line 32
	mov     ax,WORD PTR ss:[bp+6]    ; load mins
; Line 34
	cmp     BYTE PTR ss:[bp+8],'S'   ; test direction (dir == 'S')
	je      $I537                    ; not south jump
	cmp     BYTE PTR ss:[bp+8],'s'   ; test direction (dir == 's')
	jne     $I538                    ; not south jump
$I537:
; Line 35
	add     ax,10800                ; add 180 deg
; Line 36
$I537A:
	cmp     ax,21600                ; see if it's too big
	jb      $I538                   ; ok, exit
; Line 37
	sub     ax,21600                ; too big sub, bring in range
; Line 38
$I538:
; Line 39
	mov     sp,bp                   ; exit
	pop     bp
	ret

_flip_mins	ENDP

	; was c func compare_house_cusps( int first, int second, int mins )
	; edited by cjn 10/10/89 for speed making it assembly call with
	; registers only
	; Called With: first = ax      USES: bx, di
	;              second = cx
	;              mins = dx
	; returns return value in ax

PUBLIC  compare_house_cusps2  ; compare_house_cusps2
compare_house_cusps2  PROC NEAR        ; compare_house_cusps
; Line 4
	push    bp
	mov     bp,sp
	mov     cx,WORD PTR [bp+8]      ;second
	mov     ax,WORD PTR [bp+6]      ;first
; Line 5
	mov     ax,cx
	sub     cx,ax
	or      ax,ax
	jle     $I534
	; Line 6
	cmp     dx,cx
	jae     $I538
	cmp     dx,ax
	jbe     $I538
; Line 7
$L551:
	mov     ax,1
	mov     sp,bp
	pop     bp
	ret
	nop
$I534:
; Line 12
	add     cx,21600        ;5460H
	cmp     cx,dx
	jbe     $I537
	cmp     dx,ax
	ja      $L551
; Line 14
$I537:
; Line 15
	add     dx,21600        ;5460H
	cmp     dx,cx
	jae     $I538
	cmp     dx,ax
	ja      $L551
; Line 17
$I538:
; Line 18
	xor     ax,ax
; Line 19
	mov     sp,bp
	pop     bp
	ret
	nop
compare_house_cusps2 ENDP

; Line 47
	; was c func compare_house_cusps( int first, int second, int mins )
	; edited by cjn 10/10/89 for speed making it assembly call with
	; registers only
	; Called With: first = ax      USES: bx, di
	;              second = cx
	;              mins = dx
	; returns return value in ax

compare_house_cusps    PROC NEAR
; Line 48
	push    bx
	push    di
	cmp     cx,ax           ; check first against second
	jle     $I543           ; add 360d to it if nec
; Line 49
	add     ax,120          ; add 2 degrees for margin to first
; Line 50
	add     cx,120          ; add 2 degrees for margin to second
; Line 51
	mov     di,dx
	add     di,120          ; add 2 degrees for margin to mins
; Line 52
	mov     bx,cx           ; to temp reg
	sub     bx,60           ; sub 1 degree
	cmp     bx,di           ; test against mins
	jae	$I544
; Line 53
$L20003:
	sub     ax,ax           ; return 0
	pop     di
	pop     bx
	ret
$I544:
; Line 54
	mov     bx,ax           ; move first to temp
	sub     bx,60           ; sub 1 degree
	cmp     bx,di           ; test against mins
	jae	$L20003
; Line 57
$L20005:
	mov     ax,1            ; return 1 or true
	pop     di
	pop     bx
	ret
$I543:
	add     cx,21600        ; add 360 degrees to second
; Line 60
	mov     bx,ax           ; move first to temp
	sub     bx,60           ; sub 1 degree
	cmp     bx,dx           ; test mins against first minus 1 degree
	jbe	$L20005
; Line 62
	mov     bx,cx           ; move second to temp
	sub     bx,60           ; sub 1 degree
	mov     di,dx           ; move mins to temp2
	add     di,21600        ; add 360 degrees
	cmp     bx,di           ; test against temp (second-1 degree)
	jb      $L20003         ; return 0
	jmp     SHORT $L20005   ; return 1
	nop	
compare_house_cusps    ENDP



; Line 73
	; int house_number( int mins )
	; edited for speed by cjn 9/10/1989
	PUBLIC  _house_number
_house_number	PROC FAR
	push	bp
	mov	bp,sp
	sub	sp,6
	push	di
	push	si
;	mins = 6
;	i = -2
; Line 76
	mov ax,WORD PTR $MODE
	and ax, 4000h
	push ax
	mov dx,WORD PTR ss:[bp+6]            ; load mins for call
	mov cx,WORD PTR _house_cusps+2       ; load next two args
	mov ax,WORD PTR _house_cusps
	jnz     $I554
	call    NEAR PTR compare_house_cusps
	or      ax,ax                         ; test for zero
	je	$I555
; Line 77
$I553
	pop     ax
	mov     ax,12                         ; no return 12
	pop     si
	pop	di
	mov	sp,bp
	pop	bp
	ret	
	nop	
$I554:
	call    NEAR PTR compare_house_cusps2
	or      ax,ax                         ; test for zero
	jne     $I553
$I555:
	mov     si,1                             ; yes contine do loop
	mov     di,OFFSET DGROUP:_house_cusps+4  ; load loop data
	mov     bx,OFFSET DGROUP:_house_cusps+2  ; "     "    "
$L20000:
; Line 79
	mov cx,[di]                             ; Load For Called Routine
	pop ax
	and ax, 4000h
	push ax
	mov ax,[bx]                             ;   "   "    "       "
	jnz     $I558
	call    NEAR PTR compare_house_cusps
	or      ax,ax                            ; test for zero
	je      $I559                            ; yes continue looping
; Line 80
	mov     ax,si                            ; no return si
	jmp	SHORT $L20007

$I558:
	call    NEAR PTR compare_house_cusps2
	or      ax,ax                            ; test for zero
	je      $I559                            ; yes continue looping
; Line 80
	mov     ax,si                            ; no return si
	jmp     SHORT $L20007

$I559:
	add     di,2                             ; loop increment
	add     bx,2
	inc	si
	cmp     si,11                            ; gone too far?
	jle     $L20000                          ; no continue
	xor     ax,ax                            ; yes return 0
$L20007:
; Line 82
	pop     ax
	pop     si                               ; return
	pop	di
	mov	sp,bp
	pop	bp
	ret	

_house_number	ENDP



; Line 88
	; int house_cusp_intercept( int mins, int house )
	; edited for speed by cjn 9/9/1989  (local var to reg)
	PUBLIC  _house_cusp_intercept
_house_cusp_intercept	PROC FAR
	push	bp
	mov	bp,sp
	sub	sp,2
;	mins = 6
;	house = 8
; Line 91
	mov     bx,WORD PTR ss:[bp+8]         ; load house number
	shl     bx,1                          ; to a byte offset
	mov     ax,WORD PTR _house_cusps[bx]  ; load house data
	sub     ax,WORD PTR ss:[bp+6]         ; subtract mins
	cwd                                   ; abs function
	xor	ax,dx
	sub	ax,dx
	mov     bx,ax
; Line 92
	cmp     ax,80                         ; test upper limit
	jg      $I564                         ; no continue
; Line 93
$L20008:
	mov     ax,1                          ; yes return 1
	mov     sp,bp
	pop	bp
	ret	
$I564:
; Line 94
	cmp     bx, 21520                     ; test opposite end
	jge     $L20008                       ; no continue
; Line 97
	xor     ax,ax                         ; zero ax (return 0)
$I565:  mov     sp,bp
	pop	bp
	ret	
	nop	
_house_cusp_intercept   ENDP

HOUSE_TEXT	ENDS
END
