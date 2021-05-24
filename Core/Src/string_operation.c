/*
 * stringOperation.c
 *
 *  Created on: Jan 9, 2020
 *      Author: Apaul-vinas
 */

#include "include_file.h"
#define SIX_DIGIT           6
#define FIVE_DIGIT          5
#define FOUR_DIGIT          4
#define THREE_DIGIT         3
#define TWO_DIGIT           2
#define ONE_DIGIT           1


int compareArray(ubyte *srcRamAdd, ubyte *desRamAdd, int length, char delim)
{
    int k = 0;
    if(length != 0)
    {
        while(k < length)
           {
               if (desRamAdd[k] != srcRamAdd[k])
               {
                   return 0;
               }
               k++;
           }
        return 1;
    }
    else
    {
         while(desRamAdd[k] != delim)
           {
              if (desRamAdd[k] != srcRamAdd[k])
              {
                  return 0;
              }
              k++;
           }
        return 1;
    }
}


void str_copy_ram_cnt( ubyte *rec_src_ram_add,  ubyte *rec_dest_ram_add,  uint8_t rec_count)
{
    while(rec_count)
    {
        *rec_dest_ram_add = *rec_src_ram_add;
        rec_src_ram_add++;
        rec_dest_ram_add++;
        rec_count = rec_count-1;
    }
}


ubyte convert_char_to_int_and_store(char *rec_src_ram_add, int *rec_dest_ram_add, int count)
{
        *rec_dest_ram_add = 0;

        switch (count)
        {
            case SIX_DIGIT:
              *rec_dest_ram_add += (*rec_src_ram_add++ - '0') * 100000;

            case FIVE_DIGIT:
              *rec_dest_ram_add += (*rec_src_ram_add++ - '0') * 10000;

            case FOUR_DIGIT:
              *rec_dest_ram_add += (*rec_src_ram_add++ - '0') * 1000;

            case THREE_DIGIT:
              *rec_dest_ram_add += (*rec_src_ram_add++ - '0') * 100;

            case TWO_DIGIT:
              *rec_dest_ram_add += (*rec_src_ram_add++ - '0') * 10;

            case ONE_DIGIT:
              *rec_dest_ram_add += (*rec_src_ram_add - '0');
              return(count);

            default:
              return(0);
        }

}







void convert_char_to_float_and_store(char *rec_src_ram_add, float *rec_dest_ram_add, int deciPoiAccuracy)
{
    char *pktPtr = rec_src_ram_add;
    *rec_dest_ram_add = 0.0;
    float temp = 0.0;
    int tempVariable = 0, tempDecimalPart = 0, n = 0;

    while(*pktPtr++ != '.')
    {
        n++;
    }

    convert_char_to_int_and_store(rec_src_ram_add, &tempVariable, n);
    convert_char_to_int_and_store(pktPtr, &tempDecimalPart, deciPoiAccuracy);                               //accurate upto 2 decimal values
    temp = (float)tempVariable +((float)tempDecimalPart/100);
    *rec_dest_ram_add = temp;
}






ubyte convert_int_to_char_and_store(int rec_src_ram_add, ubyte *rec_dest_ram_add)
{

        int count = calculate_number_of_char_in_int(rec_src_ram_add);

        switch (count)
        {
            case 6:
                *rec_dest_ram_add++ = rec_src_ram_add/100000 + '0';

            case 5:
                *rec_dest_ram_add++ = (rec_src_ram_add/10000)%10 + '0';

            case 4:
                *rec_dest_ram_add++ = (rec_src_ram_add/1000)%10 + '0';

            case 3:
                *rec_dest_ram_add++ = (rec_src_ram_add/100)%10 + '0';

            case 2:
                *rec_dest_ram_add++ = (rec_src_ram_add/10)%10 + '0';

            case 1:
                *rec_dest_ram_add = (rec_src_ram_add/1)%10 + '0';
                return(1);

            default:
                return(0);
        }
}


ubyte convert_Negative_int_to_char_and_store(int rec_src_ram_add, ubyte *rec_dest_ram_add)
{
    if(rec_src_ram_add < 0)
    {
        rec_src_ram_add = rec_src_ram_add * (-1);
        *rec_dest_ram_add++ = '-';
    }

    int count = calculate_number_of_char_in_int(rec_src_ram_add);

    switch (count)
    {
         case 6:
             *rec_dest_ram_add++ = rec_src_ram_add/100000 + '0';

         case 5:
             *rec_dest_ram_add++ = (rec_src_ram_add/10000)%10 + '0';

         case 4:
             *rec_dest_ram_add++ = (rec_src_ram_add/1000)%10 + '0';

         case 3:
             *rec_dest_ram_add++ = (rec_src_ram_add/100)%10 + '0';

         case 2:
             *rec_dest_ram_add++ = (rec_src_ram_add/10)%10 + '0';

         case 1:
             *rec_dest_ram_add = (rec_src_ram_add/1)%10 + '0';
             return(1);

         default:
            return(0);
    }
}




