/*
 * gsm_m66.h
 *
 *  Created on: 21-Dec-2020
 *      Author: pankaj.kumar
 */

#ifndef STM32F0308_DISCOVERY_GSM_M66_H_
#define STM32F0308_DISCOVERY_GSM_M66_H_

#include "include_file.h"
//#include "string_operation.h"
//#include "main.h"

#define SIZE_OF_AT_TX_RX_BUFFER 1024

// functional code
# define FC_ALERT				'A'
#define  FC_KEEPLIVE			'K'
#define  FC_STATUS				'S'
#define	 FC_CONFIGURATION		'C'
#define	 FC_BUZZER_ON			'N'
#define	 FC_BUZZER_OFF			'F'

typedef struct  {
	unsigned char command[40];
	unsigned char Response [3][20];
	unsigned char ResponceType[3];
	unsigned char delimit1;
	unsigned char delimit2;
	uint16_t ResponseTime;
}ATCOMMANDS;

//extern ATCOMMANDS ;

struct gsm_date_time_struct
{
	unsigned char date[8];
	unsigned char time[8];

};


struct gsm_data_struct
{
	unsigned char imei[16];
  // char utc_timeStamp[16];
	unsigned char DeviceID[15];
	unsigned char RecordID[15];
   unsigned char SwVer[15];
   unsigned char imsi[16];
   unsigned char ccid[20];
   unsigned char cops[15];
   unsigned char gsm_channel[2];
   unsigned char status_port[6];
   unsigned char Response_IP[16];
   unsigned char Response_Port[6];

   unsigned char command_port[6];

   unsigned char signal_strength[3];
   unsigned char gsm_band[10];
   unsigned char snn[16];
   unsigned char server_name[20];
   uint16_t data_receive_count;
   unsigned char server_data[60];
   unsigned char FC_CONFIGRATION;
   unsigned char Responce_FC;
  // struct gsm_time_struct time;
   struct gsm_date_time_struct date_time;
}__attribute__ ((packed));



struct Gsm_Flags{
	volatile unsigned  Start:1;
	volatile unsigned  GsmInitialised:1;
	volatile unsigned  GsmErrorResponce:1;
	volatile unsigned  SimStatusChecked:1;
	volatile unsigned  ATCommandResponceReceive:1;
	volatile unsigned  ATCommandResponceOK:1;
	volatile unsigned  ATCommandNetwrokRegistered:1;
	volatile unsigned  ATCommandGPRSActivated:1;
	volatile unsigned  GprsAttachment;
	volatile unsigned  PdpContextPara;
	volatile unsigned  ActivePdpContext;
	volatile unsigned  SetTransparentMode;
	volatile unsigned  SocketStart;
	volatile unsigned  SocketDirectMode;
	volatile unsigned  SocketConnectedDirectMode;
	volatile unsigned  SocketSendData;
	volatile unsigned  DataPacketReady;
	volatile unsigned  ReceivedData;
	volatile unsigned  GsmReset;
	volatile unsigned  GsmSleep;
	volatile unsigned  crcVerified;
	volatile unsigned  imei_mactched;

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
   unsigned char crc_data[4];
   char Socket_connection;
    uint8_t TxOperation;
    uint8_t RxOperation;
    uint16_t RxDataCnt;
    uint16_t TxDataCnt;
	uint8_t TxData[SIZE_OF_AT_TX_RX_BUFFER - 892];
	//uint8_t RxData[SIZE_OF_AT_TX_RX_BUFFER- 992];
	uint8_t RxData[SIZE_OF_AT_TX_RX_BUFFER- 892];
//    union
//    {
//		uint8_t  socketRxData[SIZE_OF_AT_TX_RX_BUFFER-512];
//    //    struct Server_Status_ACK_Struct StausAckStru;
//    //    struct Server_Commnd_ACK_Struct CommandAckStru;
//    }ServerRxDataUni;
}Gsm_struct;

extern Gsm_struct gsm;

enum
{
	GSM_INIT=0,GSM_NETWROK_REG,GSM_GPRS_CONFIG,GSM_PACKET_READY,GSM_TCPIP_STATE,GSM_SOCKET_DATA_RECEIVE,GSM_SLEEP,GSM_RESET,
};

enum
{
	GPRS_REGISTERTION=0,GPRS_ATTACHMENT,PDP_CONTEXT_PARA,ACTIVATE_PDP_CONTEXT,NON_TRANSPARENT_MODE,
};

enum
{
	TCP_IP_SOCKET_CREATE=0,TCP_IP_SOCKET_SELECT_MODE,TCP_IP_CONNECTION,TCP_IP_SEND_DATA,
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
void serverdatasave();
void date_time_status();
uint8_t VerifyRespAndPrepForNxtStep(ATCOMMANDS *At_Command, char);
void SendCommandAndWaitForResponse(ATCOMMANDS *At_Command);

#endif /* STM32F0308_DISCOVERY_GSM_M66_H_ */
