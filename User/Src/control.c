#include "control.h"
#include "aht20.h"
#include "stdlib.h"
#include "math.h"
#include "stflash.h"

uint8_t timeFlag_10ms;
uint8_t sysEnable;
uint16_t rol_delay10ms = 0;
extern TIM_HandleTypeDef htim1;
SysDataTimeType sysDataTime;
uint8_t beepOn;

UserFlashType  userFlashData;

PID_ParmeType temp_PID,humidity_PID;
float targetTemp = 37.8f;
float targetHumidity = 80.0f;
void DataTimeInterrupt10ms(void)
{
	sysDataTime.mseconds+=10;		
	if(sysDataTime.mseconds >= 1000)
	{
		sysDataTime.minutes++;
		sysDataTime.mseconds = 0;
	}
	if(sysDataTime.minutes >= 60)
	{
		sysDataTime.hours++;
		sysDataTime.minutes = 0;
	}
	if(sysDataTime.hours >= 24)
	{
		sysDataTime.days++;
		sysDataTime.hours = 0;
	}
}
void PID_Init(void)
{
	temp_PID.integral_limit = 2000.0f;
	temp_PID.err = 0.0f;
	temp_PID.errlast = 0.0f;
	temp_PID.integral = 0.0f;
	temp_PID.Kp = 0.2f;
	temp_PID.Ki = 0.001f;
	temp_PID.Kd = 0.2f;
	
	humidity_PID.integral_limit = 1000.0f;
	humidity_PID.err = 0.0f;
	humidity_PID.errlast = 0.0f;
	humidity_PID.integral = 0.0f;
	humidity_PID.Kp = 5.0f;
	humidity_PID.Ki = 0.0f;
	humidity_PID.Kd = 0.0f;
}

float PID_Fun(float target,float input,PID_ParmeType* pObj)
{
	float output;
	pObj->err = target - input;
	pObj->integral += pObj->err;
	if(pObj->integral >= pObj->integral_limit)
		pObj->integral = pObj->integral_limit;
	output = pObj->Kp*pObj->err + pObj->Ki*pObj->integral + pObj->Kd*(pObj->err - pObj->errlast);
	pObj->errlast = pObj->err;
	return output;
}



void TempetatureCtrl(uint8_t enable)
{
	uint16_t setCompare;
	float setOutput = 0;
	float realTemp = (AHT20_1_Data.tempetature + AHT20_2_Data.tempetature)/2;
	float difTemp = fabs(AHT20_1_Data.tempetature - AHT20_2_Data.tempetature);
	if(sysDataTime.days < 7)
	{
		targetTemp = 37.8f;
	}else if(sysDataTime.days < 14)
	{
		targetTemp = 37.8f;
	}else{
		targetTemp = 37.8f;
	}
	if((enable)&&(difTemp < 2.0f))
	{
		setOutput = PID_Fun(targetTemp,realTemp,&temp_PID);
		if(setOutput > 100.0f)
			setOutput = 100.0f;
		else if(setOutput < 0.0f)
			setOutput = 0.0f;
		setCompare = (uint16_t)setOutput;
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,setCompare);
	}else
	{
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,0);
	}
	if(realTemp > 38.5f)
	{
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,0);
	}
	if((realTemp > 38.5f)||(realTemp < 36.0f))
	{
		beepOn = 1;
	}else
	{
		beepOn = 0;
	}
}

void HumidityCtrl(uint8_t enable)
{
	uint16_t setCompare;
	float setOutput = 0.0f;
	float realHumidity = (AHT20_1_Data.humidity + AHT20_2_Data.humidity)/2;
	float difHumidity = fabs(AHT20_1_Data.humidity - AHT20_2_Data.humidity);
	if((difHumidity < 20.0)&&(enable))
	{
		setOutput = PID_Fun(targetHumidity,realHumidity,&humidity_PID)+30;
		if(setOutput > 70.0f)
			setOutput = 70.0f;
		else if(setOutput < 0.0f)
			setOutput = 0.0f;		
		setCompare = (uint16_t)setOutput + 30;
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,setCompare);	
	}else
	{
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,0);
	}
	if((realHumidity > 80.0f)||(realHumidity < 60.0f))
	{
		beepOn = 1;
	}else
	{
		beepOn = 0;
	}
}

void control_init(void)
{
	
	PID_Init();
	STMFLASH_Read(USER_DATA_ADDR,(uint16_t*)&userFlashData,sizeof(userFlashData));
	sysDataTime.days = userFlashData.days;
}

void Rol_Egg(void)
{
	if(rol_delay10ms > 0)
	{
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,500);
		rol_delay10ms--;
	}else{
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,0);
	}
}

void Beep_Ctrl(uint8_t enable)
{
	static uint16_t cnt = 0;
	if(enable)
	{
		cnt = (cnt+1)%100;
		if(cnt > 50)
		{
			//BEEP On
		}else
		{
			//Beep Off
		}
		
	}else
	{
		//Beep Off
	}
}

void control_Loop(void)
{
	if(timeFlag_10ms == 1)
	{
		DataTimeInterrupt10ms();
		TempetatureCtrl(sysEnable);
		HumidityCtrl(sysEnable);
		if((sysDataTime.days > DEGG_ROL)&&(sysDataTime.days < DEGG_STOPROL))
		{
			if((sysDataTime.hours%4 == 0)&&\
				(sysDataTime.minutes == 0 )&&\
				(sysDataTime.seconds == 0 )&&\
				(sysDataTime.mseconds == 0 ))
			{
				rol_delay10ms = 100;
			}			
		}
		Rol_Egg();
		if((sysDataTime.hours == 0)&&\
			(sysDataTime.minutes == 0 )&&\
			(sysDataTime.seconds == 0 )&&\
			(sysDataTime.mseconds == 0 ))
		{
			//记录系统信息
			userFlashData.days = sysDataTime.days;
			STMFLASH_Write(USER_DATA_ADDR,(uint16_t*)&userFlashData,sizeof(userFlashData));
		}	
		Beep_Ctrl(beepOn);
		
	}
}
