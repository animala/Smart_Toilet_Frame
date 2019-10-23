
#ifndef MN101AF50D
#define MN101AF50D
#include "TYPESTRUCT.h"


/**********************************************/
/* MACRO DEFINE */
#define __UMEM8(addr)  (*((volatile unsigned char  *)addr))
#define __UMEM16(addr) (*((volatile unsigned short *)addr))
#define __UMEM32(addr) (*((volatile unsigned long  *)addr))


/* SPECIAL REGISTER DEFINE */

#define CHDRVSEL	__UMEM8(0x3DF0)
//@@0724 ->
//	*		#define PWMMD		__UMEM16(0x3E00)
//	*		#define PWMMDL		__UMEM8(0x3E00)
//	*		#define PWMMDH		__UMEM8(0x3E01)
//	*		#define PWMSEL		__UMEM16(0x3E02)
//	*		#define PWMSELL		__UMEM8(0x3E02)
//	*		#define PWMSELH		__UMEM8(0x3E03)
//	*		#define PWMSET		__UMEM16(0x3E04)
//	*		#define PWMSETL		__UMEM8(0x3E04)
//	*		#define PWMSETH		__UMEM8(0x3E05)
//	*		#define TCMPA		__UMEM16(0x3E06)
//	*		#define TCMPAL		__UMEM8(0x3E06)
//	*		#define TCMPAH		__UMEM8(0x3E07)
//	*		#define TCMPB		__UMEM16(0x3E08)
//	*		#define TCMPBL		__UMEM8(0x3E08)
//	*		#define TCMPBH		__UMEM8(0x3E09)
//	*		#define TCMPC		__UMEM16(0x3E0A)
//	*		#define TCMPCL		__UMEM8(0x3E0A)
//	*		#define TCMPCH		__UMEM8(0x3E0B)
//	*		#define OUTMD		__UMEM8(0x3E0C)
//	*		#define DTMSET		__UMEM8(0x3E0D)
//	*		#define DTMSET1		__UMEM8(0x3E0E)
//	*		#define PWMBC		__UMEM16(0x3E10)
//	*		#define PWMBCL		__UMEM8(0x3E10)
//	*		#define PWMBCH		__UMEM8(0x3E11)
//	*		#define BCSTR		__UMEM8(0x3E12)
//	*		#define PWMOFFL		__UMEM8(0x3E13)
//	*		#define PWMOFFH		__UMEM8(0x3E14)
//	*		#define IRQCULL		__UMEM8(0x3E15)
//	*		#define PWMTMCNT	__UMEM8(0x3E16)
//	*		#define RELCTR		__UMEM8(0x3E17)
//	*		#define PWMODR		__UMEM8(0x3E18)
//	*		#define RELSTAT		__UMEM8(0x3E19)
//	*		#define PWMCMP1		__UMEM8(0x3E1A)
//	*		#define PWMCMP2		__UMEM8(0x3E1B)
//	*		#define PRTKEY		__UMEM8(0x3E50)
//	*		#define CKTRMD		__UMEM8(0x3E51)
//	*		#define CKMONEN		__UMEM8(0x3E52)
//	*		#define CKMONSETU	__UMEM8(0x3E53)
//	*		#define CKMONSETL	__UMEM8(0x3E54)
//	*		#define CKMONSTAT	__UMEM8(0x3E55)
//@@0724 <-

#define LCDMD1		__UMEM8(0x3E40)
#define LCDMD2		__UMEM8(0x3E41)
#define LCDMD3		__UMEM8(0x3E42)





#define OSCLOCK		__UMEM8(0x3E56)

