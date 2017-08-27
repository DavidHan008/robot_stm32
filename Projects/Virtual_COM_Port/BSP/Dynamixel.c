#include "Sys_Conf.h"
#include "string.h"

Servo_Data_Frame_TypeDef Servo_Data_Frame_Tx;
Servo_Data_Frame_TypeDef Servo_Data_Frame_Rx;
Servo_Arg_TypeDef        Servo_Arg;
//Frame_Header*2��ID*1��Lenth*1��Cmd*1,Addr*1��Data*N��Check_Sum*1
u16 DanceMove[8][NUM_OF_SERVO+1];
//�ṹ��ָ����ʽ��Ϊʵ��
void Servo_Data_Send(Servo_Data_Frame_TypeDef *data_frame)
{
    u8 i;
	u8 tx_buf[32];
	u16 check_sum_temp = 0;
	tx_buf[FRAME_HEADER_H] = SERVO_FRAME_HEAD0;
	tx_buf[FRAME_HEADER_L] = SERVO_FRAME_HEAD1;
	tx_buf[SERVO_ID] 	   = data_frame->ID;
	tx_buf[DATA_LENTH]     = data_frame->Len;
	tx_buf[SERVO_CMD] 	   = data_frame->Cmd;
	for(i=0;i<data_frame->Len-2;i++)//����ת��
		tx_buf[i+5] = data_frame->Data[i];
	for(i=2;i<data_frame->Len+3;i++)//����У���
    	check_sum_temp += tx_buf[i];
  	tx_buf[data_frame->Len+3] = ~check_sum_temp;//���У���
	USART_Send_Assign(USART2,tx_buf,tx_buf[DATA_LENTH]+4);
}
//дһ���֣������ֽ�
void Servo_Write_Word(u8 id,u8 add,u16 data)
{
	u8 i;
	u8 tx_buf[32];
	u16 check_sum_temp = 0;
	tx_buf[FRAME_HEADER_H] = SERVO_FRAME_HEAD0;
	tx_buf[FRAME_HEADER_L] = SERVO_FRAME_HEAD1;
	tx_buf[SERVO_ID] 	   = id;//�β�
	tx_buf[DATA_LENTH]     = 5;
	tx_buf[SERVO_CMD] 	   = CMD_WRITE;
	tx_buf[5]			   = add;//�β�
	tx_buf[6]			   = data;//�β�
	tx_buf[7]			   = data>>8;
	for(i=2;i<8;i++)//����У���
    	check_sum_temp += tx_buf[i];
  	tx_buf[8] = ~check_sum_temp;//���У���
	USART_Send_Assign(USART2,tx_buf,9);
}
//дһ���ֽ�
void Servo_Write_Byte(u8 id,u8 add,u8 data)
{
	u8 i;
	u8 tx_buf[32];
	u16 check_sum_temp = 0;
	tx_buf[FRAME_HEADER_H] = SERVO_FRAME_HEAD0;
	tx_buf[FRAME_HEADER_L] = SERVO_FRAME_HEAD1;
	tx_buf[SERVO_ID] 	   = id;//�β�
	tx_buf[DATA_LENTH]     = 4;
	tx_buf[SERVO_CMD] 	   = CMD_WRITE;
	tx_buf[5]			   = add;//�β�
	tx_buf[6]			   = data;//�β�
	for(i=2;i<7;i++)//����У���
    	check_sum_temp += tx_buf[i];
  	tx_buf[7] = ~check_sum_temp;//���У���
	USART_Send_Assign(USART2,tx_buf,8);
}
//��ȡһ���ֽ�
void Servo_Read_Byte(u8 id,u8 add)
{
	u8 i;
	u8 tx_buf[32];
	u16 check_sum_temp = 0;
	tx_buf[FRAME_HEADER_H] = SERVO_FRAME_HEAD0;
	tx_buf[FRAME_HEADER_L] = SERVO_FRAME_HEAD1;
	tx_buf[SERVO_ID] 	   = id;//�β�
	tx_buf[DATA_LENTH]     = 4;
	tx_buf[SERVO_CMD] 	   = CMD_READ;
	tx_buf[5]			   = add;//�β�
	tx_buf[6]			   = 0x01;//һ���ֽڳ���
	for(i=2;i<7;i++)//����У���
    	check_sum_temp += tx_buf[i];
  	tx_buf[7] = ~check_sum_temp;//���У���
	USART_Send_Assign(USART2,tx_buf,8);
}
//��ȡһ����
void Servo_Read_Word(u8 id,u8 add)
{
	u8 i;
	u8 tx_buf[32];
	u16 check_sum_temp = 0;
	tx_buf[FRAME_HEADER_H] = SERVO_FRAME_HEAD0;
	tx_buf[FRAME_HEADER_L] = SERVO_FRAME_HEAD1;
	tx_buf[SERVO_ID] 	   = id;//�β�
	tx_buf[DATA_LENTH]     = 4;
	tx_buf[SERVO_CMD] 	   = CMD_READ;
	tx_buf[5]			   = add;//�β�
	tx_buf[6]			   = 0x02;//һ���ֽڳ���
	for(i=2;i<7;i++)//����У���
    	check_sum_temp += tx_buf[i];
  	tx_buf[7] = ~check_sum_temp;//���У���
	USART_Send_Assign(USART2,tx_buf,8);
}
#define MX 1
//�ŷ����������λ  
void Servo_Reset(u8 id)
{//��MXϵ�ж����������������ID������
	u8 i;
	u8 tx_buf[32];
	u16 check_sum_temp = 0;
	tx_buf[FRAME_HEADER_H] = SERVO_FRAME_HEAD0;
	tx_buf[FRAME_HEADER_L] = SERVO_FRAME_HEAD1;
	tx_buf[SERVO_ID] 	   = id;//�β�
	tx_buf[DATA_LENTH]     = 0X02;
	tx_buf[SERVO_CMD] 	   = CMD_RESET;
	for(i=2;i<5;i++)//����У���
    	check_sum_temp += tx_buf[i];
  	tx_buf[5] = ~check_sum_temp;//���У���
	USART_Send_Assign(USART2,tx_buf,6);
}
void Servo_Pos_Read(u16 *array)
{
  u8 i;
  //��ȡ����λ��,��ʼλ��ʹ��
  for(i=1;i<10;i++)
  {
    Servo_Read_Word(i,P_PRESENT_POSITION_L);//��ȡ��ǰλ��
	Delay_us(20);
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);//ʹ�ܴ����жϽ���
        Delay_ms(10);
	USART_ITConfig(USART2,USART_IT_RXNE,DISABLE);//�رմ����жϽ���
	
    if(USART_Data.Servo.Flag)//���յ�����
      array[i] = (USART_Data.Servo.Data[6]<<8) |USART_Data.Servo.Data[5];
    else
      array[i] = 2048;
    USART_Data.Servo.Flag = FALSE;
  }
}
//��������ʹ�ܿ���
void Servo_Torque_EN(bool flag)
{	
  u8 i;
  if(flag)
  {
	for(i=1;i<NUM_OF_SERVO+1;i++)
        {
          Servo_Write_Byte(i,P_TORQUE_ENABLE,1);
          Delay_ms(30);
        }
  }
  else
  {
	for(i=1;i<NUM_OF_SERVO+1;i++)
        {
          Servo_Write_Byte(i,P_TORQUE_ENABLE,0);
          Delay_ms(30);
        }
  }  
}
void Servo_Struct_Init()
{
  u8 i;
  Servo_Arg.Action_Flag = FALSE;
  Servo_Arg.Init_Pos_Flag = FALSE;
  Servo_Arg.Step_Num = 25;//30����3����ִ����
  //��һ̨FANFAN�Ĳ�����A�棩
//  Servo_Arg.Init_Pos[1] = 2274;
//  Servo_Arg.Init_Pos[2] = 2086;
//  Servo_Arg.Init_Pos[3] = 1999;
//  Servo_Arg.Init_Pos[4] = 1792;
//  Servo_Arg.Init_Pos[5] = 2000;
//  Servo_Arg.Init_Pos[6] = 1833;
//  Servo_Arg.Init_Pos[7] = 1850;
//  Servo_Arg.Init_Pos[8] = 1539;
//  Servo_Arg.Init_Pos[9] = 1754;
  //�ڶ�̨FANFAN�Ĳ�����B�棩
//  Servo_Arg.Init_Pos[1] = 3400;//2832;
//  Servo_Arg.Init_Pos[2] = 2053;//2048;
//  Servo_Arg.Init_Pos[3] = 1973;//2048;
//  Servo_Arg.Init_Pos[4] = 2012;//2000;
//  Servo_Arg.Init_Pos[5] = 1981;//2000;
//  Servo_Arg.Init_Pos[6] = 2112;//2118;
//  Servo_Arg.Init_Pos[7] = 2048;
//  Servo_Arg.Init_Pos[8] = 2048;
//  Servo_Arg.Init_Pos[9] = 2048;
    //����̨FANFAN�Ĳ�������2��
//  Servo_Arg.Init_Pos[1] = 1850;
//  Servo_Arg.Init_Pos[2] = 2292;
//  Servo_Arg.Init_Pos[3] = 2263;
//  Servo_Arg.Init_Pos[4] = 2289;
//  Servo_Arg.Init_Pos[5] = 2335;
//  Servo_Arg.Init_Pos[6] = 2059;
//  Servo_Arg.Init_Pos[7] = 1968;
//  Servo_Arg.Init_Pos[8] = 2106;
//  Servo_Arg.Init_Pos[9] = 2092;
  //B ֱ����� FANFAN�Ĳ�����ֱ1��
  Servo_Arg.Init_Pos[1] = 2342;
  Servo_Arg.Init_Pos[2] = 1772;
  Servo_Arg.Init_Pos[3] = 2216;
  Servo_Arg.Init_Pos[4] = 1761;
  Servo_Arg.Init_Pos[5] = 1786;
  Servo_Arg.Init_Pos[6] = 2038;
  Servo_Arg.Init_Pos[7] = 2123;
  Servo_Arg.Init_Pos[8] = 1474;
  Servo_Arg.Init_Pos[9] = 1746;  
  for(i=1;i<NUM_OF_SERVO+1;i++)
  {
    Servo_Arg.Goal_Pos[i] = Servo_Arg.Init_Pos[i];//�����ж���
    Servo_Arg.Pre_Pos[i] = Servo_Arg.Init_Pos[i];
    Servo_Arg.Step_Pos[i] = Servo_Arg.Init_Pos[i];
  }
}
void Servo_Init()
{
//�ŷ����������ʼ��
  u8 i;
  for(i=1;i<NUM_OF_SERVO+1;i++)
  {
    
#ifdef AX
	//��˳�߾�
	Servo_Write_Word(i,P_CW_COMPLIANCE_MARGIN,0X0F0F);
	//����б��
	Servo_Write_Word(i,P_CW_COMPLIANCE_SLOPE,0XFFFF);
	//�˶��ٶ�����
	Servo_Write_Word(i,P_GOAL_SPEED_L,0X0101);
#endif
#ifdef MX
        //P GAIN
        Servo_Write_Byte(i,P_P_GAIN,0X40);
        Delay_ms(10);
         //I GAIN
        Servo_Write_Byte(i,P_I_GAIN,0X01);
         //D GAIN
        //Servo_Write_Byte(i,P_D_GAIN,0x00);
        //�˶��ٶ�����
        Delay_ms(10);
        Servo_Write_Word(i,P_GOAL_SPEED_L,0x0035);//0x0022);//0x004a);
        //Servo_Write_Word(i,P_GOAL_SPEED_L,0x0022);//0x004a);
        Delay_ms(10);
        //���ٶ�����/////////////
        Servo_Write_Byte(i,73,0x00);
#endif        
  }
  Servo_Torque_EN(FALSE);
  
  	for(i=1;i<NUM_OF_SERVO+1;i++)
        {
          Servo_Write_Word(i,P_MAX_TORQUE_L,0x03ff);
          Delay_ms(10);
        }
	//Servo_Reset(i);
}
///////////Ӧ�����ÿ�ο������Զ�ʶ����λ�������ֶ�����
//mxϵ�о�����֤����ʹ��Ť�ؿ���û����

