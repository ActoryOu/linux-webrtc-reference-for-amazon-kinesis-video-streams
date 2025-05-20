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

#include "logging.h"
#if METRIC_PRINT_ENABLED
#include "metric.h"
#endif

#include <time.h>
#include <unistd.h>

#define METRIC_PRINT_INTERVAL_MS ( 10000 )

MetricContext_t context;

/* Convert event ID enum into string. */
static const char * ConvertEventToString( MetricEvent_t event );

/* Calculate the duration in miliseconds from start & end time. */
static uint64_t CalculateEventDurationMs( uint64_t startTimeUs,
                                          uint64_t endTimeUs );

static const char * ConvertEventToString( MetricEvent_t event )
{
    const char * pRet = "Unknown";
    switch( event )
    {
        case METRIC_EVENT_NONE:
            pRet = "None";
            break;
        case METRIC_EVENT_SIGNALING_DESCRIBE_CHANNEL:
            pRet = "Describe Signaling Channel";
            break;
        case METRIC_EVENT_SIGNALING_GET_ENDPOINTS:
            pRet = "Get Signaling Endpoints";
            break;
        case METRIC_EVENT_SIGNALING_GET_ICE_SERVER_LIST:
            pRet = "Get Ice Server List";
            break;
        case METRIC_EVENT_SIGNALING_CONNECT_WSS_SERVER:
            pRet = "Connect Websocket Server";
            break;
        case METRIC_EVENT_SIGNALING_GET_CREDENTIALS:
            pRet = "Get Authentication Temporary Credentials";
            break;
        case METRIC_EVENT_ICE_GATHER_HOST_CANDIDATES:
            pRet = "Gather ICE Host Candidate";
            break;
        case METRIC_EVENT_ICE_GATHER_SRFLX_CANDIDATES:
            pRet = "Gather ICE Srflx Candidate";
            break;
        case METRIC_EVENT_ICE_GATHER_RELAY_CANDIDATES:
            pRet = "Gather ICE Relay Candidate";
            break;
        case METRIC_EVENT_SIGNALING_JOIN_STORAGE_SESSION:
            pRet = "Join Storage Session";
            break;
        case METRIC_EVENT_ICE_FIND_P2P_CONNECTION:
            pRet = "Find Peer-To-Peer Connection";
            break;
        case METRIC_EVENT_PC_DTLS_HANDSHAKING:
            pRet = "DTLS Handshaking";
            break;
        case METRIC_EVENT_SENDING_FIRST_FRAME:
            pRet = "First Frame";
            break;
        case METRIC_EVENT_HANDLE_SDP_OFFER:
            pRet = "Handle SDP Offer";
            break;
        case METRIC_EVENT_HANDLE_EXTRACT_SDP_OFFER:
            pRet = "Extract SDP Offer";
            break;
        case METRIC_EVENT_HANDLE_DESERIALIZE_SDP_OFFER:
            pRet = "Deserialize SDP Offer";
            break;
        case METRIC_EVENT_HANDLE_START_PEER_CONNECTION:
            pRet = "Start Peer Connection";
            break;
        case METRIC_EVENT_HANDLE_SET_REMOTE_DESCRIPTION:
            pRet = "Set Remote Description";
            break;
        case METRIC_EVENT_HANDLE_SET_LOCAL_DESCRIPTION:
            pRet = "Set Local Description";
            break;
        case METRIC_EVENT_HANDLE_CREATE_SDP_ANSWER:
            pRet = "Create SDP Answer";
            break;
        case METRIC_EVENT_HANDLE_SERIALIZE_SDP_ANSWER:
            pRet = "Serialize SDP Answer";
            break;
        case METRIC_EVENT_HANDLE_SEND_SDP_ANSWER:
            pRet = "Send SDP Answer";
            break;
        case METRIC_EVENT_HANDLE_PC_DESERIALIZE_SDP_OFFER:
            pRet = "Deserialize Peer Connection SDP Offer";
            break;
        case METRIC_EVENT_HANDLE_SET_PAYLOAD_TYPES:
            pRet = "Set Payload Types";
            break;
        case METRIC_EVENT_HANDLE_START_ICE_CONTROLLER:
            pRet = "Start ICE Controller";
            break;
        case METRIC_EVENT_HANDLE_INIT_RTP:
            pRet = "Init RTP Library";
            break;
        case METRIC_EVENT_HANDLE_INIT_RTCP:
            pRet = "Init RTCP Library";
            break;
        case METRIC_EVENT_HANDLE_WRITE_STARTUP_BARRIER:
            pRet = "Write StartUp Barrier";
            break;
        case METRIC_EVENT_HANDLE_ADD_REMOTE_CANDIDATES:
            pRet = "Add Remote Candidates";
            break;
        case METRIC_EVENT_HANDLE_INIT_ICE:
            pRet = "Init ICE Library";
            break;
        case METRIC_EVENT_HANDLE_FREE_SOCKET_CONTEXTS:
            pRet = "Free Socket Contexts";
            break;
        case METRIC_EVENT_HANDLE_ADD_LOCAL_CANDIDATES:
            pRet = "Add Local Candidates";
            break;
        case METRIC_EVENT_HANDLE_START_POLLING:
            pRet = "Start Polling";
            break;
        case METRIC_EVENT_HANDLE_ON_TIMER_EXPIRE:
            pRet = "On Timer Expire";
            break;
        case METRIC_EVENT_HANDLE_ADD_RELAY_CANDIDATES:
            pRet = "Add Relay Candidates";
            break;
        case METRIC_EVENT_HANDLE_ADD_RELAY_CANDIDATE_0:
            pRet = "Add Relay Candidate 0";
            break;
        case METRIC_EVENT_HANDLE_ADD_RELAY_CANDIDATE_1:
            pRet = "Add Relay Candidate 1";
            break;
        case METRIC_EVENT_HANDLE_ADD_RELAY_CANDIDATE_2:
            pRet = "Add Relay Candidate 2";
            break;
        case METRIC_EVENT_HANDLE_ADD_RELAY_CANDIDATE_3:
            pRet = "Add Relay Candidate 3";
            break;
        case METRIC_EVENT_HANDLE_ADD_RELAY_CANDIDATE_4:
            pRet = "Add Relay Candidate 4";
            break;
        case METRIC_EVENT_HANDLE_ADD_RELAY_CANDIDATE_5:
            pRet = "Add Relay Candidate 5";
            break;
        case METRIC_EVENT_HANDLE_ADD_RELAY_CANDIDATE_6:
            pRet = "Add Relay Candidate 6";
            break;
        case METRIC_EVENT_HANDLE_ADD_RELAY_CANDIDATE_7:
            pRet = "Add Relay Candidate 7";
            break;
        case METRIC_EVENT_HANDLE_CREATE_SOCKET_CONTEXT_0:
            pRet = "Create Socket Context 0";
            break;
        case METRIC_EVENT_HANDLE_CREATE_SOCKET_CONTEXT_1:
            pRet = "Create Socket Context 1";
            break;
        case METRIC_EVENT_HANDLE_CREATE_SOCKET_CONTEXT_2:
            pRet = "Create Socket Context 2";
            break;
        case METRIC_EVENT_HANDLE_CREATE_SOCKET_CONTEXT_3:
            pRet = "Create Socket Context 3";
            break;
        case METRIC_EVENT_HANDLE_CREATE_SOCKET_CONTEXT_4:
            pRet = "Create Socket Context 4";
            break;
        case METRIC_EVENT_HANDLE_CREATE_SOCKET_CONTEXT_5:
            pRet = "Create Socket Context 5";
            break;
        case METRIC_EVENT_HANDLE_CREATE_SOCKET_CONTEXT_6:
            pRet = "Create Socket Context 6";
            break;
        case METRIC_EVENT_HANDLE_CREATE_SOCKET_CONTEXT_7:
            pRet = "Create Socket Context 7";
            break;
        case METRIC_EVENT_HANDLE_CREATE_TCP_CONNECTION:
            pRet = "Create TCP Connection";
            break;
        case METRIC_EVENT_HANDLE_TCP_CONNECT:
            pRet = "Complete TCP Connect";
            break;
        case METRIC_EVENT_HANDLE_TLS_HANDSHAKE:
            pRet = "Start TLS Handshaking";
            break;
        default:
            pRet = "Unknown";
            break;
    }

    return pRet;
}