#define P0OUT		__UMEM8(0x3E70)
#define P2OUT		__UMEM8(0x3E72)
//	*		#define P3OUT		__UMEM8(0x3E73)	//@@0724
//	*		#define P4OUT		__UMEM8(0x3E74)	//@@0724
#define P5OUT		__UMEM8(0x3E75)
#define P6OUT		__UMEM8(0x3E76)
#define P7OUT		__UMEM8(0x3E77)
#define P8OUT		__UMEM8(0x3E78)
#define P9OUT		__UMEM8(0x3E79)
#define PAOUT		__UMEM8(0x3E7A)
#define P0IN		__UMEM8(0x3E80)
#define P2IN		__UMEM8(0x3E82)
//	*		#define P3IN		__UMEM8(0x3E83)	//@@0724
//	*		#define P4IN		__UMEM8(0x3E84)	//@@0724
#define P5IN		__UMEM8(0x3E85)
#define P6IN		__UMEM8(0x3E86)
#define P7IN		__UMEM8(0x3E87)
#define P8IN		__UMEM8(0x3E88)
#define P9IN		__UMEM8(0x3E89)
#define PAIN		__UMEM8(0x3E8A)
#define P0DIR		__UMEM8(0x3E90)
#define P2DIR		__UMEM8(0x3E92)
//	*		#define P3DIR		__UMEM8(0x3E93)	//@@0724
//	*		#define P4DIR		__UMEM8(0x3E94)	//@@0724
#define P5DIR		__UMEM8(0x3E95)
#define P6DIR		__UMEM8(0x3E96)
#define P7DIR		__UMEM8(0x3E97)
#define P8DIR		__UMEM8(0x3E98)
#define P9DIR		__UMEM8(0x3E99)
#define PADIR		__UMEM8(0x3E9A)
#define P0PLUD		__UMEM8(0x3EA0)
#define P2PLU		__UMEM8(0x3EA2)
//	*		#define P3PLUD		__UMEM8(0x3EA3)	//@@0724
#define P6PLU		__UMEM8(0x3EA6)
//	*		#define P7PLU		__UMEM8(0x3EA7)	//@@0724
//	*		#define P8PLU		__UMEM8(0x3EA8)	//@@0724
//	*		#define P4PLUD		__UMEM8(0x3EA4)	//@@0724
#define P5PLUD		__UMEM8(0x3EA5)
//	*		#define P6PLUD		__UMEM8(0x3EA6)	//@@0724
#define P7PLUD		__UMEM8(0x3EA7)
#define P8PLUD		__UMEM8(0x3EA8)
#define P9PLUD		__UMEM8(0x3EA9)
#define PAPLU		__UMEM8(0x3EAA)
//	*		#define PBPLUD		__UMEM8(0x3EAB)	//@@0724
#define SELUD		__UMEM8(0x3EAF)

#define P0OMD1		__UMEM8(0x3EB0)
//	*		#define P3OMD		__UMEM8(0x3EB3)	//@@0724
//	*		#define P4OMD		__UMEM8(0x3EB4)	//@@0724
#define P5OMD		__UMEM8(0x3EB5)
#define P6OMD		__UMEM8(0x3EB6)
//	*		#define P8OMD		__UMEM8(0x3EB8)	//@@0724
//	*		#define P9OMD		__UMEM8(0x3EB9)	//@@0724
#define PAOMD		__UMEM8(0x3EBA)
#define SELUD2         __UMEM8(0x3EBF)

#define P0OMD2		__UMEM8(0x3EC0)
//	*		#define P3IMD		__UMEM8(0x3EC3)	//@@0724
//	*		#define P4IMD		__UMEM8(0x3EC4)	//@@0724
#define P5IMD		__UMEM8(0x3EC5)
#define P9IMD		__UMEM8(0x3EC9)
#define PAIMD		__UMEM8(0x3ECA)
//	*		#define PBIMD		__UMEM8(0x3ECB)	//@@0724

//	*		#define P0LEDCNT	__UMEM8(0x3EE0)	//@@0724
//	*		#define P0LEDSEL	__UMEM8(0x3EE1)	//@@0724

#define P0ODC		__UMEM8(0x3EF0)
//	*		#define P2ODC		__UMEM8(0x3EF2)	//@@0724
//	*		#define P3ODC		__UMEM8(0x3EF3)	//@@0724
#define P5ODC		__UMEM8(0x3EF5)
//	*		#define P6ODC		__UMEM8(0x3EF6)	//@@0724
#define P7ODC		__UMEM8(0x3EF7)
//	*		#define P9ODC		__UMEM8(0x3EF9)	//@@0724
#define PAODC		__UMEM8(0x3DFF)		//@@0724	__UMEM8(0x3EFA)
#define CPUM		__UMEM8(0x3F00)
#define MEMCTR		__UMEM8(0x3F01)
#define WDCTR		__UMEM8(0x3F02)
#define DLYCTR		__UMEM8(0x3F03)

//#define WD2CTR		__UMEM8(0x3F05)
#define HANDSHAKE	__UMEM8(0x3F06)
//	*		#define AUCTR		__UMEM8(0x3F07)	//@@0724
#define SC0SEL		__UMEM8(0x3F10)
#define SC0MD0		__UMEM8(0x3F11)
#define SC0MD1		__UMEM8(0x3F12)
#define SC0MD2		__UMEM8(0x3F13)
#define SC0MD3		__UMEM8(0x3F14)
#define SC0STR		__UMEM8(0x3F15)
#define RXBUF0		__UMEM8(0x3F16)
#define TXBUF0		__UMEM8(0x3F17)
#define LINCTR		__UMEM8(0x3F18)
#define RSTFACT		__UMEM8(0x3F19)
#define OSCCNT		__UMEM8(0x3F1A)
#define RCCNT		__UMEM8(0x3F1B)
#define OSCSCNT		__UMEM8(0x3F1C)
//	*		#define RCSCNT		__UMEM8(0x3F1D)	//@@0724
#define PLLCNT		__UMEM8(0x3F1F)
#define SC1SEL		__UMEM8(0x3F20)
#define SC1MD0		__UMEM8(0x3F21)
#define SC1MD1		__UMEM8(0x3F22)
#define SC1MD2		__UMEM8(0x3F23)
#define SC1MD3		__UMEM8(0x3F24)
#define SC1STR		__UMEM8(0x3F25)
#define RXBUF1		__UMEM8(0x3F26)
#define TXBUF1		__UMEM8(0x3F27)
#define SC2SEL		__UMEM8(0x3F30)
#define SC2MD0		__UMEM8(0x3F31)
#define SC2MD1		__UMEM8(0x3F32)
#define SC2MD2		__UMEM8(0x3F33)
#define SC2MD3		__UMEM8(0x3F34)
#define SC2STR		__UMEM8(0x3F35)
#define RXBUF2		__UMEM8(0x3F36)
#define TXBUF2		__UMEM8(0x3F37)
#define SCINTSEL	__UMEM8(0x3F28)
#define LVIMD		__UMEM8(0x3F2F)
#define KEYT3_1IMD	__UMEM8(0x3F3E)
#define KEYT3_2IMD	__UMEM8(0x3F3F)
//	*		#define WD2MDSEL	__UMEM8(0x3F4C)	//@@0724
//	*		#define WD2CLR		__UMEM8(0x3F4D)	//@@0724
#define IRQEXPEN   __UMEM8(0x3F4E)
#define IRQEXPDT   __UMEM8(0x3F4F)