void Action_Play(u8 group)
{
  u8 i;
  //TIM_Cmd(TIM5, DISABLE);
  for(i=1;i<NUM_OF_SERVO+1;i++)//����Ŀ��λ��
    Servo_Arg.Goal_Pos[i] = Servo_Arg.Init_Pos[i];
  switch(group)
  {//ִ��ָ����Ķ���
  case 0x01:
    {//���󿴽���
      Servo_Arg.Step_Num = 20;//30;
      Servo_Arg.Goal_Pos[1] = Servo_Arg.Init_Pos[1]+300;
      
      Servo_Arg.Goal_Pos[2] = Servo_Arg.Init_Pos[2]+700;
      Servo_Arg.Goal_Pos[3] = Servo_Arg.Init_Pos[3]-700;
      
      Servo_Arg.Goal_Pos[4] = Servo_Arg.Init_Pos[4]-500;
      
      Servo_Arg.Goal_Pos[6] = Servo_Arg.Init_Pos[6]-400;
      Servo_Arg.Goal_Pos[7] = Servo_Arg.Init_Pos[7]+400;
      
      Servo_Arg.Goal_Pos[8] = Servo_Arg.Init_Pos[8]+900;
      Servo_Arg.Goal_Pos[9] = Servo_Arg.Init_Pos[9]-400;
    }break;
  case 0x02:
    {//���ҿ�����
      Servo_Arg.Step_Num = 20;//30;
      Servo_Arg.Goal_Pos[1] = Servo_Arg.Init_Pos[1]-300;
      
      Servo_Arg.Goal_Pos[2] = Servo_Arg.Init_Pos[2]+700;
      Servo_Arg.Goal_Pos[3] = Servo_Arg.Init_Pos[3]-700;
      
      Servo_Arg.Goal_Pos[5] = Servo_Arg.Init_Pos[5]-500;
      
      Servo_Arg.Goal_Pos[6] = Servo_Arg.Init_Pos[6]-400;
      Servo_Arg.Goal_Pos[7] = Servo_Arg.Init_Pos[7]+400;
      
      Servo_Arg.Goal_Pos[8] = Servo_Arg.Init_Pos[8]+400;
      Servo_Arg.Goal_Pos[9] = Servo_Arg.Init_Pos[9]-900;
    }break;
  case 0x03:
    {//�˶�1
      Servo_Arg.Step_Num = 20;//25;
      Servo_Arg.Goal_Pos[2] = Servo_Arg.Init_Pos[2]+1000;
      Servo_Arg.Goal_Pos[3] = Servo_Arg.Init_Pos[3]-1200;
      Servo_Arg.Goal_Pos[6] = Servo_Arg.Init_Pos[6]+400;
      Servo_Arg.Goal_Pos[7] = Servo_Arg.Init_Pos[7]+400;
    }break;
  case 0x04:
    {//�˶�2
      Servo_Arg.Step_Num = 20;//25;
      Servo_Arg.Goal_Pos[2] = Servo_Arg.Init_Pos[2]+1200;
      Servo_Arg.Goal_Pos[3] = Servo_Arg.Init_Pos[3]-1000;
      Servo_Arg.Goal_Pos[6] = Servo_Arg.Init_Pos[6]-400;
      Servo_Arg.Goal_Pos[7] = Servo_Arg.Init_Pos[7]-400;
    }break;
  case 0x05:
    {//��
      Servo_Arg.Step_Num = 15;//25;
      Servo_Arg.Goal_Pos[4] = Servo_Arg.Init_Pos[4]-320;
      Servo_Arg.Goal_Pos[5] = Servo_Arg.Init_Pos[5]-320;
    }break;  
  case 0x06:
    {//���к�1
      Servo_Arg.Step_Num = 23;//30;
      Servo_Arg.Goal_Pos[1] = Servo_Arg.Init_Pos[1]-150;
      
      Servo_Arg.Goal_Pos[3] = Servo_Arg.Init_Pos[3]-1200;
      Servo_Arg.Goal_Pos[5] = Servo_Arg.Init_Pos[5]-200;
      Servo_Arg.Goal_Pos[7] = Servo_Arg.Init_Pos[7]+700;
      Servo_Arg.Goal_Pos[9] = Servo_Arg.Init_Pos[9]+900;
    }break;  
  case 0x07:
    {//���к�2
      Servo_Arg.Step_Num = 23;//30;
      Servo_Arg.Goal_Pos[1] = Servo_Arg.Init_Pos[1]+150;
      
      Servo_Arg.Goal_Pos[2] = Servo_Arg.Init_Pos[2]+1200;
      Servo_Arg.Goal_Pos[4] = Servo_Arg.Init_Pos[4]-200;
      Servo_Arg.Goal_Pos[6] = Servo_Arg.Init_Pos[6]-700;
      Servo_Arg.Goal_Pos[8] = Servo_Arg.Init_Pos[8]-900;
    }break;  
  case 0x08:
    {//��ӭ
      Servo_Arg.Step_Num = 22;//30;
      Servo_Arg.Goal_Pos[2] = Servo_Arg.Init_Pos[2]+600;
      Servo_Arg.Goal_Pos[3] = Servo_Arg.Init_Pos[3]-600;
      
      Servo_Arg.Goal_Pos[4] = Servo_Arg.Init_Pos[4]-400;
      Servo_Arg.Goal_Pos[5] = Servo_Arg.Init_Pos[5]-400;
      
      Servo_Arg.Goal_Pos[6] = Servo_Arg.Init_Pos[6]-500;
      Servo_Arg.Goal_Pos[7] = Servo_Arg.Init_Pos[7]+500;
      
      Servo_Arg.Goal_Pos[8] = Servo_Arg.Init_Pos[8]+600;
      Servo_Arg.Goal_Pos[9] = Servo_Arg.Init_Pos[9]-600;
    }break; 
  case 0x09:
    {//����
      Servo_Arg.Step_Num = 15;//20;
      Servo_Arg.Goal_Pos[1] = Servo_Arg.Init_Pos[1]-150;
      
      Servo_Arg.Goal_Pos[3] = Servo_Arg.Init_Pos[3]-400;
      Servo_Arg.Goal_Pos[7] = Servo_Arg.Init_Pos[7]+400;
    }break;  
  case 0x0A:
    {//����
      Servo_Arg.Step_Num = 20;//35;
      Servo_Arg.Goal_Pos[6] = Servo_Arg.Init_Pos[6]-800;
      Servo_Arg.Goal_Pos[7] = Servo_Arg.Init_Pos[7]+800;
      
      Servo_Arg.Goal_Pos[8] = Servo_Arg.Init_Pos[8]+900;
      Servo_Arg.Goal_Pos[9] = Servo_Arg.Init_Pos[9]-900;
      
      Servo_Arg.Goal_Pos[2] = Servo_Arg.Init_Pos[2]+800;
      Servo_Arg.Goal_Pos[3] = Servo_Arg.Init_Pos[3]-800;
      
      Servo_Arg.Goal_Pos[4] = Servo_Arg.Init_Pos[4]-200;
      Servo_Arg.Goal_Pos[5] = Servo_Arg.Init_Pos[5]-200;
      
    }break; 
  case 0x0B:
    {//����
      Servo_Arg.Step_Num = 22;//35;
      Servo_Arg.Goal_Pos[1] = Servo_Arg.Init_Pos[1]+300;
      Servo_Arg.Goal_Pos[2] = Servo_Arg.Init_Pos[2]+1500;
      Servo_Arg.Goal_Pos[4] = Servo_Arg.Init_Pos[4]-400;
      Servo_Arg.Goal_Pos[6] = Servo_Arg.Init_Pos[6]-800;
      Servo_Arg.Goal_Pos[8] = Servo_Arg.Init_Pos[8]+900;
    }break; 
  case 0x0C:
    {//ӵ��
      Servo_Arg.Step_Num = 22;//30;
      Servo_Arg.Goal_Pos[2] = Servo_Arg.Init_Pos[2]+500;
      Servo_Arg.Goal_Pos[3] = Servo_Arg.Init_Pos[3]-500;
      
      Servo_Arg.Goal_Pos[4] = Servo_Arg.Init_Pos[4]-200;
      Servo_Arg.Goal_Pos[5] = Servo_Arg.Init_Pos[5]-200;
      
      Servo_Arg.Goal_Pos[6] = Servo_Arg.Init_Pos[6]-600;
      Servo_Arg.Goal_Pos[7] = Servo_Arg.Init_Pos[7]+600;
      
      Servo_Arg.Goal_Pos[8] = Servo_Arg.Init_Pos[8]-200;
      Servo_Arg.Goal_Pos[9] = Servo_Arg.Init_Pos[9]+200;
    }break; 
  case 0x0D:
    {//�Һ���ǰ
      Servo_Arg.Step_Num = 15;//25;
      Servo_Arg.Goal_Pos[1] = Servo_Arg.Init_Pos[1]+150;
      
      Servo_Arg.Goal_Pos[6] = Servo_Arg.Init_Pos[6]-400;
      Servo_Arg.Goal_Pos[7] = Servo_Arg.Init_Pos[7]-400;
    }break;  
  case 0x0E:
    {//�����ǰ
      Servo_Arg.Step_Num = 15;//25;
      Servo_Arg.Goal_Pos[1] = Servo_Arg.Init_Pos[1]-150;
      
      Servo_Arg.Goal_Pos[6] = Servo_Arg.Init_Pos[6]+400;
      Servo_Arg.Goal_Pos[7] = Servo_Arg.Init_Pos[7]+400;
    }break;  
  case 0x0F:
    {//�ɰ�
      Servo_Arg.Step_Num = 18;//25;
      
      Servo_Arg.Goal_Pos[4] = Servo_Arg.Init_Pos[4]-200;
      Servo_Arg.Goal_Pos[5] = Servo_Arg.Init_Pos[5]-200;
      
      Servo_Arg.Goal_Pos[6] = Servo_Arg.Init_Pos[6]+400;
      Servo_Arg.Goal_Pos[7] = Servo_Arg.Init_Pos[7]-400;
      
      Servo_Arg.Goal_Pos[8] = Servo_Arg.Init_Pos[8]-200;
      Servo_Arg.Goal_Pos[9] = Servo_Arg.Init_Pos[9]+200;
    }break;  
    
  case 0x10:
    {//�ҿ�
      Servo_Arg.Step_Num = 15;//15;
      Servo_Arg.Goal_Pos[1] = Servo_Arg.Init_Pos[1]-250;
    }break;  
  case 0x11:
    {//��
      Servo_Arg.Step_Num = 15;//15;
      Servo_Arg.Goal_Pos[1] = Servo_Arg.Init_Pos[1]+250;
    }break;  
  case 0x12:
    {//������
      Servo_Arg.Step_Num = 20;//25;
      Servo_Arg.Goal_Pos[1] = Servo_Arg.Init_Pos[1]+200;
      
      Servo_Arg.Goal_Pos[2] = Servo_Arg.Init_Pos[2]+600;
      Servo_Arg.Goal_Pos[6] = Servo_Arg.Init_Pos[6]-600;
      Servo_Arg.Goal_Pos[8] = Servo_Arg.Init_Pos[8]+900;
    }break; 
  case 0x13:
    {//������
      Servo_Arg.Step_Num = 20;//25;
      Servo_Arg.Goal_Pos[1] = Servo_Arg.Init_Pos[1]-200;
      
      Servo_Arg.Goal_Pos[3] = Servo_Arg.Init_Pos[3]-600;
      Servo_Arg.Goal_Pos[7] = Servo_Arg.Init_Pos[7]+600;
      Servo_Arg.Goal_Pos[9] = Servo_Arg.Init_Pos[9]-900;
    }break; 
    
  case 0x14:
    {//����1
      Servo_Arg.Step_Num = 15;//20;
      Servo_Arg.Goal_Pos[1] = Servo_Arg.Init_Pos[1]+250;
      
      Servo_Arg.Goal_Pos[5] = Servo_Arg.Init_Pos[5]-200;
      Servo_Arg.Goal_Pos[7] = Servo_Arg.Init_Pos[7]-400;
      Servo_Arg.Goal_Pos[9] = Servo_Arg.Init_Pos[9]+300;
    }break; 
  case 0x15:
    {//����2
      Servo_Arg.Step_Num = 15;//20;
      Servo_Arg.Goal_Pos[1] = Servo_Arg.Init_Pos[1]-250;
      
      Servo_Arg.Goal_Pos[4] = Servo_Arg.Init_Pos[4]-200;
      Servo_Arg.Goal_Pos[6] = Servo_Arg.Init_Pos[6]+400;
      Servo_Arg.Goal_Pos[8] = Servo_Arg.Init_Pos[8]-500;
    }break; 
   case 0x16:
    {//��ӭ1
      Servo_Arg.Step_Num = 20;//20;
      Servo_Arg.Goal_Pos[1] = Servo_Arg.Init_Pos[1]+250; 
      
      Servo_Arg.Goal_Pos[2] = Servo_Arg.Init_Pos[2]+500;
      Servo_Arg.Goal_Pos[4] = Servo_Arg.Init_Pos[4]-300;
      Servo_Arg.Goal_Pos[6] = Servo_Arg.Init_Pos[6]-300;
      Servo_Arg.Goal_Pos[8] = Servo_Arg.Init_Pos[8]+500;
    }break; 
       case 0x17:
    {//��ӭ2
      Servo_Arg.Step_Num = 20;//20;
      Servo_Arg.Goal_Pos[1] = Servo_Arg.Init_Pos[1]-250;   
      
      Servo_Arg.Goal_Pos[3] = Servo_Arg.Init_Pos[3]-500;
      Servo_Arg.Goal_Pos[5] = Servo_Arg.Init_Pos[5]-300;
      Servo_Arg.Goal_Pos[7] = Servo_Arg.Init_Pos[7]+300;
      Servo_Arg.Goal_Pos[9] = Servo_Arg.Init_Pos[9]-500;
    }break; 
  case 0x23:
    {
//        Servo_Arg.Step_Num = 25;//25;
//        Servo_Arg.Goal_Pos[1] = Servo_Arg.Init_Pos[1]+500;//ͷ
//        Servo_Arg.Step_Num = 20;//30;
//        Servo_Arg.Goal_Pos[2] = Servo_Arg.Init_Pos[2]+1000;//��
          Servo_Arg.Step_Num = 20;//30;
          Servo_Arg.Goal_Pos[6] = Servo_Arg.Init_Pos[6]-1000;//��
    }break;
  default ://�ص���ʼλ��
    {  
      Servo_Arg.Step_Num = 20;//20;
    }break;
    
  }
  if(!group)
  {
      Servo_Arg.Init_Pos_Flag = TRUE;
      Step_Counter = 1;
  }
  else
  {
      Servo_Arg.Action_Flag = TRUE;  
  }      
  //TIM_Cmd(TIM5,ENABLE);
}

