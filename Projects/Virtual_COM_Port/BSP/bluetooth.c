/********************   One Artisan's Regret And Pride   ***********************
*
*	@File    	�� bluetooth.c
*	@Brief   	�� 
*	@Author  	�� admin@oarap.org
*	@Hardware	�� STM32F103RCT6
*	@Date		�� 2017-03
*	@Description    �� ����ͨѶ��Ԫ
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
	����ģ���ʼ��
********************************************************************************/
void Bluetooth_Init()
{
  USART_Send_Str(BT_USART,"AT");    //����ָ��ͬ��
  Delay_ms(200);
  USART_Send_Str(BT_USART,"AT");    
}

/*******************************************************************************
	���ͷ����������λ��
********************************************************************************/
void Bluetooth_Send_Return_to_ROS(u8 obj,u8 param)
{
	u8 send_buf[6];
	
	send_buf[HEAD]   = ROS_FRAME_HEAD;
	send_buf[OBJ]    = obj;
	send_buf[CMD]    = RETURN_CMD;
	send_buf[PARAM1] = param;
	
	send_buf[PARAM1+1] 	 = 0x06;
	send_buf[PARAM1+2] 	 = ROS_FRAME_END;
	USART_Send_Assign(BT_USART,send_buf,6);
}
/*******************************************************************************
	�������ݸ���λ��
********************************************************************************/
void Bluetooth_Send_Data_to_ROS(u8 obj,u8 cmd,u8 *param,u8 len)
{
	u8 send_buf[32];
	u8 i;
	
	send_buf[HEAD]   = ROS_FRAME_HEAD;
	send_buf[OBJ]    = obj;
	send_buf[CMD]    = cmd;
	for(i=0;i<len;i++)
	{
	  send_buf[PARAM1+i] = param[i];
	}
	
	send_buf[len+3] 	 = len+5;
	send_buf[len+4] 	 = ROS_FRAME_END;
	USART_Send_Assign(BT_USART,send_buf,len+5);
}
/*******************************************************************************
	�������ݽ��մ洢У��ص�����
********************************************************************************/
void Bluetooth_USART_Data_RX_Handler(u16 usart_data)
{
	USART_Data.BT.Data[USART_Data.BT.Pointer++]=usart_data;
	if(USART_Data.BT.Data[HEAD] != ROS_FRAME_HEAD)			//֡ͷУ��  
	  USART_Data.BT.Pointer = 0;
	if(USART_Data.BT.Pointer > 31)				//�������
	  USART_Data.BT.Pointer=0;
	if(USART_Data.BT.Pointer-1 >= 4) 			//�ȴ�֡β
	{
	  if ((USART_Data.BT.Data[USART_Data.BT.Pointer-1] == ROS_FRAME_END)&&
		  (USART_Data.BT.Data[USART_Data.BT.Pointer-2] == USART_Data.BT.Pointer))
	  {
		if((USART_Data.BT.Data[CMD] == 0x80)||
		   (USART_Data.BT.Data[CMD] == 0x81)||
		   (USART_Data.BT.Data[CMD] == 0x82))
		{
		  USART_Data.BT.Flag=TRUE; 
		  USART_Data.BT.Pointer=0;
		}
	  }
	}
}
/*******************************************************************************
	�������ݴ���
********************************************************************************/
/*void Bluetooth_Data_Process()
{
	if(USART_Data.BT.Flag)
	{
	  Beep(1,20);
		switch (USART_Data.BT.Data[OBJ])
		{
		  case BEEP_OBJ:
			Beep_Obj_Handler(&USART_Data.BT.Data[PARAM1]);
			//Bluetooth_Send_Return_to_ROS(BEEP_OBJ,OK_PARAM);
			break;
		  case MOTION_OBJ:
			Motion_Control_Obj_Handler(&USART_Data.BT.Data[PARAM1]);
			break;
		default: break;
		}
		USART_Data.BT.Flag = FALSE;
	}
}

	 */









