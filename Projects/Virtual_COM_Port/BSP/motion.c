/********************   One Artisan's Regret And Pride   ***********************
*
*	@File    	�� ahrs.c
*	@Brief   	�� 
*	@Author  	�� admin@oarap.org
*	@Hardware	�� STM32F103RCT6
*	@Date		�� 2017-03
*	@Description    �� ���Ե�ԪMPU9250+JY901 ��ahrs
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

Motion_Data_Typdef Motion_Data;


/*******************************************************************************
	�˶����ݳ�ʼ��
********************************************************************************/
void Motion_Data_Init()
{//�˶����ݳ�ʼ��
  	Motion_Data.Control.Update_Flag = FALSE;
	Motion_Data.Control.Enable_Flag = FALSE;
	Motion_Data.Control.PWM_Limit = 5000;
}
/*******************************************************************************
	��λ��ָ�ʱ��⣨��RTC�ж��б����ã�
********************************************************************************/
void Motion_Control_Data_Time_Out_Check_Handler()
{
  if (!Motion_Data.Control.Update_Flag)//1sʱ����û�յ�������ֹͣ�˶���
  {
    Motion_Data.Control.Motor_Ang_Vel[LEFT]  = 0;
    Motion_Data.Control.Motor_Ang_Vel[RIGHT] = 0;
  }
  Motion_Data.Control.Update_Flag = FALSE;
}
/*******************************************************************************
	�˶����ƶ���Ĵ��������ros�������ݺ���ܱ����ã�
********************************************************************************/
void Motion_Control_Obj_Handler(u8 *param)
{
	Motion_Data.Control.Motor_Ang_Vel[LEFT]  =  (param[0]<<8 | param[1]);
	Motion_Data.Control.Motor_Ang_Vel[RIGHT] =  (param[2]<<8 | param[3]);
	/*Motion_Data.Control.Motor_Ang_Vel[LEFT] /= 100;
	Motion_Data.Control.Motor_Ang_Vel[RIGHT] /=  100;*/
	Motion_Data.Control.Update_Flag = TRUE;
}
/*******************************************************************************
	�˶��������ݵķ��ͣ����͸���������
********************************************************************************/
void Motion_Control_Data_Send()
{ //�˶��������ݷ��ͣ��������㣩 
  //if(Motion_Data.Control.Enable_Flag)   
	  RMDS_Vel_Send_Arg(1,Motion_Data.Control.PWM_Limit,Motion_Data.Control.Motor_Ang_Vel[LEFT]);
	  Delay_ms(1);              
	  RMDS_Vel_Send_Arg(2,Motion_Data.Control.PWM_Limit,Motion_Data.Control.Motor_Ang_Vel[RIGHT]);
	  Delay_ms(1); 
	  
	  //��ֹ���
	  if((abs_s32(Motion_Data.Status.Pos[LEFT])  >= MAX_POSITIVE_POS) || 
		 (abs_s32(Motion_Data.Status.Pos[RIGHT]) >= MAX_POSITIVE_POS))
	  {
		Motion_Data.Status.Motor_Ang_Vel[LEFT] [0] = 0;
		Motion_Data.Status.Motor_Ang_Vel[RIGHT][0] = 0;
		
		RMDS_Init(RMDS_VEL_MODE);
		Delay_ms(500);
	  }
}
/*******************************************************************************
	�˶�״̬���ݵĶ�ȡ
********************************************************************************/
void Motion_Status_Data_Read()
{//�˶�״̬���ݶ�ȡ���������㣩
  RMDS_Get_Status(1);
  Delay_ms(3);
  RMDS_Get_Status(2);
  Delay_ms(3);
}
/*******************************************************************************
	�˶����ٶȵ�ƽ��ֵ����
********************************************************************************/
void Motor_Ang_Vel_Average_Calculate()
{
  	u8 i;
	s32 buf=0;
	for(i=0;i<AVERAGE_NUM;i++)
	{
		buf +=Motion_Data.Status.Motor_Ang_Vel[LEFT][i];
	}
	Motion_Data.Status.Motor_Ang_Vel_Average[LEFT] =buf/(AVERAGE_NUM);
	buf =0;
	for(i=0;i<AVERAGE_NUM;i++)
	{
		buf +=Motion_Data.Status.Motor_Ang_Vel[RIGHT][i];
	}
	Motion_Data.Status.Motor_Ang_Vel_Average[RIGHT] =buf/(AVERAGE_NUM);  
	  
	  
}