void Dance_Move(u8 comboNum, u8 group)
{
  u8 i,j;
  //TIM_Cmd(TIM5, DISABLE);
  for (i=1; i<=comboNum;i++)
  {
    for(j=1;j<NUM_OF_SERVO+1;j++)//����Ŀ��λ��
    {
      DanceMove[i-1][j] = Servo_Arg.Init_Pos[j];
    }
  }
  switch(group)
  {//ִ��ָ����Ķ���
       case 0x18:
    {//��������
      Servo_Arg.Step_Num = 20;//20;
      Servo_Arg.Goal_Pos[1] = Servo_Arg.Init_Pos[1]+300;
      
      Servo_Arg.Goal_Pos[4] = Servo_Arg.Init_Pos[4]-400;
      Servo_Arg.Goal_Pos[5] = Servo_Arg.Init_Pos[5]-400;
    }break; 
       case 0x19:
    {//��������
      Servo_Arg.Step_Num = 20;//20;
      Servo_Arg.Goal_Pos[1] = Servo_Arg.Init_Pos[1]-300;
      
      Servo_Arg.Goal_Pos[4] = Servo_Arg.Init_Pos[4]-400;
      Servo_Arg.Goal_Pos[5] = Servo_Arg.Init_Pos[5]-400;
    }break; 
       case 0x1A:
    {//��������
      Servo_Arg.Step_Num = 20;//20;
      Servo_Arg.Goal_Pos[1] = Servo_Arg.Init_Pos[1]+300;
      
      Servo_Arg.Goal_Pos[6] = Servo_Arg.Init_Pos[6]-400;//�����ǰ
      Servo_Arg.Goal_Pos[7] = Servo_Arg.Init_Pos[7]-400;//�ұ����
    }break; 
       case 0x1B:
    {//��������
      Servo_Arg.Step_Num = 20;//20;
      Servo_Arg.Goal_Pos[1] = Servo_Arg.Init_Pos[1]-300;
      
      Servo_Arg.Goal_Pos[6] = Servo_Arg.Init_Pos[6]+400;//������
      Servo_Arg.Goal_Pos[7] = Servo_Arg.Init_Pos[7]+400;//�ұ���ǰ
    }break; 
       case 0x1C:
    {//�赸�����ֽ�1
      Servo_Arg.Step_Num = 25;//20;
      Servo_Arg.Goal_Pos[2] = Servo_Arg.Init_Pos[2]+900;//��
      Servo_Arg.Goal_Pos[3] = Servo_Arg.Init_Pos[3]-900;//��
      Servo_Arg.Goal_Pos[8] = Servo_Arg.Init_Pos[8]-800;//��
      Servo_Arg.Goal_Pos[9] = Servo_Arg.Init_Pos[9]+800;//��
      Servo_Arg.Goal_Pos[6] = Servo_Arg.Init_Pos[6]-300;//ǰ��ڱ�
      Servo_Arg.Goal_Pos[7] = Servo_Arg.Init_Pos[7]+300;//ǰ��ڱ�
    }break; 
       case 0x1D:
    {//�赸�����ֽ�2
      Servo_Arg.Step_Num = 25;//20;
      DanceMove[1][2] = Servo_Arg.Init_Pos[2]+150;//��
      DanceMove[1][3] = Servo_Arg.Init_Pos[3]-150;//��
      DanceMove[1][4] = Servo_Arg.Init_Pos[4]-800;//��
      DanceMove[1][5] = Servo_Arg.Init_Pos[5]-800;//��
      DanceMove[1][8] = Servo_Arg.Init_Pos[8]-200;//ǰ��ڱ�
      DanceMove[1][9] = Servo_Arg.Init_Pos[9]+200;//ǰ��ڱ�
      //DanceMove[0][1] = Servo_Arg.Init_Pos[1]+250;//��
      DanceMove[0][2] = Servo_Arg.Init_Pos[2]+1000;//��
      DanceMove[0][6] = Servo_Arg.Init_Pos[6]-600;//ǰ��ڱ�
      DanceMove[0][3] = Servo_Arg.Init_Pos[3]-1000;//��
      DanceMove[0][7] = Servo_Arg.Init_Pos[7]+600;//ǰ��ڱ�
      DanceMove[0][8] = Servo_Arg.Init_Pos[8]-600;//ǰ��ڱ�
      DanceMove[0][9] = Servo_Arg.Init_Pos[9]+600;//ǰ��ڱ�
    }break; 
       case 0x1E:
    {//�赸�����ֽ�3
      Servo_Arg.Step_Num = 28;
//      Servo_Arg.Dance_Step_Num[1] = 30;
//      Servo_Arg.Dance_Step_Num[2] = 15;
//      Servo_Arg.Dance_Step_Num[3] = 30;
      DanceMove[0][2] = Servo_Arg.Init_Pos[2]+300;//��
      DanceMove[0][3] = Servo_Arg.Init_Pos[3]-300;//��
      DanceMove[0][5] = Servo_Arg.Init_Pos[5]-100;//��
      DanceMove[0][4] = Servo_Arg.Init_Pos[4]-100;//��
      
      DanceMove[3][1] = Servo_Arg.Init_Pos[1]+250;//ǰ��ڱ�
      DanceMove[3][3] = Servo_Arg.Init_Pos[3]-281;//ǰ��ڱ�
      DanceMove[3][5] = Servo_Arg.Init_Pos[5]-373;//��
      DanceMove[3][7] = Servo_Arg.Init_Pos[7]-498;//��
      DanceMove[3][9] = Servo_Arg.Init_Pos[9]+504;//��
      DanceMove[3][2] = Servo_Arg.Init_Pos[2]+883;//��
      DanceMove[3][4] = Servo_Arg.Init_Pos[4]-526;//��
      DanceMove[3][6] = Servo_Arg.Init_Pos[6]-1047;//��
      DanceMove[3][8] = Servo_Arg.Init_Pos[8]+50;//�⡢
      
      DanceMove[2][2] = Servo_Arg.Init_Pos[2]+300;//��
      DanceMove[2][3] = Servo_Arg.Init_Pos[3]-300;//��
      DanceMove[2][5] = Servo_Arg.Init_Pos[5]-100;//��
      DanceMove[2][4] = Servo_Arg.Init_Pos[4]-100;//��
      
      DanceMove[1][1] = Servo_Arg.Init_Pos[1]-250;//ǰ��ڱ�
      DanceMove[1][3] = Servo_Arg.Init_Pos[3]-883;//��
      DanceMove[1][5] = Servo_Arg.Init_Pos[5]-526;//��
      DanceMove[1][7] = Servo_Arg.Init_Pos[7]+1047;//��
      DanceMove[1][9] = Servo_Arg.Init_Pos[9]-50;//�⡢
      DanceMove[1][2] = Servo_Arg.Init_Pos[2]+281;//ǰ��ڱ�
      DanceMove[1][4] = Servo_Arg.Init_Pos[4]-373;//��
      DanceMove[1][6] = Servo_Arg.Init_Pos[6]+498;//��
      DanceMove[1][8] = Servo_Arg.Init_Pos[8]-504;//��
    }break; 
       case 0x20:
    {//�赸�����ֽ�1
      Servo_Arg.Step_Num = 15;//20;

      DanceMove[1][1] = Servo_Arg.Init_Pos[1]-250;//��
      DanceMove[1][3] = Servo_Arg.Init_Pos[3]-400;//��
      DanceMove[1][4] = Servo_Arg.Init_Pos[4]-400;//��
      DanceMove[1][7] = Servo_Arg.Init_Pos[7]+400;//ǰ��ڱ�
      
      DanceMove[0][1] = Servo_Arg.Init_Pos[1]+250;//��
      DanceMove[0][2] = Servo_Arg.Init_Pos[2]+400;//��
      DanceMove[0][5] = Servo_Arg.Init_Pos[5]-400;//��
      DanceMove[0][6] = Servo_Arg.Init_Pos[6]-400;//ǰ��ڱ�
    }break; 
       case 0x21:
    {//�赸������Ȧ
      Servo_Arg.Step_Num = 20;
//      Servo_Arg.Dance_Step_Num[1] = 25;
//      Servo_Arg.Dance_Step_Num[2] = 15;
//      Servo_Arg.Dance_Step_Num[3] = 25;

      DanceMove[0][5] = Servo_Arg.Init_Pos[5]-300;//��
      DanceMove[0][4] = Servo_Arg.Init_Pos[4]-300;//��
      DanceMove[0][3] = Servo_Arg.Init_Pos[3]-150;//��
      DanceMove[0][2] = Servo_Arg.Init_Pos[2]+150;//��
      
      DanceMove[3][6] = Servo_Arg.Init_Pos[6]+400;//ǰ��ڱ�
      DanceMove[3][7] = Servo_Arg.Init_Pos[7]+400;//ǰ��ڱ�
      DanceMove[3][1] = Servo_Arg.Init_Pos[1]-250;//��
      DanceMove[3][3] = Servo_Arg.Init_Pos[3]-400;//��
      DanceMove[3][2] = Servo_Arg.Init_Pos[2]+400;//��
      DanceMove[3][8] = Servo_Arg.Init_Pos[8]-400;//��
      DanceMove[3][9] = Servo_Arg.Init_Pos[9]-400;//��
      
      DanceMove[2][5] = Servo_Arg.Init_Pos[5]-300;//��
      DanceMove[2][4] = Servo_Arg.Init_Pos[4]-300;//��
      DanceMove[2][3] = Servo_Arg.Init_Pos[3]-150;//��
      DanceMove[2][2] = Servo_Arg.Init_Pos[2]+150;//��
      
      DanceMove[1][8] = Servo_Arg.Init_Pos[8]+400;//ǰ��ڱ�
      DanceMove[1][9] = Servo_Arg.Init_Pos[9]+400;//ǰ��ڱ�
      DanceMove[1][6] = Servo_Arg.Init_Pos[6]-400;//ǰ��ڱ�
      DanceMove[1][7] = Servo_Arg.Init_Pos[7]-400;//ǰ��ڱ�
      DanceMove[1][1] = Servo_Arg.Init_Pos[1]+250;//��
      DanceMove[1][3] = Servo_Arg.Init_Pos[3]-400;//��
      DanceMove[1][2] = Servo_Arg.Init_Pos[2]+400;//��

    }break; 
       case 0x22://����
    {//�赸�����ֽ�3
      Servo_Arg.Step_Num = 20;//20;
      DanceMove[0][2] = Servo_Arg.Init_Pos[2]+1100;//��
      DanceMove[0][4] = Servo_Arg.Init_Pos[4]-400;//��
      DanceMove[0][5] = Servo_Arg.Init_Pos[5]-400;//��
      DanceMove[0][3] = Servo_Arg.Init_Pos[3]-1100;//��
      DanceMove[0][6] = Servo_Arg.Init_Pos[6]-600;//ǰ��ڱ�
      DanceMove[0][7] = Servo_Arg.Init_Pos[7]+600;//ǰ��ڱ�

    }break; 
  case 0x23:
    {
//        Servo_Arg.Step_Num = 25;//25;
//        Servo_Arg.Goal_Pos[1] = Servo_Arg.Init_Pos[1]+500;//ͷ
//        Servo_Arg.Step_Num = 20;//30;
//        Servo_Arg.Goal_Pos[2] = Servo_Arg.Init_Pos[2]+1000;//��
          Servo_Arg.Step_Num = 20;//30;
          Servo_Arg.Goal_Pos[6] = Servo_Arg.Init_Pos[6]-1000;//��
    }break;
  default ://�ص���ʼλ��
    {  
      Servo_Arg.Step_Num = 20;//20;
    }break;
    
  }
  Servo_Arg.Dance_Flag = TRUE;        
}

