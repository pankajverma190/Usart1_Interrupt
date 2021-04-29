/*
 * gsm_m66.h
 *
 *  Created on: 21-Dec-2020
 *      Author: pankaj.kumar
 */

#ifndef STM32F0308_DISCOVERY_GSM_M66_H_
#define STM32F0308_DISCOVERY_GSM_M66_H_

#include "include_file.h"

#include "main.h"

#define SIZE_OF_AT_TX_RX_BUFFER 1024

typedef struct  {
	unsigned char command[40];
	unsigned char Responce [3][20];
	unsigned char ResponceType[3];
	unsigned char delimit1;
	unsigned char delimit2;
	uint16_t ResponseTime;
}ATCOMMANDS;

//extern ATCOMMANDS ;


struct gsm_data_struct
{
   char imei[16];
  // char utc_timeStamp[16];
   char DeviceID[15];
   char RecordID[15];
   char SwVer[15];
   char imsi[16];
   char ccid[20];
   char cops[15];
   char lac[8];
   char cellid[6];
   char gsm_channel[2];
   char status_port[6];
   char command_port[6];

   char signal_strength[3];
   char modem_data_status[2];
   char gsm_band[20];
   char fnn[32];
   char snn[16];
   char server_name[25];
//   struct gsm_time_struct time;
//   struct gsm_date_struct date;
}__attribute__ ((packed));


struct Gsm_Flags{
	volatile unsigned  Start:1;
	volatile unsigned  GsmInitialised:1;
	volatile unsigned  GsmErrorResponce:1;
	volatile unsigned  ATCommandResponceReceive:1;
	volatile unsigned  ATCommandResponceOK:1;
	volatile unsigned  ATCommandNetwrokRegistered:1;
	volatile unsigned  ATCommandGPRSActivated:1;

}__attribute__ ((packed));

//struct gsm_flags
//{
//    volatile unsigned Start:1;
//    volatile unsigned GsmInitialised:1;
//    volatile unsigned GSMNetworkCheck:1;
//    volatile unsigned GprsInitialise:1;
//    volatile unsigned GprsAttachment:1;
//    volatile unsigned PdpContextPara:1;
//    volatile unsigned ActivePdpContext:1;
//    volatile unsigned DataPacketReady:1;
//    volatile unsigned SocketCreated:1;
//    volatile unsigned SocketConfigured:1;
//    volatile unsigned SocketConnected:1;
//    volatile unsigned SocketSent:1;
//    volatile unsigned SocketClosed:1;
//    volatile unsigned ServerResponsed:1;
//    volatile unsigned ServerResponsedFailed:1;
//    volatile unsigned SleepModeActivate:1;
//    volatile unsigned WakeupModeActivate:1;
//    volatile unsigned GsmWakeup:1;
//    volatile unsigned WrittenSuccessfully:1;
//    volatile unsigned WriteAttemptComplete:1;
//
//    volatile unsigned FramDataRead:1;
//    volatile unsigned FramPacketReady:1;
//
//    volatile unsigned ActivateGprs:1;
//    volatile unsigned GprsIdentify:1;
//
//    volatile unsigned TransmitData:1;
//    volatile unsigned AtCommandResponseReceived:1;
//}__attribute__ ((packed));
typedef struct{
	struct Gsm_Flags Flags;
	struct gsm_data_struct gsm_data;
    uint8_t NetworkRegistrationStat;
    uint8_t NetworkRegistrationN;
    uint8_t SocketNo;
    uint8_t TxOperation;
    uint16_t RxDataCnt;
    uint16_t TxDataCnt;
	uint8_t TxData[SIZE_OF_AT_TX_RX_BUFFER];
	uint8_t RxData[SIZE_OF_AT_TX_RX_BUFFER];
}Gsm_struct;

extern Gsm_struct gsm;

enum
{
	GSM_INIT=0,GSM_NETWROK_REG,GSM_GPRS_CONFIG,GSM_PACKET_READY,GSM_SOCKET_CONNECTION,GSM_SOCKET_DATA_RECEIVE,GSM_RESET,
};

//typedef enum{
//	FALSE =0,
//	TRUE,
//}bool;

void GSM_USART1_UART_Init(void);
void gsm_task(void);
uint8_t send_At_Command_Test(ATCOMMANDS *atcommand);

// GSM functions for read status and details
void gsm_ccid(void);
void gsm_imsi(void);
void gsm_imei(void);
bool gsm_sim_Status(void);
bool network_registration_status(void);
void cops(void);
void prepare_data_packet(void);
#endif /* STM32F0308_DISCOVERY_GSM_M66_H_ */
