#ifndef CONTROLLER_COMMUNICATOR_H
#define CONTROLLER_COMMUNICATOR_H

#include "sampled_map.h"
#include "condition_map.h"
#include "tcp_socket_client.h"

void* send_target_flows_to_controller(void* param);

void* send_target_flows_to_controller(void* param) {
    int i = 0;
    condition_t condition;
    sampled_flow_map_t* p_sampled_flow_map = NULL;

    DEBUG("start send_target_flows_to_controller");
    /*init the socket*/
    init_socket_client();

    //check the buffer just switched out
    p_sampled_flow_map = &sampled_buffers.sampled_flow_map[1-sampled_buffers.idx];

    //check every sample flow, and send to the controller if it meets the conditons 
    for (; i < SAMPLE_FIXED_SIZE; i++) {
        //get the sampled_record 
        sampled_record_t* p_sampled_record =  &p_sampled_flow_map->sampled_flows[i];
        flow_key_t flow_key = p_sampled_record->flow_key;
        
        //get loss rate of the flow 
        condition = get_condition(flow_key);

        //if 1. loss rate is smaller than target_loss_rate, 
        //or 2. the total sampled volume for the flow is lower than the threshold
        if (condition.loss_rate < TARGET_LOSS_RATE_THRESHOLD) {
            continue;
        }
        if (condition.volume < TARGET_VOLUME_THRESHOLD) {
            continue;
        }

        /*write data to the controller*/
        write_data_to_server((void*) p_sampled_record, sizeof(sampled_record_t));
    }

    /*close the socket*/
    close_socket();
    DEBUG("end send_target_flows_to_controller");
    return NULL;
}

#endif
