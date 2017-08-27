/********************   One Artisan's Regret And Pride   ***********************
*
*	@File    	�� usart.c
*	@Brief   	�� 
*	@Author  	�� Blade@oarap.org
*	@Hardware	�� STM32F103RCT6
*	@Date		�� 2016-05
*	@Description�� 
*	@History	�� 
*
*	Rev1.0 
*		Date��2016-05-16
*		Author��Blade
*		Modification��
*
*--------------------Copyright (C) oarap.org 2016------------------------------
*----------------------All rights reserved-------------------------------------
*
********************          һ���������ź��뽾��          ********************/

#include "Sys_Conf.h"

USART_Data_TypDef USART_Data;//����USART���ݵĽṹ��

void USART1_Config(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;	
  USART_InitTypeDef USART_InitStructure;  //���崮�ڳ�ʼ���ṹ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);//��ӳ��
  //GPIO_PinRemapConfig(GPIO_Remap_USART1,ENABLE);//��ӳ��
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  //����ͨѶ��������
  USART_InitStructure.USART_BaudRate = USART1_Baud;//9600; //������
  USART_InitStructure.USART_WordLength = USART_WordLength_8b; //����λ8λ
  USART_InitStructure.USART_StopBits = USART_StopBits_1;	//ֹͣλ1λ
  USART_InitStructure.USART_Parity = USART_Parity_No;		//У��λ ��
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��������
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;		//ʹ�ܽ��պͷ�������
  //�����ϸ���ֵ�Ľṹ�����⺯��USART_Init���г�ʼ��
  USART_Init(USART1, &USART_InitStructure); 
  USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//ʹ�ܴ����жϽ���
  //USART_ITConfig(USART1,USART_IT_TXE,ENABLE);//ʹ�ܴ����жϽ���//////////////////////
  USART_Cmd(USART1, ENABLE);//����USART1��ע��������RCC_APB2PeriphClockCmd()���õ�����
}

void USART2_Config(void)
{	
  GPIO_InitTypeDef GPIO_InitStructure;	
  USART_InitTypeDef USART_InitStructure;  //���崮�ڳ�ʼ���ṹ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
  
  /**********************   ȫ˫��   ********************/
  //USART2_TX ->PA2			
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	       //ѡ�д���Ĭ������ܽ�         
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�������������� 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//����ܽ�2��ģʽ  
  GPIO_Init(GPIOA, &GPIO_InitStructure);           //���ú������ѽṹ�����������г�ʼ��		   
  
  //USART2_RX ->PA3
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	        
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /**********************   ��˫��   ********************/
  /*GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	       //ѡ�д���Ĭ������ܽ�    
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;  //�������������� 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//����ܽ�2��ģʽ  
  GPIO_Init(GPIOA, &GPIO_InitStructure);           //���ú������ѽṹ�����������г�ʼ��
  GPIO_SetBits(GPIOA,GPIO_Pin_2);*/
  
  /*����ͨѶ��������*/
  USART_InitStructure.USART_BaudRate = USART2_Baud; //������
  USART_InitStructure.USART_WordLength = USART_WordLength_8b; //����λ8λ
  USART_InitStructure.USART_StopBits = USART_StopBits_1;	//ֹͣλ1λ
  USART_InitStructure.USART_Parity = USART_Parity_No;		//У��λ ��
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��������
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;		//ʹ�ܽ��պͷ�������
  USART_Init(USART2, &USART_InitStructure); 
  
  USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);//ʹ�ܴ����жϽ���
  USART_Cmd(USART2, ENABLE);//����USART1��ע��������RCC_APB2PeriphClockCmd()���õ�����	/****************----        ��˫��ģʽ����ע�⣡      ---*******************/
  
  /**********************   ��˫��   ********************/
  //USART_HalfDuplexCmd(USART2,ENABLE); 
}

