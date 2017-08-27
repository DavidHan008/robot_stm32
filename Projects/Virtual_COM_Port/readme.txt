/********************   One Artisan's Regret And Pride   ***********************
*
*	@File    	�� readme.txt
*	@Brief   	�� 
*	@Author  	�� admin@oarap.org
*	@Hardware	�� STM32F103RCT6
*	@Date		�� 2017-03
*	@Description    �� ϵͳ�Ĺ���˵��
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

/********************          ���ڲ���          ********************/
USART1 �� USB-UARTΪ��λ��ͨ�ŵĶ˿�
USART2 ����IMU	115200������		���ؽǶ� ��γ�� ����
USART3 ����485ͨ��	115200������
UART4  ������������ͨ��	38400������
UART5  ���മ��	
/********************          ��ʱ��          ********************/
TIM2����������ͨ�ż�ʱ
TIM4������������������
TIM3���ĸ�ͨ���ֱ������·��ˢ�����PWM��

Motion_Data	  ���յ���������λ����Ŀ������
RMDS_Status	  ������в�������
Odom_Data	  ���͸���λ���ķ�������

ahrs motion odom�ж��й���Vector3_Data_TypDef�Ľṹ�嶨��

/********************          ͨ��Э��          ********************/
0xAA�����������еĵ�[5]��
***��ʽ��
0xA5 0x01 0x80 
...  		//����	��λ��ǰ��λ�ں��ģʽ
frame_len 0xAA
***������ʾ����
0xA5 0x01 0x80 
0x02 		//��������2ms
frame_len 0xAA
***�˶������ơ�ʾ����
0xA5 0x02 0x80 
{Motor_Ang_Vel[LEFT]1  Motor_Ang_Vel[LEFT]2} 		//����RPM��s16����
{Motor_Ang_Vel[RIGHT]1  Motor_Ang_Vel[RIGHT]2}		//����RPM��s16����
frame_len 0xAA
***�˶����ݡ�������ʾ����
0xA5 0x02 0x80
{Motor_Ang_Vel_Average[LEFT]1   Motor_Ang_Vel_Average[LEFT]2} 	//����RPM��s16����
{Motor_Ang_Vel_Average[RIGHT]1  Motor_Ang_Vel_Average[RIGHT]2}  //����RPM��s16����
{Pos[LEFT]1   Pos[LEFT]2  Pos[LEFT]3  Pos[LEFT]4} 				//���ֱ�����,s32����
{Pos[RIGHT]1  Pos[RIGHT]2 Pos[RIGHT]3 Pos[RIGHT]4}              //���ֱ�����,s32����
frame_len 0xAA
***IMU���ݷ���ʾ����
0xA5 0x03 0x80
{AHRS_Data.IMU.Acc.x1    AHRS_Data.IMU.Acc.x2}			//Acc.x��s16����
{AHRS_Data.IMU.Acc.y1    AHRS_Data.IMU.Acc.y2}			//Acc.y��s16����
{AHRS_Data.IMU.Acc.z1    AHRS_Data.IMU.Acc.z2}			//Acc.z��s16����
{AHRS_Data.IMU.Gyro.x1   AHRS_Data.IMU.Gyro.x2}			//Gyro.x��s16����
{AHRS_Data.IMU.Gyro.y1   AHRS_Data.IMU.Gyro.y2}			//Gyro.y��s16����
{AHRS_Data.IMU.Gyro.z1   AHRS_Data.IMU.Gyro.z2}			//Gyro.z��s16����
{AHRS_Data.IMU.Ang.x1   AHRS_Data.IMU.Ang.x2}			//Ang.x��s16����
{AHRS_Data.IMU.Ang.y1   AHRS_Data.IMU.Ang.y2}			//Ang.y��s16����
{AHRS_Data.IMU.Ang.z1   AHRS_Data.IMU.Ang.z2}			//Ang.z��s16����
frame_len 0xAA
***������ݷ���ʾ����
0xA5 0x05 0x80
{Bat_Vol1    Bat_Vol2}			//Bat_Vol��u16����			//Ang.z��s16����
frame_len 0xAA



ros�ж���cmd_vel���⣬Ȼ��ͨ��������int32����Motor_Ang_Vel[LEFT] ��Motor_Ang_Vel[RIGHT]����ʽ����λ��ǰ��λ�ں󣬴������������1000������������STM32

/********************          ��������          ********************/
�������裺9980R��910R
((x/4096)*3.3)/(910/(9980+910))=V	x*0.009641408

/********************          RMDS          ********************/
RMDS�ٶȻ���
P=0.01	D=0.15
0.03	0.2
0.08 	0.4
0.05	0.4












