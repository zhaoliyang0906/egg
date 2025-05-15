#ifndef  __CONTROL_H_
#define  __CONTROL_H_

#include "main.h"

#define DEGG_ROL			12
#define DEGG_STOPROL		18
#define USER_DATA_ADDR		0x800FC00

typedef struct{
	uint16_t eggType;
	uint16_t days;
}UserFlashType;

typedef struct{
	uint16_t days;
	uint16_t hours;
	uint16_t minutes;
	uint16_t seconds;
	uint16_t mseconds;	
}SysDataTimeType;

typedef struct{
	float errlast;
	float err;
	float integral;
	float integral_limit;
	float Kp;
	float Ki;
	float Kd;	
}PID_ParmeType;


#endif