//void TIM5_IRQHandler(void)   //TIM5�ж�
//{	
//  u8 static Step_Counter = 1;
//  u8 i;
//  if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
//  {	
//    if(Servo_Arg.Action_Flag)
//    {//ִ�ж���
//      for(i=1;i<NUM_OF_SERVO+1;i++)
//      {//����ÿ�������һ����Ҫ�����λ��
//        if(Servo_Arg.Goal_Pos[i] > Servo_Arg.Pre_Pos[i])
//          Servo_Arg.Step_Pos[i] = Servo_Arg.Pre_Pos[i] + ((Servo_Arg.Goal_Pos[i] - Servo_Arg.Pre_Pos[i]) * Step_Counter / Servo_Arg.Step_Num);
//        else
//          Servo_Arg.Step_Pos[i] = Servo_Arg.Pre_Pos[i] - ((Servo_Arg.Pre_Pos[i] - Servo_Arg.Goal_Pos[i]) * Step_Counter / Servo_Arg.Step_Num);   
//      }
//      for(i=1;i<NUM_OF_SERVO+1;i++)
//      {
//        Servo_Write_Word(i,P_GOAL_POSITION_L,Servo_Arg.Step_Pos[i]);
//        Delay_ms(6);
//      }    
//      Step_Counter++;
//      if(Step_Counter >= Servo_Arg.Step_Num)
//      {//˵�������һ�ζ���
//        for(i=1;i<NUM_OF_SERVO+1;i++)
//          Servo_Arg.Pre_Pos[i] = Servo_Arg.Goal_Pos[i];//���µ�ǰλ��
//        Step_Counter = 1;
//        Servo_Arg.Action_Flag = FALSE;
//        Servo_Arg.Init_Pos_Flag = TRUE;//׼������
//      }
//      else
//      {
//      }
//    }
//    else if(Servo_Arg.Init_Pos_Flag)
//    {//���س�ʼλ��
//      for(i=1;i<NUM_OF_SERVO+1;i++)
//      {//����ÿ�������һ����Ҫ�����λ��
//        if(Servo_Arg.Init_Pos[i] > Servo_Arg.Pre_Pos[i])
//          Servo_Arg.Step_Pos[i] = Servo_Arg.Pre_Pos[i] + ((Servo_Arg.Init_Pos[i] - Servo_Arg.Pre_Pos[i]) * Step_Counter / Servo_Arg.Step_Num);
//        else
//          Servo_Arg.Step_Pos[i] = Servo_Arg.Pre_Pos[i] - ((Servo_Arg.Pre_Pos[i] - Servo_Arg.Init_Pos[i]) * Step_Counter / Servo_Arg.Step_Num);   
//
//      }
//      for(i=1;i<NUM_OF_SERVO+1;i++)
//      {
//        Servo_Write_Word(i,P_GOAL_POSITION_L,Servo_Arg.Step_Pos[i]);
//        Delay_ms(6);
//      }    
//      Step_Counter++;
//      if(Step_Counter >= Servo_Arg.Step_Num)
//      {//˵���ص��˳�ʼλ��
//        Step_Counter = 1;
//        Servo_Arg.Init_Pos_Flag = FALSE;//�������
//        Servo_Torque_EN(FALSE);//�ر�Ť�����
//        for(i=1;i<NUM_OF_SERVO+1;i++)
//          Servo_Arg.Pre_Pos[i] = Servo_Arg.Init_Pos[i];//���µ�ǰλ��
//         USB_Send_Return_to_PC(ACTION_OBJ,OK_ARG);//������Ϣ
//         
//         //���س�ʼ״̬����
//         Eye_Action(0);
//      }
//    }
//    TIM_ClearITPendingBit(TIM5, TIM_IT_Update);  //���TIMx���жϴ�����λ:TIM �ж�Դ 	
//  }
//  TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
//}
