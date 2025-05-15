#include "myiic.h"
	

//IIC��ʼ��
void IIC_Init(void)
{
    SDA1_OUT();
	SDA2_OUT();
    IIC1_SDAH();
    IIC1_SCLH();  
	IIC2_SDAH();
    IIC2_SCLH(); 
}

//����IIC��ʼ�ź�
void IIC1_Start(void)
{
	SDA1_OUT();     //sda�����
	IIC1_SDAH();	  	  
	IIC1_SCLH();
	delay_us(2);
 	IIC1_SDAL();//START:when CLK is high,DATA change form high to low 
	delay_us(2);
	IIC1_SCLL();//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  

void IIC2_Start(void)
{
	SDA2_OUT();     //sda�����
	IIC2_SDAH();	  	  
	IIC2_SCLH();
	delay_us(2);
 	IIC2_SDAL();//START:when CLK is high,DATA change form high to low 
	delay_us(2);
	IIC2_SCLL();//ǯסI2C���ߣ�׼�����ͻ�������� 
}

//����IICֹͣ�ź�
void IIC1_Stop(void)
{
	SDA1_OUT();//sda�����
	IIC1_SCLL();
	IIC1_SDAL();//STOP:when CLK is high DATA change form low to high
 	delay_us(2);
	IIC1_SCLH(); 
	delay_us(2);
	IIC1_SDAH();//����I2C���߽����ź�
	delay_us(2);							   	
}
void IIC2_Stop(void)
{
	SDA2_OUT();//sda�����
	IIC2_SCLL();
	IIC2_SDAL();//STOP:when CLK is high DATA change form low to high
 	delay_us(2);
	IIC2_SCLH(); 
	delay_us(2);
	IIC2_SDAH();//����I2C���߽����ź�
	delay_us(2);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
uint8_t IIC1_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	SDA1_IN();      //SDA����Ϊ����  
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
	IIC1_SCLL();//ʱ�����0 	   
	return 0;  
} 

uint8_t IIC2_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	SDA2_IN();      //SDA����Ϊ����  
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
	IIC2_SCLL();//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
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

//������ACKӦ��		    
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
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC1_Send_Byte(uint8_t txd)
{                        
    uint8_t t;   
	SDA1_OUT(); 	    
    IIC1_SCLL();//����ʱ�ӿ�ʼ���ݴ���
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
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
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
    IIC2_SCLL();//����ʱ�ӿ�ʼ���ݴ���
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
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		IIC2_SCLH();
		delay_us(2); 
		IIC2_SCLL();	
		delay_us(2);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
uint8_t IIC1_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA1_IN();//SDA����Ϊ����
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
        IIC1_NAck();//����nACK
    else
        IIC1_Ack(); //����ACK   
    return receive;
}

uint8_t IIC2_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA2_IN();//SDA����Ϊ����
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
        IIC2_NAck();//����nACK
    else
        IIC2_Ack(); //����ACK   
    return receive;
}

void delay_us(uint32_t nus)
{		
    uint32_t told,tnow,tcnt=0;
	uint32_t reload=1000;				//LOAD��ֵ	    	  					
	told=TIM4->CNT;        				//�ս���ʱ�ļ�����ֵ      
	while(1)
	{
		tnow=TIM4->CNT;	
		if(tnow!=told)
		{	    
			if(tnow > told) tcnt += tnow - told;	
			else tcnt += reload - told + tnow;	    
			told = tnow;
			if(tcnt >= nus)
                return;			//ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳�.
		}  
	}
}






