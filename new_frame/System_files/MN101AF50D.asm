;/**********************************************************************/
#ifdef DOC

;TITLE:  僗僞乕僩傾僢僾(MN101AF50DXW)

;TITDOC: 僗僞乕僩傾僢僾儖乕僠儞

;MODIFY: ZKL_William

;DATE:   2014/07/11

#endif
;/**********************************************************************/
#define STACKTOP 0x1000			;1kByte		/* @016YS[10/07/28]change 0x03ff -> 0x0400 */
;#define OSC2M
;#define OSC4M              ;      fosc =fpll=fs
#define OSC8M              ;      fosc =fpll=fs
;#define OSC10M
;#define OSC16M
;#define OSC20M
#ifdef OSC2M
							; internal osc 16MHz :1/2.0MHz * (8 + 2(HANDSHAKE)) * (24 + 1) = 125us	
#define	WAIT_TIME	200		
							; External Oscillation  2MHz : 1/2MHz * 7cycle *  8 = 175us
#endif 

#ifdef OSC4M

							
#define	WAIT_TIME	100		
							; External Oscillation  4MHz : 1/4MHz * 7cycle *  8 = 175us
#endif

#ifdef OSC8M

#define	WAIT_TIME	50		
							; External Oscillation  8MHz : 1/8MHz * 7cycle *  8 = 175us

#endif 

#ifdef OSC10M

#define	WAIT_TIME	40		
							; External Oscillation  10MHz : 1/10MHz * 7cycle *  8 = 175us

#endif 
#ifdef OSC16M

#define	WAIT_TIME	25		
							; External Oscillation  16MHz : 1/16MHz * 7cycle *  8 = 175us

#endif 

#ifdef OSC20M

#define	WAIT_TIME	20		
							; External Oscillation20MHz : 1/20MHz * 7cycle *  8 = 175us

#endif 
;CPU Control Register
#define	CPUM		0x3F00

;Clock Contrl Relations Register
#define	HANDSHAKE	0x3F06		;Internal ROM access method control register (Clock more than 10MHz is necessary)
#define OSCCNT		0x3F1A		;External high-speed oscillation control register
#define	RCCNT		0x3F1B		;Internal high-speed oscillation control register
#define	OSCSCNT 	0x3F1C		;External low-speed oscillation control register
;#define	RCSCNT 		0x3F1D		;Internal low-speed oscillation control register
				; 50D无内部低速振荡器
#define CHDRVSEL	0x3DF0		;External Oscillation Control Register

#define	PLLCNT		0x3F1F		;Clock multiplication circuit control register

#define	OSCLOCK 	0x3E56		;Oscillation Control Register Protect Register

;#define WDCTR2		0x3F05		;Watchdog timer 2 control register 50D与51A不同，没有看门狗2
#define WDCTR           0x3F02
#define LVIMD           0x3F2F
#if 0 ; sean				; 50D没有看门狗2以及保护寄存器
#define WD2MDSEL	0x3F4C
#define PRTKEY		0x3E50
#endif

;Definition
; sean, using external 8M OSC
#define	SC_SLECT	0		;0:External Oscillation	1:Internal Oscillation

#define	BP_SLECT	1		;0:ICE/FLASH	1:Debug Probe Using
#define testpll         1               ;   1:*2   /2   PLL
#define	WAIT_EXT	0x186A		; internal osc 20MHz :1/10MHz * (8 + 2(HANDSHAKE)) * (0x1869 + 1) = 10ms	/* @016YS[10/07/28]add */
							


_STEXT		SECTION	CODE,PUBLIC,0
_CONST		SECTION	CODE,PUBLIC,1
_GCONST		SECTION	CODE,PUBLIC,1
_DATA		SECTION	DATA,PUBLIC,1
_GDATA		SECTION	DATA,PUBLIC,1
_ROMDATA	SECTION	CODE,PUBLIC,1
_GROMDATA	SECTION	CODE,PUBLIC,1
_ROMDATAEND	SECTION	CODE,PUBLIC,1
_ENTRY		SECTION CODE,PUBLIC,0
_TEXT		SECTION	CODE,PUBLIC,0
_BSS		SECTION	DATA,PUBLIC,1
_GBSS		SECTION	DATA,PUBLIC,1
_BSSEND		SECTION	DATA,PUBLIC,1

	GLOBAL	_EnableIrq, _DisableIrq, _vRAM_NMI
	
