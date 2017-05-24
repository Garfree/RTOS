/*******************************************************************************
  * @file    type.h
  * @author  garfree
  * @version V1.0.0
  * @date    09-May-2017
  * @brief   
  *****************************************************************************/
#ifndef  __TYPE_H 
#define  __TYPE_H

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t

#define s8 int8_t
#define s16 int16_t
#define s32 int32_t

#define TRUE 	1
#define FALSE 	0

typedef struct {
	u8 b0: 1;
	u8 b1: 1;
	u8 b2: 1;
	u8 b3: 1;
	u8 b4: 1;
	u8 b5: 1;
	u8 b6: 1;
	u8 b7: 1;
}b8;

typedef union {
	b8  BIT;
	u8	BYTE;
}ub8;

typedef union {
	struct {   	
		u8 BYTEH;
		u8 BYTEL;
	}BYTES;
	u16  WORD;
}uw16;

typedef union {
	struct {   	
		u8 BYTE0; //bit0-bit7
		u8 BYTE1;
		u8 BYTE2;
		u8 BYTE3;
	}BYTES;
	u32 DWORD;
}uw32;

#endif 
