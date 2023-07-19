
/*******************************************************************************
  Charger configuration managemnt header file

  File Name:
    ocpp_chargerconfiguration.h

  

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




#ifndef __OCPP_CHARGERCONFIGURATION_H
#define __OCPP_CHARGERCONFIGURATION_H

#define SET_CHARGER_CNF_SUCCESS         0
#define SET_CHARGER_CNF_FAILED          1
#define SET_CHARGER_CNF_REBOOT_REQUIRED 2
#define SET_CHARGER_CNF_NOT_PRESENT     3

typedef enum 
{
    CHARGER_CONF_ID = 0,
    CHARGER_CONF_KEY,
    CHARGER_CONF_TYPE,
    CHARGER_CONF_VALUE,
    CHARGER_CONF_READONLY
}DB_CHARGER_TABLE_ROW;

typedef struct get_charger_config_key_t
{
    char key[40][40];
    uint8_t array_size;
}get_charger_config_key_t;

typedef struct db_data_t
{
    char id[20];
    char key[40];
    char type[20];
    char value[20];
    char readonly[20];
}db_data_t;

typedef struct set_charger_config_key_t
{
    char key[50];
    char value[50];
    uint16_t value_int;
}set_charger_config_key_t;


typedef struct get_charger_config_responce_t
{
    db_data_t db_data[10];
    uint8_t db_data_counter;
    uint8_t total_db_data_required;
    uint8_t new_data;
    uint8_t data_send_to_csm;
    char uuid[100];
    uint8_t update_data;
    uint8_t set_complete;
    uint8_t set_responce;
}get_charger_config_responce_t;

void ocpp_chargerconfiguration_init(void);
void ocpp_chargerconfiguration_get(get_charger_config_key_t keys);
void ocpp_chargerconfiguration_closedb(void);
void ocpp_chargerconfiguration_register_send_getconfiguration(uint8_t status,char *uuid);
cJSON *create_getcharger_conf_responce(uint16_t responce_status);
void ocpp_chargerconfiguration_update(set_charger_config_key_t key_value);
cJSON *create_setcharger_conf_responce(uint16_t responce_status);
void ocpp_chargerconfiguration_task(void);



#endif


