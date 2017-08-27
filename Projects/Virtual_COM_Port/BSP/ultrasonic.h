#ifndef __Ultrasonic_H
#define	__Ultrasonic_H

//2016-09-18 
//Blade
//�޸�GPIO��define��ʹ�ó�����ģ������޸Ĵ˴��Ĺܽ�
//����Ҫע�����RCC_APB2


#define WINDOW_UPPER_VALUE 45		    //�ͻش��ڵ�����
#define WINDOW_FLOOR_VALUE 23 		    //�ͻش��ڵ�����
//#define THRESHOLD_VALUE		60



#define NUM_OF_ULTRASONIC 8	//����������������
typedef struct 
{
	GPIO_TypeDef* 	TRIG_PORT;
	uint16_t 		TRIG_PIN;
	GPIO_TypeDef* 	ECHO_PORT;
	uint16_t 		ECHO_PIN;
	uint8_t 		ECHO_GPIO_PortSourceGPIO;
	uint8_t 		ECHO_GPIO_PinSource;
	uint32_t 		ECHO_EXTI_Line;
	uint8_t 		ECHO_EXTI_IRQn;
}Ultrasonic_GPIO_TypeDef;

extern Ultrasonic_GPIO_TypeDef Ultrasonic_GPIO[NUM_OF_ULTRASONIC];

void Ultrasonic_GPIO_Struct_Init();
void Ultrasonic_GPIO_Configuration(void);               //�Գ�����ģ���ʼ��
void Obstacle_Scan();//�ϰ�����



#endif /* __UltrasonicWave_H */

