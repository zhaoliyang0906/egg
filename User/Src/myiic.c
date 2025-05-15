#include "myiic.h"
	

//IIC初始化
void IIC_Init(void)
{
    SDA1_OUT();
	SDA2_OUT();
    IIC1_SDAH();
    IIC1_SCLH();  
	IIC2_SDAH();
    IIC2_SCLH(); 
}

//产生IIC起始信号
void IIC1_Start(void)
{
	SDA1_OUT();     //sda线输出
	IIC1_SDAH();	  	  
	IIC1_SCLH();
	delay_us(2);
 	IIC1_SDAL();//START:when CLK is high,DATA change form high to low 
	delay_us(2);
	IIC1_SCLL();//钳住I2C总线，准备发送或接收数据 
}	  

void IIC2_Start(void)
{
	SDA2_OUT();     //sda线输出
	IIC2_SDAH();	  	  
	IIC2_SCLH();
	delay_us(2);
 	IIC2_SDAL();//START:when CLK is high,DATA change form high to low 
	delay_us(2);
	IIC2_SCLL();//钳住I2C总线，准备发送或接收数据 
}

//产生IIC停止信号
void IIC1_Stop(void)
{
	SDA1_OUT();//sda线输出
	IIC1_SCLL();
	IIC1_SDAL();//STOP:when CLK is high DATA change form low to high
 	delay_us(2);
	IIC1_SCLH(); 
	delay_us(2);
	IIC1_SDAH();//发送I2C总线结束信号
	delay_us(2);							   	
}
void IIC2_Stop(void)
{
	SDA2_OUT();//sda线输出
	IIC2_SCLL();
	IIC2_SDAL();//STOP:when CLK is high DATA change form low to high
 	delay_us(2);
	IIC2_SCLH(); 
	delay_us(2);
	IIC2_SDAH();//发送I2C总线结束信号
	delay_us(2);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
uint8_t IIC1_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	SDA1_IN();      //SDA设置为输入  
	IIC1_SDAH();delay_us(1);	   
	IIC1_SCLH();delay_us(1);	 
	while(READ_SDA1)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC1_Stop();
			return 1;
		}
	}
	IIC1_SCLL();//时钟输出0 	   
	return 0;  
} 

uint8_t IIC2_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	SDA2_IN();      //SDA设置为输入  
	IIC2_SDAH();delay_us(1);	   
	IIC2_SCLH();delay_us(1);	 
	while(READ_SDA2)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC2_Stop();
			return 1;
		}
	}
	IIC2_SCLL();//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void IIC1_Ack(void)
{
	IIC1_SCLL();
	SDA1_OUT();
	IIC1_SDAL();
	delay_us(2);
	IIC1_SCLH();
	delay_us(2);
	IIC1_SCLL();
}
void IIC2_Ack(void)
{
	IIC2_SCLL();
	SDA2_OUT();
	IIC2_SDAL();
	delay_us(2);
	IIC2_SCLH();
	delay_us(2);
	IIC2_SCLL();
}

//不产生ACK应答		    
void IIC1_NAck(void)
{
	IIC1_SCLL();
	SDA1_OUT();
	IIC1_SDAH();
	delay_us(2);
	IIC1_SCLH();
	delay_us(2);
	IIC1_SCLL();
}			
void IIC2_NAck(void)
{
	IIC2_SCLL();
	SDA2_OUT();
	IIC2_SDAH();
	delay_us(2);
	IIC2_SCLH();
	delay_us(2);
	IIC2_SCLL();
}			
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC1_Send_Byte(uint8_t txd)
{                        
    uint8_t t;   
	SDA1_OUT(); 	    
    IIC1_SCLL();//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        if((txd&0x80)>>7)
        {
            IIC1_SDAH();
        }else
        {
            IIC1_SDAL();
        }
        txd<<=1; 	  
		delay_us(2);   //对TEA5767这三个延时都是必须的
		IIC1_SCLH();
		delay_us(2); 
		IIC1_SCLL();	
		delay_us(2);
    }	 
} 	    

void IIC2_Send_Byte(uint8_t txd)
{                        
    uint8_t t;   
	SDA2_OUT(); 	    
    IIC2_SCLL();//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        if((txd&0x80)>>7)
        {
            IIC2_SDAH();
        }else
        {
            IIC2_SDAL();
        }
        txd<<=1; 	  
		delay_us(2);   //对TEA5767这三个延时都是必须的
		IIC2_SCLH();
		delay_us(2); 
		IIC2_SCLL();	
		delay_us(2);
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
uint8_t IIC1_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA1_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        IIC1_SCLL(); 
        delay_us(2);
		IIC1_SCLH();
        receive <<= 1;
        if(READ_SDA1)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        IIC1_NAck();//发送nACK
    else
        IIC1_Ack(); //发送ACK   
    return receive;
}

uint8_t IIC2_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA2_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        IIC2_SCLL(); 
        delay_us(2);
		IIC2_SCLH();
        receive <<= 1;
        if(READ_SDA2)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        IIC2_NAck();//发送nACK
    else
        IIC2_Ack(); //发送ACK   
    return receive;
}

void delay_us(uint32_t nus)
{		
    uint32_t told,tnow,tcnt=0;
	uint32_t reload=1000;				//LOAD的值	    	  					
	told=TIM4->CNT;        				//刚进入时的计数器值      
	while(1)
	{
		tnow=TIM4->CNT;	
		if(tnow!=told)
		{	    
			if(tnow > told) tcnt += tnow - told;	
			else tcnt += reload - told + tnow;	    
			told = tnow;
			if(tcnt >= nus)
                return;			//时间超过/等于要延迟的时间,则退出.
		}  
	}
}