ubyte calculate_number_of_char_in_int(int value)
{

        int temp = 0, length = 0;
        /*int i = 0;
        for( ; i < 6; i++)
        {
            temp = value/100000 + '0';
            if(temp || length)
            {
                length++;
            }
        }
        */

        switch (6)
        {
            case 6:
                temp = value/100000 ;
                if(temp || length)
                {
                    length++;
                }

            case 5:
                temp = (value/10000)%10 ;
                if(temp || length)
                {
                    length++;
                }

            case 4:
                temp = (value/1000)%10 ;
                if(temp || length)
                {
                    length++;
                }

            case 3:
                temp = (value/100)%10 ;
                if(temp || length)
                {
                    length++;
                }

            case 2:
                temp = (value/10)%10 ;
                if(temp || length)
                {
                    length++;
                }

            case 1:
                temp = value%10 ;
                if(temp || length)
                {
                    length++;
                }
                return(length);

            default:
              return(0);
        }
}




void str_fill(ubyte *rec_ram_add,  uinteger rec_count,  ubyte rec_char)
{
    while(rec_count--)
        *rec_ram_add++ = rec_char;
}


uinteger str_copy_ram_lim_ret( ubyte *rec_src_ram_add,  ubyte *rec_dest_ram_add,  ubyte rec_delimitter,ubyte src_dest)
{
     ubyte *rec_src_add = rec_src_ram_add;
    while(*rec_src_ram_add != rec_delimitter)
        *rec_dest_ram_add++ = *rec_src_ram_add++;
    return (rec_src_ram_add - rec_src_add + src_dest);
}


unsigned str_comp_ram( unsigned char *rec_src_ram_add,  ubyte *rec_dest_ram_add,  uinteger rec_count)
{
    while(rec_count)
    {
        if(*rec_dest_ram_add != *rec_src_ram_add)
        	return(0);
        else
        {
        	rec_dest_ram_add++;
        	rec_src_ram_add++;
        	rec_count = rec_count-1;
        }
    }
    return(1);
}



unsigned str_comp_ram_lim( ubyte *rec_src_ram_add,  ubyte *rec_dest_ram_add,  uinteger rec_delim)
{
    while(*rec_src_ram_add != rec_delim)
    {
        if(*rec_dest_ram_add++ != *rec_src_ram_add++)
            return(0);
    }
    return(1);
}


void str_copy_ram_lim( ubyte *rec_src_ram_add,  ubyte *rec_dest_ram_add,  ubyte rec_delimitter)
{
    while(*rec_src_ram_add != rec_delimitter)
        *rec_dest_ram_add++ = *rec_src_ram_add++;
}

ubyte float_to_char ( float *rec_src_ram_add, ubyte *rec_dest_ram_add , ubyte dec_cnt)
{
    ubyte ascii_buff[10] = {0};
    ubyte ascii_buff_count = 0;
    uinteger flag = 0;
    float temp = 0.0;
    sword rec_byte=0,n = 0;
    temp = *rec_src_ram_add;
    flag = temp * 1000;

    if(flag > 99 && flag <= 999)
        flag = 1;
    else if (flag > 9 && flag <= 99)
        flag = 2;
    else if (flag > 0 && flag <= 9)
        flag = 3;
    else
        flag = 0;

    switch (dec_cnt)
    {
        case 5:
        *rec_src_ram_add = *rec_src_ram_add * 100000;
        break;
        case 4:
        *rec_src_ram_add = *rec_src_ram_add * 10000;
        break;
        case 3:
        *rec_src_ram_add = *rec_src_ram_add * 1000;
        break;
        case 2:
        *rec_src_ram_add = *rec_src_ram_add * 100;
        break;
        case 1:
        *rec_src_ram_add = *rec_src_ram_add*10;
        break;
        default:
        *rec_src_ram_add = 0;
        break;
    }

    if(!*rec_src_ram_add)
    {
        *rec_dest_ram_add = 0x30;
        return(1);
    }
    rec_byte = *rec_src_ram_add;
    while(rec_byte)
    {

        if( n !=dec_cnt)
        {
        ascii_buff[ascii_buff_count++] = (rec_byte % 10) + 0x30;
        rec_byte = rec_byte / 10;
        }
        else
        ascii_buff[ascii_buff_count++] = '.';

        n++;
    }
 //   rec_byte = ascii_buff_count;

    if(flag == 3)
    {
        ascii_buff[ascii_buff_count++]= '0';
        ascii_buff[ascii_buff_count++]= '0';
        ascii_buff[ascii_buff_count++]= '.';
        ascii_buff[ascii_buff_count++]= '0';
    }
    else if(flag == 2)
    {
        ascii_buff[ascii_buff_count++]= '0';
        ascii_buff[ascii_buff_count++]= '.';
        ascii_buff[ascii_buff_count++]= '0';
    }
    else if(flag == 1)
    {
        ascii_buff[ascii_buff_count++]= '.';
        ascii_buff[ascii_buff_count++]= '0';
    }
    rec_byte = ascii_buff_count;
    while(ascii_buff_count)
            *rec_dest_ram_add++ = ascii_buff[--ascii_buff_count];
    return(rec_byte);
}