#define SC4MD0		__UMEM8(0x3F50)
#define SC4MD1		__UMEM8(0x3F51)
#define SC4MD2		__UMEM8(0x3F52)
#define SC4MD3		__UMEM8(0x3F53)
#define SC4AD0		__UMEM8(0x3F54)
#define SC4AD1		__UMEM8(0x3F55)
#define SC4STR0		__UMEM8(0x3F56)
#define SC4STR1		__UMEM8(0x3F57)
#define RXBUF4		__UMEM8(0x3F58)
#define TXBUF4		__UMEM8(0x3F59)
#define SC4SEL		__UMEM8(0x3F5A)
#define STB_EDG		__UMEM8(0x3F5E)
#define STB_MSK		__UMEM8(0x3F5F)
#define TM0BC		__UMEM8(0x3F60)
#define TM1BC		__UMEM8(0x3F61)
#define TM0OC		__UMEM8(0x3F62)
#define TM1OC		__UMEM8(0x3F63)
#define TM0MD		__UMEM8(0x3F64)
#define TM1MD		__UMEM8(0x3F65)
#define CK0MD		__UMEM8(0x3F66)
#define CK1MD		__UMEM8(0x3F67)
#define TM2BC		__UMEM8(0x3F68)
#define TM3BC		__UMEM8(0x3F69)
#define TM2OC		__UMEM8(0x3F6A)
#define TM3OC		__UMEM8(0x3F6B)
#define TM2MD		__UMEM8(0x3F6C)
#define TM3MD		__UMEM8(0x3F6D)
#define CK2MD		__UMEM8(0x3F6E)
#define CK3MD		__UMEM8(0x3F6F)

#define TMABC		__UMEM8(0x3F71)
#define TMAOC		__UMEM8(0x3F73)
#define TMAMD1		__UMEM8(0x3F75)
#define TMAMD2		__UMEM8(0x3F77)
#define TM6BC		__UMEM8(0x3F78)
#define TM6OC		__UMEM8(0x3F79)
#define TM6MD		__UMEM8(0x3F7A)
#define TBCLR		__UMEM8(0x3F7B)
#define TM6BEN		__UMEM8(0x3F7C)
//	*		#define RMCTR		__UMEM8(0x3F7D)	//@@0724
#define TM7MD4		__UMEM8(0x3F7E)
#define TM7BC		__UMEM16(0x3F80)
#define TM7BCL		__UMEM8(0x3F80)
#define TM7BCH		__UMEM8(0x3F81)
#define TM7OC1		__UMEM16(0x3F82)
#define TM7OC1L		__UMEM8(0x3F82)
#define TM7OC1H		__UMEM8(0x3F83)
#define TM7PR1		__UMEM16(0x3F84)
#define TM7PR1L		__UMEM8(0x3F84)
#define TM7PR1H		__UMEM8(0x3F85)
#define TM7IC		__UMEM16(0x3F86)
#define TM7ICL		__UMEM8(0x3F86)
#define TM7ICH		__UMEM8(0x3F87)
#define TM7MD1		__UMEM8(0x3F88)
#define TM7MD2		__UMEM8(0x3F89)
#define TM7OC2		__UMEM16(0x3F8A)
#define TM7OC2L		__UMEM8(0x3F8A)
#define TM7OC2H		__UMEM8(0x3F8B)
#define TM7PR2		__UMEM16(0x3F8C)
#define TM7PR2L		__UMEM8(0x3F8C)
#define TM7PR2H		__UMEM8(0x3F8D)
#define TM7MD3		__UMEM8(0x3F9E)
#define TMCKSEL1	__UMEM8(0x3FB0)
#define TMCKSEL2	__UMEM8(0x3FB1)
#define TMINSEL1	__UMEM8(0x3FB2)
#define TMINSEL2	__UMEM8(0x3FB3)
#define FBEWER		__UMEM8(0x3FBD)
#define FEWSPD		__UMEM8(0x3FBF)

