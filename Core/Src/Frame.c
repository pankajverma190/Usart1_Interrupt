/*
 * Frame.c
 *
 *  Created on: 28-Apr-2021
 *      Author: pankaj.kumar
 */


#include"include_file.h"


char DeviceID[15] = "NER12345";
char TimeStmp[15] = "123123123123123";
char RecordID[10] = "12345";
char SwVer[5] = "1.00";
char Server_name[25] = "gsm.apaulinstruments.in";
char Status_Port[5] = "9000";
char Command_Port[5] = "8000";
char Modem_data_status[2] = "1";

uint32_t str_copy_ram_lim_ret( char *rec_src_ram_add,  char *rec_dest_ram_add,  char rec_delimitter,char src_dest)
{
     char *rec_src_add = rec_src_ram_add;
    while(*rec_src_ram_add != rec_delimitter)
        *rec_dest_ram_add++ = *rec_src_ram_add++;
    return (rec_src_ram_add - rec_src_add + src_dest);
}


unsigned str_comp_ram( char *rec_src_ram_add,  char *rec_dest_ram_add,  uint32_t rec_count)
{
    while(rec_count--)
    {
        if(*rec_dest_ram_add++ != *rec_src_ram_add++)
            return(0);
    }
    return(1);
}



unsigned str_comp_ram_lim( char *rec_src_ram_add,  char *rec_dest_ram_add,  uint8_t rec_delim)
{
    while(*rec_src_ram_add != rec_delim)
    {
        if(*rec_dest_ram_add++ != *rec_src_ram_add++)
            return(0);
    }
    return(1);
}


void str_copy_ram_lim( char *rec_src_ram_add,  char *rec_dest_ram_add,  char rec_delimitter)
{
    while(*rec_src_ram_add != rec_delimitter)
        *rec_dest_ram_add++ = *rec_src_ram_add++;
}


