/*
 * peripheral_task.h
 *
 *  Created on: 10-Apr-2021
 *      Author: pankaj.kumar
 */

#ifndef INC_PERIPHERAL_TASK_H_
#define INC_PERIPHERAL_TASK_H_

#include "include_file.h"

extern UART_HandleTypeDef huart1;

#endif /* INC_PERIPHERAL_TASK_H_ */
void peripheral_init(void);
void gsm_init(void);