#define ANCTR0		__UMEM8(0x3FC5)
#define ANCTR1		__UMEM8(0x3FC6)
#define ANCTR2		__UMEM8(0x3FC7)
#define ANBUF0		__UMEM8(0x3FC8)
#define ANBUF1		__UMEM8(0x3FC9)
//	*		#define ADICR		__UMEM8(0x3FFD)	//@@0724
#define EDGDT		__UMEM8(0x3F1E)

#define IRQCNT     __UMEM8(0x3FD0)
#define NF0CTR		__UMEM8(0x3FD1)
#define NF1CTR		__UMEM8(0x3FD2)
#define NF2CTR		__UMEM8(0x3FD3)
#define NF3CTR		__UMEM8(0x3FD4)
#define NF4CTR		__UMEM8(0x3FD5)
#define NF5CTR		__UMEM8(0x3FD6)
#define LVLMD		__UMEM8(0x3FD7)	//@@0724
#define NMICR		__UMEM8(0x3FE1)
#define IRQ0ICR		__UMEM8(0x3FE2)
#define IRQ1ICR		__UMEM8(0x3FE3)
#define IRQ2ICR		__UMEM8(0x3FE4)
#define IRQ3ICR		__UMEM8(0x3FE5)
#define IRQ4ICR		__UMEM8(0x3FE6)
//#define TSDTICR		__UMEM8(0x3FE7)
//	*		#define LVLMD		__UMEM8(0x3FE8)	//@@0724
#define TM0ICR		__UMEM8(0x3FE9)
#define TM1ICR		__UMEM8(0x3FEA)
#define TM2ICR		__UMEM8(0x3FEB)
#define TM3ICR		__UMEM8(0x3FEC)
#define TMRICR		__UMEM8(0x3FEE)		//@@0724	__UMEM8(0x3FEC)
//#define TM3ICR		__UMEM8(0x3FEC)
#define TM6ICR		__UMEM8(0x3FEF)
#define TBICR		__UMEM8(0x3FF0)
#define TM7ICR		__UMEM8(0x3FF1)
#define TM8ICR		__UMEM8(0x3FF2)
//	*		#define TM7OC2ICR	__UMEM8(0x3FF6)	//@@0724
//	*		#define PWMOVICR	__UMEM8(0x3FF9)	//@@0724
//	*		#define PWMUDICR	__UMEM8(0x3FFA)	//@@0724
#define SC0TICR		__UMEM8(0x3FF4)
#define SC0RICR		__UMEM8(0x3FF5)
#define SC1TICR		__UMEM8(0x3FF6)
#define SC1RICR		__UMEM8(0x3FF7)

#define SC2TICR		__UMEM8(0x3FF8)
#define SC2RICR		__UMEM8(0x3FF9)
#define PERIILR   __UMEM8(0x3FFE)

