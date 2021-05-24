/*
 * crc_function.h
 *
 *  Created on: 19-May-2021
 *      Author: pankaj.kumar
 */

#ifndef INC_CRC_FUNCTION_H_
#define INC_CRC_FUNCTION_H_

#ifdef	__cplusplus
extern "C" {
#endif
typedef enum
{
    MODBUS,
    MICROCHIP,
    ASCII_MODBUS,
    ASCII_MICROCHIP
}crc_types;

uint8_t verify_crc(unsigned char *rec_buff_address, unsigned int rec_buff_length);
void generate_crc(unsigned char *rec_buff_address, unsigned int rec_buff_length);
#ifdef	__cplusplus
}
#endif

#endif /* INC_CRC_FUNCTION_H_ */
