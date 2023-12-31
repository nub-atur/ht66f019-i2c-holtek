; Generated by holtek-gcc v3.19, Wed Sep 06 23:59:07 2023
; 
; Configuration:
;       without long instruction
;       Single ROM, Multi-RAM
;       bits_per_rom_unit:16
;       with mp1
;       with tbhp, address(0x9)
;          Use tabrd-const
;       
;       
;       
; use 'tabrdc' instead of 'tabrd'
;       

#pragma translator "holtek-gcc 4.6.4" "3.19" "build 20130711"
; Rebuild 718

ir equ [2]
mp equ [3]
sbp equ [1]
acc equ [5]
bp equ [4]
tblp equ [7]
tbhp equ [9]
status equ [10]
c equ [10].0
ac equ [10].1
z equ [10].2
ov equ [10].3
intc equ [11]

extern ra:byte
extern rb:byte
extern rc:byte
extern rd:byte
extern re:byte
extern rf:byte
extern rg:byte
extern rh:byte
extern _Crom2Prom:near
extern _Crom2PromNext:near

RAMBANK 0 @HCCINIT, @HCCINIT0

RAMBANK 0 @BITDATASEC, @BITDATASEC1
@HCCINIT	.section 'data'
@HCCINIT0	.section 'data'
@BITDATASEC	 .section 'data'
@BITDATASEC1	 .section 'data'

#pragma debug scope 1 1
	extern __DELAY3:near
	extern __DELAYX3:near
	extern __DELAYX6:near
	extern __DELAYY5:near
	extern __DELAYY3:near
	extern _builtin_holtek_delay_2:byte
___wdtc equ [26]
public _main
#pragma debug scope 2 1
#line 11 "C:\Users\mediv\Nhap\demo\demo.c"
IFDEF WITH_DEFAULT_STARTUP
extern _main_initial0:near
extern _main_startup:near
ENDIF

ROMBANK 0 @start
@start .section com_l 'code'
_main_startup1:
@start .section com_e 'code'
	jmp _main

_main .section 'code'
_main proc
    local _main_2 db 37 dup(?)
#pragma debug array 42 8 14 2
#pragma debug variable 42 2 _main_2+17 "z"
#pragma debug array 43 7 17 2
#pragma debug variable 43 2 _main_2+0 "text"
#pragma debug array 44 7 6 2
#pragma debug variable 44 2 _main_2+31 "text2"
#line 14 "C:\Users\mediv\Nhap\demo\demo.c"
	mov a,84
	mov _main_2[0],a
	mov a,97
	mov _main_2[1],a
	mov a,105
	mov _main_2[2],a
	mov a,119
	mov _main_2[3],a
	mov a,97
	mov _main_2[4],a
	mov a,110
	mov _main_2[5],a
	mov a,67
	mov _main_2[6],a
	mov a,104
	mov _main_2[7],a
	mov a,105
	mov _main_2[8],a
	mov a,112
	mov _main_2[9],a
	mov a,32
	mov _main_2[10],a
	mov a,103
	mov _main_2[11],a
	mov a,103
	mov _main_2[12],a
	mov a,32
	mov _main_2[13],a
	mov a,101
	mov _main_2[14],a
	mov a,122
	mov _main_2[15],a
	clr _main_2[16]
#line 15 "C:\Users\mediv\Nhap\demo\demo.c"
	mov a,32
	mov _main_2[31],a
	mov a,116
	mov _main_2[32],a
	mov a,32
	mov _main_2[33],a
	mov a,61
	mov _main_2[34],a
	mov a,32
	mov _main_2[35],a
	clr _main_2[36]
#line 18 "C:\Users\mediv\Nhap\demo\demo.c"
	mov a,175
	mov [26],a
#line 19 "C:\Users\mediv\Nhap\demo\demo.c"
	call _I2C_Master_Init
#line 26 "C:\Users\mediv\Nhap\demo\demo.c"
	call _lcdinit
#line 27 "C:\Users\mediv\Nhap\demo\demo.c"
	call _mpu_init