//@@0724 ->
//			
//	*		#define TSTMD		__UMEM8(0x3E20)
//	*		#define TSCKMD		__UMEM8(0x3E21)
//	*		#define TSTCHSEL	__UMEM8(0x3E22)
//	*		#define TSRESULT	__UMEM8(0x3E23)
//	*		#define TSERROR		__UMEM8(0x3E24)
//	*		
//	*		#define TSCH0EXDATL	__UMEM8(0x3E30)
//	*		#define TSCH0EXDATH	__UMEM8(0x3E31)
//	*		#define TSCH1EXDATL	__UMEM8(0x3E32)
//	*		#define TSCH1EXDATH	__UMEM8(0x3E33)
//	*		#define TSCH2EXDATL	__UMEM8(0x3E34)
//	*		#define TSCH2EXDATH	__UMEM8(0x3E35)
//	*		#define TSCH3EXDATL	__UMEM8(0x3E36)
//	*		#define TSCH3EXDATH	__UMEM8(0x3E37)
//	*		#define TSCH4EXDATL	__UMEM8(0x3E38)
//	*		#define TSCH4EXDATH	__UMEM8(0x3E39)
//	*		#define TSCH5EXDATL	__UMEM8(0x3E3A)
//	*		#define TSCH5EXDATH	__UMEM8(0x3E3B)
//	*		#define TSCH6EXDATL	__UMEM8(0x3E3C)
//	*		#define TSCH6EXDATH	__UMEM8(0x3E3D)
//	*		#define TSCH7EXDATL	__UMEM8(0x3E3E)
//	*		#define TSCH7EXDATH	__UMEM8(0x3E3F)
//	*		
//	*		#define TSCH0CTDATL	__UMEM8(0x3E40)
//	*		#define TSCH0CTDATH	__UMEM8(0x3E41)
//	*		#define TSCH1CTDATL	__UMEM8(0x3E42)
//	*		#define TSCH1CTDATH	__UMEM8(0x3E43)
//	*		#define TSCH2CTDATL	__UMEM8(0x3E44)
//	*		#define TSCH2CTDATH	__UMEM8(0x3E45)
//	*		#define TSCH3CTDATL	__UMEM8(0x3E46)
//	*		#define TSCH3CTDATH	__UMEM8(0x3E47)
//	*		#define TSCH4CTDATL	__UMEM8(0x3E48)
//	*		#define TSCH4CTDATH	__UMEM8(0x3E49)
//	*		#define TSCH5CTDATL	__UMEM8(0x3E4A)
//	*		#define TSCH5CTDATH	__UMEM8(0x3E4B)
//	*		#define TSCH6CTDATL	__UMEM8(0x3E4C)
//	*		#define TSCH6CTDATH	__UMEM8(0x3E4D)
//	*		#define TSCH7CTDATL	__UMEM8(0x3E4E)
//	*		#define TSCH7CTDATH	__UMEM8(0x3E4F)
//	*		
//	*		#define TSCH0EXDAT	__UMEM16(0x3E30)
//	*		#define TSCH1EXDAT	__UMEM16(0x3E32)
//	*		#define TSCH2EXDAT	__UMEM16(0x3E34)
//	*		#define TSCH3EXDAT	__UMEM16(0x3E36)
//	*		#define TSCH4EXDAT	__UMEM16(0x3E38)
//	*		#define TSCH5EXDAT	__UMEM16(0x3E3A)
//	*		#define TSCH6EXDAT	__UMEM16(0x3E3C)
//	*		#define TSCH7EXDAT	__UMEM16(0x3E3E)
//	*		
//	*		#define TSCH0CTDAT	__UMEM16(0x3E40)
//	*		#define TSCH1CTDAT	__UMEM16(0x3E42)
//	*		#define TSCH2CTDAT	__UMEM16(0x3E44)
//	*		#define TSCH3CTDAT	__UMEM16(0x3E46)
//	*		#define TSCH4CTDAT	__UMEM16(0x3E48)
//	*		#define TSCH5CTDAT	__UMEM16(0x3E4A)
//	*		#define TSCH6CTDAT	__UMEM16(0x3E4C)
//	*		#define TSCH7CTDAT	__UMEM16(0x3E4E)
//	*		
//	*		#define TSATCNT0	__UMEM8(0x3E60)
//	*		#define TSATCNT1	__UMEM8(0x3E61)
//	*		#define TSATTRC		__UMEM8(0x3E62)
//	*		#define TSATRAMAP	__UMEM16(0x3E63)
//	*		#define TSATREGAP	__UMEM8(0x3E66)
//@@0724 <-

/**********************************
   IO定义
***********************************/

/****************P0 Define********************************/

// MN101AFB3D

/****************P0 Define********************************/               	//  51A   ----->  B3D  ----->  50D
#define	   PO_EESCL	  ((*(volatile TYPE_BYTE *)&P0OUT).bit.b5)		//	P00: EE SCL --> B3D P05	as 50D Same
#define	   PM_EESCL	  ((*(volatile TYPE_BYTE *)&P0DIR).bit.b5)		//	P00: EE SCL --> B3D P05	as 50D Same	
#define	   PO_EESDA   ((*(volatile TYPE_BYTE *)&P0OUT).bit.b6)			//	P01: EE SDA --> B3D P06	as 50D Same   
#define	   Pi_EESDA   ((*(volatile TYPE_BYTE *)&P0IN).bit.b6)			//	P01: EE SDA --> B3D P06	as 50D Same
#define	   PM_EESDA	  ((*(volatile TYPE_BYTE *)&P0DIR).bit.b6)		//	P01: EE SDA --> B3D P06	as 50D Same	
//#define	   PO_nouse	   ((*(volatile TYPE_BYTE *)&P8OUT).bit.b2)		//	P02:预? --> B3D P82 as 50D None Use
#define	   PO_ISD_RESET	((*(volatile TYPE_BYTE *)&P0OUT).bit.b5)	//	P07:ISD3800复位管脚   --> B3D P05 as 50D Same
#define	   PM_ISD_RESET      ((*(volatile TYPE_BYTE *)&P0DIR).bit.b5)		//	P07: --> P05 as 50D Same

#define	   ISD_CSN	       ((*(volatile TYPE_BYTE *)&P8OUT).bit.b3)		//	P03:语音模块的片选管脚 --> B3D P83 as 50D None Use
#define	   PM_CSN      ((*(volatile TYPE_BYTE *)&P8DIR).bit.b3)		//	P03: -->B3D  P83 as 50D None Use

#define	   ISD_SDI 	       ((*(volatile TYPE_BYTE *)&P8IN).bit.b4)		//	P04: --> B3D P84 as 50D None Use
#define	   PM_SI 	       ((*(volatile TYPE_BYTE *)&P8DIR).bit.b4)		//	P04: --> B3D P84 as 50D None Use

