/********************   One Artisan's Regret And Pride   ***********************
*
*	@File    	�� str.c
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

//�Ա��ַ���str1��str2
//*str1:�ַ���1ָ��
//*str2:�ַ���2ָ��
//����ֵ:0�����;1�������;
/////////�������Զ����յ�һ���ַ����ĳ������Ա�
u8 blade_strcmp(u8 *str1,u8 *str2)
{
  u8 i=blade_strlen(str1);
	while(i>0)
	{
		if(*str1!=*str2)return 1;//�����
		if(*str1=='\0')break;//�Ա������.
		str1++;
		str2++;
		i--;
	}
	return 0;//�����ַ������
}
//��str1������copy��str2
//*str1:�ַ���1ָ��
//*str2:�ַ���2ָ��			   
void blade_strcopy(u8*str1,u8 *str2)
{
	while(1)
	{										   
		*str2=*str1;	//����
		if(*str1=='\0')break;//���������.
		str1++;
		str2++;
	}
}
//�õ��ַ����ĳ���(�ֽ�)
//*str:�ַ���ָ��
//����ֵ:�ַ����ĳ���		   
u8 blade_strlen(u8*str)
{
	u8 len=0;
	while(1)
	{							 
		if(*str=='\0')break;
		len++;
		str++;
	}
	return len;
}