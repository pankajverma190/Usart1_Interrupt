/*
 * string_operation.h
 *
 *  Created on: 04-May-2021
 *      Author: pankaj.kumar
 */

#ifndef INC_STRING_OPERATION_H_
#define INC_STRING_OPERATION_H_

#define ubyte			unsigned char
#define uinteger		unsigned int
#define  sword  		uint16_t

int compareArray(uint8_t *srcRamAdd, ubyte *desRamAdd, int length, char delim);
void convert_char_to_float_and_store(char *rec_src_ram_add, float *rec_dest_ram_add, int deciPoiAccuracy);
unsigned char convert_char_to_int_and_store(char *rec_src_ram_add, int *rec_dest_ram_add, int count);
ubyte convert_int_to_char_and_store(int rec_src_ram_add, ubyte *rec_dest_ram_add);
ubyte calculate_number_of_char_in_int(int value);
//void str_fill(char *rec_ram_add,  int rec_count,  char rec_char);// Pankaj
ubyte float_to_char ( float *rec_src_ram_add, ubyte *rec_dest_ram_add , ubyte dec_cnt);
ubyte convert_Negative_int_to_char_and_store(int rec_src_ram_add, ubyte *rec_dest_ram_add);
#endif /* INC_STRING_OPERATION_H_ */
