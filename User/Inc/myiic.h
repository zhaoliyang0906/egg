#ifndef _MYIIC_H
#define _MYIIC_H
#include "main.h"





//IO��������
#define SDA1_IN()  {T1_SDA_GPIO_Port->CRL&=0X0FFFFFFF;T1_SDA_GPIO_Port->CRL|=(uint32_t)8<<8;}	//PB2����ģʽ
#define SDA1_OUT() {T1_SDA_GPIO_Port->CRL&=0X0FFFFFFF;T1_SDA_GPIO_Port->CRL|=(uint32_t)3<<8;} //PB2���ģʽ

#define SDA2_IN()  {T2_SDA_GPIO_Port->CRH&=0X0FFFFFFF;T2_SDA_GPIO_Port->CRH|=(uint32_t)8<<12;}	//PB11����ģʽ
#define SDA2_OUT() {T2_SDA_GPIO_Port->CRH&=0X0FFFFFFF;T2_SDA_GPIO_Port->CRH|=(uint32_t)3<<12;} //PB11���ģʽ

//IO����
#define   IIC1_SCLH()      T1_SCL_GPIO_Port->BSRR = T1_SCL_Pin      
#define   IIC1_SCLL()      T1_SCL_GPIO_Port->BSRR = (T1_SCL_Pin<<16) 

#define   IIC1_SDAH()      T1_SDA_GPIO_Port->BSRR = T1_SDA_Pin      
#define   IIC1_SDAL()      T1_SDA_GPIO_Port->BSRR = (T1_SDA_Pin<<16) 


//IO����
#define   IIC2_SCLH()      T2_SCL_GPIO_Port->BSRR = T2_SCL_Pin      
#define   IIC2_SCLL()      T2_SCL_GPIO_Port->BSRR = (T2_SCL_Pin<<16) 

#define   IIC2_SDAH()      T2_SDA_GPIO_Port->BSRR = T2_SDA_Pin      
#define   IIC2_SDAL()      T2_SDA_GPIO_Port->BSRR = (T2_SDA_Pin<<16) 

#define   READ_SDA1    ((T1_SDA_GPIO_Port->IDR & T1_SDA_Pin) != (uint32_t)GPIO_PIN_RESET)?GPIO_PIN_SET:GPIO_PIN_RESET
#define   READ_SDA2    ((T2_SDA_GPIO_Port->IDR & T2_SDA_Pin) != (uint32_t)GPIO_PIN_RESET)?GPIO_PIN_SET:GPIO_PIN_RESET

#pragma pack(1)




#pragma pack()

void delay_us(uint32_t nus);
//IIC���в�������
void IIC1_Init(void);                //��ʼ��IIC��IO��				 
void IIC1_Start(void);				//����IIC��ʼ�ź�
void IIC1_Stop(void);	  			//����IICֹͣ�ź�
void IIC1_Send_Byte(uint8_t txd);			//IIC����һ���ֽ�
uint8_t IIC1_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
uint8_t IIC1_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC1_Ack(void);					//IIC����ACK�ź�
void IIC1_NAck(void);				//IIC������ACK�ź�

void IIC2_Init(void);                //��ʼ��IIC��IO��				 
void IIC2_Start(void);				//����IIC��ʼ�ź�
void IIC2_Stop(void);	  			//����IICֹͣ�ź�
void IIC2_Send_Byte(uint8_t txd);			//IIC����һ���ֽ�
uint8_t IIC2_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
uint8_t IIC2_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC2_Ack(void);					//IIC����ACK�ź�
void IIC2_NAck(void);				//IIC������ACK�ź�





#endif

