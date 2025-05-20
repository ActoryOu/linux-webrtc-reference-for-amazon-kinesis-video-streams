/*
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef METRIC_H
#define METRIC_H

#pragma once

/* *INDENT-OFF* */
#ifdef __cplusplus
extern "C" {
#endif
/* *INDENT-ON* */

#include <stdio.h>
#include <inttypes.h>
#include <pthread.h>

typedef enum MetricEvent
{
    METRIC_EVENT_NONE = 0,

    /* Signaling Events */
    METRIC_EVENT_SIGNALING_DESCRIBE_CHANNEL,
    METRIC_EVENT_SIGNALING_GET_ENDPOINTS,
    METRIC_EVENT_SIGNALING_GET_ICE_SERVER_LIST,
    METRIC_EVENT_SIGNALING_CONNECT_WSS_SERVER,
    METRIC_EVENT_SIGNALING_GET_CREDENTIALS,
    METRIC_EVENT_SIGNALING_JOIN_STORAGE_SESSION,

    /* ICE Events. */
    METRIC_EVENT_ICE_GATHER_HOST_CANDIDATES,
    METRIC_EVENT_ICE_GATHER_SRFLX_CANDIDATES,
    METRIC_EVENT_ICE_GATHER_RELAY_CANDIDATES,
    METRIC_EVENT_ICE_FIND_P2P_CONNECTION,

    /* Peer Connection Events. */
    METRIC_EVENT_PC_DTLS_HANDSHAKING,

    /* Combine case. */
    METRIC_EVENT_SENDING_FIRST_FRAME,

    /* Profiling Case - Handle SDP Offer. */
    METRIC_EVENT_HANDLE_SDP_OFFER,
    METRIC_EVENT_HANDLE_EXTRACT_SDP_OFFER,
    METRIC_EVENT_HANDLE_DESERIALIZE_SDP_OFFER,
    METRIC_EVENT_HANDLE_START_PEER_CONNECTION,
    METRIC_EVENT_HANDLE_SET_REMOTE_DESCRIPTION,
    METRIC_EVENT_HANDLE_SET_LOCAL_DESCRIPTION,
    METRIC_EVENT_HANDLE_CREATE_SDP_ANSWER,
    METRIC_EVENT_HANDLE_SERIALIZE_SDP_ANSWER,
    METRIC_EVENT_HANDLE_SEND_SDP_ANSWER,

    /* Profiling Case - Set Remote Description. */
    METRIC_EVENT_HANDLE_PC_DESERIALIZE_SDP_OFFER,
    METRIC_EVENT_HANDLE_SET_PAYLOAD_TYPES,
    METRIC_EVENT_HANDLE_START_ICE_CONTROLLER,
    METRIC_EVENT_HANDLE_INIT_RTP,
    METRIC_EVENT_HANDLE_INIT_RTCP,
    METRIC_EVENT_HANDLE_WRITE_STARTUP_BARRIER,
    METRIC_EVENT_HANDLE_ADD_REMOTE_CANDIDATES,

    /* Profiling Case - Start ICE Controller. */
    METRIC_EVENT_HANDLE_INIT_ICE,
    METRIC_EVENT_HANDLE_FREE_SOCKET_CONTEXTS,
    METRIC_EVENT_HANDLE_ADD_LOCAL_CANDIDATES,
    METRIC_EVENT_HANDLE_START_POLLING,
    METRIC_EVENT_HANDLE_ON_TIMER_EXPIRE,

    /* Profiling Case - Add Local Candidates. */
    METRIC_EVENT_HANDLE_ADD_RELAY_CANDIDATES,
    METRIC_EVENT_HANDLE_ADD_RELAY_CANDIDATE_0,
    METRIC_EVENT_HANDLE_ADD_RELAY_CANDIDATE_1,
    METRIC_EVENT_HANDLE_ADD_RELAY_CANDIDATE_2,
    METRIC_EVENT_HANDLE_ADD_RELAY_CANDIDATE_3,
    METRIC_EVENT_HANDLE_ADD_RELAY_CANDIDATE_4,
    METRIC_EVENT_HANDLE_ADD_RELAY_CANDIDATE_5,
    METRIC_EVENT_HANDLE_ADD_RELAY_CANDIDATE_6,
    METRIC_EVENT_HANDLE_ADD_RELAY_CANDIDATE_7,
    METRIC_EVENT_HANDLE_CREATE_SOCKET_CONTEXT_0,
    METRIC_EVENT_HANDLE_CREATE_SOCKET_CONTEXT_1,
    METRIC_EVENT_HANDLE_CREATE_SOCKET_CONTEXT_2,
    METRIC_EVENT_HANDLE_CREATE_SOCKET_CONTEXT_3,
    METRIC_EVENT_HANDLE_CREATE_SOCKET_CONTEXT_4,
    METRIC_EVENT_HANDLE_CREATE_SOCKET_CONTEXT_5,
    METRIC_EVENT_HANDLE_CREATE_SOCKET_CONTEXT_6,
    METRIC_EVENT_HANDLE_CREATE_SOCKET_CONTEXT_7,

    /* Profiling Case - Create TURN TCP Connection. */
    METRIC_EVENT_HANDLE_CREATE_TCP_CONNECTION,
    METRIC_EVENT_HANDLE_TCP_CONNECT,
    METRIC_EVENT_HANDLE_TLS_HANDSHAKE,

    METRIC_EVENT_MAX,
} MetricEvent_t;

typedef enum MetricEventState
{
    METRIC_EVENT_STATE_NONE = 0,
    METRIC_EVENT_STATE_RECORDING,
    METRIC_EVENT_STATE_RECORDED,
} MetricEventState_t;

typedef struct MetricEventRecord
{
    MetricEventState_t state;
    uint64_t startTimeUs;
    uint64_t endTimeUs;
} MetricEventRecord_t;

typedef struct MetricContext
{
    uint8_t isInit;
    MetricEventRecord_t eventRecords[ METRIC_EVENT_MAX ];
    pthread_mutex_t mutex;
} MetricContext_t;

void Metric_Init( void );
void Metric_StartEvent( MetricEvent_t event );
void Metric_EndEvent( MetricEvent_t event );
void Metric_PrintMetrics( void );
void Metric_ResetEvent( void );

/* *INDENT-OFF* */
#ifdef __cplusplus
}
#endif
/* *INDENT-ON* */

#endif /* METRIC_H */
