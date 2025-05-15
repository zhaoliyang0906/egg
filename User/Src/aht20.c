#include "myiic.h"
#include "aht20.h"

AHT20_DataType AHT20_1_Data,AHT20_2_Data;


uint8_t AHT20_1_Init(void)
{
	uint8_t txdata = (AHT20ADDR<<1)|CMD_W;
	uint8_t rcvdata;
	IIC1_Start();
	IIC1_Send_Byte(txdata);
	if(IIC1_Wait_Ack())
		return 1;
	IIC1_Send_Byte(0x71);
	if(IIC1_Wait_Ack())
		return 1;
	rcvdata = IIC1_Read_Byte(1);
	IIC1_Stop();
	
	if(CAL_MASK&rcvdata)
	{
		return 0;
	}
	IIC1_Start();
	IIC1_Send_Byte(txdata);	
	if(IIC1_Wait_Ack())
		return 1;
	IIC1_Send_Byte(0xBE);
	if(IIC1_Wait_Ack())
		return 1;	
	IIC1_Send_Byte(0x08);
	if(IIC1_Wait_Ack())
		return 1;	
	IIC1_Send_Byte(0x00);
	if(IIC1_Wait_Ack())
		return 1;	
	HAL_Delay(20);
	return 0;
}

uint8_t AHT20_2_Init(void)
{
	uint8_t txdata = (AHT20ADDR<<1)|CMD_W;
	uint8_t rcvdata;
	IIC2_Start();
	IIC2_Send_Byte(txdata);
	if(IIC2_Wait_Ack())
		return 1;
	IIC2_Send_Byte(0x71);
	if(IIC2_Wait_Ack())
		return 1;
	rcvdata = IIC2_Read_Byte(1);
	IIC2_Stop();
	
	if(CAL_MASK&rcvdata)
	{
		return 0;
	}
	IIC2_Start();
	IIC2_Send_Byte(txdata);	
	if(IIC2_Wait_Ack())
		return 1;
	IIC2_Send_Byte(0xBE);
	if(IIC2_Wait_Ack())
		return 1;	
	IIC2_Send_Byte(0x08);
	if(IIC2_Wait_Ack())
		return 1;	
	IIC2_Send_Byte(0x00);
	if(IIC2_Wait_Ack())
		return 1;	
	HAL_Delay(20);
	return 0;
}

void AHT20_1_Trig(void)
{
	uint8_t txdata = (AHT20ADDR<<1)|CMD_W;
	IIC1_Start();
	IIC1_Send_Byte(txdata);
	if(IIC1_Wait_Ack())
		return ;
	IIC1_Send_Byte(0xAC);
	if(IIC1_Wait_Ack())
		return ;
	IIC1_Send_Byte(0x33);
	if(IIC1_Wait_Ack())
		return ;
	IIC1_Send_Byte(0x00);
	if(IIC1_Wait_Ack())
		return ;
	IIC1_Stop();	
}


void AHT20_2_Trig(void)
{
	uint8_t txdata = (AHT20ADDR<<1)|CMD_W;
	IIC2_Start();
	IIC2_Send_Byte(txdata);
	if(IIC2_Wait_Ack())
		return ;
	IIC2_Send_Byte(0xAC);
	if(IIC2_Wait_Ack())
		return ;
	IIC2_Send_Byte(0x33);
	if(IIC2_Wait_Ack())
		return ;
	IIC2_Send_Byte(0x00);
	if(IIC2_Wait_Ack())
		return ;
	IIC2_Stop();	
}

AHT20_DataType ReadAHT20_1(void)
{
	AHT20_DataType data = {0,0};
	uint32_t tempdata;
	uint32_t humdata;
	uint8_t datatmp[7];
	uint8_t txdata = (AHT20ADDR<<1)|CMD_R;
	IIC1_Start();
	IIC1_Send_Byte(txdata);	
	if(IIC1_Wait_Ack())
		return data;
	for(uint8_t i = 0; i < 7; i++)
	{
		datatmp[i] = IIC1_Read_Byte(1);		
	}
	IIC1_Stop();
	if((datatmp[0]&0x80) == 0)
	{
		humdata = (datatmp[1]<<12)|(datatmp[2]<<4)|(datatmp[3]>>4);
		tempdata = ((datatmp[3]<<16)|(datatmp[4]<<8)|datatmp[5])&0xFFFFF;
		data.humidity = ((float)(humdata*100))/((float)(2^20));
		data.tempetature = ((float)tempdata)/((float)(2^20))*200.0f-50.0f;
	}
	return data;
}

AHT20_DataType ReadAHT20_2(void)
{
	AHT20_DataType data = {0,0};
	uint32_t tempdata;
	uint32_t humdata;
	uint8_t datatmp[7];
	uint8_t txdata = (AHT20ADDR<<1)|CMD_R;
	IIC2_Start();
	IIC2_Send_Byte(txdata);	
	if(IIC2_Wait_Ack())
		return data;
	for(uint8_t i = 0; i < 7; i++)
	{
		datatmp[i] = IIC2_Read_Byte(1);		
	}
	IIC2_Stop();
	if((datatmp[0]&0x80) == 0)
	{
		humdata = (datatmp[1]<<12)|(datatmp[2]<<4)|(datatmp[3]>>4);
		tempdata = ((datatmp[3]<<16)|(datatmp[4]<<8)|datatmp[5])&0xFFFFF;
		data.humidity = ((float)(humdata*100))/((float)(2^20));
		data.tempetature = ((float)tempdata)/((float)(2^20))*200.0f-50.0f;
	}
	return data;
}

void AHT20_10msLoop(void)
{
	static uint8_t loopCnt = 0;
	loopCnt++;
	
	if(loopCnt == 1)
	{
		AHT20_1_Trig();
		AHT20_2_Trig();
	}else if(loopCnt == 10)
	{
		AHT20_1_Data = ReadAHT20_1();
		AHT20_2_Data = ReadAHT20_2();	
	} 
	if(loopCnt == 10)
	{
		loopCnt = 0;
	}
	
}

