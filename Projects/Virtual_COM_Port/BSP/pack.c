/********************   One Artisan's Regret And Pride   ***********************
*
*	@File    	�� packet.c
*	@Brief   	�� 
*	@Author  	�� admin@oarap.org
*	@Hardware	�� STM32F103RCT6
*	@Date		�� 2017-03
*	@Description    �� ͨ��Э���д���ͽ������
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

USB_Data_Frame_TypDef USB_Data_Frame_Tx;//������
USB_Data_Frame_TypDef USB_Data_Frame_Rx;//�����ã���USART�ж��д���USART_DATA�У��ں�̨����������ýṹ��ֽ�USART����

void USB_Send_Data_Frame(USB_Data_Frame_TypDef *data_frame)//��������֡
{
  u8 i;
  u8 buf[32];
  data_frame->Head = ROS_FRAME_HEAD;//��ʼ���ṹ��
  data_frame->End  = ROS_FRAME_END;
  buf[0] = data_frame->Head;//֡ͷ
  buf[1] = data_frame->Obj;//����
  buf[2] = data_frame->Cmd;//ָ��
  for(i=0;i < data_frame->Arg_Lenth;i++)
  {
    buf[i+3] = data_frame->Arg[i];
  }
  buf[i+3] = data_frame->End;//֡β
  USB_SendBuf(buf,i+4);//����Buf�е�ǰi+3������
}
bool USB_Rec_Data_Frame(USB_Data_Frame_TypDef *data_frame)
{//�����յ���ת�浽���ݽ��ܽṹ����
  u8 i;
  if(USART_Data.USB.Pointer < 4)
  {
    return FALSE;//���ݴ���
  }
  else
  {
  }
  data_frame->Arg_Lenth = USART_Data.USB.Pointer-4;
  data_frame->End = USART_Data.USB.Data[USART_Data.USB.Pointer-1];//��ʡʱ��
  for(i=USART_Data.USB.Pointer-2;i>=3;i--)//�Ӻ���ǰ�����ݴ浽�ṹ���У���ʡʱ��
  {     
    data_frame->Arg[i-3] = USART_Data.USB.Data[i];
  }
  data_frame->Cmd		     = USART_Data.USB.Data[2];
  data_frame->Obj		     = USART_Data.USB.Data[1];
  data_frame->Head		     = USART_Data.USB.Data[0];
  
  if((data_frame->Head!=0XA5) || (data_frame->End!=0XAA))
  {
    return FALSE;//���ݴ���
  }
  else
  {
    return TRUE;
  }
}
void USB_Send_Return_to_PC(u8 obj,u8 arg)
{
  USB_Data_Frame_Tx.Obj    = obj;
  USB_Data_Frame_Tx.Cmd    = RETURN_CMD;
  USB_Data_Frame_Tx.Arg[0] = arg;
  USB_Data_Frame_Tx.Arg_Lenth = 1;
  USB_Send_Data_Frame(&USB_Data_Frame_Tx);
}
void USB_Send_Data_to_PC(u8 obj,u8 cmd,u8 *arg,u8 arg_len)
{
  u8 i;
  USB_Data_Frame_Tx.Obj    = obj;
  USB_Data_Frame_Tx.Cmd    = cmd;
  for(i=0;i<arg_len;i++)
  {
    USB_Data_Frame_Tx.Arg[i] = arg[i];
  }
  USB_Data_Frame_Tx.Arg_Lenth = arg_len;
  USB_Send_Data_Frame(&USB_Data_Frame_Tx);
}


///////////////////////////////////////
bool Data_Frame_Check(USB_Data_Frame_TypDef *data_frame)
{//�����յ���ת�浽���ݽ��ܽṹ����
  u8 i;
  if(USART_Data.USB.Pointer < 4)
  {
    return FALSE;//���ݴ���
  }
  else
  {
  }
  data_frame->Arg_Lenth = USART_Data.USB.Pointer-4;
  data_frame->End = USART_Data.USB.Data[USART_Data.USB.Pointer-1];//��ʡʱ��
  for(i=USART_Data.USB.Pointer-2;i>=3;i--)//�Ӻ���ǰ�����ݴ浽�ṹ���У���ʡʱ��
  {     
    data_frame->Arg[i-3] = USART_Data.USB.Data[i];
  }
  data_frame->Cmd		     = USART_Data.USB.Data[2];
  data_frame->Obj		     = USART_Data.USB.Data[1];
  data_frame->Head		     = USART_Data.USB.Data[0];
  
  if((data_frame->Head!=0XA5) || (data_frame->End!=0XAA))
  {
    return FALSE;//���ݴ���
  }
  else
  {
    return TRUE;
  }
}