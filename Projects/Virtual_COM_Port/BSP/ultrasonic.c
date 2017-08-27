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


//extern u8 Obstacle_Weight_Buf[];
extern u8 Obstacle_Weight[];//�ȣ��ϰ��﷽��Ȩ��
extern u16 Distance_Sum[];//���ϰ������

Ultrasonic_GPIO_TypeDef Ultrasonic_GPIO[NUM_OF_ULTRASONIC];

void Ultrasonic_GPIO_Struct_Init()
{
  Ultrasonic_GPIO[0].TRIG_PORT				= GPIOB;
  Ultrasonic_GPIO[0].TRIG_PIN					= GPIO_Pin_7;
  Ultrasonic_GPIO[0].ECHO_PORT				= GPIOB;
  Ultrasonic_GPIO[0].ECHO_PIN					= GPIO_Pin_8;
  Ultrasonic_GPIO[0].ECHO_GPIO_PortSourceGPIO	= GPIO_PortSourceGPIOB;
  Ultrasonic_GPIO[0].ECHO_GPIO_PinSource		= GPIO_PinSource8;
  Ultrasonic_GPIO[0].ECHO_EXTI_Line			= EXTI_Line8;
  Ultrasonic_GPIO[0].ECHO_EXTI_IRQn			= EXTI9_5_IRQn;
  
  Ultrasonic_GPIO[1].TRIG_PORT				= GPIOB;
  Ultrasonic_GPIO[1].TRIG_PIN					= GPIO_Pin_5;
  Ultrasonic_GPIO[1].ECHO_PORT				= GPIOB;
  Ultrasonic_GPIO[1].ECHO_PIN					= GPIO_Pin_6;
  Ultrasonic_GPIO[1].ECHO_GPIO_PortSourceGPIO	= GPIO_PortSourceGPIOB;
  Ultrasonic_GPIO[1].ECHO_GPIO_PinSource		= GPIO_PinSource6;
  Ultrasonic_GPIO[1].ECHO_EXTI_Line			= EXTI_Line6;
  Ultrasonic_GPIO[1].ECHO_EXTI_IRQn			= EXTI9_5_IRQn;
  
  Ultrasonic_GPIO[2].TRIG_PORT				= GPIOB;
  Ultrasonic_GPIO[2].TRIG_PIN					= GPIO_Pin_3;
  Ultrasonic_GPIO[2].ECHO_PORT				= GPIOB;
  Ultrasonic_GPIO[2].ECHO_PIN					= GPIO_Pin_4;
  Ultrasonic_GPIO[2].ECHO_GPIO_PortSourceGPIO	= GPIO_PortSourceGPIOB;
  Ultrasonic_GPIO[2].ECHO_GPIO_PinSource		= GPIO_PinSource4;
  Ultrasonic_GPIO[2].ECHO_EXTI_Line			= EXTI_Line4;
  Ultrasonic_GPIO[2].ECHO_EXTI_IRQn			= EXTI4_IRQn;
  
  Ultrasonic_GPIO[3].TRIG_PORT				= GPIOA;		        
  Ultrasonic_GPIO[3].TRIG_PIN					= GPIO_Pin_8;         
  Ultrasonic_GPIO[3].ECHO_PORT				= GPIOA;		        
  Ultrasonic_GPIO[3].ECHO_PIN					= GPIO_Pin_15;	        
  Ultrasonic_GPIO[3].ECHO_GPIO_PortSourceGPIO	= GPIO_PortSourceGPIOA;
  Ultrasonic_GPIO[3].ECHO_GPIO_PinSource		= GPIO_PinSource15;
  Ultrasonic_GPIO[3].ECHO_EXTI_Line			= EXTI_Line15;		
  Ultrasonic_GPIO[3].ECHO_EXTI_IRQn			= EXTI15_10_IRQn;
  
  Ultrasonic_GPIO[4].TRIG_PORT				= GPIOC;		        
  Ultrasonic_GPIO[4].TRIG_PIN					= GPIO_Pin_8;         
  Ultrasonic_GPIO[4].ECHO_PORT				= GPIOC;		        
  Ultrasonic_GPIO[4].ECHO_PIN					= GPIO_Pin_9;	        
  Ultrasonic_GPIO[4].ECHO_GPIO_PortSourceGPIO	= GPIO_PortSourceGPIOC;
  Ultrasonic_GPIO[4].ECHO_GPIO_PinSource		= GPIO_PinSource9;
  Ultrasonic_GPIO[4].ECHO_EXTI_Line			= EXTI_Line9;			
  Ultrasonic_GPIO[4].ECHO_EXTI_IRQn			= EXTI9_5_IRQn;
  
  Ultrasonic_GPIO[5].TRIG_PORT				= GPIOC;		        
  Ultrasonic_GPIO[5].TRIG_PIN					= GPIO_Pin_6;          
  Ultrasonic_GPIO[5].ECHO_PORT				= GPIOC;		        
  Ultrasonic_GPIO[5].ECHO_PIN					= GPIO_Pin_7;	        
  Ultrasonic_GPIO[5].ECHO_GPIO_PortSourceGPIO	= GPIO_PortSourceGPIOC;
  Ultrasonic_GPIO[5].ECHO_GPIO_PinSource		= GPIO_PinSource7;
  Ultrasonic_GPIO[5].ECHO_EXTI_Line			= EXTI_Line7;			
  Ultrasonic_GPIO[5].ECHO_EXTI_IRQn			= EXTI9_5_IRQn;
  
  Ultrasonic_GPIO[6].TRIG_PORT				= GPIOB;	        
  Ultrasonic_GPIO[6].TRIG_PIN					= GPIO_Pin_13;          
  Ultrasonic_GPIO[6].ECHO_PORT				= GPIOB;		        
  Ultrasonic_GPIO[6].ECHO_PIN					= GPIO_Pin_12;	        
  Ultrasonic_GPIO[6].ECHO_GPIO_PortSourceGPIO	= GPIO_PortSourceGPIOB;
  Ultrasonic_GPIO[6].ECHO_GPIO_PinSource		= GPIO_PinSource12;
  Ultrasonic_GPIO[6].ECHO_EXTI_Line			= EXTI_Line12; 		
  Ultrasonic_GPIO[6].ECHO_EXTI_IRQn			= EXTI15_10_IRQn;
  
  Ultrasonic_GPIO[7].TRIG_PORT				= GPIOB;		        
  Ultrasonic_GPIO[7].TRIG_PIN					= GPIO_Pin_15;          
  Ultrasonic_GPIO[7].ECHO_PORT				= GPIOB;		        
  Ultrasonic_GPIO[7].ECHO_PIN					= GPIO_Pin_14;	        
  Ultrasonic_GPIO[7].ECHO_GPIO_PortSourceGPIO	= GPIO_PortSourceGPIOB;
  Ultrasonic_GPIO[7].ECHO_GPIO_PinSource		= GPIO_PinSource14;
  Ultrasonic_GPIO[7].ECHO_EXTI_Line			= EXTI_Line14;			
  Ultrasonic_GPIO[7].ECHO_EXTI_IRQn			= EXTI15_10_IRQn;
  
}
void Ultrasonic_GPIO_Configuration(void)
{
  u8 i;
  GPIO_InitTypeDef GPIO_InitStructure;	
  EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  
  Ultrasonic_GPIO_Struct_Init();
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);	//�ر�jtag(PB3.PB4)
  //1.1�汾��Ӳ��������Ҫ����SWD�˿ڣ���Ϊû��ʹ��SWD�˿�
  //ͨ��AFIO_EXTICRx����GPIO���ϵ��ⲿ�ж�/�¼���������ʹ��AFIOʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO , ENABLE);////////////////////
  for(i=0;i<NUM_OF_ULTRASONIC;i++)
  {
	//���
	GPIO_InitStructure.GPIO_Pin = Ultrasonic_GPIO[i].TRIG_PIN;					 //TRIG
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		     //��Ϊ�������ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	         
	GPIO_Init(Ultrasonic_GPIO[i].TRIG_PORT, &GPIO_InitStructure);	                 //��ʼ������GPIO 
	
	//����
	GPIO_InitStructure.GPIO_Pin = Ultrasonic_GPIO[i].ECHO_PIN;				     //ECH0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;		 //��Ϊ����
	GPIO_Init(Ultrasonic_GPIO[i].ECHO_PORT,&GPIO_InitStructure);						 //��ʼ��GPIO
	
	GPIO_EXTILineConfig(Ultrasonic_GPIO[i].ECHO_GPIO_PortSourceGPIO,Ultrasonic_GPIO[i].ECHO_GPIO_PinSource);
	
	EXTI_InitStructure.EXTI_Line = Ultrasonic_GPIO[i].ECHO_EXTI_Line;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;///////////////////˫�������ش�����ʽ
	EXTI_InitStructure.EXTI_LineCmd = DISABLE;////////////////////////////
	EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���	
	
	NVIC_InitStructure.NVIC_IRQChannel = Ultrasonic_GPIO[i].ECHO_EXTI_IRQn;//EXTI9_5_IRQn;			//ʹ�����ڵ��ⲿ�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//��ռ���ȼ�2 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;					//�����ȼ�2 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
  }
  
}

