/********************   One Artisan's Regret And Pride   ***********************
*
*	@File    	�� exti.c
*	@Brief   	�� 
*	@Author  	�� admin@oarap.org
*	@Hardware	�� STM32F103RCT6
*	@Date		�� 2017-03
*	@Description    �� �ⲿ�ж�ģ��
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

  

/*------------------------		����ң���ⲿ�ж�		--------------------------*/	
void EXTI0_IRQHandler(void)
{
  u8 Channelx = 1;
	if(EXTI_GetITStatus(Wireless_GPIO[Channelx].EXTI_Line) != RESET)
	{
		if((GPIO_ReadInputDataBit(Wireless_GPIO[Channelx].PORT,Wireless_GPIO[Channelx].PIN)))//������
		{
		  	Beep(1,20);
		}
		else
		{			       
			
		}
		EXTI_ClearITPendingBit(Wireless_GPIO[Channelx].EXTI_Line);  //���EXTIx��·����λ
	}
}
void EXTI2_IRQHandler(void)
{
  u8 Channelx = 0;
	if(EXTI_GetITStatus(Wireless_GPIO[Channelx].EXTI_Line) != RESET)
	{
		if((GPIO_ReadInputDataBit(Wireless_GPIO[Channelx].PORT,Wireless_GPIO[Channelx].PIN)))//������
		{
		  	Beep(1,20);
		}
		else
		{			       
			
		}
		EXTI_ClearITPendingBit(Wireless_GPIO[Channelx].EXTI_Line);  //���EXTIx��·����λ
	}
}

/*------------------------		������ECHO�ⲿ�ж�		--------------------------*/	
void EXTI4_IRQHandler(void)
{
  	u8 Channelx = 2;//ͨ��2��Ӧ���ⲿ�жϴ������
	if(EXTI_GetITStatus(Ultrasonic_GPIO[Channelx].ECHO_EXTI_Line) != RESET)
	{
		if((GPIO_ReadInputDataBit(Ultrasonic_GPIO[Channelx].ECHO_PORT,Ultrasonic_GPIO[Channelx].ECHO_PIN)))//������
		{
		  	TIM_Cmd(TIM2,ENABLE);  
		}
		else
		{			       
			TIM_Count[Channelx]=TIM_GetCounter(TIM2);
		}
		EXTI_ClearITPendingBit(Ultrasonic_GPIO[Channelx].ECHO_EXTI_Line);  //���EXTIx��·����λ
	}
}
void EXTI9_5_IRQHandler(void)
{
  u8 Channel[4]={0,1,4,5};//ͨ��0,1,4,5��Ӧ���ⲿ�жϴ������
  u8 x;
	for(x=0;x<4;x++)
	{
	  if(EXTI_GetITStatus(Ultrasonic_GPIO[Channel[x]].ECHO_EXTI_Line) != RESET)
	  {
		  if((GPIO_ReadInputDataBit(Ultrasonic_GPIO[Channel[x]].ECHO_PORT,Ultrasonic_GPIO[Channel[x]].ECHO_PIN)))//������
		  {
			  TIM_Cmd(TIM2,ENABLE); 
		  }
		  else
		  {			       
			  TIM_Count[Channel[x]]=TIM_GetCounter(TIM2);
		  }
		  EXTI_ClearITPendingBit(Ultrasonic_GPIO[Channel[x]].ECHO_EXTI_Line);  //���EXTIx��·����λ
	  }
	}
}
void EXTI15_10_IRQHandler(void)
{
  u8 Channel[3]={3,6,7};//ͨ��367��Ӧ���ⲿ�жϴ������
  u8 x;
	for(x=0;x<3;x++)
	{
	  if(EXTI_GetITStatus(Ultrasonic_GPIO[Channel[x]].ECHO_EXTI_Line) != RESET)
	  {
		  if((GPIO_ReadInputDataBit(Ultrasonic_GPIO[Channel[x]].ECHO_PORT,Ultrasonic_GPIO[Channel[x]].ECHO_PIN)))//������
		  {
			  TIM_Cmd(TIM2,ENABLE);   
		  }
		  else
		  {			       
			  TIM_Count[Channel[x]]=TIM_GetCounter(TIM2);
		  }
		  EXTI_ClearITPendingBit(Ultrasonic_GPIO[Channel[x]].ECHO_EXTI_Line);  //���EXTIx��·����λ
	  }
	}
}








//�ⲿ�жϳ�ʼ������
//��ʼ��PA0,PA13,PA15Ϊ�ж�����.
void EXTIX_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);	//�ر�jtag
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO,ENABLE);
	
	//init GPIOC.7	  ��������
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	
	//GPIOC.7
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource7);
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line7;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�4λ,��16��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//��ռ���ȼ�0λ,�����ȼ�4λ
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);  	
}