/*
 * Frame.c
 *
 *  Created on: 28-Apr-2021
 *      Author: pankaj.kumar
 */


#include"include_file.h"


char DeviceID[15] = "DSGROUP11355";		//DS + IMEI last 5 digit  + 001 or DS + IMEI last 5 digit + K2K
char TimeStmp[15] = "123123123123123";
char RecordID[10] = "48945";  //  K2K + IMEI last 5 digit
char SwVer[5] = "1.00";			//
char Server_name[] = "gsm.dsgroup.in";	// pankaj_personal  //  13.126.165.4  gsm.dsgroup.in
char Status_Port[5] = "400890";			// 4000
char Command_Port[5] = "8000";			// 8000
char Modem_data_status[2] = "1";

//uint32_t str_copy_ram_lim_ret( char *rec_src_ram_add,  char *rec_dest_ram_add,  char rec_delimitter,char src_dest)
//{
//     char *rec_src_add = rec_src_ram_add;
//    while(*rec_src_ram_add != rec_delimitter)
//        *rec_dest_ram_add++ = *rec_src_ram_add++;
//    return (rec_src_ram_add - rec_src_add + src_dest);
//}
//
//
//unsigned str_comp_ram( char *rec_src_ram_add,  char *rec_dest_ram_add,  uint32_t rec_count)
//{
//    while(rec_count--)
//    {
//        if(*rec_dest_ram_add++ != *rec_src_ram_add++)
//            return(0);
//    }
//    return(1);
//}
//
//
//
//unsigned str_comp_ram_lim( char *rec_src_ram_add,  char *rec_dest_ram_add,  uint8_t rec_delim)
//{
//    while(*rec_src_ram_add != rec_delim)
//    {
//        if(*rec_dest_ram_add++ != *rec_src_ram_add++)
//            return(0);
//    }
//    return(1);
//}
//
//
//void str_copy_ram_lim( char *rec_src_ram_add,  char *rec_dest_ram_add,  char rec_delimitter)
//{
//    while(*rec_src_ram_add != rec_delimitter)
//        *rec_dest_ram_add++ = *rec_src_ram_add++;
//}
//

