/*
 * Frame.h
 *
 *  Created on: 28-Apr-2021
 *      Author: pankaj.kumar
 */

#ifndef INC_FRAME_H_
#define INC_FRAME_H_


#define L_STX           3
#define L_PACKET        4
#define L_ETX           (unsigned char)3
#define L_FUNC_CODE     (unsigned char)1
#define L_FR_LEN        4
#define comma_len		1
#define L_CRC           (unsigned char)4
#define L_DATA          (uint8_t)1000
#define L_FRAME_INIT                        (uint8_t)(L_STX+L_FR_LEN+L_FUNC_CODE+comma_len)
#define L_FRAME_LEN(DATA)                   (uint8_t)(L_STX+L_FR_LEN+L_FUNC_CODE+DATA+L_CRC+L_ETX)
#define L_DATA_LEN(frame_length)            (uint8_t)(frame_length - L_STX - L_FR_LEN - L_ETX - L_CRC)

#define STX_STR "STX"
#define ETX_STR "ETX"


void prepare_frame(void);
void GenerateStausPacket(void);

#endif /* INC_FRAME_H_ */
