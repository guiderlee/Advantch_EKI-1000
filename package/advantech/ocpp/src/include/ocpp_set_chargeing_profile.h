/*******************************************************************************
  Charger configuration managemnt header file

  File Name:
    ocpp_set_chargeing_profile.h

  

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




#ifndef __OCPP_SET_CHARGEING_PROFILE_H
#define __OCPP_SET_CHARGEING_PROFILE_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "libwebsocket.h"
#include "ocpp.h"
#include "cJSON.h"
//#include "main.h"

typedef struct chargeingscheduleperiod_data_t
{
    uint16_t startPeriod;
    uint8_t limit;
    uint8_t numberPhases;
}chargeingscheduleperiod_data_t;

typedef struct chargeingshedule_data_t
{
    uint16_t duration;
    char startSchedule[30];
    char chargingRateUnit[5];
    chargeingscheduleperiod_data_t chargingschedule_period;
    float minchargeingrate;
}chargeingshedule_data_t;

typedef struct cschargeingprofile_data_t
{
    uint8_t chargingProfileId;
    uint8_t stackLevel;
    char chargingProfilePurpose[25];
    char chargingProfileKind[20];
    char recurrencyKind[10];
    char validFrom[30];
    char validTo[30];
    chargeingshedule_data_t chargeingshedule;
}cschargeingprofile_data_t;

typedef struct setchargingprofile_data_t
{
    uint8_t connectorId;
    cschargeingprofile_data_t cs_chargeing_profile;
    uint8_t valiad_data;
    
}setchargingprofile_data_t;


void set_chargering_profile_parser(cJSON *json);
uint8_t clear_chargering_profile_parser(cJSON *json_obj);




#endif