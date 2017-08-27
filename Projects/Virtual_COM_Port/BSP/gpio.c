/********************   One Artisan's Regret And Pride   ***********************
*
*	@File    	�� gpio.c
*	@Brief   	�� 
*	@Author  	�� admin@oarap.org
*	@Hardware	�� STM32F103RCT6
*	@Date		�� 2017-03
*	@Description    �� gpio���ü�����
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

/*******************************************************************************
	����LED��ʼ��
********************************************************************************/
void LED_GPIO_Config(void)
{	
    //����һ��GPIO_InitTypeDef ���͵Ľṹ��
    GPIO_InitTypeDef  GPIO_InitStructure;	
    //RCC_APB2PeriphClockCmd(LED1_GPIO_RCC|LED2_GPIO_RCC|LED3_GPIO_RCC,ENABLE);//ʹ��GPIO������ʱ��
	RCC_APB2PeriphClockCmd(LED1_GPIO_RCC,ENABLE);//ʹ��GPIO������ʱ��

    GPIO_InitStructure.GPIO_Pin =LED1_GPIO_PIN;//ѡ��Ҫ�õ�GPIO����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //��������ģʽΪ�������ģʽ						 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//���������ٶ�Ϊ50MHZ         
    GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);//���ÿ⺯������ʼ��GPIO
	
}
/*******************************************************************************
	LED��ƽ�仯����
********************************************************************************/
void LED_Flash_Handler()
{
  if(Systick_Data.Counter<Systick_Data.LED_Nagative)
  {LED1_ONOFF(Bit_RESET);}
  else 
  {
    if((Systick_Data.Counter >= Systick_Data.LED_Nagative) && (Systick_Data.Counter <= Systick_Data.LED_Period))
	{LED1_ONOFF(Bit_SET);}
    else //��������
	{Systick_Data.Counter=0;}
  }
}
/*******************************************************************************
	LED��ƽ��ת������ÿִ��һ�η�תһ�ε�ƽ��
********************************************************************************/
void LED_Toggle()
{
  static u8 mode=0;
  mode++;	
  if(mode%2==0)
   {LED1_ONOFF(Bit_SET);}
  else
	LED1_ONOFF(Bit_RESET);
}
	  
/*******************************************************************************
	���������ų�ʼ��
********************************************************************************/
void Buzz_GPIO_Config()
{
	    //����һ��GPIO_InitTypeDef ���͵Ľṹ��
    GPIO_InitTypeDef  GPIO_InitStructure;	
    //RCC_APB2PeriphClockCmd(LED1_GPIO_RCC|LED2_GPIO_RCC|LED3_GPIO_RCC,ENABLE);//ʹ��GPIO������ʱ��
	RCC_APB2PeriphClockCmd(BUZZ_GPIO_RCC,ENABLE);//ʹ��GPIO������ʱ��

    GPIO_InitStructure.GPIO_Pin =BUZZ_GPIO_PIN;//ѡ��Ҫ�õ�GPIO����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //��������ģʽΪ�������ģʽ						 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//���������ٶ�Ϊ50MHZ         
    GPIO_Init(BUZZ_GPIO_PORT, &GPIO_InitStructure);//���ÿ⺯������ʼ��GPIO
	
	BUZZ_ONOFF(Bit_RESET);
}
/*******************************************************************************
	��������������
********************************************************************************/
void Beep(u8 num,u16 time)
{
  u8 i;
	for(i=0;i<num;i++)
	{
		BUZZ_ONOFF(Bit_SET);
	  	Delay_ms(time);
	  	BUZZ_ONOFF(Bit_RESET);
		Delay_ms(time);
	}
}
void Beep_Obj_Handler(u8 *param)
{
	Beep(1,param[0]);
}