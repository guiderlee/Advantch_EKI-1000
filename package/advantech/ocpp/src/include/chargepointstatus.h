
/*******************************************************************************
  Charge point status message header file

  File Name:
    chargepointstatus.h

  

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


#ifndef __CHARGE_POINT_STATUS_H
#define __CHARGE_POINT_STATUS_H

#include "stdint.h"

typedef enum
{
    AVAILABLE       = 0x00,
    PREPARING       = 0x01,
    CHARGING        = 0x02,
    SUSPENDEDEVSE   = 0x03,
    SUSPENDEDEV     = 0x04,
    FINISHING       = 0x05,
    RESERVED        = 0x06,
    UNAVAILABLE     = 0x07,
    FAULTED         = 0x08
}charge_point_status_t;

typedef enum
{
    CONNECTORLOCKFAILURE    = 0x00,
    EVCOMMUNICATIONERROR    = 0x01,
    GROUNDFAILURE           = 0x02,
    HIGHTEMPERATURE         = 0x03,
    INTERNALERROR           = 0x04,
    LOCALLISTCONFLICT       = 0x05,
    NOERROR                 = 0x06,
    OTHERERROR              = 0x07,
    OVERCURRENTFAILURE      = 0x08,
    OVERVOLTAGE             = 0x09,
    POWERMETERFAILURE       = 0x0a,
    RESPOWERSWITCHFAILUREET = 0x0b,
    READERFAILURE           = 0x0c,
    RESETFAILURE            = 0x0d,
    UNDERVOLTAGE            = 0x0e,
    WEAKSIGNAL              = 0x0f

}charge_point_errorcode_t;

typedef enum 
{
    IDLE = 0x00,
    UPLOADED,
    UPLOADFAILED,
    UPLOADING
}dignostics_info_t;

typedef enum 
{
    FW_DOWNLOADED,
    FW_DOWNLOADFAILED,
    FW_DOWNLOADING,
    FW_IDLE,
    FW_INSTALLATIONFAILED,
    FW_INSTALLING,
    FW_INSTALLED
}fw_info_t;

typedef struct _status_notification_struct_t
{
    charge_point_status_t charge_point_status;
    charge_point_errorcode_t charge_point_error;
}status_notification_t;

typedef uint16_t charger_dig_info_t;
typedef uint16_t charger_fw_status_info_t;


void charge_point_status_init(void);
void set_charge_point_eror(charge_point_errorcode_t error);
void get_charge_point_error(char *str);
void set_charge_point_status(charge_point_status_t status);
void get_charge_point_status(char *str);
void set_charger_dignostics_info(dignostics_info_t status);
void get_charger_dignostics_info(char *str);
void get_charger_fw_info(char *str);

#endif