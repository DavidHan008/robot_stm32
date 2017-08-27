/********************   One Artisan's Regret And Pride   ***********************
*
*	@File    	�� sw_iic.c
*	@Brief   	�� 
*	@Author  	�� admin@oarap.org
*	@Hardware	�� STM32F103RCT6
*	@Date		�� 2017-03
*	@Description    �� ���ģ��IIC����������
*	@History	�� 
*
*	Rev1.0 
*		Date��2017
*		Author��Blade
*		Modification��
*
*--------------------Copyright (C) oarap.org 2016------------------------------
*----------------------All rights reserved-------------------------------------
*
********************          һ���������ź��뽾��          ********************/

#include "Sys_Conf.h"


//ģʽ���ú��������ö˿ڵ�������������
void GPIO_ModeSet(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin,GPIOMode_TypeDef GPIO_Mode)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin;//ѡ��Ҫ�õ�GPIO����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode; //��������ģʽΪ�������ģʽ						 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//���������ٶ�Ϊ50MHZ         
  GPIO_Init(GPIOx, &GPIO_InitStructure);//���ÿ⺯������ʼ��GPIO
}

//��ʼ��IIC
void IIC_GPIO_Init(void)
{					     
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(IIC_SCL_RCC | IIC_SDA_RCC, ENABLE );	
  
  GPIO_InitStructure.GPIO_Pin = IIC_SCL_Pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(IIC_SCL_Port, &GPIO_InitStructure);
  GPIO_SetBits(IIC_SCL_Port,IIC_SCL_Pin); 	
  
  GPIO_InitStructure.GPIO_Pin = IIC_SDA_Pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(IIC_SDA_Port, &GPIO_InitStructure);
  GPIO_SetBits(IIC_SDA_Port,IIC_SDA_Pin); 
  
}
//����IIC��ʼ�ź�
void IIC_Start(void)
{
  IIC_SDA_OUT();     //sda�����
  IIC_SDA_Write(Bit_SET);	  	  
  IIC_SCL_Write(Bit_SET);
  Delay_us(4);
  IIC_SDA_Write(Bit_RESET);//START:when CLK is high,DATA change form high to low 
  Delay_us(4);
  IIC_SCL_Write(Bit_RESET);//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void IIC_Stop(void)
{
  IIC_SDA_OUT();//sda�����
  IIC_SCL_Write(Bit_RESET);
  IIC_SDA_Write(Bit_RESET);//STOP:when CLK is high DATA change form low to high
  Delay_us(4);
  IIC_SCL_Write(Bit_SET); 
  IIC_SDA_Write(Bit_SET);//����I2C���߽����ź�
  Delay_us(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
  u8 ucErrTime=0;
  IIC_SDA_IN();      //SDA����Ϊ����  
  IIC_SDA_Write(Bit_SET);Delay_us(1);	   
  IIC_SCL_Write(Bit_SET);Delay_us(1);	 
  while(IIC_SDA_Read())
  {
    ucErrTime++;
    if(ucErrTime>250)
    {
      IIC_Stop();
      return 1;
    }
  }
  IIC_SCL_Write(Bit_RESET);//ʱ�����0 	   
  return 0;  
} 
//����ACKӦ��
void IIC_Ack(void)
{
  IIC_SCL_Write(Bit_RESET);
  IIC_SDA_OUT();
  IIC_SDA_Write(Bit_RESET);
  Delay_us(2);
  IIC_SCL_Write(Bit_SET);
  Delay_us(2);
  IIC_SCL_Write(Bit_RESET);
}
//������ACKӦ��		    
void IIC_NAck(void)
{
  IIC_SCL_Write(Bit_RESET);
  IIC_SDA_OUT();
  IIC_SDA_Write(Bit_SET);
  Delay_us(2);
  IIC_SCL_Write(Bit_SET);
  Delay_us(2);
  IIC_SCL_Write(Bit_RESET);
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte(u8 txd)
{                        
  u8 t;   
  IIC_SDA_OUT(); 	    
  IIC_SCL_Write(Bit_RESET);//����ʱ�ӿ�ʼ���ݴ���
  for(t=0;t<8;t++)
  {              
    if(((txd&0x80)>>7))
      IIC_SDA_Write(Bit_SET);
    else
      IIC_SDA_Write(Bit_RESET);
    txd<<=1; 	  
    Delay_us(2);   //��TEA5767��������ʱ���Ǳ����
    IIC_SCL_Write(Bit_SET);
    Delay_us(2); 
    IIC_SCL_Write(Bit_RESET);	
    Delay_us(2);
  }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
  unsigned char i,receive=0;
  IIC_SDA_IN();//SDA����Ϊ����
  for(i=0;i<8;i++ )
  {
    IIC_SCL_Write(Bit_RESET); 
    Delay_us(2);
    IIC_SCL_Write(Bit_SET);
    receive<<=1;
    if(IIC_SDA_Read())receive++;   
    Delay_us(1); 
  }					 
  if (!ack)
    IIC_NAck();//����nACK
  else
    IIC_Ack(); //����ACK   
  return receive;
}


/*------------------------      MPU9250         ------------------------*/
//**************************************
//��I2C�豸д��һ���ֽ�����
//**************************************
void IIC_Write_OneByte(u8 SlaveAddress,u8 REG_Address,u8 REG_data)
{
  IIC_Start();                   //��ʼ�ź�
  IIC_Send_Byte(SlaveAddress);   //�����豸��ַ+д�ź�
  IIC_Wait_Ack();	   
  IIC_Send_Byte(REG_Address);    //�ڲ��Ĵ�����ַ
  IIC_Wait_Ack(); 	 										  		   
  IIC_Send_Byte(REG_data);       //�ڲ��Ĵ�������
  IIC_Wait_Ack(); 	 										  		   
  IIC_Stop();                    //����ֹͣ�ź�
}
//**************************************
//��I2C�豸��ȡһ���ֽ�����
//**************************************
u8 IIC_Read_OneByte(u8 SlaveAddress,u8 REG_Address)
{
  u8 REG_data;
  IIC_Start();                  //��ʼ�ź�
  IIC_Send_Byte(SlaveAddress);  //�����豸��ַ+д�ź�
  REG_data=IIC_Wait_Ack();	   
  IIC_Send_Byte(REG_Address);   //���ʹ洢��Ԫ��ַ����0��ʼ
  REG_data=IIC_Wait_Ack();	   
  IIC_Start();                  //��ʼ�ź�
  IIC_Send_Byte(SlaveAddress+1);//�����豸��ַ+���ź�
  REG_data=IIC_Wait_Ack();	   
  REG_data=IIC_Read_Byte(0);		//��ȡһ���ֽ�,�������ٶ�,����NAK,�����Ĵ�������
  IIC_Stop();	                  //ֹͣ�ź�
  return REG_data;
}


/*------------------------      JY_901         ------------------------*/
/**************************ʵ�ֺ���********************************************
*����ԭ��:		u8 IICreadBytes(u8 dev, u8 reg, u8 length, u8 *data)
*��������:	    ��ȡָ���豸 ָ���Ĵ����� length��ֵ
����	dev  Ŀ���豸��ַ
reg	  �Ĵ�����ַ
length Ҫ�����ֽ���
*data  ���������ݽ�Ҫ��ŵ�ָ��
����   ���������ֽ�����
*******************************************************************************/ 
u8 IIC_Read_Bytes(u8 dev, u8 reg, u8 length, u8 *data)
{
  u8 count = 0;
  
  IIC_Start();
  IIC_Send_Byte((dev<<1));	   //����д����
  IIC_Wait_Ack();
  IIC_Send_Byte(reg);               //���͵�ַ
  IIC_Wait_Ack();	  
  IIC_Start();
  IIC_Send_Byte(((dev<<1)+1));       //�������ģʽ	
  IIC_Wait_Ack();
  
  for(count=0;count<length;count++){
    
    if(count!=length-1)
      data[count]=IIC_Read_Byte(1);  //��ACK�Ķ�����
    else  
      data[count]=IIC_Read_Byte(0);	 //���һ���ֽ�NACK
  }
  IIC_Stop();//����һ��ֹͣ����
  return count;
}

/**************************ʵ�ֺ���********************************************
*����ԭ��:		u8 IICwriteBytes(u8 dev, u8 reg, u8 length, u8* data)
*��������:	    ������ֽ�д��ָ���豸 ָ���Ĵ���
����	dev  Ŀ���豸��ַ
		reg	  �Ĵ�����ַ
		length Ҫд���ֽ���
		*data  ��Ҫд�����ݵ��׵�ַ
����   �����Ƿ�ɹ�
*******************************************************************************/ 
u8 IIC_Write_Bytes(u8 dev, u8 reg, u8 length, u8* data)
{
  
 	u8 count = 0;
	IIC_Start();
	IIC_Send_Byte(dev<<1);	   //����д����
	IIC_Wait_Ack();
	IIC_Send_Byte(reg);   //���͵�ַ
	IIC_Wait_Ack();	  
	for(count=0;count<length;count++){
		IIC_Send_Byte(data[count]); 
		IIC_Wait_Ack(); 
 }
	IIC_Stop();//����һ��ֹͣ����

    return 1; //status == 0;
	
}