/**
 * @brief convert char buffer to float buffer.
 * @param rec_src_ram_add pointer to the variable or buffer which need conversion.
 * @param rec_dest_ram_add pointer to the variable or buffer which will store the converted data.
 * @param rec_delim conversion end boundary in buffer(rec_src_ram_add).
 *
 * @return count of characters.
 */
ubyte char_to_float(ubyte *rec_src_ram_add, float *rec_dest_ram_add, ubyte rec_delim)
{
	ubyte ascii_buff[5] = {0};
	ubyte flaot_part[4] = {0};
	float number = 0;
	float dec_part = 0;
	ubyte ascii_buff_count = 0;
	ubyte temp_count = 0;
	ubyte dec_num = 0,float_num = 0;
	ubyte *rec_src_strt_ram_add = rec_src_ram_add;
	while(*rec_src_ram_add != rec_delim)
	{

		number = (*rec_src_ram_add++ - 0x30) + number * 10;
		dec_num++;
		if(*rec_src_ram_add=='.')
			break;
	}
	dec_part = 0;
	if(*rec_src_ram_add != rec_delim)
	{
		dec_num = 0;
		rec_src_ram_add++;
		while(*rec_src_ram_add != rec_delim)
		{

			dec_part = (*rec_src_ram_add++ - 0x30) + dec_part * 10;
			dec_num++;
		}
		while(dec_num--)
			dec_part/=10;
	}
	*rec_dest_ram_add = number + dec_part;
	return(rec_src_ram_add - rec_src_strt_ram_add);
}

