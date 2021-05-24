/*
 * peripheral_task.c
 *
 *  Created on: 10-Apr-2021
 *      Author: pankaj.kumar
 */
#include "peripheral_task.h"

UART_HandleTypeDef huart1;
ATCOMMANDS FOrmat1 = {"ATV1",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};

ATCOMMANDS ECHO1 = {"ATE0",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};

 void peripheral_init(void)
 {
	  MX_GPIO_Init();
	  gsm.Flags.Start = true;
 }

 void gsm_init(void)
 {
	  MX_USART1_UART_Init();
	  HAL_UART_Receive_IT(&huart1, &Uart_RxData, 1);
	  gsm.Flags.GsmInitialised = true;
	  send_At_Command_Test(&FOrmat1);
	  send_At_Command_Test(&ECHO1);


 }
