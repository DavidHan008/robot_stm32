#ifndef __COMM_H
#define __COMM_H
/********************   One Artisan's Regret And Pride   ***********************
*
*	@File    	�� smartbox.h
*	@Brief   	�� ���ܹ�ͷ�ļ�
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

#include "usart.h"


/*****************************		����֡λ�ö���	********************/
#define HEAD					0x00
#define OBJ						0X01
#define CMD						0X02
#define PARAM1					0X03
#define PARAM2					0X04
#define PARAM3					0X05
#define PARAM4					0X06
#define PARAM5					0X07
#define PARAM6					0X08
#define PARAM7					0X09
#define PARAM8					0X0A
#define PARAM9					0X0B
#define PARAM10					0X0C
#define PARAM11					0X0D
#define PARAM12					0X0E
#define PARAM13					0X0F
#define PARAM14					0X10
#define PARAM15					0X11
#define PARAM16					0X12
#define PARAM17					0X13
#define PARAM18					0X14
#define PARAM19					0X15
#define PARAM20					0X16
#define PARAM21					0X17
#define PARAM22					0X18
#define PARAM23					0X19
#define PARAM24					0X1A
/*****************************		����֡���ݶ���	********************/
//֡ͷ
#define ROS_FRAME_HEAD			0XA5
//����
#define BEEP_OBJ				0X01	//����������
#define MOTION_OBJ				0x02	//�˶�����
#define IMU_OBJ                 0x03    //IMU����	
#define RESOLVE_OBJ				0X04	//��̬�������
#define DISTANCE_OBJ 			0X05	//������
#define BAT_OBJ		 			0X06	//��ض���
#define IR_OBJ					0X07	//�������

#define DEBUG_OBJ	            0X09
#define SELF_CHECK_OBJ          0X0A
#define POS_OBJ                 0X10    //λ������
//ָ��
#define WRITE_CMD				0X80		//д�����Ҫ����
#define READ_CMD				0X81		//��ȡ�ͷ�����һ��
#define RETURN_CMD				0X82
//���ز���		
#define OK_PARAM				0X01
#define ERROR_PARAM				0X02
//֡β
#define ROS_FRAME_END			0XAA


void Bat_to_ROS();
void AHRS_Data_to_ROS();
void Resolving_Data_to_ROS();
void Motion_Data_Status_to_ROS();
void Distance_Data_to_ROS(u8 num);

void ROS_Data_Process(Element_Data_TypDef source);
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
#endif