static uint64_t CalculateEventDurationMs( uint64_t startTimeUs,
                                          uint64_t endTimeUs )
{
    return ( endTimeUs - startTimeUs ) / ( 1000 * 1000 );
}

static uint64_t GetTimestampInNs( void )
{
    struct timespec nowTime;
    clock_gettime( CLOCK_REALTIME, &nowTime );
    return ( uint64_t ) nowTime.tv_sec * 1000 * 1000 * 1000 + ( uint64_t ) nowTime.tv_nsec;
}

void Metric_Init( void )
{
    int retval;

    memset( &context, 0, sizeof( MetricContext_t ) );

    retval = pthread_mutex_init( &( context.mutex ), NULL );
    if( retval != 0 )
    {
        LogError( ( "Fail to create mutex for Metric." ) );
    }
    else
    {
        context.isInit = 1U;
    }
}

void Metric_StartEvent( MetricEvent_t event )
{
    if( ( context.isInit == 1U ) && ( event < METRIC_EVENT_MAX ) &&
        ( pthread_mutex_lock( &( context.mutex ) ) == 0 ) )
    {
        MetricEventRecord_t * pEventRecord = &context.eventRecords[ event ];

        if( pEventRecord->state == METRIC_EVENT_STATE_NONE )
        {
            pEventRecord->state = METRIC_EVENT_STATE_RECORDING;
            pEventRecord->startTimeUs = GetTimestampInNs();
        }

        pthread_mutex_unlock( &( context.mutex ) );
    }
}