/**
 * @brief convert buffer of 3 character values to a decimal value.
 * @param rec_src_ram_add pointer to the variable or buffer which need conversion.
 * @param rec_dest_ram_add pointer to the variable or buffer which will store the converted data.
 * @param rec_count number of integers.
 *
 * @return count of characters.
 */
  ubyte char_to_dec_byte_fixed(  ubyte *rec_src_ram_add,   ubyte *rec_dest_ram_add,   ubyte rec_count)
{
	*rec_dest_ram_add = 0;
	switch (rec_count)
	{
		case 3:
		*rec_dest_ram_add += (*rec_src_ram_add++ - '0') * 100;
		case 2:
		*rec_dest_ram_add += (*rec_src_ram_add++ - '0') * 10;
		case 1:
		*rec_dest_ram_add += (*rec_src_ram_add++ - '0');
		return(rec_count);
		default:
		*rec_dest_ram_add = 0;
		return(0);
	}
}
/**
 * @brief convert long decimal value to different characters.
 * @param rec_src_ram_add pointer to the variable or buffer which need conversion.
 * @param rec_dest_ram_add pointer to the variable or buffer which will store the converted data.
 *
 * @return count of characters.
 */
  ubyte dec_long_to_char(uword *rec_src_ram_add,   ubyte *rec_dest_ram_add)
{
	  ubyte ascii_buff[10] = {0};
	  ubyte ascii_buff_count = 0;
	uword rec_byte = 0;
	if(!*rec_src_ram_add)
	{
		*rec_dest_ram_add = 0x30;
		return(1);
	}
	rec_byte = *rec_src_ram_add;
	while(rec_byte)
	{
		ascii_buff[ascii_buff_count++] = (rec_byte % 10) + 0x30;
		rec_byte = rec_byte / 10;
	}
	rec_byte = ascii_buff_count;

	while(ascii_buff_count)
		*rec_dest_ram_add++ = ascii_buff[--ascii_buff_count];
	return(rec_byte);
}
/**
 * @brief convert integer decimal value to different characters.
 * @param rec_src_ram_add pointer to the variable or buffer which need conversion.
 * @param rec_dest_ram_add pointer to the variable or buffer which will store the converted data.
 *
 * @return count of characters.
 */
  ubyte dec_int_to_char(  uinteger *rec_src_ram_add,   ubyte *rec_dest_ram_add)
{
	  ubyte ascii_buff[5] = {0};
	  ubyte ascii_buff_count = 0;
	  uinteger rec_byte = 0;
	if(!*rec_src_ram_add)
	{
		*rec_dest_ram_add = 0x30;
		return(1);
	}
	rec_byte = *rec_src_ram_add;
	while(rec_byte)
	{
		ascii_buff[ascii_buff_count++] = (rec_byte % 10) + 0x30;
		rec_byte = rec_byte / 10;
	}
	rec_byte = ascii_buff_count;

	while(ascii_buff_count)
		*rec_dest_ram_add++ = ascii_buff[--ascii_buff_count];
	return(rec_byte);
}
/**
 * @brief convert byte size decimal value to different characters.
 * @param rec_src_ram_add pointer to the variable or buffer which need conversion.
 * @param rec_dest_ram_add pointer to the variable or buffer which will store the converted data.
 *
 * @return count of characters.
 */
  ubyte dec_byte_to_char (  ubyte *rec_src_ram_add,   ubyte *rec_dest_ram_add)
{
	  ubyte ascii_buff[3] = {0};
	  ubyte ascii_buff_count = 0;
	  ubyte rec_byte = 0;
	if(!*rec_src_ram_add)
	{
		*rec_dest_ram_add = 0x30;
		return(1);
	}
	rec_byte = *rec_src_ram_add;
	while(rec_byte)
	{
		ascii_buff[ascii_buff_count++] = (rec_byte % 10) + 0x30;
		rec_byte = rec_byte / 10;
	}
	rec_byte = ascii_buff_count;

	while(ascii_buff_count)
		*rec_dest_ram_add++ = ascii_buff[--ascii_buff_count];
	return(rec_byte);
}
/**
 * @brief convert integer decimal value to fixed number of characters.
 * @param rec_src_ram_add pointer to the variable or buffer which need conversion.
 * @param rec_dest_ram_add pointer to the variable or buffer which will store the converted data.
 * @param rec_char_len count of characters
 *
 * @return count of characters.
 */
  ubyte dec_int_to_char_fixed(  uinteger *rec_src_ram_add,   ubyte *rec_dest_ram_add,   ubyte rec_char_len)
{
	  uinteger rec_byte = 0;
	  ubyte ascii_buff[] = "00000";
	  ubyte ascii_buff_count = 0;
	rec_byte = *rec_src_ram_add;
	while(rec_byte)
	{
		ascii_buff[ascii_buff_count++] = (rec_byte % 10) + 0x30;
		rec_byte = rec_byte / 10;
	}
	rec_byte = rec_char_len;
	while(rec_char_len)
		*rec_dest_ram_add++ = ascii_buff[--rec_char_len];
	return(rec_byte);
}
/**
 * @brief convert long decimal value to fixed number of characters.
 * @param rec_src_ram_add pointer to the variable or buffer which need conversion.
 * @param rec_dest_ram_add pointer to the variable or buffer which will store the converted data.
 * @param rec_char_len count of characters
 *
 * @return count of characters.
 */
  ubyte dec_long_to_char_fixed(uword *rec_src_ram_add,   ubyte *rec_dest_ram_add,   ubyte rec_char_len)
{
	uword rec_byte = 0;
	  ubyte ascii_buff[] = "0000000000";
	  ubyte ascii_buff_count = 0;
	rec_byte = *rec_src_ram_add;
	while(rec_byte)
	{
		ascii_buff[ascii_buff_count++] = (rec_byte % 10) + 0x30;
		rec_byte = rec_byte / 10;
	}
	rec_byte = rec_char_len;
	while(rec_char_len)
		*rec_dest_ram_add++ = ascii_buff[--rec_char_len];
	return(rec_byte);
}
/**
 * @brief convert byte size decimal value to fixed number of characters.
 * @param rec_src_ram_add pointer to the variable or buffer which need conversion.
 * @param rec_dest_ram_add pointer to the variable or buffer which will store the converted data.
 * @param cnt count of characters
 *
 * @return count of characters.
 */
  ubyte dec_byte_to_char_fixed (  ubyte *rec_src_ram_add,   ubyte *rec_dest_ram_add,  ubyte cnt)
{
	  ubyte ascii_buff[3] = {0};
	  ubyte ascii_buff_count = 0;
	  ubyte rec_byte = 0;
          ubyte cnt_or = cnt;
	rec_byte = *rec_src_ram_add;
	while(rec_byte)
	{
		ascii_buff[ascii_buff_count++] = (rec_byte % 10) + 0x30;
		rec_byte = rec_byte / 10;
	}
	rec_byte = ascii_buff_count;

        while(ascii_buff_count < cnt)
        {
           *rec_dest_ram_add++ = '0';
           cnt--;
        }
	while(ascii_buff_count)
		*rec_dest_ram_add++ = ascii_buff[--ascii_buff_count];
	return(cnt_or);
}
/**
 * @brief
 * @param rec_byte .
 *
 * @return none.
 */
  ubyte dec_to_bcd(  ubyte rec_byte)
{
	if(rec_byte > 99)
		return(255);
	return((rec_byte / 10) * 0x10) + (rec_byte % 10);
}
/**
 * @brief
 * @param rec_byte .
 *
 * @return none.
 */
  ubyte bcd_to_dec(  ubyte rec_byte)
{
	return((rec_byte / 0x10) * 10) + (rec_byte % 0x10);
}
// @ Pankaj Verma
//ubyte float_to_char ( float *rec_src_ram_add, ubyte *rec_dest_ram_add , ubyte dec_cnt)
//{
//	ubyte ascii_buff[10] = {0};
//	ubyte ascii_buff_count = 0;
//	uinteger rec_byte = 0;
//	switch (dec_cnt)
//	{
//		case 5:
//		*rec_src_ram_add = *rec_src_ram_add * 10000;
//		break;
//		case 4:
//		*rec_src_ram_add = *rec_src_ram_add * 1000;
//		break;
//		case 3:
//		*rec_src_ram_add = *rec_src_ram_add * 100;
//		break;
//		case 2:
//		*rec_src_ram_add = *rec_src_ram_add * 10;
//		break;
//		case 1:
//		*rec_src_ram_add = *rec_src_ram_add;
//		break;
//		default:
//		*rec_src_ram_add = 0;
//		break;
//	}
//
//	if(!*rec_src_ram_add)
//	{
//		*rec_dest_ram_add = 0x30;
//		return(1);
//	}
//	rec_byte = *rec_src_ram_add;
//	while(rec_byte)
//	{
//		ascii_buff[ascii_buff_count++] = (rec_byte % 10) + 0x30;
//		rec_byte = rec_byte / 10;
//	}
//	rec_byte = ascii_buff_count;
//
//	while(ascii_buff_count)
//		*rec_dest_ram_add++ = ascii_buff[--ascii_buff_count];
//	return(rec_byte);
//}
/**
 * @brief convert byte size hex value to different characters.
 * @param rec_src_ram_add pointer to the variable or buffer which need conversion.
 * @param rec_dest_ram_add pointer to the variable or buffer which will store the converted data.
 *
 * @return none.
 */
