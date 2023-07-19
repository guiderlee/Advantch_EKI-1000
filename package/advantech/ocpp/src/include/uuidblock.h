/*******************************************************************************
  uuid genrater and packer

  File Name:
    uuidblock.h

  

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

//uuidblock.h

#ifndef __UUIDBLOCK_H
#define __UUIDBLOCK_H

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


//Declaring GUID 16 octects according to RFC4122 https://tools.ietf.org/html/rfc4122
typedef unsigned char uuid_t[16];


//UUID structure defined as mentioned in RFC4122
struct uuid
{
    uint32_t     time_low;
    uint16_t     time_mid;
    uint16_t     time_hi_and_version;
    uint16_t     clock_seq;
    uint8_t      node[6];
};

//UUID comes in lower and upper cases, to convert the GUID returned and changing it to lower format
static const char *fmt_lower = "%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x";


int random_get_fd(void);
void random_get_bytes(void *buf, size_t nbytes);
void __uuid_generate_random(uuid_t out, int *num);
void uuid_unpack(const uuid_t in, struct uuid *uu);
void uuid_pack(const struct uuid *uu, uuid_t ptr);
void uuid_unparse_lower(const uuid_t uu, char *out);
void uuid_unparse_x(const uuid_t uu, char *out, const char *fmt);

#endif