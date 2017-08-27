#ifndef _RMDS_H_
#define _RMDS_H_

#include "stm32f10x_conf.h"

//485EN�˿ڶ���
#define RMDS_GPIO_RCC           		RCC_APB2Periph_GPIOB
#define RMDS_GPIO_PORT          		GPIOB
#define RMDS_GPIO_PIN      				GPIO_Pin_1

#define RMDS_TX_EN()					GPIO_SetBits(RMDS_GPIO_PORT,RMDS_GPIO_PIN);
#define RMDS_RX_EN()					GPIO_ResetBits(RMDS_GPIO_PORT,RMDS_GPIO_PIN);

#define RMDS_FRAME_HEAD 				0X48 //RMDS������֡ͷ����
#define RMDS_RESET_CMD					0X00
#define RMDS_MODE_CMD					0x01
		
#define RMDS_OPEN_MODE					0x01
#define RMDS_CUR_MODE					0x02
#define RMDS_VEL_MODE					0x03
#define RMDS_POS_MODE					0x04
#define RMDS_VEL_POS_MODE				0x05
#define RMDS_CUR_VEL_MODE				0x06
#define RMDS_CUR_POS_MODE				0x07
#define RMDS_CUR_VEL_POS_MODE			0x08

#define MAX_POSITIVE_POS                 1073741820       //�������ֵ
#define MAX_NAGETIVE_POS                -1073741820      //�������ֵ


typedef struct
{//��ʮ���ֽڵĳ���
	u8 Frame_Head;
	u8 RMDS_ID;
	u8 Data[8];
}RMDS_Frame_TypeDef;

void RMDS_Init(u8 mode);
void RMDS_GPIO_Config();
void RMDS_Get_Status(u8 rmds_id);
void RMDS_Ping_Device(u8 rmds_id);
void RMDS_Reset(u16 rmds_id,u8 cmd);
void RMDS_Mode_Change_Send(u16 rmds_id,u8 mode);
void RMDS_Send_Frame(RMDS_Frame_TypeDef rmds_frame);
void RMDS_Vel_Pos_Send_Arg(u16 rmds_id,u16 pwm,u16 vel,s32 pos);
void RMDS_Vel_Send_Arg(u16 rmds_id,u16 pwm,u16 vel);
void RMDS_USART_Data_RX_Handler(u16 usart_data);

#endif