//#######################################################################################
void hex_byte_to_char(  ubyte *rec_src_ram_add,   ubyte *rec_dest_ram_add)
{
	*rec_dest_ram_add = *rec_src_ram_add / 0x10;
    //rec_dest_ram_add[0] = *rec_src_ram_add / 0x10;
    *(rec_dest_ram_add + 1) = *rec_src_ram_add % 0x10;
	//rec_dest_ram_add[1] = *rec_src_ram_add % 0x10;

	/*if(rec_dest_ram_add[0] <= 0x09)
		rec_dest_ram_add[0] += 0x30;
	else
		rec_dest_ram_add[0] += 0x37;

	if(rec_dest_ram_add[1] <= 0x09)
		rec_dest_ram_add[1] += 0x30;
	else
		rec_dest_ram_add[1] += 0x37;*/
    if(*rec_dest_ram_add <= 0x09)
		*rec_dest_ram_add += 0x30;
	else
		*rec_dest_ram_add += 0x37;

	if(*(rec_dest_ram_add + 1) <= 0x09)
		*(rec_dest_ram_add + 1) += 0x30;
	else
		*(rec_dest_ram_add + 1) += 0x37;
}
/**
 * @brief convert integer size hex value to different characters.
 * @param rec_src_ram_add pointer to the variable or buffer which need conversion.
 * @param rec_dest_ram_add pointer to the variable or buffer which will store the converted data.
 *
 * @return none.
 */
void hex_int_to_char(  uinteger *rec_src_ram_add,   ubyte *rec_dest_ram_add)
{
	  ubyte temp_byte;

	rec_dest_ram_add[0] = (  ubyte)((*rec_src_ram_add / 0x1000));
	rec_dest_ram_add[1] = (  ubyte)((*rec_src_ram_add / 0x0100) % 0x0010);
	rec_dest_ram_add[2] = (  ubyte)((*rec_src_ram_add / 0x0010) % 0x0010);
	rec_dest_ram_add[3] = (  ubyte)(*rec_src_ram_add % 0x0010);

	for(temp_byte = 0; temp_byte < 4; temp_byte++)
	{
		if(rec_dest_ram_add[temp_byte] <= 0x09)
			rec_dest_ram_add[temp_byte] += 0x30;
		else
			rec_dest_ram_add[temp_byte] += 0x37;
	}
}
/**
 * @brief convert word size hex value to different characters.
 * @param rec_src_ram_add pointer to the variable or buffer which need conversion.
 * @param rec_dest_ram_add pointer to the variable or buffer which will store the converted data.
 *
 * @return none.
 */
