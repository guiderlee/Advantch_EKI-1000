/*******************************************************************************
  main.c application to test OCPP 1.6

  File Name:
    main.c

  

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

#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>

#include "ocppprocess.h"
#include "ocpp_chargerconfiguration.h"
#include "chargepointstatus.h"


typedef enum 
{
    OCPP16_NO_CB_STATUS = 0x00,
    OCCP16_BOOTNOTIFICATION = 0x01,
    OCCP16_HEARTBEAT,
    OCCP16_AUTH,
    OCCP16_START,
    OCCP16_STOP,
    OCCP16_REMOTESTART,
    OCCP16_REMOTESTOP,
}OCCP_cb_status_t;

uint8_t cb_status_update = 0;
uint8_t boot_status = 0;
uint8_t HB_status = 0;
uint8_t AUTH_status = 0;
uint8_t sta_status = 0;
uint8_t st_status = 0;

uint8_t isocpp_connected = 0;

static double wh;

void bootNcb(uint8_t status, double interval);
void Heartbeetcb(uint8_t status);
void Authcb(uint8_t status);
void Startcb(uint8_t status);
void Stopcb(uint8_t status);
void remote_start_cb(void);
void remote_stop_cb(void);




void remote_start_cb(void)
{
    cb_status_update = OCCP16_REMOTESTART;
}
void remote_stop_cb(void)
{
    cb_status_update = OCCP16_REMOTESTOP;
}

void bootNcb(uint8_t status, double interval)
{
    cb_status_update = OCCP16_BOOTNOTIFICATION;
    boot_status = status;
}
void Heartbeetcb(uint8_t status)
{
    cb_status_update = OCCP16_HEARTBEAT;
    HB_status = status;
}
void Authcb(uint8_t status)
{
    cb_status_update = OCCP16_AUTH;
    AUTH_status = status;
}
void Startcb(uint8_t status)
{
    cb_status_update = OCCP16_START;
    sta_status = status;

}
void Stopcb(uint8_t status)
{
    cb_status_update = OCCP16_STOP;
    st_status = status;
}

bool kbhit()
{
    int byteswaiting;
    ioctl(0, FIONREAD, &byteswaiting);
    return byteswaiting > 0;
}


void main(void)
{
    char ch;
    init_callback(bootNcb,Heartbeetcb,Authcb,Startcb,Stopcb);
	init_remote_call_cb(remote_start_cb,remote_stop_cb);
	init_ocpp_process();
    ocpp_chargerconfiguration_init();
    charge_point_status_init();

    


    while(1)
    {
        if(is_ocpp_connected() == false)
        {
            if((isocpp_connected == 0) || (isocpp_connected == 2))
            {
                printf("OCPP Not Connected Please check URL properly\n\r");
            }
            isocpp_connected = 1;
        }
        else
        {
            if((isocpp_connected == 0) || (isocpp_connected == 1))
            {
                printf("OCPP Connected\n\r");
            }
            isocpp_connected = 2;
            ocpp_chargerconfiguration_task();
            switch(cb_status_update)
            {
                case OCCP16_BOOTNOTIFICATION:
                    printf("\n\rOCCP 1.6 boot notification successfull\n\r");
                    cb_status_update = OCPP16_NO_CB_STATUS;
                break;
                case OCCP16_HEARTBEAT:
                    printf("\n\r OCPP 1.6 Heartbeet received\n\r");
                    cb_status_update = OCPP16_NO_CB_STATUS;
                break;
                case OCCP16_AUTH:
                    cb_status_update = OCPP16_NO_CB_STATUS;
                    printf("\n\r OCCP 1.6 AUTH responce received\n\r");
                    if(AUTH_status == 1)
                    {
                        printf("OCCP 1.6 Auth Accepted\n\r");
                    }
                    else
                    {
                        printf("OCCP 1.6 Auth Rejected\n\r");
                    }
                break;
                case OCCP16_START:
                    cb_status_update = OCPP16_NO_CB_STATUS;
                    printf("\n\r OCCP 1.6 Start responce received\n\r");
                    if(sta_status == 1)
                    {
                        printf("OCCP 1.6 Start Accepted\n\r");
                    }
                    else
                    {
                        printf("OCCP 1.6 Start Rejected\n\r");
                    }
                break;
                case OCCP16_STOP:
                    cb_status_update = OCPP16_NO_CB_STATUS;
                    printf("\n\r OCCP 1.6 Stop responce received\n\r");
                    if(st_status == 1)
                    {
                        printf("OCCP 1.6 Stop Accepted\n\r");
                    }
                    else
                    {
                        printf("OCCP 1.6 Stop Rejected\n\r");
                    }
                break;
                case OCCP16_REMOTESTART:
                    cb_status_update = OCPP16_NO_CB_STATUS;
                    printf("\n\r OCCP 1.6 Remote start request\n\r");
                    ocpp_send_Start();
                break;
                case OCCP16_REMOTESTOP:
                    cb_status_update = OCPP16_NO_CB_STATUS;
                    printf("\n\r OCCP 1.6 Remote start request\n\r");
                    ocpp_send_Stop(wh);
                break;

            }
            if(kbhit() == true)
            {
                ch = getc(stdin);
                printf("I received %c %02x\n",ch,ch);

                if(ch == 0x0a)
                {
                    printf("Received Enter\n\r");
                }
                else
                {
                    switch(ch)
                    {
                        case 'b':
                            ocpp_send_BootNotification();
                        break;
                        case 'h':
                            ocpp_send_HeartBeet();
                        break;
                        case 'a':
                        ocpp_send_Auth();
                        break;
                        case 'm':
                        ocpp_send_meterData(wh,230);
                        break;
                        case 's':
                        ocpp_send_Start();
                        break;
                        case 't':
                        ocpp_send_Stop(wh);
                        break;
                        case '1':
                            ocpp_send_StatusNotification();
                        break;
                        case '2':   
                            ocpp_send_DignosticsNotification();
                        break;
                        case '3':
                            ocpp_send_FirmwareStatusNotification();
                        break;
                        case 'n':
                        //ocpp_chargerconfiguration_get("AllowOfflineTxForUnknownId");
                        //ocpp_chargerconfiguration_register_send_getconfiguration(1,"1234");
                        break;
                        case 'Q':
                            ocpp_chargerconfiguration_closedb();
                            return;
                        break;

                    }
                }

                
            }
            
        }
        ocpp_chargerconfiguration_closedb();
        
        
    }
}


