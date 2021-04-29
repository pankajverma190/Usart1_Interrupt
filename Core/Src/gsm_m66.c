/*
 * gsm_m66.c
 *
 *  Created on: 21-Dec-2020
 *      Author: pankaj.kumar
 */

#include "gsm_m66.h"


Gsm_struct gsm;


int AtCommandTimer = 0;

ATCOMMANDS ECHO = {"ATE0",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
ATCOMMANDS Long_Format_Result = {"ATV1",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
ATCOMMANDS Short_Format_Result = {"ATV0",{"0\r","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
ATCOMMANDS Reset_Module = {"AT+CRESET",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};

ATCOMMANDS CCID = {"AT+CICCID",{"\r\n+CCID: ","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
ATCOMMANDS IMSI = {"AT+CIMI",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
//ATCOMMANDS IMEI = {"AT+CN",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
ATCOMMANDS IMEI = {"AT+CGSN",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
ATCOMMANDS Syncro_CLock = {"AT+CCLK?",{"\r\n+CCLK: ","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
ATCOMMANDS Signal_Quality = {"AT+CSQ",{"\r\n+CSQ: ","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
ATCOMMANDS Sim_Detect = {"AT+CPIN?",{"READY","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
ATCOMMANDS Operator_Details = {"AT+COPS?",{"\r\n+COPS:","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};

ATCOMMANDS Netwrok_Registration_Set = {"AT+CREG=1",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
ATCOMMANDS Netwrok_Registration_Get = {"AT+CREG?",{"\r\n+CREG:","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};

ATCOMMANDS GPRS_Registration_Set = {"AT+CGREG=1",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
ATCOMMANDS GPRS_Registration_Get = {"AT+CGREG?",{"\r\n+CGREG:","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
ATCOMMANDS Packet_Domain_Attach_Write = {"AT+CGETT=1",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
ATCOMMANDS Packet_Domain_detach_Write = {"AT+CGETT=0",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
ATCOMMANDS Packet_Domain_Read = {"AT+CGETT?",{"\r\n+CGETT:","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};

ATCOMMANDS PDP_Context_Activate = {"AT+CGACT=1",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
ATCOMMANDS PDP_Context_Deactivate = {"AT+CGACT=0",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};

ATCOMMANDS Define_PDP_Context_Write = {"AT+CGDCONT=1",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
ATCOMMANDS Define_PDP_Context_Read = {"AT+CGDCONT?",{"\r\n+CGDCONT:\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};


uint8_t send_At_Command_Test(ATCOMMANDS *atcommand)
{
	gsm.Flags.ATCommandResponceReceive = false;
	gsm.Flags.GsmErrorResponce = false;
	memset(gsm.RxData, 0, sizeof(gsm.RxData));
	gsm.RxDataCnt = 0;
	int i = 0;
	while(atcommand->command[i] != '\0')
	{
		HAL_UART_Transmit(&huart1, &atcommand->command[i],1,100);
		i++;
	}
	HAL_UART_Transmit(&huart1, &atcommand->delimit1,1,100);
	HAL_UART_Transmit(&huart1, &atcommand->delimit2,1,100);
	startTimer(&AtCommandTimer, atcommand->ResponseTime, false);
	while(gsm.Flags.ATCommandResponceReceive == false)
	{
		if(isTimerComplete(AtCommandTimer))                                         //create a delay till response is not received
		{
			break;
		}
	}
	stopTimer(AtCommandTimer);
	return 1;
}

//uint8_t send_At_Command_Test(ATCOMMANDS *atcommand , uint8_t Line_Feed_No)
//{
//	Line_Feed_Number = Line_Feed_No;
//	gsm.Flags.ATCommandResponceReceive = false;
//	memset(gsm.RxData, 0, sizeof(gsm.RxData));
//	gsm.RxDataCnt = 0;
//	int i = 0;
//	while((int)atcommand->command[i] != NULL)
//	{
//		HAL_UART_Transmit(&huart1, &atcommand->command[i],1,100);
//		i++;
//	}
//	HAL_UART_Transmit(&huart1, &atcommand->delimit1,1,100);
//	HAL_UART_Transmit(&huart1, &atcommand->delimit2,1,100);
//	startTimer(&AtCommandTimer, atcommand->ResponseTime, false);
//	while(gsm.Flags.ATCommandResponceReceive == false)
//	{
//		if(isTimerComplete(AtCommandTimer))                                         //create a delay till response is not received
//		{
//			break;
//		}
//	}
//	stopTimer(AtCommandTimer);
//	return 1;
//}

//void GSM_USART1_UART_Init(void)
//{
//	gsm_huart.Instance = USART1;
//	gsm_huart.Init.BaudRate = 115200;
//	gsm_huart.Init.WordLength = UART_WORDLENGTH_8B;
//	gsm_huart.Init.StopBits = UART_STOPBITS_1;
//	gsm_huart.Init.Parity = UART_PARITY_NONE;
//	gsm_huart.Init.Mode = UART_MODE_TX_RX;
//	gsm_huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
//	gsm_huart.Init.OverSampling = UART_OVERSAMPLING_16;
//	gsm_huart.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
//	gsm_huart.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
//  if (HAL_UART_Init(&gsm_huart) != HAL_OK)
//  {
//    Error_Handler();
//  }
//}

//void USART1_IRQHandler(void)
//{
//  /* USER CODE BEGIN USART1_IRQn 0 */
//
//  /* USER CODE END USART1_IRQn 0 */
//  HAL_UART_IRQHandler(&gsm_huart);
//
////
//  /* USER CODE END USART1_IRQn 1 */
//}



int gsm_state;
void gsm_task(void)
{
	uint8_t feedback = 0;
	switch(gsm_state)
	    {
	        case GSM_INIT:
	        {
	            if((gsm.Flags.Start == true)&&(gsm.Flags.GsmInitialised != true))
	            {
	            	peripheral_init();
	            	gsm_init();
//	                Uart_Init_Gsm(&UartConfig, &GsmPoPi, 9600);
//	                Initialise_Gsm_seperate(&GsmPoPi);
	            }

	            if(gsm.Flags.GsmInitialised)
	            {
	            	if(gsm_sim_Status())
	            	{
		            	gsm_ccid();
		            	gsm_imsi();
		            	gsm_imei();
		            	gsm_state = GSM_NETWROK_REG;
		            	break;
	            	}
	            	else
	            	{
	            		gsm_state = GSM_INIT;
	            	}

	            	//gsm_state = GSM_NETWORK_CHECK;
	            }
	        }
	        break;
	        case GSM_NETWROK_REG:
			{
				send_At_Command_Test(&Netwrok_Registration_Set);
				if(network_registration_status())
				{
					cops();
					gsm.Flags.ATCommandNetwrokRegistered=true;
					gsm_state = GSM_GPRS_CONFIG;
				}
				else
				{
					gsm.Flags.ATCommandNetwrokRegistered=false;
					gsm_state = GSM_NETWROK_REG;
					break;
				}

			}
			break;
	        case GSM_GPRS_CONFIG:
	        {
	        	//clock set or sync clock data with ME
	        	//

	        }
	        break;
	        case GSM_PACKET_READY:
	        {
	        	prepare_data_packet();
	        }
	        break;
	        case GSM_SOCKET_CONNECTION:
	        {

	        }
	        break;
	        case GSM_SOCKET_DATA_RECEIVE:
	        {

	        }
	        break;
	        case GSM_RESET:
	        {

	        }
	        break;
	    }

}


unsigned char* jump_char_fixed(unsigned char *pktPtr, char character)
{
    while(*pktPtr++ !=  character);
    return pktPtr;
}



void gsm_ccid()
{
	int i=0;
	send_At_Command_Test(&CCID);
	unsigned char *pktptr = &gsm.RxData[0];
	pktptr = jump_char_fixed(pktptr,':');
	pktptr++;
	while(*pktptr != '\r')
	{
		gsm.gsm_data.ccid[i++] = *pktptr;
		pktptr++;
	}
}


void gsm_imsi()
{
	int i=0;
	send_At_Command_Test(&IMSI);
	unsigned char *pktptr = &gsm.RxData[0];
	pktptr = jump_char_fixed(pktptr,'\n');
//	pktptr++;
	while(*pktptr != '\r')
	{
		gsm.gsm_data.imsi[i++] = *pktptr;
		pktptr++;
	}
}
void gsm_imei()
{
	int i=0;
	send_At_Command_Test(&IMEI);
	unsigned char *pktptr = &gsm.RxData[0];
	pktptr = jump_char_fixed(pktptr,'\n');
	//pktptr++;
	while(*pktptr != '\r')
	{
		gsm.gsm_data.imei[i++] = *pktptr;
		pktptr++;
	}
}

bool gsm_sim_Status()
{
	int i=0;
	send_At_Command_Test(&Sim_Detect);
	unsigned char *pktptr = &gsm.RxData[0];
	pktptr = jump_char_fixed(pktptr,':');
	pktptr++;
	while(*pktptr != '\r')
	{
		if(*pktptr == Sim_Detect.Responce[0][i])
			i++;
		else return false;
		pktptr++;
	}
	return true;
}



bool network_registration_status(void)
{
	send_At_Command_Test(&Netwrok_Registration_Get);
	unsigned char *pktptr = &gsm.RxData[0];
	pktptr = jump_char_fixed(pktptr,',');
	pktptr++;
	if(*pktptr == '1')
		return true;
	else
		return false;
}


void cops(void)
{
	int i=0;
	send_At_Command_Test(&Signal_Quality);
	unsigned char *pktptr = &gsm.RxData[0];
	pktptr = jump_char_fixed(pktptr,':');
	pktptr++;
	while(*pktptr != '\r')
	{
		gsm.gsm_data.imei[i++] = *pktptr;
		pktptr++;
	}
}

void prepare_data_packet(void)
{

}




void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1)
	{
//		Uart_RxData[gsm.RxDataCnt] = '\0';
//		gsm.Flags.ATCommandResponceReceive = true;
//		huart->pRxBuffPtr = Uart_RxData;
//		while(Uart_RxData[count] !='\0')
//		{
//			gsm.RxData[count] = Uart_RxData[count];
//			count++;
//		}
//		gsm.RxData[count] = '\0';
		gsm.RxData[gsm.RxDataCnt] = Uart_RxData;
		gsm.RxDataCnt = (1+gsm.RxDataCnt)% MAX_BUFFER_SIZE;
	}
	HAL_UART_Receive_IT(&huart1, &Uart_RxData, 1);
}