void hex_word_to_char(uword *rec_src_ram_add,   ubyte *rec_dest_ram_add)
{
	  ubyte temp_byte;

	rec_dest_ram_add[0] = (  ubyte)((*rec_src_ram_add / 0x10000000));
	rec_dest_ram_add[1] = (  ubyte)((*rec_src_ram_add / 0x01000000) % 0x00000010);
	rec_dest_ram_add[2] = (  ubyte)((*rec_src_ram_add / 0x00100000) % 0x00000010);
	rec_dest_ram_add[3] = (  ubyte)((*rec_src_ram_add / 0x00010000) % 0x00000010);
	rec_dest_ram_add[4] = (  ubyte)((*rec_src_ram_add / 0x00001000) % 0x00000010);
	rec_dest_ram_add[5] = (  ubyte)((*rec_src_ram_add / 0x00000100) % 0x00000010);
	rec_dest_ram_add[6] = (  ubyte)((*rec_src_ram_add / 0x00000010) % 0x00000010);
	rec_dest_ram_add[7] = (  ubyte)( *rec_src_ram_add % 0x00000010);

	for(temp_byte = 0; temp_byte < 8; temp_byte++)
	{
		if(rec_dest_ram_add[temp_byte] <= 0x09)
			rec_dest_ram_add[temp_byte] += 0x30;
		else
			rec_dest_ram_add[temp_byte] += 0x37;
	}
}
/*ubyte char_to_hex_byte_cnt(  ubyte *rec_src_ram_add,   ubyte *rec_dest_ram_add)
{
    ubyte temp_buff[2];
	temp_buff[0] = rec_src_ram_add[0];
	temp_buff[1] = rec_src_ram_add[1];
	temp_buff[0] -= _IF_NUM(temp_buff[0])? '0': _IF_ALPHA_HEX(temp_buff[0])? '7': temp_buff[0];
	temp_buff[1] -= _IF_NUM(temp_buff[1])? '0': _IF_ALPHA_HEX(temp_buff[1])? '7': temp_buff[1];
	*rec_dest_ram_add = ((temp_buff[0] << 4) | temp_buff[1]);
}*/
 /**
 * @brief convert buffer of two char value to a byte size hex value.
 * @param rec_src_ram_add pointer to the variable or buffer which need conversion.
 * @param rec_dest_ram_add pointer to the variable or buffer which will store the converted data.
  *
 * @return none.
 */
  ubyte char_to_hex_byte_cnt(  ubyte *rec_src_ram_add,   ubyte *rec_dest_ram_add)
{
    ubyte temp_buff[2];
	temp_buff[0] = *rec_src_ram_add;
	temp_buff[1] = *(rec_src_ram_add+1);
	temp_buff[0] -= _IF_NUM(temp_buff[0])? '0': _IF_ALPHA_HEX(temp_buff[0])? '7': temp_buff[0];
	temp_buff[1] -= _IF_NUM(temp_buff[1])? '0': _IF_ALPHA_HEX(temp_buff[1])? '7': temp_buff[1];
	*rec_dest_ram_add = ((temp_buff[0] << 4) | temp_buff[1]);
}

/**
 * @brief convert buffer of max two char values to a byte size hex value.
 * @param rec_src_ram_add pointer to the variable or buffer which need conversion.
 * @param rec_dest_ram_add pointer to the variable or buffer which will store the converted data.
 * @param rec_delim conversion end boundary in buffer(rec_src_ram_add).
 *
 * @return count of characters .
 */
  ubyte char_to_hex_byte(  ubyte *rec_src_ram_add,   ubyte *rec_dest_ram_add,   ubyte rec_delim)
{
	  ubyte ascii_buff[2] = {0};
	  ubyte ascii_buff_count = 0;
	  ubyte dig_length = 0;

	while(*rec_src_ram_add != rec_delim)
	{
		*rec_src_ram_add++;
		ascii_buff_count++;
		if(ascii_buff_count > sizeof(ascii_buff))
		{
			*rec_dest_ram_add = 0;
			return(0);
		}
	}

	for(dig_length = 0; dig_length < ascii_buff_count; dig_length++)
	{
		rec_src_ram_add--;
		if('0' <= *rec_src_ram_add && *rec_src_ram_add <= '9')
			ascii_buff[(sizeof(ascii_buff) - 1) - dig_length] = (*rec_src_ram_add - '0');
		else
			ascii_buff[(sizeof(ascii_buff) - 1) - dig_length] = (*rec_src_ram_add - '7');
	}

	*rec_dest_ram_add = ((ascii_buff[0] << 4) | ascii_buff[1]);
	return(++dig_length);

}
 /**
 * @brief convert char buffer to integer buffer
 * @param rec_src_ram_add pointer to the variable or buffer which need conversion.
 * @param rec_dest_ram_add pointer to the variable or buffer which will store the converted data.
 * @param rec_count count of characters in buffer.
 *
 * @return count of characters.
 */
