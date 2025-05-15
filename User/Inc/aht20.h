#ifndef AHT20_H_
#define AHT20_H_

#include "main.h"


#define CAL_MASK				0x08

#define AHT20ADDR				0x38
#define CMD_R    				1
#define CMD_W    				0

#define REA_DSTA_CMD			0x71

typedef struct
{
	float tempetature;
	float humidity;
} AHT20_DataType;



extern AHT20_DataType 	AHT20_1_Data;
extern AHT20_DataType	AHT20_2_Data;

#endif


