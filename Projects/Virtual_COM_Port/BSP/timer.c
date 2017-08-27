/********************   One Artisan's Regret And Pride   ***********************
*
*	@File    	�� sw_iic.c
*	@Brief   	�� 
*	@Author  	�� admin@oarap.org
*	@Hardware	�� STM32F103RCT6
*	@Date		�� 2017-03
*	@Description    �� ���ģ��IIC����������
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

u16 TIM_Count[NUM_OF_ULTRASONIC];//ʱ�Ӽ�������������¼ÿ�����������صĽŸߵ�ƽ������ʱ�Ӹ���
u16 Ultrasonic_Distance[NUM_OF_ULTRASONIC];      //������ľ��� 

//ͨ�ö�ʱ���жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3
/*********************        TIM2        *******************************/
void Timer2_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	//TIM_OCInitTypeDef        TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler = psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  ////////////////TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
		TIM2, //TIM2
		//TIM_IT_Update |   //TIM �ж�Դ
		//TIM_IT_CC1 | //CCR1�ж�ʹ��
		//TIM_IT_CC2 |
		TIM_IT_Trigger ,  //TIM �����ж�Դ 
		ENABLE  //ʹ��
		);
	//TIM_ARRPreloadConfig(TIM2, ENABLE);               	//ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���                     
		  
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���							 
	 TIM_Cmd(TIM2,ENABLE);
}
/*********************        TIM3       *******************************/
void Timer3_Init(void)
{	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef        TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��
	//��ʱ����ʱʱ��T���㹫ʽ��T=(TIM_Period+1)*(TIM_Prescaler+1)/TIMxCLK=(3600*10/72M)s=0.0005s����2KƵ��
	TIM_TimeBaseStructure.TIM_Period = TIM3_PERIOD;//�Զ���װ��ֵ��ȡֵ������0x0000~0xFFFF֮��
	TIM_TimeBaseStructure.TIM_Prescaler =10-1;//Ԥ��Ƶֵ��+1Ϊ��Ƶϵ����ȡֵ������0x0000~0xFFFF֮��							 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 				//ʱ�ӷָ�
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//���ϼ���ģʽ	 
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ 
	
	TIM_OCInitStructure.TIM_Pulse =0;//�����ر�ռ�ձ����
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;             //TIM�����ȵ���ģʽ1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     //�������:TIM����Ƚϼ��Ը�
	//ͨ��1
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);          	//����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable); 	//ʹ��TIMx��CCR1�ϵ�Ԥװ�ؼĴ���
	//ͨ��2
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);          	//����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable); 	//ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
	//ͨ��3 
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);          	//����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable); 	//ʹ��TIMx��CCR3�ϵ�Ԥװ�ؼĴ���
	//ͨ��4 
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);          	//����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable); 	//ʹ��TIMx��CCR4�ϵ�Ԥװ�ؼĴ���
	
	TIM_ARRPreloadConfig(TIM3, ENABLE);               	//ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���                     
	TIM_Cmd(TIM3, DISABLE);								//��ֹTIM3ʹ��
	TIM_Cmd(TIM3, ENABLE);								//ʹ�ܶ�ʱ��	
}

void Timer4_Init(u16 arr,u16 psc)
{	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	//TIM_OCInitTypeDef        TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //ʱ��ʹ��
	//��ʱ����ʱʱ��T���㹫ʽ��T=(TIM_Period+1)*(TIM_Prescaler+1)/TIMxCLK=(3600*10/72M)s=0.0005s����2KƵ��
	TIM_TimeBaseStructure.TIM_Period = arr;//�Զ���װ��ֵ��ȡֵ������0x0000~0xFFFF֮��
	TIM_TimeBaseStructure.TIM_Prescaler =psc;//Ԥ��Ƶֵ��+1Ϊ��Ƶϵ����ȡֵ������0x0000~0xFFFF֮��							 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 				//ʱ�ӷָ�
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//���ϼ���ģʽ	 
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ 
/*	
	TIM_OCInitStructure.TIM_Pulse =4600;//�����ر�ռ�ձ����
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;             //TIM�����ȵ���ģʽ1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     //�������:TIM����Ƚϼ��Ը�
	//ͨ��1
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);          	//����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable); 	//ʹ��TIMx��CCR1�ϵ�Ԥװ�ؼĴ���
	
	//ͨ��2
	TIM_OCInitStructure.TIM_Pulse =4605;//�����ر�ռ�ձ����
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);          	//����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable); 	//ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
*/
		TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
		TIM4, 
		TIM_IT_Update |   //TIM �ж�Դ
		//TIM_IT_CC1 | //CCR1�ж�ʹ��
		//TIM_IT_CC2 |
		TIM_IT_Trigger ,  //TIM �����ж�Դ 
		ENABLE  //ʹ��
		);
		
	TIM_ARRPreloadConfig(TIM4, ENABLE);               	//ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���   
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���							 
	TIM_Cmd(TIM4, ENABLE);								//ʹ�ܶ�ʱ��	
}

