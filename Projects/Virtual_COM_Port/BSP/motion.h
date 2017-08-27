#ifndef __MOTION_H
#define __MOTION_H
/*union Float_Data //union������Ϊʵ��char�����float֮���ת��
{
    float f;
    u8 c[4];
	s32 i;
};*/	
#define AVERAGE_NUM	25

typedef struct
{
	bool Update_Flag;			//�˶�״̬���±�־λ
	bool Enable_Flag;			//�˶�ʹ�ܱ�־λ
	s16  Motor_Ang_Vel[2];		//ת�ٿ��Ƶ�
    u16 PWM_Limit;
}Control_Data_TypDef;			//�˶���������
typedef struct
{
	s16 Cur[2];
	s16 Motor_Ang_Vel[2][AVERAGE_NUM];
	s32 Pos[2];
	s16 Motor_Ang_Vel_Average[2];			//������
	bool Feedback_Flag;
}Status_Data_TypDef;			//�˶�״̬����
typedef struct
{
	Control_Data_TypDef		Control;
	Status_Data_TypDef		Status;
}Motion_Data_Typdef;
extern Motion_Data_Typdef Motion_Data;
	

	
void Motion_Control_Data_Time_Out_Check_Handler();	//���ʱ��⺯��
void Motion_Control_Obj_Handler(u8 *param);
void Motion_Data_Init();
void Motion_Control_Data_Send();
void Motion_Status_Data_Read();
void Motor_Ang_Vel_Average_Calculate();
#endif

