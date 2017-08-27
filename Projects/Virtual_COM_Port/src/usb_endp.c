/**
  ******************************************************************************
  * @file    usb_endp.c
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   Endpoint routines
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "usb_lib.h"
#include "usb_desc.h"
#include "usb_mem.h"
#include "hw_config.h"
#include "usb_istr.h"
#include "usb_pwr.h"
	//�����
#include "usb_type.h"
#include "usart.h"
#include "string.h"
	
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Interval between sending IN packets in frame number (1 frame = 1ms) */
#define VCOMPORT_IN_FRAME_INTERVAL             5

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
//uint8_t USB_Rx_Buffer[VIRTUAL_COM_PORT_DATA_SIZE];
extern  uint8_t USART_Rx_Buffer[];
extern uint32_t USART_Rx_ptr_out;
extern uint32_t USART_Rx_length;
extern uint8_t  USB_Tx_State;

extern void USB_SendBuf(uint8_t *_pTxBuf, uint8_t _ucLen);//,�������ݵĽӿں�����ͨ��ENDP1�������ݵ���λ��
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


///BLADE�Զ�����ӣ�ͨ��ENDP1�������ݵ���λ��
void USB_Send_Str(uint8_t *_pTxBuf)
{
  uint8_t _ucLen = strlen(_pTxBuf);
  UserToPMABufferCopy(_pTxBuf, ENDP1_TXADDR, _ucLen);
  SetEPTxCount(ENDP1, _ucLen);
  SetEPTxValid(ENDP1);
}
void USB_SendBuf(uint8_t *_pTxBuf, uint8_t _ucLen)
{
  UserToPMABufferCopy(_pTxBuf, ENDP1_TXADDR, _ucLen);
  SetEPTxCount(ENDP1, _ucLen);
  SetEPTxValid(ENDP1);
}//printf("begin,wait data download\r\n");

/*******************************************************************************
* Function Name  : EP1_IN_Callback
* Description    :
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void EP1_IN_Callback (void)
{
  uint16_t USB_Tx_ptr;
  uint16_t USB_Tx_length;
  
  if (USB_Tx_State == 1)
  {
    if (USART_Rx_length == 0) 
    {
      USB_Tx_State = 0;
    }
    else 
    {
      if (USART_Rx_length > VIRTUAL_COM_PORT_DATA_SIZE){
        USB_Tx_ptr = USART_Rx_ptr_out;
        USB_Tx_length = VIRTUAL_COM_PORT_DATA_SIZE;
        
        USART_Rx_ptr_out += VIRTUAL_COM_PORT_DATA_SIZE;
        USART_Rx_length -= VIRTUAL_COM_PORT_DATA_SIZE;    
      }
      else 
      {
        USB_Tx_ptr = USART_Rx_ptr_out;
        USB_Tx_length = USART_Rx_length;
        
        USART_Rx_ptr_out += USART_Rx_length;
        USART_Rx_length = 0;
      }
      UserToPMABufferCopy(&USART_Rx_Buffer[USB_Tx_ptr], ENDP1_TXADDR, USB_Tx_length);
      SetEPTxCount(ENDP1, USB_Tx_length);
      SetEPTxValid(ENDP1); 
    }
  }
}

/*******************************************************************************
* Function Name  : EP3_OUT_Callback
* Description    : USB���ݽ��յĻص����������ݴ���USB_Rx_Buffer�У���������USB������
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void EP3_OUT_Callback(void)
{/////////////ֱ�Ӱ���λ������������һ���Դ洢��USART_Data.PC�У�����ָ�����ݱ�־λ
//uint16_t USB_Rx_Cnt;
  /* Get the received data buffer and update the counter */
  ////USB_Rx_Cnt = USB_SIL_Read(EP3_OUT, USB_Rx_Buffer);ԭ���ĺ���
  USART_Data.USB.Pointer = USB_SIL_Read(EP3_OUT, USART_Data.USB.Data);//���ݳ��ȴ���Pointer������д��Data
  
  USART_Data.USB.Flag=TRUE;//���յ�����������֡
  /* USB data will be immediately processed, this allow next USB traffic being 
  NAKed till the end of the USART Xfer */
 //���Կ��ǲ���д�뵽usart1���Ͼ�usart1�޷������ж�
  //USB_To_USART_Send_Data(USART_Data.PC.Data,USART_Data.PC.Pointer);
 
  /* Enable the receive of data on EP3 */
  SetEPRxValid(ENDP3);
}
/*******************************************************************************
* Function Name  : SOF_Callback / INTR_SOFINTR_Callback
* Description    :
* Input          : None.
* Output         : None.
* Return         : None.
SOF,��ʵ��START OF FRAME�ļ�д������֡�׵���˼��ȫ���豸������5ms�ᷢ��һ��
*******************************************************************************/
void SOF_Callback(void)
{
  static uint32_t FrameCount = 0;
  
  if(bDeviceState == CONFIGURED)/*�豸״̬*/
  {
    if (FrameCount++ == VCOMPORT_IN_FRAME_INTERVAL)
    {
      /* Reset the frame counter */
      FrameCount = 0;
      
      /* Check the data to be sent through IN pipe */
      Handle_USBAsynchXfer();
    }
  }  
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