_L2:
#line 31 "C:\Users\mediv\Nhap\demo\demo.c"
	mov a,-56
	mov __delay_ms_2[0],a
	clr __delay_ms_2[1]
	clr __delay_ms_2[2]
	clr __delay_ms_2[3]
	call __delay_ms
#line 32 "C:\Users\mediv\Nhap\demo\demo.c"
	clr _lcdcursor_2[2]
	clr _lcdcursor_2[3]
	mov a,1
	mov _lcdcursor_2[0],a
	clr _lcdcursor_2[1]
	call _lcdcursor
#line 33 "C:\Users\mediv\Nhap\demo\demo.c"
	mov a,low offset _main_2
	mov ra,a
	mov a,high offset _main_2
	mov rb,a
	mov a,31
	add a,ra
	mov _lcdprint_2[0],a
	mov a,0
	adc a,rb
	mov _lcdprint_2[1],a
	call _lcdprint
#line 34 "C:\Users\mediv\Nhap\demo\demo.c"
	mov a,13
	mov _I2C_Read_2[2],a
	mov a,low offset _main_2
	mov ra,a
	mov a,high offset _main_2
	mov rb,a
	mov a,17
	add a,ra
	mov _I2C_Read_2[0],a
	mov a,0
	adc a,rb
	mov _I2C_Read_2[1],a
	call _I2C_Read
#line 37 "C:\Users\mediv\Nhap\demo\demo.c"
	mov a,-48
	mov __delay_ms_2[0],a
	mov a,7
	mov __delay_ms_2[1],a
	clr __delay_ms_2[2]
	clr __delay_ms_2[3]
	call __delay_ms
#line 42 "C:\Users\mediv\Nhap\demo\demo.c"
	clr _lcdcursor_2[2]
	clr _lcdcursor_2[3]
	clr _lcdcursor_2[0]
	clr _lcdcursor_2[1]
	call _lcdcursor
#line 43 "C:\Users\mediv\Nhap\demo\demo.c"
	mov a,low offset _main_2
	mov _lcdprint_2[0],a
	mov a,high offset _main_2
	mov _lcdprint_2[1],a
	call _lcdprint
#line 44 "C:\Users\mediv\Nhap\demo\demo.c"
	mov a,-24
	mov __delay_ms_2[0],a
	mov a,3
	mov __delay_ms_2[1],a
	clr __delay_ms_2[2]
	clr __delay_ms_2[3]
	call __delay_ms
	jmp _L2
	jmp $
_main endp

@dummy proc
	call _main
@dummy endp

#line 44 "C:\Users\mediv\Nhap\demo\demo.c"
#pragma debug scope 1 1
#pragma debug struct_begin 45 "__wdtc_bits"
#pragma debug field 21 8 0 1 "__ws0" ;0,1
#pragma debug field 21 8 0 1 "__ws1" ;1,1
#pragma debug field 21 8 0 1 "__ws2" ;2,1
#pragma debug field 21 8 0 1 "__we0" ;3,1
#pragma debug field 21 8 0 1 "__we1" ;4,1
#pragma debug field 21 8 0 1 "__we2" ;5,1
#pragma debug field 21 8 0 1 "__we3" ;6,1
#pragma debug field 21 8 0 1 "__we4" ;7,1
#pragma debug struct_end
#pragma debug union_begin 46 ""
#pragma debug field 2 45 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 46 1 ___wdtc "__wdtc" 1
#line 11 "C:\Users\mediv\Nhap\demo\demo.c"
@code .section at 0 'code'
	jmp _main_startup1

extern _I2C_Master_Init:near
extern _lcdinit:near
extern _mpu_init:near
extern __delay_ms_2:byte
extern __delay_ms:near
extern _lcdcursor_2:byte
extern _lcdcursor:near
extern _lcdprint_2:byte
extern _lcdprint:near
extern _I2C_Read_2:byte
extern _I2C_Read:near

; 
; Generated by holtek-gcc v3.19, Wed Sep 06 23:59:07 2023
; Rebuild 718
; end of file
