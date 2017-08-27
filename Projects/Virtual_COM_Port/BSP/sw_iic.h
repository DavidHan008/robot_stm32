#ifndef __SW_IIC_H
#define __SW_IIC_H


//�ӿڶ���,��ֲ����ʱ����Ҫ�����˴�
#define IIC_SCL_RCC             RCC_APB2Periph_GPIOC
#define IIC_SCL_Port            GPIOC
#define IIC_SCL_Pin             GPIO_Pin_0
#define IIC_SDA_RCC             RCC_APB2Periph_GPIOC
#define IIC_SDA_Port            GPIOC
#define IIC_SDA_Pin             GPIO_Pin_2

//д����
#define IIC_SCL_Write(x)        GPIO_WriteBit(IIC_SCL_Port,IIC_SCL_Pin,x)
#define IIC_SDA_Write(x)        GPIO_WriteBit(IIC_SDA_Port,IIC_SDA_Pin,x)

//������
#define IIC_SDA_Read()          GPIO_ReadInputDataBit(IIC_SDA_Port,IIC_SDA_Pin)

//IO��������
#define IIC_SDA_IN()            GPIO_ModeSet(IIC_SDA_Port,IIC_SDA_Pin,GPIO_Mode_IN_FLOATING)                      //{GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=8<<12;}
#define IIC_SDA_OUT()           GPIO_ModeSet(IIC_SDA_Port,IIC_SDA_Pin,GPIO_Mode_Out_PP)                   //{GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=3<<12;}

//IIC���в�������
void IIC_GPIO_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�
void IIC_Write_OneByte(u8 SlaveAddress,u8 REG_Address,u8 REG_data);
u8 IIC_Read_OneByte(u8 SlaveAddress,u8 REG_Address);
u8 IIC_Read_Bytes(u8 dev, u8 reg, u8 length, u8 *data);
u8 IIC_Write_Bytes(u8 dev, u8 reg, u8 length, u8* data);

void GPIO_ModeSet(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin,GPIOMode_TypeDef GPIO_Mode);    //�������ģʽ�ı�

#endif
