_STEXT		SECTION			; Designate -T_STEXT=4000 by Linker
	da	A(Reset)	;0 reset vector address
	da	A(NoIRQ)	;1 interrupt vector ( Actual interrupt function name must be set. )	
	da	A(NoIRQ)	;2 interrupt vector ( Actual interrupt function name must be set. )
	da	A(NoIRQ)	;3 interrupt vector ( Actual interrupt function name must be set. )
	da	A(NoIRQ)	;4 interrupt vector ( Actual interrupt function name must be set. )
	da	A(NoIRQ)	;5 interrupt vector ( Actual interrupt function name must be set. )
	da	A(NoIRQ)	;6 interrupt vector ( Actual interrupt function name must be set. )
	da	A(NoIRQ)	;7 interrupt vector ( Actual interrupt function name must be set. )
	da	A(NoIRQ)	;8 interrupt vector ( Actual interrupt function name must be set. )
	da	A(_INT_TM0)	;9 interrupt vector ( A function name, "_Interrupt", is  set. )
	da	A(_INT_TM1)	;10 interrupt vector ( Actual interrupt function name must be set. )
	da	A(NoIRQ)	;11 interrupt vector ( Actual interrupt function name must be set. )
	da	A(_INT_TM3)	;12 interrupt vector ( Actual interrupt function name must be set. )
	da	A(NoIRQ)	;13 interrupt vector ( Actual interrupt function name must be set. )
	da	A(NoIRQ)	;14 interrupt vector ( Actual interrupt function name must be set. )
	da	A(NoIRQ)	;15 interrupt vector ( Actual interrupt function name must be set. )
	da	A(NoIRQ)	;16 interrupt vector ( Actual interrupt function name must be set. )
	da	A(NoIRQ)	;17 interrupt vector ( Actual interrupt function name must be set. )
	da	A(NoIRQ)	;18 interrupt vector ( Actual interrupt function name must be set. )
	da	A(NoIRQ)	;19 interrupt vector ( Actual interrupt function name must be set. )
	da	A(_INT_TX0)	;20 interrupt vector ( Actual interrupt function name must be set. )
	da	A(_INT_RX0)	;21 interrupt vector ( Actual interrupt function name must be set. )
	da	A(NoIRQ)	;22 interrupt vector ( Actual interrupt function name must be set. )
	da	A(NoIRQ)	;23 interrupt vector ( Actual interrupt function name must be set. )
	da	A(NoIRQ)	;24 interrupt vector ( Actual interrupt function name must be set. )
	da	A(NoIRQ)	;25 interrupt vector ( Actual interrupt function name must be set. )
	da	A(NoIRQ)	;26 interrupt vector ( Actual interrupt function name must be set. )
	da	A(NoIRQ)	;27 interrupt vector ( Actual interrupt function name must be set. )
	da	A(NoIRQ)	;28 interrupt vector ( Actual interrupt function name must be set. )
	da	A(NoIRQ)	;29 interrupt vector ( Actual interrupt function name must be set. )
	da	A(NoIRQ)	;30 interrupt vector ( Actual interrupt function name must be set. )
#if BP_SLECT	; Using Debug Probe 
	da	A(MonInterrupt)		; 31: MonInterrupt definition Do not Change!
#else
	da	A(NoIRQ)		; 31:
#endif


	org	0xc0			; _STEXT + 0xc0 (0x40c0)  Flash Option Area

	;dc	0x05			; Flash Option WD2 Operation When STOP Mode, low-speed oscillation possible stop page91
	dc	0x28			; Select PORT2 POR0  INPUT 5V
	dc	0x3f			; 
	org	0xd0			; _STEXT + 0xd0 (0x40d0) address


_TEXT		SECTION
NoIRQ:					; No Use Interrupt
	rti

	align 1


; Reset Start : Internal high-speed oscillation 20MHz, fs = 2.5MHz (CPUM default = 0x20 -> 8 divided)

Reset:

	movw	STACKTOP,A0		; Initialize of STACK Pointer
	movw	A0,SP

	;mov	0x30,D0			;
	mov	0x30,D0	
	mov	D0,PSW			; All Interrupt Disable, Level 3


; HANDSHAKE Circuit Setting

	mov	0x04,(HANDSHAKE)	; HANDSHAKE Circuit ON		Below Setting, Case of more than fs=10MHz, Register is necessary ON


; High-Speed Oscillation Setting	Attention : Case of select External high-speed oscillation, necessary 2 steps setting
;							-> External terminal switching and External oscillation select do not at the same time

