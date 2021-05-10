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
ATCOMMANDS GPRS_Registration_Get = {"AT+CGREG?",{"\r\n+CGREG: 1,1","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
ATCOMMANDS Packet_Domain_Attach_Write = {"AT+CGATT=1",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
ATCOMMANDS Packet_Domain_detach_Write = {"AT+CGATT=0",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
ATCOMMANDS Packet_Domain_Read = {"AT+CGATT?",{"\r\n+CGATT:","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};

ATCOMMANDS PDP_Context_Activate = {"AT+CGACT=1,1",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
ATCOMMANDS PDP_Context_Deactivate = {"AT+CGACT=0",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
ATCOMMANDS PDP_Context_Read = {"AT+CGACT?",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};

ATCOMMANDS Define_PDP_Context_Write = {"AT+CGDCONT=1,""\"IP""\",""\"airtelgprs.com""\"",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
//ATCOMMANDS Define_PDP_Context_Write[3] = {
//										{"AT+CGDCONT=1,""\"IP""\",""\"airtelgprs.com""\"",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500},
//										{"AT+CGDCONT=2,""\"IP""\",""\"airtelgprs.com""\"",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500},
//										{"AT+CGDCONT=3,""\"IP""\",""\"airtelgprs.com""\"",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500},
//									};
ATCOMMANDS Define_PDP_Context_Read = {"AT+CGDCONT?",{"\r\n+CGDCONT:\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};

ATCOMMANDS TCPIP_Non_Transparent_Mode_Set = {"AT+CIPMODE=0",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};

ATCOMMANDS TCPIP_Direct_Mode_Set = {"AT+CIPRXGET=0",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};

// create socket
ATCOMMANDS CreateSocket = {"AT+NETOPEN",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',5000}; //returns a number identifying the socket

//ATCOMMANDS Socket_connection_Direct_Mode[10] = {
//												{"AT+CIPOPEN=0,""\"TCP""\",""\"13.126.165.4""\",4000",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',5000}, //returns a number identifying the socket};
//												{"AT+CIPOPEN=1,""\"TCP""\",""\"13.126.165.4""\",4000",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',5000},
//												{"AT+CIPOPEN=2,""\"TCP""\",""\"13.126.165.4""\",4000",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',5000},
//												{"AT+CIPOPEN=3,""\"TCP""\",""\"13.126.165.4""\",4000",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',5000},
//												{"AT+CIPOPEN=4,""\"TCP""\",""\"13.126.165.4""\",4000",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',5000},
//												{"AT+CIPOPEN=5,""\"TCP""\",""\"13.126.165.4""\",4000",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',5000},
//												{"AT+CIPOPEN=6,""\"TCP""\",""\"13.126.165.4""\",4000",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',5000},
//												{"AT+CIPOPEN=7,""\"TCP""\",""\"13.126.165.4""\",4000",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',5000},
//												{"AT+CIPOPEN=8,""\"TCP""\",""\"13.126.165.4""\",4000",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',5000},
//												{"AT+CIPOPEN=9,""\"TCP""\",""\"13.126.165.4""\",4000",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',5000}
//											};

ATCOMMANDS Socket_connection_Direct_Mode = {"AT+CIPOPEN=0,""\"TCP""\",""\"13.126.165.4""\",4000",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',5000}; //returns a number identifying the socket};

ATCOMMANDS TcpIp_Send_data = {"AT+CIPSEND=0,",{"\r\nOK\r\n+CIPSEND:","\r\n>","\r\n+CME ERROR"},{0,0,0},'\r','\n',5000}; //returns a number identifying the socket


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



static uint8_t gsm_state;
static uint8_t gprs_state = 0;
static uint8_t tcp_ip_state = 0;
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
	            	gsm_state = GSM_NETWROK_REG; 		// test

	            }
	        }
	        break;
	        case GSM_NETWROK_REG:
			{
				send_At_Command_Test(&Netwrok_Registration_Set);
//				if(network_registration_status())
//				{
//					cops();
//					gsm.Flags.ATCommandNetwrokRegistered=true;
//					gsm_state = GSM_GPRS_CONFIG;
//				}
//				else
//				{
//					gsm.Flags.ATCommandNetwrokRegistered=false;
//					gsm_state = GSM_NETWROK_REG;
//					break;
//				}
				gsm_state = GSM_GPRS_CONFIG;		// test
				gsm.Flags.ATCommandNetwrokRegistered=true;
			}
			break;
	        case GSM_GPRS_CONFIG:
	        {
	        	//clock set or sync clock data with ME

	        	 if(gsm.Flags.ATCommandNetwrokRegistered)               //second OR condition is to further close the socket
	        	 {
	        		 switch(gprs_state)
	        		 {
	        		 	 case GPRS_REGISTERTION:
	        		 	 {
	        		 		 int gprs_reg_status = 0;
	        		 		 SendCommandAndWaitForResponse(&GPRS_Registration_Set);
	        		 		 SendCommandAndWaitForResponse(&GPRS_Registration_Get);
	        		 		 char data[]= "\r\n+CGREG: 1,1\r\n\r\nOK\r\n";
	        		 		 int j=0;
	        		 		 while(data[j] != '\0')
	        		 		 {
	        		 			 gsm.RxData[j] = data[j];
	        		 			 j++;
	        		 		 }
	        		 		 gprs_reg_status = VerifyRespAndPrepForNxtStep(&GPRS_Registration_Get , 0);
	        		 		 if(gprs_reg_status)
	        	             {
	        		 			 gsm.Flags.ATCommandGPRSActivated = true;
	        		 			 gprs_state = GPRS_ATTACHMENT;
	        	             }
	        		 		 else
	        		 		 {
	        		 			 //if(retry_function(GSM_SLEEP, GPRS_ATTACHMENT, RETRY_GPRS))
	        		 			 gsm.Flags.ATCommandGPRSActivated = false;
	        		 		 }
	        		 	 }
	        		 	 break;
	        		 	 case GPRS_ATTACHMENT:
	        		 	 {
	        		 		 int gprs_attach_status = 0;
	        		 		 SendCommandAndWaitForResponse(&Packet_Domain_Attach_Write);
	        		 		 SendCommandAndWaitForResponse(&Packet_Domain_Read);
	        		 		 gprs_attach_status = VerifyRespAndPrepForNxtStep(&Packet_Domain_Read , 0);
	        		 		 if(gprs_attach_status)
	        		 		 {
	        		 			 gsm.Flags.GprsAttachment = true;
	        		 			 gprs_state = PDP_CONTEXT_PARA;
	        		 		 }
	        		 		 else
	        		 		 {
	        		 			// if(retry_function(GSM_SLEEP, GPRS_ATTACHMENT, RETRY_GPRS))
	        		 				 gsm.Flags.GprsAttachment = false;
	        		 		 }
	        		 	 }
	        		 	 break;
	        		 	 case PDP_CONTEXT_PARA:
	        		 	 {
	        		 		 int pdp_context_status = 0;
	        		 		 SendCommandAndWaitForResponse(&Define_PDP_Context_Write);
	        		 		SendCommandAndWaitForResponse(&Define_PDP_Context_Read);
	        		 		 pdp_context_status = VerifyRespAndPrepForNxtStep(&Define_PDP_Context_Read, 0);
	        		 		 if(pdp_context_status)
	        		 		 {
	        		 			 gsm.Flags.PdpContextPara = true;
	        		 			 gprs_state = ACTIVATE_PDP_CONTEXT;
	        		 		 }
	        		 		 else
	        		 		 {
	        		 			// if(retry_function(GSM_SLEEP, GPRS_ATTACHMENT, RETRY_GPRS))
	        		 				 gsm.Flags.PdpContextPara = false;
	        		 		 }
	        		 	 }
	        		 	 break;
	        		 	 case ACTIVATE_PDP_CONTEXT:
	        		 	 {
	        		 		 int activePdp_status = 0;
	        		 		 SendCommandAndWaitForResponse(&PDP_Context_Activate);
	        		 		SendCommandAndWaitForResponse(&PDP_Context_Read);
	        		 		 activePdp_status = VerifyRespAndPrepForNxtStep(&PDP_Context_Read, 0);
	        		 		 if(activePdp_status)
	        		 		 {
	        		 			 gsm.Flags.ActivePdpContext = true;
	        		 			 gprs_state = NON_TRANSPARENT_MODE;
	        		 			// gsm_state = GSM_PACKET_READY;
	        		 		 }
	        		 		 else
	        		 		 {
	        		 			 //   gsm_state = GSM_SLEEP;
	        		 	//		 if(retry_function(GSM_SLEEP, GPRS_ATTACHMENT, RETRY_GPRS))
	        		 				 gsm.Flags.ActivePdpContext = false;
	        		 		 }
	        		 	 }
	        		 	 break;
	 	        		case NON_TRANSPARENT_MODE:
	 	        		{
	 	        			send_At_Command_Test(&TCPIP_Non_Transparent_Mode_Set);
	 	        			gsm.Flags.SetTransparentMode = true;
	 	        			gprs_state = GPRS_ATTACHMENT;
	 	        			gsm_state = GSM_PACKET_READY;
	 	        		}
	 	        		break;
	        		 }
	        	 }
	        }
	        break;
	        case GSM_PACKET_READY:
	        {
	        	prepare_data_packet();
	        	gsm_state = GSM_TCPIP_STATE;
	        }
	        break;
	        case GSM_TCPIP_STATE:
	        {
	        		switch(tcp_ip_state)
	        		{
	        		case TCP_IP_SOCKET_CREATE:
	        		{
	        			int tcpip_status = 0;
	        			SendCommandAndWaitForResponse(&CreateSocket);
	        			tcpip_status = VerifyRespAndPrepForNxtStep(&CreateSocket, 0);
	        			if(tcpip_status)
	        			{
	        				gsm.Flags.SocketStart = true;
	        				tcp_ip_state = TCP_IP_SOCKET_SELECT_MODE;
	        			}
	        			else
	        			{
	        				//if(retry_function(GSM_SLEEP, GPRS_ATTACHMENT, RETRY_GPRS))
	        				gsm.Flags.SocketStart = false;
	        			}
	        		}
	        		break;
	        		case TCP_IP_SOCKET_SELECT_MODE:
	        		{
	        			send_At_Command_Test(&TCPIP_Direct_Mode_Set);
	        			int tcpip_mode_select = 0;
	        			SendCommandAndWaitForResponse(&TCPIP_Direct_Mode_Set);
	        			tcpip_mode_select = VerifyRespAndPrepForNxtStep(&TCPIP_Direct_Mode_Set, 0);
	        			if(tcpip_mode_select)
	        			{
	        				gsm.Flags.SocketDirectMode = true;
	        				tcp_ip_state = TCP_IP_CONNECTION;
	        			}
	        			else
	        			{
	        				//if(retry_function(GSM_SLEEP, GPRS_ATTACHMENT, RETRY_GPRS))
	        				gsm.Flags.SocketDirectMode = false;
	        			}
	        		}
	        		break;
	        		case TCP_IP_CONNECTION:
	        		{
	        			int tcpip_status = 0;
	        			SendCommandAndWaitForResponse(&Socket_connection_Direct_Mode);
	        			tcpip_status = VerifyRespAndPrepForNxtStep(&Socket_connection_Direct_Mode, 0);
	        			if(tcpip_status)
	        			{
	        				gsm.Flags.SocketConnectedDirectMode = true;
	        				tcp_ip_state = TCP_IP_SEND_DATA;
	        			}
	        			else
	        			{
	        				//if(retry_function(GSM_SLEEP, GPRS_ATTACHMENT, RETRY_GPRS))
	        				gsm.Flags.SocketConnectedDirectMode = false;
	        			}
	        		}
	        		break;
	        		case TCP_IP_SEND_DATA:
	        		{
	        			int tcpip_status = 0;
	        			SendCommandAndWaitForResponse(&TcpIp_Send_data);
	        			if(compareArray(gsm.RxData,&TcpIp_Send_data.Response[1][0],0,'\0'))
						{
	        				//data send
	        				HAL_UART_Transmit(&huart1,26,1,100);
						}
	        			else
	        			{
	        				break;
	        			}
	        			tcpip_status = VerifyRespAndPrepForNxtStep(&TcpIp_Send_data,':');
	        			if(tcpip_status)
	        			{
	        				gsm.Flags.SocketSendData = true;
	        				tcp_ip_state = TCP_IP_SOCKET_CREATE;
	        				gsm_state = GSM_SOCKET_DATA_RECEIVE;
	        			}
	        			else
	        			{
	        				//if(retry_function(GSM_SLEEP, GPRS_ATTACHMENT, RETRY_GPRS))
	        				gsm.Flags.SocketSendData = false;
	        			}
	        		}
	        		break;
	        		}
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


uint8_t VerifyRespAndPrepForNxtStep(ATCOMMANDS *At_Command, char delimiter)
{
    if(!compareArray(gsm.RxData, &At_Command->Response[0][0] , 0, delimiter))
    {
       // gsm_state = GSM_RESET_MODULE; //Pankaj Verma
        return 0;
    }

//    if(At_Command == &CreateSocket)
//    {
//        gsm.SocketNo = (gsm.RxData[10] - '0');
//    }
//
//    if(At_Command == &ConnectSocket[gsm.SocketNo])
//    {
//       // Gsm.Flags.GprsInitialised = TRUE;
//    }
//
//    if(At_Command == &CloseSocket[gsm.SocketNo])
//    {
//        gsm_state = GSM_RESET;
//    }
    return 1;
}


void SendCommandAndWaitForResponse(ATCOMMANDS *At_Command)
{
	send_At_Command_Test(At_Command);
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
		if(*pktptr == Sim_Detect.Response[0][i])
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


// git add .
//  git status
// git commit -m "gsm verification function"
// git push -u origin master


//gs-N-*LSIXfJyAhEGechtFQraiq*T;fA
//
//
//administrator
//
//
//13.126.165.4
