/*******************************************************************************
  Wesocket managment header file

  File Name:
    libwebsocket.h

  

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



#ifndef OCPP_WS_CLIENT_H__
#define OCPP_WS_CLIENT_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <signal.h>
#include <stddef.h>
#include <pthread.h>
#include <sys/time.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <arpa/inet.h>



#define FRAME_CHUNK_LENGTH 1024
#define HELPER_RECV_BUF_SIZE 1024

#define CLIENT_IS_SSL (1 << 0)
#define CLIENT_CONNECTING (1 << 1)
#define CLIENT_SHOULD_CLOSE (1 << 2)
#define CLIENT_SENT_CLOSE_FRAME (1 << 3)

#define REQUEST_HAS_CONNECTION (1 << 0)
#define REQUEST_HAS_UPGRADE (1 << 1)
#define REQUEST_VALID_STATUS (1 << 2)
#define REQUEST_VALID_ACCEPT (1 << 3)

#define WS_FRAGMENT_START (1 << 0)
#define WS_FRAGMENT_FIN (1 << 7)

#define WS_EXIT_MALLOC -1
#define WS_EXIT_PTHREAD_MUTEX_INIT -2
#define WS_EXIT_PTHREAD_CREATE -3
#define WS_EXIT_BAD_SCHEME -4

#define WS_OPEN_CONNECTION_ADDRINFO_ERR -1
#define WS_OPEN_CONNECTION_ADDRINFO_EXHAUSTED_ERR -2
#define WS_RUN_THREAD_RECV_ERR -3
#define WS_DO_CLOSE_SEND_ERR -4
#define WS_HANDLE_CTL_FRAME_SEND_ERR -5
#define WS_COMPLETE_FRAME_MASKED_ERR -6
#define WS_DISPATCH_MESSAGE_NULL_PTR_ERR -7
#define WS_SEND_AFTER_CLOSE_FRAME_ERR -8
#define WS_SEND_DURING_CONNECT_ERR -9
#define WS_SEND_NULL_DATA_ERR -10
#define WS_SEND_DATA_TOO_LARGE_ERR -11
#define WS_SEND_SEND_ERR -12
#define WS_HANDSHAKE_REMOTE_CLOSED_ERR -13
#define WS_HANDSHAKE_RECV_ERR -14
#define WS_HANDSHAKE_BAD_STATUS_ERR -15
#define WS_HANDSHAKE_NO_UPGRADE_ERR -16
#define WS_HANDSHAKE_NO_CONNECTION_ERR -17
#define WS_HANDSHAKE_BAD_ACCEPT_ERR -18
#define WS_HELPER_ALREADY_BOUND_ERR -19
#define WS_HELPER_CREATE_SOCK_ERR -20
#define WS_HELPER_BIND_ERR -21
#define WS_HELPER_LISTEN_ERR -22


typedef struct _wsclient_frame {
    unsigned int fin;
    unsigned int opcode;
    unsigned int mask_offset;
    unsigned int payload_offset;
    unsigned int rawdata_idx;
    unsigned int rawdata_sz;
    unsigned long long payload_len;
    char *rawdata;
    struct _wsclient_frame *next_frame;
    struct _wsclient_frame *prev_frame;
    unsigned char mask[4];
} wsclient_frame;

typedef struct _wsclient_message{
    unsigned int opcode;
    unsigned long long payload_len;
    char *payload;
} wsclient_message;

typedef struct _wsclient_error {
    int code;
    int extra_code;
    char *str;
} wsclient_error;

typedef struct _wsclient {
    pthread_t helper_thread;
    pthread_t handshake_thread;
    pthread_t run_thread;
    pthread_mutex_t lock;
    pthread_mutex_t send_lock;
    char *URI;
    int sockfd;
    int flags;
    int (*onopen)(struct _wsclient *);
    int (*onclose)(struct _wsclient *);
    int (*onerror)(struct _wsclient *, wsclient_error *err);
    int (*onmessage)(struct _wsclient *, wsclient_message *msg);
    wsclient_frame *current_frame;
    struct sockaddr_un helper_sa;
    int helper_sock;
} wsclient;


wsclient *libwsclient_new(const char *URI);
wsclient_error *libwsclient_new_error(int errcode);
ssize_t _libwsclient_read(wsclient *c, void *buf, size_t length);
ssize_t _libwsclient_write(wsclient *c, const void *buf, size_t length);
int libwsclient_open_connection(const char *host, const char *port);
int libwsclient_complete_frame(wsclient *c, wsclient_frame *frame);
void libwsclient_handle_control_frame(wsclient *c, wsclient_frame *ctl_frame);
void libwsclient_run(wsclient *c);
void libwsclient_finish(wsclient *client);       
void *libwsclient_run_thread(void *ptr);
void *libwsclient_handshake_thread(void *ptr);
void libwsclient_cleanup_frames(wsclient_frame *first);
void libwsclient_in_data(wsclient *c, char in);
void libwsclient_dispatch_message(wsclient *c, wsclient_frame *current);
int libwsclient_send(wsclient *client, char *strdata);
void libwsclient_onclose(wsclient *client, int (*cb)(wsclient *c));
void libwsclient_onopen(wsclient *client, int (*cb)(wsclient *c));
void libwsclient_onmessage(wsclient *client, int (*cb)(wsclient *c, wsclient_message *msg));
void libwsclient_onerror(wsclient *client, int (*cb)(wsclient *c, wsclient_error *err));




//int libwsclient_flags; //global flags variable


#endif