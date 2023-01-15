;	Static Name Aliases
;
	TITLE   test.cpp
	.8087
INCLUDELIB      LLIBCE
INCLUDELIB	OLDNAMES.LIB
TEST_TEXT	SEGMENT  WORD PUBLIC 'CODE'
TEST_TEXT	ENDS
_DATA	SEGMENT  WORD PUBLIC 'DATA'
_DATA	ENDS
CONST	SEGMENT  WORD PUBLIC 'CONST'
CONST	ENDS
_BSS	SEGMENT  WORD PUBLIC 'BSS'
_BSS	ENDS
DGROUP	GROUP	CONST, _BSS, _DATA
	ASSUME DS: DGROUP, SS: DGROUP
EXTRN	__acrtused:ABS
EXTRN	_printf:FAR
_DATA      SEGMENT
$SG543	DB	'%d, %d, %d, %d',  0aH,  00H
$SG544	DB	'%d, %d, %d, %d',  0aH,  00H
$SG545	DB	'%d, %d, %d, %d',  0aH,  00H
$SG546	DB	'%d, %d, %d, %d',  0aH,  00H
$SG547	DB	'%d, %d, %d, %d',  0aH,  00H
$SG548	DB	'%d, %d, %d, %d',  0aH,  00H
$SG549	DB	'%d, %d, %d, %d',  0aH,  00H
$SG550	DB	'%d, %d, %d, %d',  0aH,  00H
_DATA      ENDS
TEST_TEXT      SEGMENT
	ASSUME	CS: TEST_TEXT
	PUBLIC	?compare_house_cusps@@ZAHHHG@Z	; compare_house_cusps
?compare_house_cusps@@ZAHHHG@Z	PROC FAR	; compare_house_cusps
; Line 4
	push	bp
	mov	bp,sp
;	first = 6
;	second = 8
;	mins = 10
	mov	cx,WORD PTR [bp+8]	;second
	mov	bx,WORD PTR [bp+6]	;first
; Line 5
	mov	ax,cx
	sub	ax,bx
	or	ax,ax
	jle	$I534
	mov	dx,WORD PTR [bp+10]	;mins
; Line 6
	cmp	dx,cx
	jae	$I538
	cmp	dx,bx
	jbe	$I538
; Line 7
$L551:
	mov	ax,1
	mov	sp,bp
	pop	bp
	ret	
	nop	
$I534:
	mov	dx,WORD PTR [bp+10]	;mins
; Line 12
	add	cx,21600	;5460H
	cmp	cx,dx
	jbe	$I537
	cmp	dx,bx
	ja	$L551
; Line 14
$I537:
; Line 15
	add	dx,21600	;5460H
	cmp	dx,cx
	jae	$I538
	cmp	dx,bx
	ja	$L551
; Line 17
$I538:
; Line 18
	xor	ax,ax
; Line 19
	mov	sp,bp
	pop	bp
	ret	
	nop	

?compare_house_cusps@@ZAHHHG@Z	ENDP
	PUBLIC	_main
_main	PROC FAR
; Line 25
	mov	ax,200	;00c8H
	push	ax
	mov	cx,500	;01f4H
	push	cx
	mov	dx,100	;0064H
	push	dx
	push	cs
	call	NEAR PTR ?compare_house_cusps@@ZAHHHG@Z	; compare_house_cusps
	add	sp,6
	push	ax
	mov	ax,200	;00c8H
	push	ax
	mov	cx,500	;01f4H
	push	cx
	mov	dx,100	;0064H
	push	dx
	mov	bx,OFFSET DGROUP:$SG543
	push	ds
	push	bx
	call	FAR PTR _printf
	add	sp,12	;000cH
; Line 27
	mov	ax,800	;0320H
	push	ax
	mov	ax,500	;01f4H
	push	ax
	mov	cx,100	;0064H
	push	cx
	push	cs
	call	NEAR PTR ?compare_house_cusps@@ZAHHHG@Z	; compare_house_cusps
	add	sp,6
	push	ax
	mov	ax,800	;0320H
	push	ax
	mov	ax,500	;01f4H
	push	ax
	mov	cx,100	;0064H
	push	cx
	mov	dx,OFFSET DGROUP:$SG544
	push	ds
	push	dx
	call	FAR PTR _printf
	add	sp,12	;000cH