#if SC_SLECT
	;Internal high-speed oscillation using
	mov	0x00,(OSCCNT)		; select of internal high-speed oscillation, fpll-div : stop, fpll-div : no divided
;	mov	0x21,(CPUM)		; NORMAL-IDLE mode setting -> no necessary select 20MHz, necessary 16MHz switching
	mov	0x82,(RCCNT)		; 16MHz select (16MHz select is "0x82")
					; This switching do below fs=10MHz

	;<<Attention>> switching 16MHz operation,
	;there is necessary wait times of 30us
	;please addition here

;	mov	0x20,(CPUM)		; NORMAL mode setting -> no necessary select 20MHz, necessary 16MHz switching


#else
	;External high-speed oscillation using
	mov	0x11,(OSCCNT)		; select of external high-speed oscillation, fpll-div : stop, fpll-div : no divided

	mov	0x00,(CHDRVSEL)		; External high-speed oscillation performance selection : Normal performance
					; Low Voltage operation, select "igh performance", 5V operation is OK in "Normal performance"
	; 选择外部寄存器就需要选择高速振荡器的模式。之后再等待稳定。
	
	;<<Attention>> Oscillation Stabilization Wait is necessary of external oscillation
	;For the oscillation stabilization wait cycle required for External high-speed/low-speed frequency,
	;it is recommended to consult the oscillator manufacturer for determining appropriate values
	;please addition here
	;mov	0x00,(CHDRVSEL) ;
	movw	0,DW0			; D0弶婜壔丄埲屻敪怳巕埨掕懸偪乮敪怳巕埶懚乯	/* B@016YS[10/07/28]add */
ext_wait:
	addw	1,DW0			; 2cycle
	cmpw	WAIT_EXT,DW0		; 2cycle
	bls	ext_wait		; 4cycle WAIT_EXT >= D0 偱 ext_wait傊

	bset	(OSCCNT)1		; switching on External high-speed oscillation

	; form here, fosc depend on external oscillation
	; case of external oscillation 10MHz, operation fs = 1.25MHz

	
	nop				;
	nop				;
	mov	0x81,(RCCNT)		; Internal high-speed oscillation control : disable
	mov	0x00,(HANDSHAKE)
					; When the RCON flag is set to stop the internal high-speed oscillation
					; after the operation clock is changed to the external high-speed oscillation
#endif

;watch dog timer2 setting
;	mov	0x88,(PRTKEY)		; enable WD2MDSEL writing  50D无看门狗2
;	mov	0x00,(WD2MDSEL)		; Watch dog 2 disable
;	mov	0xff,(PRTKEY)		; disable writing to register  sean change 00->44 enable WDCTR

; Low-Speed Oscillation Setting
	mov	0x00,(OSCSCNT)		; Operation clock selection : internal low-speed oscillation, P25/P26 function selection : General port
;	//mov	0x81,(RCSCNT)		; Internal low-speed oscillation control : Stop

	;internal low-speed oscillation using or external low-speed oscillation using is necessary setting here


; PLL Setting
#if SC_SLECT
        mov	0x00,(PLLCNT)                ;ling 2012.11.6
#if 0
	;Internal high-speed oscillation using
	mov	0x10,(PLLCNT)		; PLL use 2 multiplication select (16MHz / 2 divided) * 2 multiplication = 16MHz

	bset	(PLLCNT)0		; PLL operation start
	mov 0xA6,D0
LOOP
	add  -1,d0              ;Loop 100us wait (10MHz)
	bne  LOOP               ;
	;At microcontroller reset release, LSI starts with the internal ROM access method = HANDSHAKE
	bset (PLLCNT)1          ;PLL clock operation
#endif					; 
#else
	;External high-speed oscillation using
#if testpll
        ;mov	0x00,(PLLCNT)		; PLL use 4 multiplication select 20171013 修改
        mov	0x10,(PLLCNT)     ; PLL use 2 multiplication select 7.5MHz to 10MHz  20171013 修改

	bset	(PLLCNT)0		; PLL operation start
#endif
	mov	0,D0			; D0 register initialize
pll_wait:
	add	1,D0			; 2cycle
	cmp	WAIT_TIME,D0		; 2cycle
	bls	pll_wait		; 3cycle WAIT_TIME >= D0 -> pll_wait
#if testpll
	bset	(PLLCNT)1		; PLL clock operation
