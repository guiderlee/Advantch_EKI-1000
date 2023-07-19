/*******************************************************************************
  ocpp core source header file

  File Name:
    ocpp.h

  

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

//ocpphelper.h


#ifndef __OCPPHELPER_H
#define __OCPPHELPER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <fcntl.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>
#include "libwebsocket.h"
#include "cJSON.h"

//Message length defined for OCPP Payload
#define MESSAGE_MAX_LEN 1000

#define UNLOCKCONNECTOR_SUCCESS     0
#define UNLOCKCONNECTOR_FAILED      1
#define UNLOCKCONNECTOR_NOT_PRESENT 2



//OCPP frame structure defined
typedef struct _ocpp_frame
{
    char *messageCode;     //messageCode of character type
    char *messageID;       //messageID or UUID for uniquely identifying each message
    char *action;          //What action is to be used
    cJSON *jsonPacket;     //JSON packet associated with that particular action 
}ocpp_frame;

typedef struct _ocpp_responce_frame
{
    char *messageCode;     //messageCode of character type
    char *messageID;       //messageID or UUID for uniquely identifying each message
    cJSON *jsonPacket;     //JSON packet associated with that particular action 
}ocpp_responce_frame;




/**
 * Fucntion prototypes defined here
*/

ocpp_frame *createocppframe(char *messagecode, char *actiontocms, cJSON *jsonpacket);
cJSON *readocppconfig(const char *filePath);
cJSON *createbootnotificationrequest(cJSON *config);
int sendframe(wsclient *c,ocpp_frame *packet);
int sendresponceframe(wsclient *c,ocpp_responce_frame *packet);
ocpp_frame *processocppframe(char *payload);
static int getSubString(char *source, char *target,int from, int to);
int changeTimeOfMachine(char *isoTime);
cJSON *createheartbeetpacket(cJSON *config);
cJSON *createauthpacket(cJSON *config);
cJSON *createstartpacket(cJSON *config);
cJSON *createstoppacket(cJSON *config,double kw,double txid);
uint8_t gettagidstatus(cJSON *reply,uint64_t *interval);
cJSON *creatmwterdata(double kwh,double v);
uint8_t checktagidmatch(cJSON *config,cJSON *reply);
uint8_t processmsgcodeframe(char *payload,char *ret);

ocpp_frame *processocppcallframe(char *payload);
ocpp_responce_frame *createocppreplyframe(char *messagecode, char *uuid,cJSON *jsonpacket);
cJSON *createremotestarttranspacket(uint8_t status);

cJSON *create_reservenow_responce(uint16_t responce_status);
cJSON *create_changeavaliability_responce(uint16_t responce_status);
cJSON *create_CancelReservation_responce(uint16_t responce_status);
cJSON *create_Reset_responce(uint16_t responce_status);
cJSON *create_UnlockConnector_responce(uint16_t responce_status);
cJSON *create_ClearCache_responce(uint16_t responce_status);
cJSON *create_GetDiagnostics_responce(char *location);
cJSON *create_UpdateFirmware_responce(uint8_t responce);
cJSON *create_DataTransfer_responce(uint16_t responce_status);
cJSON *create_setchargeingprofile_responce(uint16_t responce_status);
cJSON *create_clearchargeing_responce(uint16_t responce_status);
cJSON *createstatusnotificationrequest(void);
cJSON *createdignosicsnotificationrequest(void);
cJSON *createfirmwarenotificationrequest(void);
cJSON *Trigger_responce(char *status_str);

#endif
