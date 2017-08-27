
#ifndef __PACK_H
#define __PACK_H
typedef struct 
{
	u8 Head;		        //֡ͷ
	u8 Obj;				//����
	u8 Cmd;				//ָ��
	u8 Arg[28];			//����
	u8 End;		                //֡β
	
	u8 Arg_Lenth;		        //��������
}USB_Data_Frame_TypDef;

extern USB_Data_Frame_TypDef USB_Data_Frame_Tx;//������
extern USB_Data_Frame_TypDef USB_Data_Frame_Rx;//�����ã���USART�ж��д���USART_DATA�У��ں�̨����������ýṹ��ֽ�USART����

void USB_Send_Data_Frame(USB_Data_Frame_TypDef *data_frame);
bool USB_Rec_Data_Frame(USB_Data_Frame_TypDef *data_frame);
void USB_Send_Return_to_PC(u8 obj,u8 arg);
void USB_Send_Data_to_PC(u8 obj,u8 cmd,u8 *arg,u8 arg_len);

extern void USB_SendBuf(uint8_t *_pTxBuf, uint8_t _ucLen);
extern void USB_Send_Str(uint8_t *_pTxBuf);
#endif
