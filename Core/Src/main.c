/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "include_file.h"


//uint8_t TxData [] = "HELLO_WORLD\r\n";
//uint8_t atcom[] = "ok\r\n";

 Gsm_struct gsm;


//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//	uint8_t count = 0;
//	if(huart->Instance == USART1)
//	{
//		gsm.Flags.ATCommandResponceReceive = true;
//		//huart->pRxBuffPtr = RxData;
//		gsm.RxDataCnt = huart->RxXferCount;
//		while(RxData[count] !='\0')
//		{
//			gsm.RxData[count] = RxData[count];
//			count++;
//		}
//	}
//
//	HAL_UART_Receive_IT(&huart1, RxData, MAX_BUFFER_SIZE);
//}

/* Private function prototypes -----------------------------------------------*/


//uint8_t send_At_Command_Test(ATCOMMANDS *atcommand , uint8_t Line_Feed_No);

//
//int AtCommandTimer = 0;
///**
//  * @brief  The application entry point.
//  * @retval int    AT+CICCID
//  */
//ATCOMMANDS ECHO = {"ATE0",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
//ATCOMMANDS CCID = {"AT+CICCID",{"\r\n+CCID: ","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
//ATCOMMANDS IMSI = {"AT+CIMI",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
//ATCOMMANDS IMEI = {"AT+CGSN",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
//ATCOMMANDS Syncro_CLock = {"AT+CCLK?",{"\r\n+CCLK: ","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
//ATCOMMANDS Signal_Quality = {"AT+CSQ",{"\r\n+CSQ: ","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
//ATCOMMANDS Sim_Detect = {"AT+CPIN?",{"\r\n+CPIN: ","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
//ATCOMMANDS Operator_Details = {"AT+COPS?",{"\r\n+COPS:","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};

int main(void)

{

  HAL_Init();
  SystemClock_Config();

  peripheral_init();
//  MX_GPIO_Init();
//  MX_USART1_UART_Init();
  int feedback= 0;
//  HAL_UART_Receive_IT(&huart1, Uart_RxData, MAX_BUFFER_SIZE);
//  HAL_UART_Transmit(&huart1, TxData,sizeof(TxData),100);
//  for(int i=0 ;atcom[i]!='\0';i++)
//  {
//	  HAL_UART_Transmit(&huart1, &atcom[i],1,100);
//  }

 // feedback = send_At_Command_Test(&Req_Mfr_Idt);
// feedback = send_At_Command_Test(&ECHO , 2);
////
// feedback = send_At_Command_Test(&IMEI, 4);
//
// feedback = send_At_Command_Test(&CCID, 4);
////
// feedback = send_At_Command_Test(&IMSI, 4);
//
// feedback = send_At_Command_Test(&Sim_Detect, 4);
//
// feedback = send_At_Command_Test(&Signal_Quality, 4);
//
// feedback = send_At_Command_Test(&Syncro_CLock, 4);

  gsm_task();
 while (1)
  {

  }
}
//
//uint8_t send_At_Command_Test(ATCOMMANDS *atcommand , uint8_t Line_Feed_No)
//{
//	Line_Feed_Number = Line_Feed_No;
//	gsm.Flags.ATCommandResponceReceive = false;
//	memset(gsm.RxData, '\0', sizeof(gsm.RxData));
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
////	gsm.Flags.ATCommandResponceReceive = false;
//	return 1;
//}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_2;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, LD4_Pin|LD3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD4_Pin LD3_Pin */
  GPIO_InitStruct.Pin = LD4_Pin|LD3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