void USART3_Config(void)
{	
  GPIO_InitTypeDef GPIO_InitStructure;	
  USART_InitTypeDef USART_InitStructure;  //���崮�ڳ�ʼ���ṹ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
  
  /*USART3_TX ->PB10*/			
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	       //ѡ�д���Ĭ������ܽ�         
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�������������� 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//����ܽ�9��ģʽ  
  GPIO_Init(GPIOB, &GPIO_InitStructure);           //���ú������ѽṹ�����������г�ʼ��		   
  /*USART3_RX ->PB11*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	        
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  /*����ͨѶ��������*/
  USART_InitStructure.USART_BaudRate = USART3_Baud; //������
  USART_InitStructure.USART_WordLength = USART_WordLength_8b; //����λ8λ
  USART_InitStructure.USART_StopBits = USART_StopBits_1;	//ֹͣλ1λ
  USART_InitStructure.USART_Parity = USART_Parity_No;		//У��λ ��
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��������
  USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;		//ʹ�ܽ��պͷ�������
  
  USART_Init(USART3, &USART_InitStructure); 
  USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);//ʹ�ܴ����жϽ���
  USART_Cmd(USART3, ENABLE);//����USART3��ע��������RCC_APB2PeriphClockCmd()���õ�����
}

void UART4_Config(void)
{	
  GPIO_InitTypeDef GPIO_InitStructure;	
  USART_InitTypeDef USART_InitStructure;  //���崮�ڳ�ʼ���ṹ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
  /*UART4_TX ->PC10*/			
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	   //ѡ�д���Ĭ������ܽ�         
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�������������� 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//����ܽ�9��ģʽ  
  GPIO_Init(GPIOC, &GPIO_InitStructure);           //���ú������ѽṹ�����������г�ʼ��		   
  /*UART4_RX ->Pc11*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	        
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  /*����ͨѶ��������*/
  USART_InitStructure.USART_BaudRate = UART4_Baud; //������
  USART_InitStructure.USART_WordLength = USART_WordLength_8b; //����λ8λ
  USART_InitStructure.USART_StopBits = USART_StopBits_1;	//ֹͣλ1λ
  USART_InitStructure.USART_Parity = USART_Parity_No;		//У��λ ��
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��������
  USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;		//ʹ�ܽ��պͷ�������
  //�����ϸ���ֵ�Ľṹ�����⺯��UART_Init���г�ʼ��
  USART_Init(UART4, &USART_InitStructure); 
  USART_ITConfig(UART4,USART_IT_RXNE,ENABLE);//ʹ�ܴ����жϽ���
  USART_Cmd(UART4, ENABLE);//����UART5��ע��������RCC_APB2PeriphClockCmd()���õ�����
}
void UART5_Config(void)
{	
  GPIO_InitTypeDef GPIO_InitStructure;	
  USART_InitTypeDef USART_InitStructure;  //���崮�ڳ�ʼ���ṹ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);
  
  /*UART5_TX ->PC12*/			
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	   //ѡ�д���Ĭ������ܽ�         
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�������������� 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//����ܽ�9��ģʽ  
  GPIO_Init(GPIOC, &GPIO_InitStructure);           //���ú������ѽṹ�����������г�ʼ��		   
  /*UART5_RX ->PD2*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	        
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  /*����ͨѶ��������*/
  USART_InitStructure.USART_BaudRate = UART5_Baud;//9600; //������
  USART_InitStructure.USART_WordLength = USART_WordLength_8b; //����λ8λ
  USART_InitStructure.USART_StopBits = USART_StopBits_1;	//ֹͣλ1λ
  USART_InitStructure.USART_Parity = USART_Parity_No;		//У��λ ��
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��������
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;		//ʹ�ܽ��պͷ�������
  //�����ϸ���ֵ�Ľṹ�����⺯��UART_Init���г�ʼ��
  USART_Init(UART5, &USART_InitStructure); 
  USART_ITConfig(UART5,USART_IT_RXNE,ENABLE);//ʹ�ܴ����жϽ���
  USART_Cmd(UART5, ENABLE);//����UART5��ע��������RCC_APB2PeriphClockCmd()���õ�����
}
void USART_NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure; 
  /* Configure the NVIC Preemption Priority Bits */  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  
  /* Enable the USARTy Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;	 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;	 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;	 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;	 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}


/*void USART1_IRQHandler(void)
{
if(USART_GetFlagStatus(USART1, USART_IT_RXNE) != RESET)
{
	}
USART_ClearITPendingBit(USART1, USART_IT_RXNE);
}*/