#endif					; PLL use -> fosc=8MHz (external oscillation = 8MHz)
#endif


; fs setting
;	mov	0x00,(CPUM)		; fs = 16MHz / 2 divided = 8MHz
#if    SC_SLECT                         ;ling 2012 11 6
        mov	0x30,(CPUM)             ;16M--->4M
#else
#if testpll
	;mov	0x00,(CPUM)             ;  8M-->4M  2012.11.7
	mov	0x10,(CPUM)		; fs = 16MHz/4	@mk004    20171013 修改
#else	
        mov	0x10,(CPUM)		; fs = 16MHz/4	@mk004
#endif
#endif
	; fs = 16MHz (or later)


; fpll-div setting
#if     SC_SLECT
       	mov	(OSCCNT),D0
	or	0x80,D0			; 4 分频   0x40
	mov	D0,(OSCCNT)		; oscillation dividing selection of fpll-div
	bclr	(OSCCNT)4		; fpll-div enable
#else
	mov	(OSCCNT),D0
#if   testpll
	
	;or      0x20,D0                 ;  4M-->2M  2012.11.7   2014022201
	or      0x00,D0                 ;  0 分频 no divide  20171013 修改
#else
        or	0x40,D0			; 4 分频   0x40
#endif
	mov	D0,(OSCCNT)		; oscillation dividing selection of fpll-div

	bclr	(OSCCNT)4		; fpll-div enable
#endif
	mov	0x01,(OSCLOCK)		; Oscillation Control Register Protect Register : Writing disable
;LVI check 

;      mov      0x71,D0
;      mov      D0,(LVIMD)               ;要等待2ms 在进行中断处理，下面的清RAM操作大概是2ms
;lviloop:
;      mov      (LVIMD),D0
;      and      0x02,D0
;      cmp      0,D0
;      beq      lviloop
      
      
; All RAM area clear zero
	movw	0x0000,A0		; _BSS area beginning address -> A0
	sub	D0,D0			; D0 = 0
clearall:                               ;4M 大概清Ram时间为2ms
	mov	D0,(A0)
	addw	0x1,A0
	cmpw	STACKTOP-1,A0		; RAM area last address ?
	blt	clearall			; _BSSEND > A0 -> clear1

					; static variable with default valule initialize
; RAM area initialize
					; static variable initialize
	movw	0x0000,A0		; _BSS area beginning address -> A0
	sub	D0,D0			; D0 = 0
clear1:
	mov	D0,(A0)
	addw	0x1,A0
	cmpw	_BSSEND,A0		; RAM area last address ?
	blt	clear1			; _BSSEND > A0 -> clear1

					; static variable with default valule initialize
raminit:
	movw	_ROMDATA,A0
	movw	_DATA,A1
	cmpw	_GROMDATA,A0
	beq	next1
init1:					; ROMDATA(A0) -> DATA(A1)
	mov	(A0),D0
	mov	D0,(A1)
	addw	0x1,A0
	addw	0x1,A1
	cmpw	_GROMDATA,A0
	bne	init1

next1:
	movw	_GROMDATA,A0
	movw	_GDATA,A1
	cmpw	_ROMDATAEND,A0
	beq	next2
init2:					; GROMDATA(A0) -> GDATA(A1)
	mov	(A0),D0
	mov	D0,(A1)
	addw	0x1,A0
	addw	0x1,A1
	cmpw	_ROMDATAEND,A0
	bne	init2

next2:					; Register initialize
	subw	DW0,DW0
	movw	DW0,DW1
	movw	DW0,A0
	movw	DW0,A1
					; call main function
_loop1:
	jsr	_main

	bra	_loop1



; Interrupt control function



_EnableIrq:				;all interrupt enable function
	or	0x40,PSW
	rts

_DisableIrq:				;all interrupt disable function
	and	0xBF,PSW
	rts


#if BP_SLECT				; "0" when monitor is not used (for Debug Probe)

;;;;; From here to monitor program. Please do not change.
;;;;; Please do not set the breakpoint.

#define DEBUG_CMDFLG	0		; CMDFLG clear
#define OCDMONVER       0x0100
#define OCDRESERVE1     0x55AA
#define OCDRESERVE2     0x33CC
#define MONCT           0x3F0C
#define MONDT           0x3F0D
#define MONCTxx         0x3FFE