void Timer5_Init(u16 arr,u16 psc)
{	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);////////////////////////////
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); //ʱ��ʹ��
	//��ʱ����ʱʱ��T���㹫ʽ��T=(TIM_Period+1)*(TIM_Prescaler+1)/TIMxCLK=(3600*10/72M)s=0.0005s����2KƵ��
	TIM_TimeBaseStructure.TIM_Period = arr;//�Զ���װ��ֵ��ȡֵ������0x0000~0xFFFF֮��
	TIM_TimeBaseStructure.TIM_Prescaler =psc;//Ԥ��Ƶֵ��+1Ϊ��Ƶϵ����ȡֵ������0x0000~0xFFFF֮��							 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 				//ʱ�ӷָ�
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//���ϼ���ģʽ	 
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ 
        TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
                     TIM5, 
                     TIM_IT_Update,// |   //TIM �ж�Դ
                       //TIM_IT_Trigger ,  //TIM �����ж�Դ 
                       ENABLE  //ʹ��
                         );
        
	TIM_ARRPreloadConfig(TIM5, ENABLE);               	//ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���   
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���							 
	TIM_Cmd(TIM5, ENABLE);								//ʹ�ܶ�ʱ��	
}


void TIM2_IRQHandler(void)   //TIM2�ж�
{
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
  {
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //���TIMx���жϴ�����λ:TIM �ж�Դ //��ʱ20US
  }
  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //���TIMx���жϴ�����λ:TIM �ж�Դ //��ʱ20US
}

void TIM4_IRQHandler(void)   //TIM4�ж�
{
    static u8 Current_Sensor_Sequence = 0;			//��ǰ���ڴ���Ĵ�����
    EXTI_InitTypeDef EXTI_InitStructure;
    if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
    {	
        //�ع�ȥ
	EXTI_InitStructure.EXTI_Line = Ultrasonic_GPIO[Current_Sensor_Sequence].ECHO_EXTI_Line;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = DISABLE;
	EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���	
	
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);  //���TIMx���жϴ�����λ:TIM �ж�Դ 
	
        //���ж��д���ʱ��ת���ɾ�������ݣ�ȡ��֮ǰ���ں����м��㡣
        Ultrasonic_Distance[Current_Sensor_Sequence] = (TIM_Count[Current_Sensor_Sequence]*17/1000);//////////
        
	Current_Sensor_Sequence++;////////////////
	if(Current_Sensor_Sequence==NUM_OF_ULTRASONIC)Current_Sensor_Sequence=0;
	
	TIM_Count[Current_Sensor_Sequence]=29999;//29999��ֹ�����������ӵ��Ͽ��󾡹ܲ�������ⲿ�жϵ�TIM_Count�лỺ��������ֵ������ķ���
	
	GPIO_SetBits(Ultrasonic_GPIO[Current_Sensor_Sequence].TRIG_PORT,Ultrasonic_GPIO[Current_Sensor_Sequence].TRIG_PIN); 		  //��>10US�ĸߵ�ƽ�TRIG_PORT,TRIG_PIN��������define����?
	Delay_us(20);		                      //��ʱ20US
	GPIO_ResetBits(Ultrasonic_GPIO[Current_Sensor_Sequence].TRIG_PORT,Ultrasonic_GPIO[Current_Sensor_Sequence].TRIG_PIN);
	
	//����ǰ
	EXTI_InitStructure.EXTI_Line = Ultrasonic_GPIO[Current_Sensor_Sequence].ECHO_EXTI_Line;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���	
	
	TIM_SetCounter(TIM2,0);	
	TIM_Cmd(TIM2,DISABLE);
  }
  TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
}
void TIM5_IRQHandler(void)   //TIM5�ж�
{ 	 
  if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
  {
	Motion_Data.Status.Feedback_Flag = TRUE;
	TIM_ClearITPendingBit(TIM5, TIM_IT_Update);  //���TIMx���жϴ�����λ:TIM �ж�Դ //��ʱ20US
  }
  TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
}

