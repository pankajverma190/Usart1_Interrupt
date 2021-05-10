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


void str_copy_ram_cnt( ubyte *rec_src_ram_add,  ubyte *rec_dest_ram_add,  uinteger rec_count)
{
    while(rec_count--)
        *rec_dest_ram_add++ = *rec_src_ram_add++;
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


unsigned str_comp_ram( ubyte *rec_src_ram_add,  ubyte *rec_dest_ram_add,  uinteger rec_count)
{
    while(rec_count--)
    {
        if(*rec_dest_ram_add++ != *rec_src_ram_add++)
            return(0);
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