#define	   ISD_SCLK	       ((*(volatile TYPE_BYTE *)&P8OUT).bit.b5)		//	P05: 语音模块的SPI通信时钟口 --> B3D P85 as 50D None Use
#define	   PM_SCK      ((*(volatile TYPE_BYTE *)&P8DIR).bit.b5)		//	P05: --> B3D P85 as 50D None Use

#define	   ISD_SDO	       ((*(volatile TYPE_BYTE *)&P8OUT).bit.b6)		//	P06:语音模块的sdo数据输出管脚 --> B3D P86 as 50D None Use
#define	   PM_SDO      ((*(volatile TYPE_BYTE *)&P8DIR).bit.b6)		//	P06: --> B3D P86 as 50D None Use

//#define	   PI_KEY  ((*(volatile TYPE_BYTE *)&P2IN).bit.b0)   			//  P20:	预留按键输入 --> B3D P20

#define	   PI_ISD_Busy       ((*(volatile TYPE_BYTE *)&P2IN).bit.b1)  		//  P21:	GDO2外部中断口 --> B3D P21 as 50D Same
#define	   PI_IntUart  ((*(volatile TYPE_BYTE *)&PAOUT ).bit.b1) 		//  P22:   用于串口接收外部中断处理    --> B3D P76 --> 50D PA1

#define	   GDO2       ((*(volatile TYPE_BYTE *)&P2IN).bit.b1)   		//  P21:	GDO2外部中断口 --> B3D P21 as 50D Same
#define	   PI_WifiRxd ((*(volatile TYPE_BYTE *)&PAIN ).bit.b1) 		//  P22:   用于串口接收外部中断处理    --> B3D P76 -->  50D PA1
#define	   PM_WifiRxd ((*(volatile TYPE_BYTE *)&PADIR ).bit.b1) 		//  P22:   用于串口接收外部中断处理  --> B3D P76 --> 50D PA1
#define	   PO_WifiTxd ((*(volatile TYPE_BYTE *)&PAOUT ).bit.b2)		//  P23:	com1  第1个八字 --> B3D P75 --> 50D PA2
#define	   PMO_WifiTxd ((*(volatile TYPE_BYTE *)&PADIR ).bit.b2)		//  P23:	 --> B3D P75 --> 50D PA2
#define	   PI_Remote    ((*(volatile TYPE_BYTE *)&P2IN ).bit.b4)		//	P24:	 --> B3D P24 as 50D Same
#define	   NRST_OUT  ((*(volatile TYPE_BYTE *)&P2OUT).bit.b7)			//	P27: 	 --> B3D P27 as 50D Same

#define	   PO_COM1	((*(volatile TYPE_BYTE *)&P6OUT).bit.b7)		//	P07:COM1 --> B3D P67  as 50D Same
#define	   PO_COM2   ((*(volatile TYPE_BYTE *)&P7OUT).bit.b4)			// com5	P32: com2  第二个八字 --> B3D P62 COM5 --> 50D P74
#define	   PO_COM3	  ((*(volatile TYPE_BYTE *)&P7OUT).bit.b3)		//	P33: com3  第三个八字 --> B3D P63 COM3 --> 50D P73
#define	   PO_COM4	 ((*(volatile TYPE_BYTE *)&P6OUT).bit.b4)		// com6  P36:com4  辅助功能图标 --> B3D P64  as 50D Same
#define	   PO_TXD     ((*(volatile TYPE_BYTE *)&P0OUT ).bit.b3)		//txd0	P34: --> B3D P03  as 50D Same
#define	   PM_PO_TXD  ((*(volatile TYPE_BYTE *)&P0DIR ).bit.b3)		//	P34: --> B3D P03 as 50D Same
#define	   TDI 	      ((*(volatile TYPE_BYTE *)&P0IN ).bit.b2)			//	P35: rxd0 --> B3D P02 as 50D Same


#define	   PO_SEGI   ((*(volatile TYPE_BYTE *)&P7OUT).bit.b7)			//L	P40: SEG9 --> B3D P72 L --> 50D P77 I
#define	   PO_nouse6   ((*(volatile TYPE_BYTE *)&P7OUT).bit.b0)		// J	P41: NO USE --> B3D P70 as 50D None Use
#define	   PO_SEGH     ((*(volatile TYPE_BYTE *)&P6OUT).bit.b6)  		//H	P42: --> B3D P52 --> 50D P66 
#define	   PO_SEGG     ((*(volatile TYPE_BYTE *)&P6OUT).bit.b5)		//G	P43:  --> B3D P53 --> 50D P65
#define	   PO_SEGF   ((*(volatile TYPE_BYTE *)&P5OUT).bit.b4)			//F	P44:  --> B3D P54 --> 50D P54 same
#define	   PO_SEGE    ((*(volatile TYPE_BYTE *)&P5OUT).bit.b3)			//E	P45: --> B3D P55 --> 50D P53