void USART2_IRQHandler(void)
{
  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
  {
	JY_901_USART_Data_RX_Handler(AHRS_USART->DR);
	USART_ClearITPendingBit(USART2, USART_IT_RXNE);
  }
  USART_ClearITPendingBit(USART2, USART_IT_RXNE);
  //USART_ClearITPendingBit(USART2,USART_IT_ORE);
}

void USART3_IRQHandler(void)
{	
  if(USART_GetFlagStatus(USART3, USART_IT_RXNE) != RESET)
  {
	RMDS_USART_Data_RX_Handler(RMDS_USART->DR);
	USART_ClearITPendingBit(USART3, USART_IT_RXNE);
  }
  USART_ClearITPendingBit(USART3, USART_IT_RXNE);
}
void UART4_IRQHandler(void)
{	
  if(USART_GetFlagStatus(UART4, USART_IT_RXNE) != RESET)
  {
	Bluetooth_USART_Data_RX_Handler(BT_USART->DR);
	USART_ClearITPendingBit(UART4, USART_IT_RXNE);
  }
  USART_ClearITPendingBit(UART4, USART_IT_RXNE);
}  
void UART5_IRQHandler(void)
{	
  if(USART_GetFlagStatus(UART5, USART_IT_RXNE) != RESET)
  {
	//UART5_USART_Data_RX_Handler(UART5->DR);
	USART_ClearITPendingBit(UART5, USART_IT_RXNE);
  }
  USART_ClearITPendingBit(UART5, USART_IT_RXNE);
}  


void USART_Data_Struct_Init()
{
  USART_Data.USB.Flag = FALSE;
  USART_Data.USB.Pointer = 0;
  USART_Data.USB.Descrip = USB_DESCRIP;
  
  
  USART_Data.BT.Flag = FALSE;
  USART_Data.BT.Pointer = 0;
  USART_Data.BT.Descrip = BT_DESCRIP;
  
  USART_Data.RMDS.Flag = FALSE;
  USART_Data.RMDS.Pointer = 0;
  USART_Data.RMDS.Descrip = RMDS_DESCRIP;
  
  USART_Data.AHRS.Flag = FALSE;
  USART_Data.AHRS.Pointer = 0;
  USART_Data.AHRS.Descrip = AHRS_DESCRIP;
}
//=============================================================================
//���ܸ�Ҫ:��ָ����USART�������ݲ��һ��еȴ����ܣ�������Ϻ��Զ���ձ�־λ
//=============================================================================
void USART_Send(USART_TypeDef* USARTx,u16 data)
{
  USART_SendData(USARTx,data);
  while(USART_GetFlagStatus(USARTx,USART_FLAG_TC) !=SET);//�ȴ���������жϱ�־λ	
  USART_ClearFlag(USARTx,USART_FLAG_TC);
}

//����ָ�����ȵ�����
void USART_Send_Assign(USART_TypeDef* USARTx,u8 *data,u8 Data_Len)
{
  while(Data_Len--)
  {
	USART_SendData(USARTx,*data++);
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) !=SET); //XE
	USART_ClearFlag(USARTx,USART_FLAG_TC);
  }
}
//�����ַ���
void USART_Send_Str(USART_TypeDef* USARTx,u8 *str)
{
  u8 i=0;
  while(str[i]!='\0')
  {
	USART_Send(USARTx,str[i]);
	i++;
  }
}