ubyte char_to_dec_int_fixed(ubyte *rec_src_ram_add, uinteger *rec_dest_ram_add, ubyte rec_count)
{
	*rec_dest_ram_add = 0;
	switch (rec_count)
	{
		case 5:
		*rec_dest_ram_add += (*rec_src_ram_add++ - '0') * 10000;
		case 4:
		*rec_dest_ram_add += (*rec_src_ram_add++ - '0') * 1000;
		case 3:
		*rec_dest_ram_add += (*rec_src_ram_add++ - '0') * 100;
		case 2:
		*rec_dest_ram_add += (*rec_src_ram_add++ - '0') * 10;
		case 1:
		*rec_dest_ram_add += (*rec_src_ram_add++ - '0');
		return(rec_count);
		default:
		*rec_dest_ram_add = 0;
		return(0);
	}
}
/**
 * @brief convert char buffer to decimal long values buffer
 * @param rec_src_ram_add pointer to the variable or buffer which need conversion.
 * @param rec_dest_ram_add pointer to the variable or buffer which will store the converted data.
 * @param rec_count count of characters in buffer.
 *
 * @return count of characters.
 */
ubyte char_to_dec_long_fixed(ubyte *rec_src_ram_add, uword *rec_dest_ram_add, ubyte rec_count)
{
	*rec_dest_ram_add = 0;
	switch (rec_count)
	{
        case 6:
        *rec_dest_ram_add += (*rec_src_ram_add++ - '0') * 100000;
		case 5:
		*rec_dest_ram_add += (*rec_src_ram_add++ - '0') * 10000;
		case 4:
		*rec_dest_ram_add += (*rec_src_ram_add++ - '0') * 1000;
		case 3:
		*rec_dest_ram_add += (*rec_src_ram_add++ - '0') * 100;
		case 2:
		*rec_dest_ram_add += (*rec_src_ram_add++ - '0') * 10;
		case 1:
		*rec_dest_ram_add += (*rec_src_ram_add++ - '0');
		return(rec_count);
		default:
		*rec_dest_ram_add = 0;
		return(0);
	}
}
/**
 * @brief covert a buffer of max 4 char values to integer size hex value.
 * @param rec_src_ram_add pointer to the variable or buffer which need conversion.
 * @param rec_dest_ram_add pointer to the variable or buffer which will store the converted data.
 *
 * @return none.
 */
void char_to_hex_int(ubyte *rec_src_ram_add, uinteger *rec_dest_ram_add)
{
	ubyte temp_buff[4];
	temp_buff[0] = rec_src_ram_add[0];
	temp_buff[1] = rec_src_ram_add[1];
	temp_buff[2] = rec_src_ram_add[2];
	temp_buff[3] = rec_src_ram_add[3];
	temp_buff[0] -= _IF_NUM(temp_buff[0])? '0': _IF_ALPHA_HEX(temp_buff[0])? '7': temp_buff[0];
	temp_buff[1] -= _IF_NUM(temp_buff[1])? '0': _IF_ALPHA_HEX(temp_buff[1])? '7': temp_buff[1];
	temp_buff[2] -= _IF_NUM(temp_buff[2])? '0': _IF_ALPHA_HEX(temp_buff[2])? '7': temp_buff[2];
	temp_buff[3] -= _IF_NUM(temp_buff[3])? '0': _IF_ALPHA_HEX(temp_buff[3])? '7': temp_buff[3];
	*rec_dest_ram_add = (((uinteger)temp_buff[0] << 12) |
						 ((uinteger)temp_buff[1] << 8) |
						 ((uinteger)temp_buff[2] << 4) |
						 ((uinteger)temp_buff[3]));
}

