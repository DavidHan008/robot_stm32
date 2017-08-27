/********************   One Artisan's Regret And Pride   ***********************
*
*	@File    	�� systick.c
*	@Brief   	�� 
*	@Author  	�� admin@oarap.org
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

Systick_Data_TypeDef Systick_Data;
/*******************************************************************************
	Systick���жϴ������
********************************************************************************/
void SysTick_Handler(void)
{	
  Systick_Data.Counter++;
  if(Systick_Data.Counter > Systick_Data.LED_Period)	
  {
	Systick_Data.Counter = 0;
  }
  LED_Flash_Handler(); 
}
//=============================================================================
//��������: SYSTICK_Init
//���ܸ�Ҫ:��ʼ��SYSTICK��1us�ж�1��
//��������:��
//��������:��
//ע��    :
//SystemCoreClock/ 1000000��1us�ж�1�� 
//SystemCoreClock/ 100000:	10us�ж�һ��
//SystemCoreClock/ 10000:	100us�ж�һ��
//SystemCoreClock/ 1000��	1ms�ж�һ��   
//SystemCoreClock/ 100��	10ms�ж�һ��  
//=============================================================================
void Systick_Init(void)
{		
  while (SysTick_Config(SystemCoreClock/30));           //33.3333MS����һ��
  //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  //NVIC_SetPriority(SysTick_IRQn, 0X0F);  
  /*n=0x00~0x03 ����SystickΪ��ռ���ȼ�0  
	n=0x04~0x07 ����SystickΪ��ռ���ȼ�1  
	n=0x08~0x0B ����SystickΪ��ռ���ȼ�2  
	n=0x0C~0x0F ����SystickΪ��ռ���ȼ�3    */
  Systick_Data.LED_Period = 50;  
  Systick_Data.LED_Nagative = 2;
}
//=============================================================================
//��������: delay_us
//���ܸ�Ҫ:ÿ�ζ�ʱ1us
//��������:��
//��������:��
//ע��   :��
//=============================================================================
void Delay_us(u16 nus)
{
  u8 i;	
  while(nus--)
  {
  	i=5;
	while(i--);
  }
}
//=============================================================================
//��������: delay_ms
//���ܸ�Ҫ:ÿ�ζ�ʱ1ms
//��������:��
//��������:��
//ע��   :��
//=============================================================================
void Delay_ms( uint16_t time_ms )
{
  uint16_t i,j;
  for( i=0;i<time_ms;i++ )
  {
    for( j=0;j<10309;j++ );//��Լ1ms
  }
}