#define	   PO_SEGD     ((*(volatile TYPE_BYTE *)&P5OUT).bit.b2)		//D	PA0 --> B3D P56 --> 50D P52
#define	   PO_SEGC   	((*(volatile TYPE_BYTE *)&P5OUT).bit.b1)		//C	PA1 --> B3D P57 --> 50D P51
#define	   PO_SEGB	  ((*(volatile TYPE_BYTE *)&P5OUT ).bit.b0)		//B	PA2:  --> B3D P94 --> 50D P50
#define	   PO_SEGA     ((*(volatile TYPE_BYTE *)&P8OUT ).bit.b0)		//A	PA3:  --> B3D P71 --> 50D P80

#define	   PO_nouse7	  ((*(volatile TYPE_BYTE *)&PAOUT).bit.b4)		//	PA4: --> B3D PA4 as 50D None Use
#define	   LED_PWM0	  ((*(volatile TYPE_BYTE *)&PAOUT).bit.b5)		//	PA5:导光带 --> B3D PA5 as 50D None Use
#define	   LED_PWM1	  ((*(volatile TYPE_BYTE *)&PAOUT).bit.b6)		//	PA6: --> B3D PA6 as 50D None Use
#define	   LED_PWM2	  ((*(volatile TYPE_BYTE *)&PAOUT).bit.b7)		//	PA7: --> B3D PA7 as 50D None Use



/*
*******************************************************************************
**	Register bit define
*******************************************************************************
*/
#define PMnAll_MODE_INPUT	0x00

#define PMn0_MODE_INPUT		0x00	/* Pn0 as input mode */
#define PMn0_MODE_OUTPUT	0x01	/* Pn0 as output mode */
#define PMn1_MODE_INPUT		0x00	/* Pn1 as input mode */
#define PMn1_MODE_OUTPUT	0x02	/* Pn1 as output mode */
#define PMn2_MODE_INPUT		0x00	/* Pn2 as input mode */
#define PMn2_MODE_OUTPUT	0x04	/* Pn2 as output mode */
#define PMn3_MODE_INPUT		0x00	/* Pn3 as input mode */
#define PMn3_MODE_OUTPUT	0x08	/* Pn3 as output mode */
#define PMn4_MODE_INPUT		0x00	/* Pn4 as input mode */
#define PMn4_MODE_OUTPUT	0x10	/* Pn4 as output mode */
#define PMn5_MODE_INPUT		0x00	/* Pn5 as input mode */
#define PMn5_MODE_OUTPUT	0x20	/* Pn5 as output mode */
#define PMn6_MODE_INPUT		0x00	/* Pn6 as input mode */
#define PMn6_MODE_OUTPUT	0x40	/* Pn6 as output mode */
#define PMn7_MODE_INPUT		0x00	/* Pn7 as input mode */
#define PMn7_MODE_OUTPUT	0x80	/* Pn7 as output mode */

#define PMn0_CHANGE_OUTPUT	0xFE	/* Change Pn0 to output mode */
#define PMn1_CHANGE_OUTPUT	0xFD	/* Change Pn1 to output mode */
#define PMn2_CHANGE_OUTPUT	0xFB	/* Change Pn2 to output mode */
#define PMn3_CHANGE_OUTPUT	0xF7	/* Change Pn3 to output mode */
#define PMn4_CHANGE_OUTPUT	0xEF	/* Change Pn4 to output mode */
#define PMn5_CHANGE_OUTPUT	0xDF	/* Change Pn5 to output mode */
#define PMn6_CHANGE_OUTPUT	0xBF	/* Change Pn6 to output mode */
#define PMn7_CHANGE_OUTPUT	0x7F	/* Change Pn7 to output mode */

#define PMnALL_OMD1_NORMAL     	0x00	/* not use Pn0 as digital I/O */

#define PMn0_OMD1_1     	0x01	/* not use Pn0 as digital I/O */
#define PMn1_OMD1_1		    0x02	/* not use Pn1 as digital I/O */
#define PMn2_OMD1_1		    0x04	/* not use Pn2 as digital I/O */
#define PMn3_OMD1_1		    0x08	/* not use Pn3 as digital I/O */
#define PMn4_OMD1_1		    0x10	/* not use Pn4 as digital I/O */
#define PMn5_OMD1_1		    0x20	/* not use Pn5 as digital I/O */
#define PMn6_OMD1_1	        0x40	/* not use Pn6 as digital I/O */
#define PMn7_OMD1_1		    0x80	/* not use Pn7 as digital I/O */


#define PMnALL_OMD2_NORMAL     	0x00	/* not use Pn0 as digital I/O */