/**
 * @brief convert a buffer of max 3 char values into a byte size decimal value.
 * @param rec_src_ram_add pointer to the variable or buffer which need conversion.
 * @param rec_dest_ram_add pointer to the variable or buffer which will store the converted data.
 * @param rec_delim conversion end boundary in buffer(rec_src_ram_add).
 *
 * @return count of characters .
 */
  ubyte char_to_dec_byte(  ubyte *rec_src_ram_add,   ubyte *rec_dest_ram_add,   ubyte rec_delim)
{
	  ubyte ascii_buff[3] = {0};
	  ubyte ascii_buff_count = 0;
	  ubyte temp_count = 0;

	while(*rec_src_ram_add != rec_delim)
	{
		*rec_src_ram_add++;
		ascii_buff_count++;
		if(ascii_buff_count > sizeof(ascii_buff))
		{
			*rec_dest_ram_add = 0;
			return(0);
		}
	}

	for(temp_count = 0; temp_count < ascii_buff_count; temp_count++)
		ascii_buff[(sizeof(ascii_buff) - 1) - temp_count] = (*--rec_src_ram_add - 48);

	rec_src_ram_add += ascii_buff_count + 1;
	*rec_dest_ram_add++ = (ascii_buff[0] * 100) + (ascii_buff[1] * 10) + ascii_buff[2];
	return(ascii_buff_count + 1);
}
/**
 * @brief convert a buffer of 5 char values into a integer size decimal value.
 * @param rec_src_ram_add pointer to the variable or buffer which need conversion.
 * @param rec_dest_ram_add pointer to the variable or buffer which will store the converted data.
 * @param rec_delim conversion end boundary in buffer(rec_src_ram_add).
 *
 * @return none.
 */
  ubyte char_to_dec_int(  ubyte *rec_src_ram_add,   uinteger *rec_dest_ram_add,   ubyte rec_delim)
{
	  ubyte ascii_buff[5] = {0};
	  ubyte ascii_buff_count = 0;
	  ubyte temp_count = 0;

	while(*rec_src_ram_add != rec_delim)
	{
		*rec_src_ram_add++;
		ascii_buff_count++;
		if(ascii_buff_count > sizeof(ascii_buff))
		{
			*rec_dest_ram_add = 0;
			return(0);
		}
	}

	for(temp_count = 0; temp_count < ascii_buff_count; temp_count++)
		ascii_buff[(sizeof(ascii_buff) - 1) - temp_count] = (*--rec_src_ram_add - 48);

	*rec_dest_ram_add = ((  uinteger)ascii_buff[0] * 10000) +
						((  uinteger)ascii_buff[1] * 1000) +
						((  uinteger)ascii_buff[2] * 100) +
						((  uinteger)ascii_buff[3] * 10) +
						((  uinteger)ascii_buff[4]);
	return(ascii_buff_count + 1);
}
/**
 * @brief convert a buffer of 10 char values into a byte size decimal value.
 * @param rec_src_ram_add pointer to the variable or buffer which need conversion.
 * @param rec_dest_ram_add pointer to the variable or buffer which will store the converted data.
 * @param rec_delim conversion end boundary in buffer(rec_src_ram_add).
 *
 *
 * @return none.
 */
  ubyte char_to_dec_long(  ubyte *rec_src_ram_add, uword *rec_dest_ram_add,   ubyte rec_delim)
{
	  ubyte ascii_buff[10] = {0};
	  ubyte ascii_buff_count = 0;
	  ubyte temp_count = 0;
	uword char_to_long = 0;

	while(*rec_src_ram_add != rec_delim)
	{
		*rec_src_ram_add++;
		ascii_buff_count++;
		if(ascii_buff_count > sizeof(ascii_buff))
		{
			*rec_dest_ram_add = 0;
			return(0);
		}
	}

	for(temp_count = 0; temp_count < ascii_buff_count; temp_count++)
		ascii_buff[(sizeof(ascii_buff) - 1) - temp_count] = (*--rec_src_ram_add - 48);

	char_to_long = char_to_long + ((uword)ascii_buff[0] * 1000000000);
	char_to_long = char_to_long + ((uword)ascii_buff[1] * 100000000);
	char_to_long = char_to_long + ((uword)ascii_buff[2] * 10000000);
	char_to_long = char_to_long + ((uword)ascii_buff[3] * 1000000);
	char_to_long = char_to_long + ((uword)ascii_buff[4] * 100000);
	char_to_long = char_to_long + ((uword)ascii_buff[5] * 10000);
	char_to_long = char_to_long + ((uword)ascii_buff[6] * 1000);
	char_to_long = char_to_long + ((uword)ascii_buff[7] * 100);
	char_to_long = char_to_long + ((uword)ascii_buff[8] * 10);
	char_to_long = char_to_long + ((uword)ascii_buff[9]);

	*rec_dest_ram_add = char_to_long;

	return(ascii_buff_count + 1);
}
/**
 * @brief concatenate byte size decimal values to form a short value
 * @param rec_byte_1  first byte in chain
 * @param rec_byte_2  second byte in chain
 *
 * @return final value.
 */
  uinteger concat_byte_to_int(  ubyte rec_byte_1,   ubyte rec_byte_2 )
{
	  uinteger int_1;
	int_1 = (  uinteger)rec_byte_1;
	int_1 = int_1 * 256;
	int_1 = int_1 + (  uinteger)rec_byte_2;
	return(int_1);
}
/**
 * @brief break short size decimal value into byte size values and store in a buffer
 * @param int_1 integer value
 * @param rec_byte_add pointer of buffer to store byte size values
 *
 * @return none.
 */
void conv_integer_to_bytes(  uinteger int_1,   ubyte *rec_byte_add)
{
	*(rec_byte_add + 1) = (  ubyte) (int_1 % 256);
	int_1 = int_1 / 256;
	*rec_byte_add = (  ubyte) (int_1 % 256);
}
//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