void Metric_EndEvent( MetricEvent_t event )
{
    if( ( context.isInit == 1U ) && ( event < METRIC_EVENT_MAX ) &&
        ( pthread_mutex_lock( &( context.mutex ) ) == 0 ) )
    {
        MetricEventRecord_t * pEventRecord = &context.eventRecords[ event ];

        if( pEventRecord->state == METRIC_EVENT_STATE_RECORDING )
        {
            pEventRecord->state = METRIC_EVENT_STATE_RECORDED;
            pEventRecord->endTimeUs = GetTimestampInNs();
        }

        pthread_mutex_unlock( &( context.mutex ) );
    }
}

void Metric_PrintMetrics( void )
{
    int i;
    MetricEventRecord_t * pEventRecord;
    //static char runTimeStatsBuffer[ 4096 ];

    if( ( context.isInit == 1U ) &&
        ( pthread_mutex_lock( &( context.mutex ) ) == 0 ) )
    {
        LogInfo( ( "================================ Print Metrics Start ================================" ) );
        for( i = 0; i < METRIC_EVENT_MAX; i++ )
        {
            pEventRecord = &context.eventRecords[ i ];

            if( pEventRecord->state == METRIC_EVENT_STATE_RECORDED )
            {
                LogInfo( ( "Duration of %s: %lu ms",
                           ConvertEventToString( ( MetricEvent_t )i ),
                           CalculateEventDurationMs( pEventRecord->startTimeUs, pEventRecord->endTimeUs ) ) );
            }
        }

        //LogInfo( ( "Remaining free heap size: %u", xPortGetFreeHeapSize() ) );

        // vTaskGetRunTimeStats( runTimeStatsBuffer );
        // LogInfo( ( " == Run Time Stat Start ==\n%s\n == Run Time Stat End ==", runTimeStatsBuffer ) );
        LogInfo( ( "================================ Print Metrics End ================================" ) );

        pthread_mutex_unlock( &( context.mutex ) );
        fflush( stdout );
    }
}

void Metric_ResetEvent( void )
{
    if( ( context.isInit == 1U ) &&
        ( pthread_mutex_lock( &( context.mutex ) ) == 0 ) )
    {
        for( int i = 0; i < METRIC_EVENT_MAX; i++ )
        {
            context.eventRecords[i].state = METRIC_EVENT_STATE_NONE;
            context.eventRecords[i].endTimeUs = 0;
            context.eventRecords[i].startTimeUs = 0;
        }
        pthread_mutex_unlock( &( context.mutex ) );
    }
}
