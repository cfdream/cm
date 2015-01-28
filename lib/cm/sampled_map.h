#ifndef FIXED_SIZE_HASH_MAP_H
#define FIXED_SIZE_HASH_MAP_H

#include <pthread.h>
#include "measure_data_type.h"
#include "common_lib.h"
#include "loss_rate_map.h"

/* sampled hashtable*/
#define SAMPLE_FIXED_SIZE 1200007 //1.2 Mbytes
#define SAMPLE_LOCK_SIZE 1000     //lock size

typedef struct sampled_flows_map_s {
    sampled_record_t sampled_flows[SAMPLE_FIXED_SIZE];
    pthread_mutex_t mutexs[SAMPLE_LOCK_SIZE];

}sampled_flow_map_t;

sampled_flow_map_t sampled_flow_map;

//initial sampled_map
void initial_sampled_map(void);
//get the index of the lock
int get_lock_index_sampled_map(flow_key_t flow_key);
//get the lock
void get_sampled_map_lock(flow_key_t flow_key);
//release the lock
void release_sampled_map_lock(flow_key_t flow_key);
//get the index of sampled flow
int get_sampled_flow_index(flow_key_t flow_key);
//get the volume of one flow
uint64_t get_sampled_flow(flow_key_t flow_key);
//put the flow sampled volume
void put_sampled_flows_map(flow_key_t flow_key, uint64_t volume);


//initial sampled_map
void initial_sampled_map(void) {
    int i;
    memset(sampled_flow_map.sampled_flows, 0, sizeof(sampled_flow_map.sampled_flows));
    for ( i = 0; i < SAMPLE_LOCK_SIZE; i++) {
        pthread_mutex_init(&sampled_flow_map.mutexs[i], NULL);
    }
}
//get the index of the lock
int get_lock_index_sampled_map(flow_key_t flow_key) {
    return flow_key.srcip % SAMPLE_FIXED_SIZE;
}
//get the lock
void get_sampled_map_lock(flow_key_t flow_key) {
    int idx = get_lock_index_sampled_map(flow_key);
    request_mutex(&sampled_flow_map.mutexs[idx]);
}
//release the lock
void release_sampled_map_lock(flow_key_t flow_key) {
    int idx = get_lock_index_sampled_map(flow_key);
    release_mutex(&sampled_flow_map.mutexs[idx]);
}
//get the index of sampled flow
int get_sampled_flow_index(flow_key_t flow_key) {
    return flow_key.srcip % SAMPLE_FIXED_SIZE;
}
//get the volume of one flow
uint64_t get_sampled_flow(flow_key_t flow_key) {
    int idx = 0;
    uint64_t volume = 0;

    //lock
    get_sampled_map_lock(flow_key);
    //get data
    idx = get_sampled_flow_index(flow_key);
    if (sampled_flow_map.sampled_flows[idx].flow_key.srcip == flow_key.srcip) {
        volume = sampled_flow_map.sampled_flows[idx].volume;
    }
    //unlock
    release_sampled_map_lock(flow_key);
    return volume;
}
//put the flow sampled volume
void put_sampled_flows_map(flow_key_t flow_key, uint64_t volume) {
    int idx = 0;
    //lock
    get_sampled_map_lock(flow_key);
    //put data
    idx = get_sampled_flow_index(flow_key);
    if (!OPEN_REPLACE_MECHANISM) {
        //no replace mechanism, write directly
        sampled_flow_map.sampled_flows[idx].flow_key = flow_key;
        sampled_flow_map.sampled_flows[idx].volume = volume;
    } else {
        //open replace mechanism
        sampled_record_t existing_flow = sampled_flow_map.sampled_flows[idx];

        if (existing_flow.flow_key.srcip
            && existing_flow.flow_key.srcip != flow_key.srcip) {
            WARNING("sampled_flow_map confilt happens");
            //get the loss rate of existing flow;
            double loss_rate = get_loss_rate(flow_key);
            if (loss_rate > TARGET_LOSS_RATE_THRESHOLD ) {
                //loss rate of existing flow meets the threshold, keep the existing flow
                return;
            }
            //loss rate of existing flow < threshold, overwrite the existing flow
            sampled_flow_map.sampled_flows[idx].flow_key = flow_key;
            sampled_flow_map.sampled_flows[idx].volume = volume;
        }

    }
    //unlock
    release_loss_flow_map_lock(flow_key);
}
#endif
