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
#define  uword  			uint32_t

int compareArray(uint8_t *srcRamAdd, uint8_t *desRamAdd, int length, char delim);
void convert_char_to_float_and_store(char *rec_src_ram_add, float *rec_dest_ram_add, int deciPoiAccuracy);
unsigned char convert_char_to_int_and_store(char *rec_src_ram_add, int *rec_dest_ram_add, int count);
uint8_t convert_int_to_char_and_store(int rec_src_ram_add, uint8_t *rec_dest_ram_add);
uint8_t calculate_number_of_char_in_int(int value);
//void str_fill(char *rec_ram_add,  int rec_count,  char rec_char);// Pankaj
//uint8_t float_to_char ( float *rec_src_ram_add, uint8_t *rec_dest_ram_add , uint8_t dec_cnt);
uint8_t convert_Negative_int_to_char_and_store(int rec_src_ram_add, uint8_t *rec_dest_ram_add);
void str_fill(uint8_t *rec_ram_add,  uinteger rec_count,  uint8_t rec_char);
uinteger str_copy_ram_lim_ret( uint8_t *rec_src_ram_add,  uint8_t *rec_dest_ram_add,  uint8_t rec_delimitter,uint8_t src_dest);
unsigned str_comp_ram( uint8_t *rec_src_ram_add,  uint8_t *rec_dest_ram_add,  uinteger rec_count);
unsigned str_comp_ram_lim( uint8_t *rec_src_ram_add,  uint8_t *rec_dest_ram_add,  uinteger rec_delim);
void str_copy_ram_lim( uint8_t *rec_src_ram_add,  uint8_t *rec_dest_ram_add,  uint8_t rec_delimitter);

void str_copy_ram_cnt( ubyte *rec_src_ram_add,  ubyte *rec_dest_ram_add,  uint8_t rec_count);

ubyte char_to_dec_int_fixed(ubyte *rec_src_ram_add, uinteger *rec_dest_ram_add, ubyte rec_count);
  ubyte char_to_dec_long_fixed(ubyte *rec_src_ram_add, uword *rec_dest_ram_add, ubyte rec_count);
  ubyte char_to_hex_byte_cnt(  ubyte *rec_src_ram_add,   ubyte *rec_dest_ram_add);
  ubyte* conv_unicode_to_char(  ubyte *char_src_ptr,  uinteger count);
  ubyte dec_byte_to_char_fixed (  ubyte *rec_src_ram_add,   ubyte *rec_dest_ram_add,  ubyte cnt);
  ubyte dec_long_to_char_fixed(uword *rec_src_ram_add,   ubyte *rec_dest_ram_add,   ubyte rec_char_len);
  ubyte dec_int_to_char_fixed(  uinteger *rec_src_ram_add,   ubyte *rec_dest_ram_add,   ubyte rec_char_len);
  ubyte char_to_dec_byte(  ubyte *rec_src_ram_add,   ubyte *rec_dest_ram_add,   ubyte rec_delim);
  ubyte char_to_dec_byte_fixed(  ubyte *rec_src_ram_add,   ubyte *rec_dest_ram_add,   ubyte rec_count);
  ubyte char_to_dec_int(  ubyte *rec_src_ram_add,   uinteger *rec_dest_ram_add,   ubyte rec_delim);
  ubyte char_to_dec_long(  ubyte *rec_src_ram_add, uword *rec_dest_ram_add,   ubyte rec_delim);
  ubyte char_to_hex_byte(  ubyte *rec_src_ram_add,   ubyte *rec_dest_ram_add,   ubyte rec_delim);
  ubyte char_to_float(ubyte *rec_src_ram_add, float *rec_dest_ram_add, ubyte rec_delim);
  ubyte float_to_char ( float *rec_src_ram_add, ubyte *rec_dest_ram_add , ubyte dec_cnt); // Pankaj verma

//
//Byte	8	both
//Halfword	16	both
//Word	32	both
//Doubleword	64	both
#endif /* INC_STRING_OPERATION_H_ */