void GenerateStausPacket()
{
    memcpy(gsm.gsm_data.DeviceID,DeviceID, sizeof(DeviceID));
    memcpy(gsm.gsm_data.SwVer ,SwVer, sizeof(SwVer));
    memcpy(gsm.gsm_data.RecordID ,RecordID, sizeof(RecordID));
    memcpy(gsm.gsm_data.command_port,Command_Port , sizeof(Command_Port));
    memcpy(gsm.gsm_data.server_name,Server_name , sizeof(Server_name));
    memcpy(gsm.gsm_data.status_port,Status_Port , sizeof(Status_Port));
    memcpy(gsm.gsm_data.server_data,"INTRUDER DETECTED" , 20);

//    // start fram
    unsigned char  *char_dest_ptr = &gsm.TxData[L_FRAME_INIT];

    char_dest_ptr += str_copy_ram_lim_ret(gsm.gsm_data.DeviceID,char_dest_ptr,0,0);
    *char_dest_ptr++ = ','; // try once

    char_dest_ptr += str_copy_ram_lim_ret(gsm.gsm_data.RecordID,char_dest_ptr,0,0);
    *char_dest_ptr++ = ','; // try once

    char_dest_ptr += str_copy_ram_lim_ret(gsm.gsm_data.SwVer,char_dest_ptr,0,0);
    *char_dest_ptr++ = ','; // try once

    //    // imei
    char_dest_ptr += str_copy_ram_lim_ret(gsm.gsm_data.imei,char_dest_ptr,0,0);
    *char_dest_ptr++ = ','; // try once

    //    // imsi
    char_dest_ptr += str_copy_ram_lim_ret(gsm.gsm_data.imsi,char_dest_ptr,0,0);
    *char_dest_ptr++ = ','; // try once

    //    // ccid
    char_dest_ptr += str_copy_ram_lim_ret(gsm.gsm_data.ccid,char_dest_ptr,0,0);
    *char_dest_ptr++ = ','; // try once

    // vendor name   //
    char_dest_ptr += str_copy_ram_lim_ret(gsm.gsm_data.snn,char_dest_ptr,0,0);
    *char_dest_ptr++ = ','; // try once

    //    // signal
    char_dest_ptr += str_copy_ram_lim_ret(gsm.gsm_data.signal_strength,char_dest_ptr,0,0);
    *char_dest_ptr++ = ','; // try once

    //    // sensor data
    char_dest_ptr += str_copy_ram_lim_ret(gsm.gsm_data.server_data,char_dest_ptr,0,0);
    *char_dest_ptr++ = ','; // try once

    //    // imei
    char_dest_ptr += str_copy_ram_lim_ret(gsm.gsm_data.gsm_band,char_dest_ptr,0,0);
    *char_dest_ptr++ = ','; // try once

    //    // imei
    char_dest_ptr += str_copy_ram_lim_ret(gsm.gsm_data.gsm_channel,char_dest_ptr,0,0);
    *char_dest_ptr++ = ','; // try once

    //    // imei
    char_dest_ptr += str_copy_ram_lim_ret(gsm.gsm_data.server_name,char_dest_ptr,0,0);
    *char_dest_ptr++ = ','; // try once
    //    // imei
    char_dest_ptr += str_copy_ram_lim_ret(gsm.gsm_data.status_port,char_dest_ptr,0,0);
    *char_dest_ptr++ = ','; // try once
    //    // imei
    char_dest_ptr += str_copy_ram_lim_ret(gsm.gsm_data.command_port,char_dest_ptr,0,0);
    *char_dest_ptr++ = ','; // try once

    //    // time and date
//    char_dest_ptr += str_copy_ram_lim_ret(gsm.gsm_data.date_time.date,char_dest_ptr,0,0);
//    *char_dest_ptr++ = ','; // try once
//    char_dest_ptr += str_copy_ram_lim_ret(gsm.gsm_data.date_time.time,char_dest_ptr,0,0);
//    *char_dest_ptr++ = ','; // try once

        char crc_high_byte;
        char crc_low_byte;

        str_copy_ram_lim("STX",gsm.TxData,0);
        uinteger temp_frame_len = L_FRAME_LEN(char_dest_ptr - &gsm.TxData[L_FRAME_INIT]);
        dec_int_to_char_fixed(&temp_frame_len,&gsm.TxData[L_STX],4);
        gsm.gsm_data.FC_CONFIGRATION = FC_ALERT;
        gsm.TxData[L_STX+L_FR_LEN+L_FUNC_CODE-1]   = gsm.gsm_data.FC_CONFIGRATION;			// +2 due to two comma
        gsm.TxData[L_STX+L_FR_LEN+L_FUNC_CODE] = ',';

        crc_high_byte = gsm.TxData[char_dest_ptr - gsm.TxData];
        crc_low_byte = gsm.TxData[char_dest_ptr - gsm.TxData + 1];
        dec_byte_to_char_fixed(&crc_high_byte,&gsm.TxData[char_dest_ptr - gsm.TxData],2);
        dec_byte_to_char_fixed(&crc_low_byte,&gsm.TxData[char_dest_ptr - gsm.TxData+2],2);
        generate_crc(gsm.TxData,(char_dest_ptr - gsm.TxData));
      //  *char_dest_ptr++ = ',';
        str_copy_ram_lim("ETX",&gsm.TxData[char_dest_ptr - gsm.TxData+4],0);
        gsm.TxDataCnt = char_dest_ptr - gsm.TxData + L_CRC + L_ETX;
        gsm.Flags.DataPacketReady = 1;
//       // Gsm.TxOperation = 1;
//        int i=0;
//        while(gsm.TxData[i] != '\0')
//        {
//        	gsm.RxData[i] = gsm.TxData[i];
//        	i++;
//        }
        if(verify_crc(&gsm.RxData,(gsm.TxDataCnt - 7)))
        {
        	gsm.Flags.crcVerified = true;
        }
}


void prepare_frame(void)
{

}


//uint32_t crc32_for_byte(uint32_t r) {
//  for(int j = 0; j < 8; ++j)
//    r = (r & 1? 0: (uint32_t)0xEDB88320L) ^ r >> 1;
//  return r ^ (uint32_t)0xFF000000L;
//}
//
//void crc32(const void *data, size_t n_bytes, uint32_t* crc) {
//  static uint32_t table[0x100];
//  if(!*table)
//    for(size_t i = 0; i < 0x100; ++i)
//      table[i] = crc32_for_byte(i);
//  for(size_t i = 0; i < n_bytes; ++i)
//    *crc = table[(uint8_t)*crc ^ ((uint8_t*)data)[i]] ^ *crc >> 8;
//}
