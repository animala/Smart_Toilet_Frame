
/*************************************************************/
/*                                                           */
/*   Variable Type and Function Type		                     */
/*                                                           */
/*   Written by ZKL     2014.7.08    									    */
/*                                                           */
/*************************************************************/

#ifndef TYPESTRUCT
#define TYPESTRUCT

#define   U8    unsigned char      //无符号8位
#define   U16   unsigned int       //无符号16位
#define   U32   unsigned long int  //无符号32位

#define   S8    char               //有符号8位
#define   S16   int                //有符号16位
#define   S32   long int           //有符号32位

#define		uchar				unsigned char
#define		uint				unsigned int
#define		ulint				unsigned long 


#define FirstBit 0    //0/1:0means the first bit is 0th  bit ,1 means the first bit is 7th bit
#if  FirstBit
typedef struct {			/*定义字节、位寻址结构*/
	unsigned char b7:1;
	unsigned char b6:1;
	unsigned char b5:1;
	unsigned char b4:1;
	unsigned char b3:1;
	unsigned char b2:1;
	unsigned char b1:1;
	unsigned char b0:1;
} BYTE_FIELD;

typedef struct{			/*定义字、位寻址结构*/
	unsigned short int b15:1;
	unsigned short int b14:1;
	unsigned short int b13:1;
	unsigned short int b12:1;
	unsigned short int b11:1;
	unsigned short int b10:1;
	unsigned short int b9:1;
	unsigned short int b8:1;
	unsigned short int b7:1;
	unsigned short int b6:1;
	unsigned short int b5:1;
	unsigned short int b4:1;
	unsigned short int b3:1;
	unsigned short int b2:1;
	unsigned short int b1:1;
	unsigned short int b0:1;
} WORD_FIELD;

typedef struct{           //*定义双字、位寻址结构  //Add: 2010.01.25 
	unsigned long int  b31:1;
	unsigned long int  b30:1;
	unsigned long int  b29:1;
	unsigned long int  b28:1;
	unsigned long int  b27:1;	
	unsigned long int  b26:1;
	unsigned long int  b25:1;
	unsigned long int  b24:1;
	unsigned long int  b23:1;
	unsigned long int  b22:1;		
	unsigned long int  b21:1;
	unsigned long int  b20:1;
	unsigned long int  b19:1;
	unsigned long int  b18:1;
	unsigned long int  b17:1;
	unsigned long int  b16:1;				
	unsigned long int  b15:1;
	unsigned long int  b14:1;
	unsigned long int  b13:1;
	unsigned long int  b12:1;
	unsigned long int  b11:1;
	unsigned long int  b10:1;
	unsigned long int  b9:1;
	unsigned long int  b8:1;
	unsigned long int  b7:1;
	unsigned long int  b6:1;
	unsigned long int  b5:1;
	unsigned long int  b4:1;
	unsigned long int  b3:1;
	unsigned long int  b2:1;
	unsigned long int  b1:1;
	unsigned long int  b0:1;
} DWORD_FIELD;	


#else
typedef struct {			/*定义字节、位寻址结构*/
	unsigned char b0:1;
	unsigned char b1:1;
	unsigned char b2:1;
	unsigned char b3:1;
	unsigned char b4:1;
	unsigned char b5:1;
	unsigned char b6:1;
	unsigned char b7:1;
} BYTE_FIELD;

typedef struct{			/*定义字、位寻址结构*/
	unsigned short int b0:1;
	unsigned short int b1:1;
	unsigned short int b2:1;
	unsigned short int b3:1;
	unsigned short int b4:1;
	unsigned short int b5:1;
	unsigned short int b6:1;
	unsigned short int b7:1;
	unsigned short int b8:1;
	unsigned short int b9:1;
	unsigned short int b10:1;
	unsigned short int b11:1;
	unsigned short int b12:1;
	unsigned short int b13:1;
	unsigned short int b14:1;
	unsigned short int b15:1;
} WORD_FIELD;

typedef struct{           //*定义双字、位寻址结构  //Add: 2010.01.25 
	unsigned long int  b0:1;
	unsigned long int  b1:1;
	unsigned long int  b2:1;
	unsigned long int  b3:1;
	unsigned long int  b4:1;	
	unsigned long int  b5:1;
	unsigned long int  b6:1;
	unsigned long int  b7:1;
	unsigned long int  b8:1;
	unsigned long int  b9:1;		
	unsigned long int  b10:1;
	unsigned long int  b11:1;
	unsigned long int  b12:1;
	unsigned long int  b13:1;
	unsigned long int  b14:1;
	unsigned long int  b15:1;				
	unsigned long int  b16:1;
	unsigned long int  b17:1;
	unsigned long int  b18:1;
	unsigned long int  b19:1;
	unsigned long int  b20:1;
	unsigned long int  b21:1;
	unsigned long int  b22:1;
	unsigned long int  b23:1;
	unsigned long int  b24:1;
	unsigned long int  b25:1;
	unsigned long int  b26:1;
	unsigned long int  b27:1;
	unsigned long int  b28:1;
	unsigned long int  b29:1;
	unsigned long int  b30:1;
	unsigned long int  b31:1;
} DWORD_FIELD;	


#endif


typedef union{			/*定义字节、位寻址类型联合*/
	unsigned char byte;
	BYTE_FIELD bit;
} TYPE_BYTE;

typedef union{		/*定义字、位寻址类型联合*/
	unsigned int word;
	unsigned char byte[2];
	WORD_FIELD bit;
} TYPE_WORD;


typedef union{    /*定义双字、位寻址类型联合*/	//Add:2010.01.25
	unsigned long int dword;
	unsigned short int word[2];
	unsigned char byte[4];
	DWORD_FIELD bit;
} TYPE_DWORD;

typedef union{    /*定义双字节类型联合*/
	unsigned short int word[2];
	unsigned char byte[4];
} DWORD;

typedef union{                  //定义字类型联合
     unsigned short int word;
	 unsigned char byte [2];
} WORD;









#endif

