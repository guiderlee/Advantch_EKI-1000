/*******************************************************************************
  ocpp process this will take send and receive of ocpp messages

  File Name:
    ocppprocess.h

  

  Description:
    None
*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2023 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

//ocpprun.h

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __OCPP_PROCESS_H
#define __OCPP_PROCESS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "libwebsocket.h"
#include "ocpp.h"
#include "cJSON.h"
//#include "main.h"

#define OCPP_MESSAGE_CALL_CODE      "2"
#define OCPP_MESSAGE_RESPONCE_CODE  "3"
#define OCPP_MESSAGE_ERROR_CODE     "4"


//OCPP Machine States, as per defined in the documentation
typedef enum{
    Authorize,
    BootNotification,
    CancelReservation,
    ChangeAvailability,
    ChangeConfiguration,
    ClearCache,
    ClearChargingProfile,
    DataTransfer,
    DiagnosticsStatusNotification,
    FirmwareStatusNotification,
    GetConfiguration,
    GetDiagnostics,
    GetLocalListVersion,
    Heartbeat,
    MeterValues,
    RemoteStartTransaction,
    RemoteStopTransaction,
    GetCompositeSchedule,
    ReserveNow,
    Reset,
    StartTransaction,
    StatusNotification,
    StopTransaction,
    SendLocalList,
    SetChargingProfile,
    TriggerMessage,
    UnlockConnector,
    UpdateFirmware
}OCPP_States;

typedef enum{
    OCPP_INIT,
    OCPP_CONNECT,
    OCPP_ISCONNECTED,
    OCPP_SENDBOOTNOTIFICATION,
    OCPP_SENDHEARTBEET,
    OCPP_SENDAUTH,
    OCPP_SENDSTART,
    OCPP_SENDSTOP,
    OCPP_WAITSERVERRESPOND,
    OCPP_NOCMD,
}OCPP_PROCESS_STATE_t;

#define BOOTNOTIFICATION_MSG        0b00000001
#define HEARTBEET_MSG               0b00000010
#define AUTH_MSG                    0b00000100
#define START_MSG                   0b00001000
#define STOP_MSG                    0b00010000
#define STATUS_NOTIFICATION_MSG     0b00100000
#define STATUS_DIGNOTIFICATION_MSG  0b01000000
#define STATUS_FW_MSG               0b10000000

#define TIGGER_BOOTNOTIFICATION     0
#define TIGGER_HEARTBEAT            1
#define TRIGGER_STATUSNOTIFICATION  2
#define TRIGGER_FWNOTIFICATION      3
#define TRIGGER_DIGNOTIFICATION     4
#define TRIGGER_METERVALUE          5

typedef enum{
    MSG_NO_OPERATION,
    MSG_SENT,
    MSG_SEND_FAIL,
    MSG_REPONCE_FAIL,
    MSG_RESPONCE_WRONG_STATE,
    MSG_RESPONCE_RECEIVED
}MSG_SEND_STATE_t;

typedef void (*bootnotificationcb)(uint8_t status, double interval);
typedef void (*heartbeetcb)(uint8_t status);
typedef void (*authcb)(uint8_t status);
typedef void (*startcb)(uint8_t status);
typedef void (*stopcb)(uint8_t status);
typedef void (*remotestartcb)(void);    //connector id need to implement
typedef void (*remotestopcb)(void);     //connector id need to implement
typedef void (*socket_status_cb)(uint8_t status);


typedef struct GetDiagnostics_data_t
{
   char location[128];
   char starttime[50];
   char stoptime[50];
   uint16_t retries;
   uint16_t retryInterval;
}GetDiagnostics_data_t;

typedef struct fwupdate_data_t
{
   char location[128];
   char retrieveDate[50];
   uint16_t retries;
   uint16_t retryInterval;
}fwupdate_data_t;

typedef struct datatrasfer_data_t
{
    char vendorId[50];
    char messageId[50];
    char data[1024];
}datatrasfer_data_t;





typedef struct __OCPP_PROCESS_STRUCT_
{
    cJSON *configJson;           //assigning JSON pointer for config.json
    cJSON *developmentPacket;    //assigning JSON pointer for development information in config.json
    char *url;                   //assigning URL pointer of char type for the URL of the server i.e websocket connection address
    wsclient *myclient;

    OCPP_States ocppstates;        //According to OCPP1.6, BootNotification is the first state which registers itself to network
    OCPP_PROCESS_STATE_t ocpp_process_states;
    MSG_SEND_STATE_t isMessageSend;                   //Flag used if message is send from CP to CMS
    uint8_t isWSEstablished;              //Flag used if connection is established between CP and CMS

    ocpp_frame *ocppSendFrame;         //OCPP Send Frame defined as per ocpp_frame structure in ocpp_helper.h
    ocpp_frame *ocppReceiveFrame;       //OCPP Receive Frame defined as per ocpp_frame structure in ocpp_helper.h
    ocpp_responce_frame *ocppresponceframe;

    uint8_t ismessagesendtype;

    double starttxid;

    //callback 
    bootnotificationcb boot_notification_cb;
    heartbeetcb heart_beet_cb;
    authcb auth_cb;
    startcb start_cb;
    stopcb stop_cb;
    remotestartcb remote_start_cb;
    remotestopcb remote_stop_cb;
    socket_status_cb socketsttus_cb;

    uint8_t tigger_messages_process;
    uint8_t tigger_connectorID;


    
}OCPP_PROCESS_t;




int onclose(wsclient *c);               // This function is called when close event occurs in websocket connection
int onerror(wsclient *c, wsclient_error *err);          // This function is called when error event occurs in websocket connection
int onmessage(wsclient *c, wsclient_message *msg);         // This function is called when message event occurs in websocket connection
int onopen(wsclient *c);                // This function is called webSocket is just open

void ocpp_process_read_config(void);
void ocpp_process_get_url(void);
void ocpp_websocket_connect(void);
bool is_ocpp_connected(void);
void ocpp_process_init(void);
void ocpp_process_task(void);

//interface to others
void init_callback_connect(socket_status_cb sock_st);
void init_callback(bootnotificationcb bn,heartbeetcb hb,authcb au,startcb sta,stopcb st);
void init_ocpp_process(void);
void ocpp_send_BootNotification(void);
void ocpp_send_HeartBeet(void);
void ocpp_send_Auth(void);
void ocpp_send_Start(void);
void ocpp_send_Stop(double kwh);
void ocpp_send_meterData(double kwh,double v);
void init_remote_call_cb(remotestartcb RSTART,remotestopcb RSTOP);
void ocpp_send_reservenow_responce(char *uuid);
void ocpp_send_changeavaliability_responce(char *uuid);
void ocpp_send_cancelReservation_responce(char *uuid);
void ocpp_send_reset_responce(char *uuid, char *type);
void ocpp_send_UnlockConnector_responce(char *uuid, uint16_t connectorid);
void ocpp_send_getchargerconfig_responce(char *uuid);
void ocpp_send_setchargerconfig_responce(char *uuid,uint8_t status);
void ocpp_send_ClearCache_responce(char *uuid);
void ocpp_send_GetDiagnostics_responce(char *uuid,char *location);
void ocpp_send_UpdateFirmware_responce(char *uuid);
void ocpp_send_DataTransfer_responce(char *uuid);
void ocpp_send_setchargeingprofile_responce(char *uuid);
void ocpp_send_clearchargeingprofile_responce(char *uuid);
void ocpp_send_DignosticsNotification(void);
void ocpp_send_StatusNotification(void);
void ocpp_send_FirmwareStatusNotification(void);
void TiggerMsg_process(cJSON *json);
void ocpp_send_TimggerMessage_responce(char *uuid,char *status);

#endif

#ifdef __cplusplus
}
#endif
