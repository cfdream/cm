#ifndef GLOBAL_OPERATION_H
#define GLOBAL_OPERATION_H 

#include <time.h>
#include <pthread.h>
#include "global_data.h"
#include "sampled_map.h"
#include "condition_map.h"
#include "controller_communicator.h"

pthread_mutex_t communicator_mutex = PTHREAD_MUTEX_INITIALIZER;

void init_cm(void);
void initial_buffers(void);
void check_switch_buffers(int ith_interval);


//TODO: add this function into main(); otherwise, call this function in packet_processor.h
void init_cm(void) {

    //init global_setting, packet_sampling_setting
    init_global_setting();
    init_packet_sampling_setting();

    //init sampled_buffers and condition_buffers
    initial_buffers();

    //init rand
    srand(time(NULL));
}

//init sampled_buffers and loss_buffers
void initial_buffers(void) {
    int i = 0;
    if (g_sampled_buffer_condition_buffer_initialized) {
        return;
    }
    sampled_buffers.idx = 0;
    condition_buffers.idx = 0;
    for (; i < 2;  i++) {
        initial_condition_flow_map(i);
        initial_sampled_map(i);
    }
    g_sampled_buffer_condition_buffer_initialized = true;
}

//switch the sampled_buffers and loss_buffers
void check_switch_buffers(int ith_interval) {
    pthread_t thread_id;
    if (ith_interval > g_current_interval) {
        //!!!ith_interval is a new interval
        if (pthread_mutex_trylock(&communicator_mutex) != 0) {
            //there are other threads handling the work
            return;
        }
        sampled_buffers.idx = 1 - sampled_buffers.idx;
        condition_buffers.idx = 1- condition_buffers.idx;

        //DONE: init a thread to send data to controller 
        if(pthread_create(&thread_id, NULL,  send_target_flows_to_controller, NULL) < 0) {
            ERROR("failed to create thread to controller_communicator");
        }

        //initialize the resting buffer for usage of next time
        initial_condition_flow_map(1 - condition_buffers.idx);
        initial_sampled_map(1 - sampled_buffers.idx);

        pthread_mutex_unlock(&communicator_mutex);
    } else if (ith_interval < g_current_interval) {
        ERROR("ith_interval < g_current_interval");
    }
}

#endif