ChangeMonitorModeFlag   equ  0x20        ;Monitor Mode ON Flag
ChangeDataFlag          equ  0x40        ;
ChangeCommandFlag       equ  0x80        ;
ClearFlag               equ  0x02        ;CommandFlag and DataFlag  ClearFlag
CheckMonitorModeFlag    equ  0x40        ;Monitor Mode Check Flag
CheckCommandFlag        equ  0x20        ;Monitor and Checkcommand Flag
CheckDataFlag           equ  0x10        ;Monitor and Cheack Data Flag
CheckESCBreak           equ  0x02        ;ESC Break Flag  
CheckRomEvent           equ  0x04        ;ROM Event Flag
CheckRamEvent           equ  0x08        ;RAM Event Flag

	GLOBAL   MonInterrupt

_STEXT2      SECTION CODE,PUBLIC,0
_STEXT2      SECTION
	align 1

OCDMonitorReserve:                       ; Monitor-code
    DW  OCDRESERVE1                      ; Monitor-code
    DW  OCDRESERVE2                      ; Monitor-code
    DW  OCDMONVER                        ; Monitor-version
    DW  OCDMonitorEnd - MonInterrupt     ; Monitor-code size

	align 1
MonInterrupt:                            ; DW0,DW1,A0,A1 to SP
    addw    -8,SP                        ; Monitor-code
    movw    dw0,(6,SP)                   ; Monitor-code
    movw    dw1,(4,SP)                   ; Monitor-code
    movw    a0,(2,SP)                    ; Monitor-code
    movw    a1,(0,SP)                    ; Monitor-code

OCDSetMonitorModeFlag:                   ; SET MONITOR
    mov     (MONCT),d0                   ; Monitor-code
    btst    0x40,d0                      ; Monitor-code
    bne     OCDWaitDataFlag              ; Monitor-code
    mov     ChangeMonitorModeFlag,d0     ; Monitor-code
    mov     d0,(MONCT)                   ; Monitor-code
    
OCDWaitDataFlag:                         ; CHECK DataFlag
#if DEBUG_CMDFLG
    mov     0,(MONCTxx)
#endif
    mov     (MONCT),d0                   ; Monitor-code
    btst    CheckDataFlag,d0             ; Monitor-code
    beq     OCDWaitDataFlag              ; Monitor-code

OCDSetSPLow:                             ; SET SP_L
    movw    SP,a0                        ; Monitor-code
    movw    a0,dw0                       ; Monitor-code
    mov     d0,(MONDT)                   ; Monitor-code

OCDClearDataFlag:                        ; CLR DATA and COMMAND
    mov     ClearFlag,d0                 ; Monitor-code
    mov     d0,(MONCT)                   ; Monitor-code

OCDWaitDataFlag2:                        ; CHECK DataFlag
#if DEBUG_CMDFLG
    mov     0,(MONCTxx)
#endif
    mov     (MONCT),d0                   ; Monitor-code
    btst    CheckDataFlag,d0             ; Monitor-code
    beq     OCDWaitDataFlag2             ; Monitor-code

OCDSetSPHi:                              ; SET SP_H
    mov     d1,(MONDT)                   ; Monitor-code

OCDClearDataAndCommandFlag:              ; CLR DATA and COMMAND
    mov ClearFlag,d0                     ; Monitor-code
    mov d0,(MONCT)                       ; Monitor-code

OCDCommandLoop:                          ; LOOP MON
#if DEBUG_CMDFLG
    mov     0,(MONCTxx)
#endif
    mov     (MONCT),d0                   ; Monitor-code
    btst    CheckMonitorModeFlag,d0      ; Monitor-code
    beq     OCDGoProgram                 ; Monitor-code
    btst    CheckCommandFlag,d0          ; Monitor-code
    beq     OCDCommandLoop               ; Monitor-code

    nop                                  ; for debug

OCDChangeSP:                             ; CHANGE SP
    movw    (6,SP),a0                    ; Monitor-code
    movw    a0,sp                        ; Monitor-code
    bra     OCDClearDataAndCommandFlag   ; Monitor-code
                                         ; Monitor-code
OCDGoProgram:
    movw    (6,SP),dw0                   ; Monitor-code
    movw    (4,SP),dw1                   ; Monitor-code
    movw    (2,SP),a0                    ; Monitor-code
    movw    (0,SP),a1                    ; Monitor-code
    addw    8,SP                         ; Monitor-code
    rti                                  ; Monitor-code
	align 1
OCDMonitorEnd:

#endif


	END