; Line 29
	mov	ax,50	;0032H
	push	ax
	mov	cx,500	;01f4H
	push	cx
	mov	dx,100	;0064H
	push	dx
	push	cs
	call	NEAR PTR ?compare_house_cusps@@ZAHHHG@Z	; compare_house_cusps
	add	sp,6
	push	ax
	mov	ax,50	;0032H
	push	ax
	mov	cx,500	;01f4H
	push	cx
	mov	cx,100	;0064H
	push	cx
	mov	dx,OFFSET DGROUP:$SG545
	push	ds
	push	dx
	call	FAR PTR _printf
	add	sp,12	;000cH
; Line 31
	mov	ax,200	;00c8H
	push	ax
	mov	ax,100	;0064H
	push	ax
	mov	cx,18000	;4650H
	push	cx
	push	cs
	call	NEAR PTR ?compare_house_cusps@@ZAHHHG@Z	; compare_house_cusps
	add	sp,6
	push	ax
	mov	ax,200	;00c8H
	push	ax
	mov	ax,100	;0064H
	push	ax
	mov	cx,18000	;4650H
	push	cx
	mov	dx,OFFSET DGROUP:$SG546
	push	ds
	push	dx
	call	FAR PTR _printf
	add	sp,12	;000cH
; Line 33
	mov	ax,50	;0032H
	push	ax
	mov	ax,100	;0064H
	push	ax
	mov	cx,18000	;4650H
	push	cx
	push	cs
	call	NEAR PTR ?compare_house_cusps@@ZAHHHG@Z	; compare_house_cusps
	add	sp,6
	push	ax
	mov	ax,50	;0032H
	push	ax
	mov	ax,100	;0064H
	push	ax
	mov	cx,18000	;4650H
	push	cx
	mov	dx,OFFSET DGROUP:$SG547
	push	ds
	push	dx
	call	FAR PTR _printf
	add	sp,12	;000cH
; Line 35
	mov	ax,19200	;4b00H
	push	ax
	mov	cx,100	;0064H
	push	cx
	mov	dx,18000	;4650H
	push	dx
	push	cs
	call	NEAR PTR ?compare_house_cusps@@ZAHHHG@Z	; compare_house_cusps
	add	sp,6
	push	ax
	mov	ax,19200	;4b00H
	push	ax
	mov	cx,100	;0064H
	push	cx
	mov	dx,18000	;4650H
	push	dx
	mov	bx,OFFSET DGROUP:$SG548
	push	ds
	push	bx
	call	FAR PTR _printf
	add	sp,12	;000cH
; Line 37
	mov	ax,19200	;4b00H
	push	ax
	mov	ax,100	;0064H
	push	ax
	mov	cx,18000	;4650H
	push	cx
	push	cs
	call	NEAR PTR ?compare_house_cusps@@ZAHHHG@Z	; compare_house_cusps
	add	sp,6
	push	ax
	mov	ax,19200	;4b00H
	push	ax
	mov	ax,100	;0064H
	push	ax
	mov	cx,18000	;4650H
	push	cx
	mov	dx,OFFSET DGROUP:$SG549
	push	ds
	push	dx
	call	FAR PTR _printf
	add	sp,12	;000cH
; Line 39
	mov	ax,10800	;2a30H
	push	ax
	mov	ax,100	;0064H
	push	ax
	mov	cx,18000	;4650H
	push	cx
	push	cs
	call	NEAR PTR ?compare_house_cusps@@ZAHHHG@Z	; compare_house_cusps
	add	sp,6
	push	ax
	mov	ax,10800	;2a30H
	push	ax
	mov	ax,100	;0064H
	push	ax
	mov	ax,18000	;4650H
	push	ax
	mov	ax,OFFSET DGROUP:$SG550
	push	ds
	push	ax
	call	FAR PTR _printf
	add	sp,12	;000cH
; Line 40
	ret	
	nop	

_main	ENDP
TEST_TEXT	ENDS
END
