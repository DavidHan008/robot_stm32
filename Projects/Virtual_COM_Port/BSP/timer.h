#ifndef __TIMER_H
#define __TIMER_H

#define TIM3_PERIOD 3599

extern u16 TIM_Count[];
extern u16 Ultrasonic_Distance[]; 

void Timer2_Init(u16 arr,u16 psc); //����������
void Timer3_Init();     //PWM���
void Timer4_Init(u16 arr,u16 psc);//��������̨����ģʽ�µĵ��ȶ�ʱ��
void Timer5_Init(u16 arr,u16 psc);//����źŶ�ʱ���
#endif