void GenerateStausPacket()
{
//    memcpy(Gsm.GsmDataUni.GsmDataStru.utc_timeStamp,TimeStmp , sizeof(TimeStmp));
    memcpy(gsm.gsm_data.DeviceID,DeviceID, sizeof(DeviceID));
    memcpy(gsm.gsm_data.SwVer ,SwVer, sizeof(SwVer));
//
//    memcpy(Gsm.GsmDataUni.GsmDataStru.command_port,Command_Port , sizeof(Command_Port));
//    memcpy(Gsm.GsmDataUni.GsmDataStru.server_name,Server_name , sizeof(Server_name));
//    memcpy(Gsm.GsmDataUni.GsmDataStru.status_port,Status_Port , sizeof(Status_Port));
//    memcpy(Gsm.GsmDataUni.GsmDataStru.modem_data_status,Modem_data_status , sizeof(Modem_data_status));
//
////    memcpy(Gsm.GsmDataUni.GsmDataStru.status_port,Status_Port , sizeof(Command_Port));
////
////    memcpy(Gsm.GsmDataUni.GsmDataStru.status_port,Status_Port , sizeof(Command_Port));
////
////    memcpy(Gsm.GsmDataUni.GsmDataStru.status_port,Status_Port , sizeof(Command_Port));
////
////    memcpy(Gsm.GsmDataUni.GsmDataStru.status_port,Status_Port , sizeof(Command_Port));
////    Gsm.GsmDataUni.GsmDataStru.VehicalID = "NER12345";
////    Gsm.GsmDataUni.GsmDataStru.RecordID = "12345";
////    Gsm.GsmDataUni.GsmDataStru.SwVer = "1.01";
////    Gsm.GsmDataUni.GsmDataStru.modem_data_status = "1";
//    // start fram
    unsigned char  *char_dest_ptr = &gsm.TxData[L_FRAME_INIT];
//    // imei
        char_dest_ptr += str_copy_ram_lim_ret(gsm.gsm_data.imei,char_dest_ptr,0,0);
//        *char_dest_ptr++ = ','; // try once
////    // time
//        char_dest_ptr += str_copy_ram_lim_ret(Gsm.GsmDataUni.GsmDataStru.utc_timeStamp,char_dest_ptr,0,0);
//        *char_dest_ptr++ = ','; // try once
//    // Vehical ID
//        char_dest_ptr += str_copy_ram_lim_ret(Gsm.GsmDataUni.GsmDataStru.VehicalID,char_dest_ptr,0,0);
//        *char_dest_ptr++ = ','; // try once
//    // Record ID
//        char_dest_ptr += str_copy_ram_lim_ret(Gsm.GsmDataUni.GsmDataStru.RecordID,char_dest_ptr,0,0);
//        *char_dest_ptr++ = ','; // try once
//    // Software Version
//        char_dest_ptr += str_copy_ram_lim_ret(Gsm.GsmDataUni.GsmDataStru.SwVer,char_dest_ptr,0,0);
//        *char_dest_ptr++ = ','; // try once
//    // IMSI
//        char_dest_ptr += str_copy_ram_lim_ret(Gsm.GsmDataUni.GsmDataStru.imsi,char_dest_ptr,0,0);
//        *char_dest_ptr++ = ','; // try once
//    // CCID
//        char_dest_ptr += str_copy_ram_lim_ret(Gsm.GsmDataUni.GsmDataStru.ccid,char_dest_ptr,0,0);
//        *char_dest_ptr++ = ','; // try once
//    //signal strength
//        char_dest_ptr += str_copy_ram_lim_ret(Gsm.GsmDataUni.GsmDataStru.signal_strength,char_dest_ptr,0,0);
//        *char_dest_ptr++ = ','; // try once
//    // COPS
//        char_dest_ptr += str_copy_ram_lim_ret(Gsm.GsmDataUni.GsmDataStru.cops,char_dest_ptr,0,0);
//        *char_dest_ptr++ = ','; // try once
//    // Modem Data status
//        char_dest_ptr += str_copy_ram_lim_ret(Gsm.GsmDataUni.GsmDataStru.modem_data_status,char_dest_ptr,0,0);
//        *char_dest_ptr++ = ','; // try once
//    // LAC
//        char_dest_ptr += str_copy_ram_lim_ret(Gsm.GsmDataUni.GsmDataStru.lac,char_dest_ptr,0,0);
//        *char_dest_ptr++ = ','; // try once
//    // CELLID
//        char_dest_ptr += str_copy_ram_lim_ret(Gsm.GsmDataUni.GsmDataStru.cellid,char_dest_ptr,0,0);
//        *char_dest_ptr++ = ','; // try once
//    // Band
//        char_dest_ptr += str_copy_ram_lim_ret(Gsm.GsmDataUni.GsmDataStru.gsm_band,char_dest_ptr,0,0);
//        *char_dest_ptr++ = ','; // try once
//    // Channel
//        char_dest_ptr += str_copy_ram_lim_ret(Gsm.GsmDataUni.GsmDataStru.gsm_channel,char_dest_ptr,0,0);
//        *char_dest_ptr++ = ','; // try once
//    // FNN
//        char_dest_ptr += str_copy_ram_lim_ret(Gsm.GsmDataUni.GsmDataStru.fnn,char_dest_ptr,0,0);
//        *char_dest_ptr++ = ','; // try once
//    //SNN
//        char_dest_ptr += str_copy_ram_lim_ret(Gsm.GsmDataUni.GsmDataStru.snn,char_dest_ptr,0,0);
//        *char_dest_ptr++ = ','; // try once
//    //Server Name
//        char_dest_ptr += str_copy_ram_lim_ret(Gsm.GsmDataUni.GsmDataStru.server_name,char_dest_ptr,0,0);
//        *char_dest_ptr++ = ','; // try once
//    // Status Port
//        char_dest_ptr += str_copy_ram_lim_ret(Gsm.GsmDataUni.GsmDataStru.status_port,char_dest_ptr,0,0);
//        *char_dest_ptr++ = ','; // try once
//    // Command Port
//        char_dest_ptr += str_copy_ram_lim_ret(Gsm.GsmDataUni.GsmDataStru.command_port,char_dest_ptr,0,0);
//        *char_dest_ptr++ = ','; // try once
//    //Latitude float to char
//        //char_dest_ptr += float_to_char(Gps.GpsDataString.latitude,char_dest_ptr,4);
////        char_dest_ptr += str_copy_ram_lim_ret(Gps.GpsDataString.latitude,char_dest_ptr,0,0);
////        *char_dest_ptr++ = ','; // try once
////    // Longitude float to char
////        //char_dest_ptr += float_to_char(Gps.GpsDataString.longitude,char_dest_ptr,4);
////        char_dest_ptr += str_copy_ram_lim_ret(Gps.GpsDataString.longitude,char_dest_ptr,0,0);
////        *char_dest_ptr++ = ','; // try once
////    // Speed float to char
////        //char_dest_ptr += float_to_char(Gps.GpsDataString.speed,char_dest_ptr,3);
////        char_dest_ptr += str_copy_ram_lim_ret(Gps.GpsDataString.speed,char_dest_ptr,0,0);
////        *char_dest_ptr++ = ','; // try once
////    // Altitude float to char
////        //char_dest_ptr += float_to_char(Gps.GpsDataString.altitude,char_dest_ptr,3);
////        char_dest_ptr += str_copy_ram_lim_ret(Gps.GpsDataString.altitude,char_dest_ptr,0,0);
////        *char_dest_ptr++ = ','; // try once
//////    // Angle
//////        char_dest_ptr += str_copy_ram_lim_ret(Gps.GpsDataUni.GpsDataStru.alt,char_dest_ptr,0,0);
//////        *char_dest_ptr++ = ','; // try once
////    // No. of Satellite
////        dec_byte_to_char_fixed(&Gps.GpsDataString.satCount,char_dest_ptr,2); // decimal to char
//        char_dest_ptr += 2;
//        *char_dest_ptr++ = ',';
//    //char_dest_ptr += str_copy_ram_lim_ret(Gps.GpsDataUni.GpsDataStru.satlCnt,char_dest_ptr,0,0);
//    //*char_dest_ptr++ = ','; // try once
//    // HDOP float to char
////        char_dest_ptr += str_copy_ram_lim_ret(Gps.GpsDataString.hdopString,char_dest_ptr,0,0);
//        *char_dest_ptr++ = ','; // try once
//
//        //char crc_high_byte;
//        //char crc_low_byte;
//        //socketTxData  ,  Gsm.socketTxData[L_FRAME_INIT]
//        str_copy_ram_lim("STX,",Gsm.socketTxData,0);
//        uinteger temp_frame_len = L_FRAME_LEN(char_dest_ptr - &Gsm.socketTxData[L_FRAME_INIT]);
//        dec_int_to_char_fixed(&temp_frame_len,&Gsm.socketTxData[L_STX],4);
//        Gsm.socketTxData[L_STX+4] = ',';
//       // GSM.Params.socket[socket].tx[L_FRAME_INIT-L_FUNC_CODE]   = FC_CONFIGRATION;
//       // GSM.Params.socket[socket].tx[L_FRAME_INIT-L_FUNC_CODE+1] = ',';
//
//        //crc_generate_modbus(Gsm.socketTxData,(char_dest_ptr - Gsm.socketTxData));
//        //crc_high_byte = Gsm.socketTxData[char_dest_ptr - Gsm.socketTxData];
//        //crc_low_byte = Gsm.socketTxData[char_dest_ptr - Gsm.socketTxData + 1];
//        //dec_byte_to_char_fixed(&crc_high_byte,&Gsm.socketTxData[char_dest_ptr - Gsm.socketTxData],3);
//        //dec_byte_to_char_fixed(&crc_low_byte,&Gsm.socketTxData[char_dest_ptr - Gsm.socketTxData+3],3);
//        crc_generate_ascii_modbus(Gsm.socketTxData,(char_dest_ptr - Gsm.socketTxData));
//        str_copy_ram_lim("ETX",&Gsm.socketTxData[char_dest_ptr - Gsm.socketTxData+6],0);
//        Gsm.TxDataCnt = char_dest_ptr - Gsm.socketTxData + L_CRC + L_ETX;
////        GSM.Params.socket[socket].updated = 1;
//        Gsm.Flags.DataPacketReady = 1;
//        Gsm.TxOperation = 1;
}


void prepare_frame(void)
{

}