#define PMn0_OMD2_1     	0x01	/* not use Pn0 as digital I/O */
#define PMn1_OMD2_1		    0x02	/* not use Pn1 as digital I/O */
#define PMn2_OMD2_1		    0x04	/* not use Pn2 as digital I/O */
#define PMn3_OMD2_1		    0x08	/* not use Pn3 as digital I/O */
#define PMn4_OMD2_1		    0x10	/* not use Pn4 as digital I/O */
#define PMn5_OMD2_1		    0x20	/* not use Pn5 as digital I/O */
#define PMn6_OMD2_1	        0x40	/* not use Pn6 as digital I/O */
#define PMn7_OMD2_1		    0x80	/* not use Pn7 as digital I/O */



/* Port register(Pn.0 to 7) */
#define PnALL_OUTPUT_0		0x00	/* Pn0 output 0 */

#define Pn0_OUTPUT_0		0x00	/* Pn0 output 0 */
#define Pn0_OUTPUT_1		0x01	/* Pn0 output 1 */
#define Pn1_OUTPUT_0		0x00	/* Pn1 output 0 */
#define Pn1_OUTPUT_1		0x02	/* Pn1 output 1 */
#define Pn2_OUTPUT_0		0x00	/* Pn2 output 0 */
#define Pn2_OUTPUT_1		0x04	/* Pn2 output 1 */
#define Pn3_OUTPUT_0		0x00	/* Pn3 output 0 */
#define Pn3_OUTPUT_1		0x08	/* Pn3 output 1 */
#define Pn4_OUTPUT_0		0x00	/* Pn4 output 0 */
#define Pn4_OUTPUT_1		0x10	/* Pn4 output 1 */
#define Pn5_OUTPUT_0		0x00	/* Pn5 output 0 */
#define Pn5_OUTPUT_1		0x20	/* Pn5 output 1 */
#define Pn6_OUTPUT_0		0x00	/* Pn6 output 0 */
#define Pn6_OUTPUT_1		0x40	/* Pn6 output 1 */
#define Pn7_OUTPUT_0		0x00	/* Pn7 output 0 */
#define Pn7_OUTPUT_1		0x80	/* Pn7 output 1 */

/* Pull-up resistor option register(PUn.0 to 7) */
#define PUnALL_PULLUP_OFF	0x00	/* Pn0 Pull-up not connected */


#define PUn0_PULLUP_OFF		0x00	/* Pn0 Pull-up not connected */
#define PUn0_PULLUP_ON		0x01	/* Pn0 pull-up connected */
#define PUn1_PULLUP_OFF		0x00	/* Pn1 Pull-up not connected */
#define PUn1_PULLUP_ON		0x02	/* Pn1 pull-up connected */
#define PUn2_PULLUP_OFF		0x00	/* Pn2 Pull-up not connected */
#define PUn2_PULLUP_ON		0x04	/* Pn2 pull-up connected */
#define PUn3_PULLUP_OFF		0x00	/* Pn3 Pull-up not connected */
#define PUn3_PULLUP_ON		0x08	/* Pn3 pull-up connected */
#define PUn4_PULLUP_OFF		0x00	/* Pn4 Pull-up not connected */
#define PUn4_PULLUP_ON		0x10	/* Pn4 pull-up connected */
#define PUn5_PULLUP_OFF		0x00	/* Pn5 Pull-up not connected */
#define PUn5_PULLUP_ON		0x20	/* Pn5 pull-up connected */
#define PUn6_PULLUP_OFF		0x00	/* Pn6 Pull-up not connected */
#define PUn6_PULLUP_ON		0x40	/* Pn6 pull-up connected */
#define PUn7_PULLUP_OFF		0x00	/* Pn7 Pull-up not connected */
#define PUn7_PULLUP_ON		0x80	/* Pn7 pull-up connected */

#define PMnALL_LED_OFF      0x00

#define PMn0_LED     	    0x01	/* not use Pn0 as digital I/O */
#define PMn1_LED		    0x02	/* not use Pn1 as digital I/O */
#define PMn2_LED	        0x04	/* not use Pn2 as digital I/O */
#define PMn3_LED		    0x08	/* not use Pn3 as digital I/O */
#define PMn4_LED		    0x10	/* not use Pn4 as digital I/O */
#define PMn5_LED		    0x20	/* not use Pn5 as digital I/O */
#define PMn6_LED	        0x40	/* not use Pn6 as digital I/O */
#define PMn7_LED		    0x80	/* not use Pn7 as digital I/O */

#define PMnALL_ODC_PP         0x00

#define PMn0_ODC_OD     	0x01	/* not use Pn0 as digital I/O */
#define PMn1_ODC_OD		    0x02	/* not use Pn1 as digital I/O */
#define PMn2_ODC_OD		    0x04	/* not use Pn2 as digital I/O */
#define PMn3_ODC_OD		    0x08	/* not use Pn3 as digital I/O */
#define PMn4_ODC_OD		    0x10	/* not use Pn4 as digital I/O */
#define PMn5_ODC_OD		    0x20	/* not use Pn5 as digital I/O */
#define PMn6_ODC_OD	        0x40	/* not use Pn6 as digital I/O */
#define PMn7_ODC_OD		    0x80	/* not use Pn7 as digital I/O */




#endif