void Obstacle_Scan()//�ϰ�����
{//�������ڲ�࣬�������޸������ޣ��İ�״̬
  static u8 Obstacle_Weight_Buf[2];
  if(Ultrasonic_Distance[0] > WINDOW_UPPER_VALUE - 15)	  	Obstacle_Weight_Buf[LEFT]  &= ~BIT[0];	//Ȩ��1 
  if(Ultrasonic_Distance[1] > WINDOW_UPPER_VALUE)	  		Obstacle_Weight_Buf[LEFT]  &= ~BIT[1];	//Ȩ��2
  if(Ultrasonic_Distance[2] > WINDOW_UPPER_VALUE)	  		Obstacle_Weight_Buf[LEFT]  &= ~BIT[2];	//Ȩ��3
  if(Ultrasonic_Distance[3] > WINDOW_UPPER_VALUE)	  		Obstacle_Weight_Buf[LEFT]  &= ~BIT[3];	//Ȩ��4
  if(Ultrasonic_Distance[4] > WINDOW_UPPER_VALUE)	  		Obstacle_Weight_Buf[RIGHT] &= ~BIT[3];	//Ȩ��4
  if(Ultrasonic_Distance[5] > WINDOW_UPPER_VALUE)	  		Obstacle_Weight_Buf[RIGHT] &= ~BIT[2];	//Ȩ��3
  if(Ultrasonic_Distance[6] > WINDOW_UPPER_VALUE)	  		Obstacle_Weight_Buf[RIGHT] &= ~BIT[1];	//Ȩ��2
  if(Ultrasonic_Distance[7] > WINDOW_UPPER_VALUE - 15)	  	Obstacle_Weight_Buf[RIGHT] &= ~BIT[0];	//Ȩ��1
  
  if(Ultrasonic_Distance[0] < WINDOW_FLOOR_VALUE - 15)	 	Obstacle_Weight_Buf[LEFT]  |=  BIT[0];	 
  if(Ultrasonic_Distance[1] < WINDOW_FLOOR_VALUE)	  		Obstacle_Weight_Buf[LEFT]  |=  BIT[1];
  if(Ultrasonic_Distance[2] < WINDOW_FLOOR_VALUE)	  		Obstacle_Weight_Buf[LEFT]  |=  BIT[2];
  if(Ultrasonic_Distance[3] < WINDOW_FLOOR_VALUE)	  		Obstacle_Weight_Buf[LEFT]  |=  BIT[3];
  if(Ultrasonic_Distance[4] < WINDOW_FLOOR_VALUE)	  		Obstacle_Weight_Buf[RIGHT] |=  BIT[3];
  if(Ultrasonic_Distance[5] < WINDOW_FLOOR_VALUE)	  		Obstacle_Weight_Buf[RIGHT] |=  BIT[2];
  if(Ultrasonic_Distance[6] < WINDOW_FLOOR_VALUE)	  		Obstacle_Weight_Buf[RIGHT] |=  BIT[1];
  if(Ultrasonic_Distance[7] < WINDOW_FLOOR_VALUE - 15)	  	Obstacle_Weight_Buf[RIGHT] |=  BIT[0];
  
  u8 Buf = 0;
  u8 i;
  for(i=0;i<4;i++)
  {
	if(Obstacle_Weight_Buf[LEFT]&BIT[i]) 
	{
	  Buf += 7; 
	}
  }
  Obstacle_Weight[LEFT] = Buf;//����������ʽ������Ȩ�ص���ʽ��ÿ����������Ϊͬ����Ȩ��
  Buf = 0;
  for(i=0;i<4;i++)
  {
	if(Obstacle_Weight_Buf[RIGHT]&BIT[i]) 
	{
	  Buf +=7; 
	}
	else
	{
	}
  }
  Obstacle_Weight[RIGHT] = Buf;//����������ʽ������Ȩ�ص���ʽ��ÿ����������Ϊͬ����Ȩ��
  Buf = 0;
  
  //���������ϰ���ľ����
  Distance_Sum[LEFT]=0;
  Distance_Sum[RIGHT]=0;
  for(i=0;i<4;i++)
  {
	Distance_Sum[LEFT]+=Ultrasonic_Distance[i];
  }
  for(i=4;i<8;i++)
  {
	Distance_Sum[RIGHT]+=Ultrasonic_Distance[i];
  }
}

