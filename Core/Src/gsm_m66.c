/*
 * gsm_m66.c
 *
 *  Created on: 21-Dec-2020
 *      Author: pankaj.kumar
 */

#include "gsm_m66.h"


Gsm_struct gsm;


int AtCommandTimer = 0;

ATCOMMANDS ECHO = {"ATE0",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',100};
//ATCOMMANDS Long_Format_Result = {"ATV1",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',100};
//ATCOMMANDS Short_Format_Result = {"ATV0",{"0\r","","\r\n+CME ERROR"},{0,0,0},'\r','\n',100};
ATCOMMANDS Reset_Module = {"AT+CRESET",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
ATCOMMANDS Automatic_Time_Zone_Update = {"AT+CTZU=1",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};

ATCOMMANDS Save_user_setting_to_ME = {"AT&W0",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};


ATCOMMANDS CCID = {"AT+CICCID",{"\r\n+CCID: ","","\r\n+CME ERROR"},{0,0,0},'\r','\n',200};
ATCOMMANDS IMSI = {"AT+CIMI",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',200};
//ATCOMMANDS IMEI = {"AT+CN",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
ATCOMMANDS IMEI = {"AT+CGSN",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',200};
ATCOMMANDS Syncro_CLock = {"AT+CCLK?",{"\r\n+CCLK: ","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
ATCOMMANDS Signal_Quality = {"AT+CSQ",{"\r\n+CSQ: ","","\r\n+CME ERROR"},{0,0,0},'\r','\n',200};
ATCOMMANDS Sim_Detect = {"AT+CPIN?",{"READY","","\r\n+CME ERROR"},{0,0,0},'\r','\n',200};
ATCOMMANDS Operator_Details = {"AT+COPS?",{"\r\n+COPS:","","\r\n+CME ERROR"},{0,0,0},'\r','\n',200};

ATCOMMANDS Netwrok_Registration_Set = {"AT+CREG=1",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',200};
ATCOMMANDS Netwrok_Registration_Get = {"AT+CREG?",{"\r\n+CREG: 1,1","","\r\n+CME ERROR"},{0,0,0},'\r','\n',200};

ATCOMMANDS GPRS_Registration_Set = {"AT+CGREG=1",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',200};
ATCOMMANDS GPRS_Registration_Get = {"AT+CGREG?",{"\r\n+CGREG: 1,1","","\r\n+CME ERROR"},{0,0,0},'\r','\n',200};
ATCOMMANDS Packet_Domain_Attach_Write = {"AT+CGATT=1",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',200};
ATCOMMANDS Packet_Domain_detach_Write = {"AT+CGATT=0",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',200};
ATCOMMANDS Packet_Domain_Read = {"AT+CGATT?",{"\r\n+CGATT:","","\r\n+CME ERROR"},{0,0,0},'\r','\n',200};

ATCOMMANDS PDP_Context_Activate = {"AT+CGACT=1,1",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',200};
ATCOMMANDS PDP_Context_Deactivate = {"AT+CGACT=0,1",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',200};
ATCOMMANDS PDP_Context_Read = {"AT+CGACT?",{"\r\n+CGACT: 1,1","","\r\n+CME ERROR"},{0,0,0},'\r','\n',200};

ATCOMMANDS Define_PDP_Context_Write = {"AT+CGDCONT=1,""\"IP""\",""\"airtelgprs.com""\"",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',200};
//ATCOMMANDS Define_PDP_Context_Write[3] = {
//										{"AT+CGDCONT=1,""\"IP""\",""\"airtelgprs.com""\"",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500},
//										{"AT+CGDCONT=2,""\"IP""\",""\"airtelgprs.com""\"",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500},
//										{"AT+CGDCONT=3,""\"IP""\",""\"airtelgprs.com""\"",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500},
//									};
/* need to be check with full format */
//ATCOMMANDS Define_PDP_Context_Read = {"AT+CGDCONT?",{"\r\n+AT+CGDCONT: 1,""\"IP""\",""\"airtelgprs.com""\"","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
ATCOMMANDS Define_PDP_Context_Read = {"AT+CGDCONT?",{"\r\n+CGDCONT: 1,""\"IP""\"","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};

ATCOMMANDS TCPIP_Non_Transparent_Mode_Set = {"AT+CIPMODE=0",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',200};
ATCOMMANDS TCPIP_Non_Transparent_Mode_GET= {"AT+CIPMODE?",{"\r\n+CIPMODE: 0","","\r\n+CME ERROR"},{0,0,0},'\r','\n',200};

ATCOMMANDS TCPIP_Direct_Mode_Set = {"AT+CIPRXGET=0",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',200};

// create socket
ATCOMMANDS CreateSocket = {"AT+NETOPEN",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',1000}; //returns a number identifying the socket

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

ATCOMMANDS Socket_connection_Direct_Mode = {"AT+CIPOPEN=0,""\"TCP""\",""\"13.126.165.4""\",4000",{"\r\nOK\r\n\r\n+CIPOPEN: 0,","","\r\n+CME ERROR"},{0,0,0},'\r','\n',1000}; //returns a number identifying the socket};

ATCOMMANDS TcpIp_Send_data = {"AT+CIPSEND=0,",{"\r\n>\r\nOK\r\n\r\n+CIPSEND:","","\r\n+CME ERROR"},{0,0,0},'\r','\n',5000}; //returns a number identifying the socket

ATCOMMANDS Socket_closed_connection_Direct_Mode = {"AT+CIPCLOSE=0",{"\r\nOK\r\n\r\n+CIPCLOSE: 0","","\r\n+CME ERROR"},{0,0,0},'\r','\n',100};

ATCOMMANDS Socket_Closed = {"AT+NETCLOSE",{"\r\nOK\r\n\r\n+NETCLOSE: 0","","\r\n+CME ERROR"},{0,0,0},'\r','\n',100};


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

	switch(gsm_state)
	    {
	        case GSM_INIT:
	        {
	            if((gsm.Flags.Start == true)&&(gsm.Flags.GsmInitialised != true))
	            {
	            	//peripheral_init();
	            	gsm_init();
	          	  send_At_Command_Test(&Automatic_Time_Zone_Update);
	          	  send_At_Command_Test(&Save_user_setting_to_ME);
	            }

	            if(gsm.Flags.GsmInitialised)
	            {
	            	if(gsm_sim_Status())
	            	{
		            	gsm_ccid();
		            	gsm_imsi();
		            	gsm_imei();
		            	gsm.Flags.SimStatusChecked=true;
		            	gsm_state = GSM_NETWROK_REG;
		            	break;
	            	}
	            	else
	            	{
	            		gsm_state = GSM_INIT;
	            	}
	            	//gsm_state = GSM_TCPIP_STATE; 		// test
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
				//gsm_state = GSM_GPRS_CONFIG;		// test
				//gsm.Flags.ATCommandNetwrokRegistered=true;
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
	        		 		uint8_t gprs_reg_status = 0;
	        		 		 SendCommandAndWaitForResponse(&GPRS_Registration_Set);
	        		 		 SendCommandAndWaitForResponse(&GPRS_Registration_Get);
//	        		 		 char data[]= "\r\n+CGREG: 1,1\r\n\r\nOK\r\n";
//	        		 		 int j=0;
//	        		 		 while(data[j] != '\0')
//	        		 		 {
//	        		 			 gsm.RxData[j] = data[j];
//	        		 			 j++;
//	        		 		 }
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
	        		 		uint8_t gprs_attach_status = 0;
	        		 		 SendCommandAndWaitForResponse(&Packet_Domain_Attach_Write);
	        		 		 SendCommandAndWaitForResponse(&Packet_Domain_Read);
	        		 		 gprs_attach_status = VerifyRespAndPrepForNxtStep(&Packet_Domain_Read , 0);
	        		 		//gprs_attach_status = 1;
	        		 		 if(gprs_attach_status)
	        		 		 {
	        		 			 gsm.Flags.GprsAttachment = true;
	        		 			 gprs_state = PDP_CONTEXT_PARA;
	        		 		 }
	        		 		 else
	        		 		 {
	        		 			SendCommandAndWaitForResponse(&Packet_Domain_detach_Write);
	        		 			// if(retry_function(GSM_SLEEP, GPRS_ATTACHMENT, RETRY_GPRS))
	        		 				 gsm.Flags.GprsAttachment = false;
	        		 		 }
	        		 	 }
	        		 	 break;
	        		 	 case PDP_CONTEXT_PARA:
	        		 	 {
	        		 		uint8_t pdp_context_status = 0;
	        		 		 SendCommandAndWaitForResponse(&Define_PDP_Context_Write);
	        		 		SendCommandAndWaitForResponse(&Define_PDP_Context_Read);
	        		 		 pdp_context_status = VerifyRespAndPrepForNxtStep(&Define_PDP_Context_Read, 0);
	        		 		//pdp_context_status = 1;
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
	        		 		uint8_t activePdp_status = 0;
	        		 		 SendCommandAndWaitForResponse(&PDP_Context_Activate);
	        		 		SendCommandAndWaitForResponse(&PDP_Context_Read);
	        		 		 activePdp_status = VerifyRespAndPrepForNxtStep(&PDP_Context_Read, 0);
	        		 		//activePdp_status = 1;
	        		 		 if(activePdp_status)
	        		 		 {
	        		 			 gsm.Flags.ActivePdpContext = true;
	        		 			 gprs_state = NON_TRANSPARENT_MODE;
	        		 			// gsm_state = GSM_PACKET_READY;
	        		 		 }
	        		 		 else
	        		 		 {
	        		 			SendCommandAndWaitForResponse(&PDP_Context_Deactivate);
	        		 			 //   gsm_state = GSM_SLEEP;
	        		 	//		 if(retry_function(GSM_SLEEP, GPRS_ATTACHMENT, RETRY_GPRS))
	        		 				 gsm.Flags.ActivePdpContext = false;
	        		 		 }
	        		 	 }
	        		 	 break;
	 	        		case NON_TRANSPARENT_MODE:
	 	        		{
	 	        			send_At_Command_Test(&TCPIP_Non_Transparent_Mode_Set);
	 	        			send_At_Command_Test(&TCPIP_Non_Transparent_Mode_GET);
	 	        			uint8_t non_transparent_status = 0;
	 	        			non_transparent_status = VerifyRespAndPrepForNxtStep(&TCPIP_Non_Transparent_Mode_GET, 0);
	 	        			//non_transparent_status = 1;
	 	        			if(non_transparent_status)
	 	        			{
	 	        				gsm.Flags.SetTransparentMode = true;
	 	        				gprs_state = GPRS_ATTACHMENT;
	 	        				gsm_state = GSM_PACKET_READY;
	 	        			}
	 	        			else
	 	        			{
	 	        				gsm.Flags.SetTransparentMode = false;
	 	        				gprs_state = NON_TRANSPARENT_MODE;

	 	        			}
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
	        			uint8_t tcpip_status = 0;
	        			SendCommandAndWaitForResponse(&CreateSocket);
	        			tcpip_status = VerifyRespAndPrepForNxtStep(&CreateSocket, 0);
	        			//tcpip_status = 1;
	        			if(tcpip_status)
	        			{
	        				gsm.Flags.SocketStart = true;
	        				tcp_ip_state = TCP_IP_SOCKET_SELECT_MODE;
	        			}
	        			else
	        			{
	        				//if(retry_function(GSM_SLEEP, GPRS_ATTACHMENT, RETRY_GPRS))
		        			SendCommandAndWaitForResponse(&Socket_closed_connection_Direct_Mode);
		        			SendCommandAndWaitForResponse(&Socket_Closed);
	        				gsm.Flags.SocketStart = false;
	        			}
	        		}
	        		break;
	        		case TCP_IP_SOCKET_SELECT_MODE:
	        		{
	        			uint8_t tcpip_mode_select = 0;
	        			SendCommandAndWaitForResponse(&TCPIP_Direct_Mode_Set);
	        			tcpip_mode_select = VerifyRespAndPrepForNxtStep(&TCPIP_Direct_Mode_Set, 0);
	        			//tcpip_mode_select = 1;
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
	        			uint8_t tcpip_status = 0;
	        			SendCommandAndWaitForResponse(&Socket_connection_Direct_Mode);
	        			tcpip_status = VerifyRespAndPrepForNxtStep(&Socket_connection_Direct_Mode, 0);
	        			//tcpip_status = 1;
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
	        			uint8_t tcpip_status = 0, ctrl_z = 0x1A;
	        			//char tx_data[]="STX,HELLO DS GROUP SEND DATA FROM STM32,ETX";
	        			//char tx_data[]="Quectel’s passion for a smarter world drives us to accelerate IoT innovation. A highly customer-centric organization, we create superior cellular and GNSS modules and antennas backed by outstanding support and services. Our growing global team of over 3000 professionals, the largest in the IoT modules industry worldwide, ensures we are first to market and continue to set the pace of development. Listed on the Shanghai Stock Exchange (603236.SS), our international leadership is devoted to advancing IoT across the globe.";
	        			SendCommandAndWaitForResponse(&TcpIp_Send_data);
	        			GenerateStausPacket();
//	        			HAL_UART_Transmit(&huart1,&gsm.TxData,sizeof(gsm.TxData),1000);
//	        			HAL_UART_Transmit(&huart1,&ctrl_z,sizeof(ctrl_z),100);
	        			if(compareArray(gsm.RxData,&TcpIp_Send_data.Response[1][0],0,'\0'))
						{
	        				//data send
	        				HAL_UART_Transmit(&huart1,&gsm.TxData,sizeof(gsm.TxData),1000);

	        				//HAL_UART_Transmit(&huart1,&tx_data,sizeof(tx_data),1000);
	        				HAL_UART_Transmit(&huart1,&ctrl_z,sizeof(ctrl_z),100);
						}
	        			else
	        			{
	        				break;
	        			}
	        			delayMiliSec(1000);
	        			tcpip_status = VerifyRespAndPrepForNxtStep(&TcpIp_Send_data,0);
	        			//tcpip_status = 1;
	        			if(tcpip_status)
	        			{
	        				gsm.Flags.SocketSendData = true;
	        				tcp_ip_state = TCP_IP_SOCKET_CREATE;
	        				gsm_state = GSM_SOCKET_DATA_RECEIVE;
	        				gsm.RxOperation = 0;
	        				gsm.RxDataCnt = 0;
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
	        	uint8_t receive_status = 0;
	        	memset(gsm.RxData, 0, sizeof(gsm.RxData));
	        	startTimer(&AtCommandTimer, 10000, false);
	        	while(gsm.Flags.ATCommandResponceReceive == false)
	        	{
	        		if(isTimerComplete(AtCommandTimer))
	        			break;
	        	}

	        	stopTimer(AtCommandTimer);
	        	if(gsm.RxOperation == true)
	        	{
	        		if(compareArray(gsm.RxData, "\r\nRECV FROM:13.126.165.4:4000\r\n+IPD", 0, '\0'))
	        		{
	        			gsm.Flags.ReceivedData = true;
	        			gsm.Flags.GsmReset = false;
	        			serverdatasave();
	        			SendCommandAndWaitForResponse(&Socket_closed_connection_Direct_Mode);
	        			SendCommandAndWaitForResponse(&Socket_Closed);
	        			gsm.RxOperation = false;
	        			gsm_state = GSM_SLEEP;
	        		}
	        		else
	        		{
	        			//tcp_ip_state = TCP_IP_CONNECTION;
	        			tcp_ip_state = TCP_IP_SEND_DATA;
	        			gsm_state = GSM_TCPIP_STATE;
	        			gsm.Flags.ReceivedData = false;
	        			gsm.RxOperation = false;
	        			break;
	        		}
	        	}
	        }
	        break;
	        case GSM_SLEEP:
	        {
	        	gsm_state = GSM_RESET;
	        	gsm.Flags.GsmSleep = true;
	        }
	        break;
	        case GSM_RESET:
	        {
	        	send_At_Command_Test(&Reset_Module);
	      //  	memset(gsm.Flags,0,sizeof(gsm.Flags));
	      //  	memset(gsm,0,sizeof(gsm));
	        	startTimer(&AtCommandTimer, 50000, false);
	        	while(isTimerComplete(AtCommandTimer))
	        	{
		        	gsm.Flags.GsmInitialised = true;
		        	gsm.Flags.Start = true;
		        	gsm.Flags.GsmReset = true;
		        	gsm_state = GSM_INIT;
		        	stopTimer(AtCommandTimer);
	        	}

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

void serverdatasave()
{
	int i=0;  				//    \r\nRECV FROM:13.126.165.4:4000\r\n+IPD
	unsigned char *pktptr = &gsm.RxData[0];
	pktptr = jump_char_fixed(pktptr,':');
	while(*pktptr != ':')
	{
		gsm.gsm_data.Response_IP[i++] = *pktptr;
		pktptr++;
	}
	i=0;
	while(*pktptr != '\r')
	{
		gsm.gsm_data.Response_Port[i++] = *pktptr;
		pktptr++;
	}
	pktptr++;
	pktptr++;
	pktptr++;
	pktptr++;
	pktptr++;
	i=0;
	char count[] = "\0";
	while(*pktptr != '\r')
	{
		count[i++] = *pktptr;
		pktptr++;
	}
	convert_char_to_int_and_store(count,&gsm.gsm_data.data_receive_count,4);
	pktptr++;
	i=0;
	while(*pktptr != '\0')
	{
		gsm.gsm_data.server_data[i++] = *pktptr;
		pktptr++;
	}
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
	//pktptr++;
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
		gsm.gsm_data.cops[i++] = *pktptr;
		pktptr++;
	}
}

void prepare_data_packet(void)
{
	date_time_status();
	gsm.gsm_data.FC_CONFIGRATION = FC_ALERT;
	//gsm.gsm_data.server_data[] = "data send to server";
}
void date_time_status()
{
	int i=0;
	send_At_Command_Test(&Syncro_CLock);		//   +CCLK: "21/03/26,15:03:29+22"
	unsigned char *pktptr = &gsm.RxData[0];
	pktptr = jump_char_fixed(pktptr,'"');
	pktptr++;
	while(*pktptr != ',')
	{
		gsm.gsm_data.date_time.date[i++] = *pktptr;
		pktptr++;
	}
	pktptr++;
	while(*pktptr != '+')
	{
		gsm.gsm_data.date_time.time[i++] = *pktptr;
		pktptr++;
	}

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
		gsm.RxOperation = true;
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

//
//ATCOMMANDS ECHO = {"ATE0",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
//ATCOMMANDS Long_Format_Result = {"ATV1",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
//ATCOMMANDS Short_Format_Result = {"ATV0",{"0\r","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
//ATCOMMANDS Reset_Module = {"AT+CRESET",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
//
//ATCOMMANDS CCID = {"AT+CICCID",{"\r\n+CCID: ","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
//ATCOMMANDS IMSI = {"AT+CIMI",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
////ATCOMMANDS IMEI = {"AT+CN",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
//ATCOMMANDS IMEI = {"AT+CGSN",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
//ATCOMMANDS Syncro_CLock = {"AT+CCLK?",{"\r\n+CCLK: ","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
//ATCOMMANDS Signal_Quality = {"AT+CSQ",{"\r\n+CSQ: ","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
//ATCOMMANDS Sim_Detect = {"AT+CPIN?",{"READY","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
//ATCOMMANDS Operator_Details = {"AT+COPS?",{"\r\n+COPS:","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
//
//ATCOMMANDS Netwrok_Registration_Set = {"AT+CREG=1",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
//ATCOMMANDS Netwrok_Registration_Get = {"AT+CREG?",{"\r\n+CREG: 1,1","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
//
//ATCOMMANDS GPRS_Registration_Set = {"AT+CGREG=1",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
//ATCOMMANDS GPRS_Registration_Get = {"AT+CGREG?",{"\r\n+CGREG: 1,1","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
//ATCOMMANDS Packet_Domain_Attach_Write = {"AT+CGATT=1",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
//ATCOMMANDS Packet_Domain_detach_Write = {"AT+CGATT=0",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
//ATCOMMANDS Packet_Domain_Read = {"AT+CGATT?",{"\r\n+CGATT:","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
//
//ATCOMMANDS PDP_Context_Activate = {"AT+CGACT=1,1",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
//ATCOMMANDS PDP_Context_Deactivate = {"AT+CGACT=0,1",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
//ATCOMMANDS PDP_Context_Read = {"AT+CGACT?",{"\r\n+CGACT: 1,1","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
//
//ATCOMMANDS Define_PDP_Context_Write = {"AT+CGDCONT=1,""\"IP""\",""\"airtelgprs.com""\"",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
////ATCOMMANDS Define_PDP_Context_Write[3] = {
////										{"AT+CGDCONT=1,""\"IP""\",""\"airtelgprs.com""\"",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500},
////										{"AT+CGDCONT=2,""\"IP""\",""\"airtelgprs.com""\"",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500},
////										{"AT+CGDCONT=3,""\"IP""\",""\"airtelgprs.com""\"",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500},
////									};
///* need to be check with full format */
////ATCOMMANDS Define_PDP_Context_Read = {"AT+CGDCONT?",{"\r\n+AT+CGDCONT: 1,""\"IP""\",""\"airtelgprs.com""\"","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
//ATCOMMANDS Define_PDP_Context_Read = {"AT+CGDCONT?",{"\r\n+CGDCONT: 1,""\"IP""\"","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
//
//ATCOMMANDS TCPIP_Non_Transparent_Mode_Set = {"AT+CIPMODE=0",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
//ATCOMMANDS TCPIP_Non_Transparent_Mode_GET= {"AT+CIPMODE?",{"\r\n+CIPMODE: 0","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
//
//ATCOMMANDS TCPIP_Direct_Mode_Set = {"AT+CIPRXGET=0",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
//
//// create socket
//ATCOMMANDS CreateSocket = {"AT+NETOPEN",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',5000}; //returns a number identifying the socket
//
////ATCOMMANDS Socket_connection_Direct_Mode[10] = {
////												{"AT+CIPOPEN=0,""\"TCP""\",""\"13.126.165.4""\",4000",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',5000}, //returns a number identifying the socket};
////												{"AT+CIPOPEN=1,""\"TCP""\",""\"13.126.165.4""\",4000",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',5000},
////												{"AT+CIPOPEN=2,""\"TCP""\",""\"13.126.165.4""\",4000",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',5000},
////												{"AT+CIPOPEN=3,""\"TCP""\",""\"13.126.165.4""\",4000",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',5000},
////												{"AT+CIPOPEN=4,""\"TCP""\",""\"13.126.165.4""\",4000",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',5000},
////												{"AT+CIPOPEN=5,""\"TCP""\",""\"13.126.165.4""\",4000",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',5000},
////												{"AT+CIPOPEN=6,""\"TCP""\",""\"13.126.165.4""\",4000",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',5000},
////												{"AT+CIPOPEN=7,""\"TCP""\",""\"13.126.165.4""\",4000",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',5000},
////												{"AT+CIPOPEN=8,""\"TCP""\",""\"13.126.165.4""\",4000",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',5000},
////												{"AT+CIPOPEN=9,""\"TCP""\",""\"13.126.165.4""\",4000",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',5000}
////											};
//
//ATCOMMANDS Socket_connection_Direct_Mode = {"AT+CIPOPEN=0,""\"TCP""\",""\"13.126.165.4""\",4000",{"\r\nOK\r\n\r\n+CIPOPEN: 0,","","\r\n+CME ERROR"},{0,0,0},'\r','\n',5000}; //returns a number identifying the socket};
//
//ATCOMMANDS TcpIp_Send_data = {"AT+CIPSEND=0,",{"\r\n>\r\nOK\r\n\r\n+CIPSEND:","","\r\n+CME ERROR"},{0,0,0},'\r','\n',5000}; //returns a number identifying the socket
//
//ATCOMMANDS Socket_closed_connection_Direct_Mode = {"AT+CIPCLOSE=0",{"\r\nOK\r\n\r\n+CIPCLOSE: 0","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
//
//ATCOMMANDS Socket_Closed = {"AT+NETCLOSE",{"\r\nOK\r\n\r\n+NETCLOSE: 0","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
//

