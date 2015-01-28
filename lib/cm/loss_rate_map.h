#ifndef LOSS_RATE_MAP_H
#define LOSS_RATE_MAP_H


#include <pthread.h>
#include "measure_data_type.h"
#include "debug_output.h"
#include "common_lib.h"

/*loss flow hashtable*/
//TODO: find some prime number here
#define LOSS_FIXED_SIZE 12000007 //12 Mbytes
#define LOSS_LOCK_SIZE 1000     //lock size

typedef struct loss_flows_map_s {
    loss_rate_record_t loss_flows[LOSS_FIXED_SIZE];
    pthread_mutex_t mutexs[LOSS_LOCK_SIZE];

}loss_flow_map_t;

loss_flow_map_t loss_flow_map;

/*function defintion*/
//initial the mutexs in loss_flow_map
void initial_loss_flow_map(void);
//get index of lock
int get_lock_index_loss_flow_map(flow_key_t flow_key);
//get lock
void get_loss_flow_map_lock(flow_key_t flow_key);
//release lock
void release_loss_flow_map_lock(flow_key_t flow_key);
//get the loss_flow index of one flow
int get_index_in_loss_flow_map(flow_key_t flow_key);
//get loss rate of one flow 
double get_loss_rate(flow_key_t flow_key);
//put loss rate
void put_loss_rate(flow_key_t flow_key, double loss_rate);

//initial the mutexs in loss_flow_map
void initial_loss_flow_map(void) {
    int i = 0;
    memset(loss_flow_map.loss_flows, 0, sizeof(loss_flow_map.loss_flows));
    for (; i < LOSS_LOCK_SIZE; i++) {
        pthread_mutex_init(&loss_flow_map.mutexs[i], NULL);
    }
}

/*function declarision*/
//get index of the lock
int get_lock_index_loss_flow_map(flow_key_t flow_key) {
    return flow_key.srcip % LOSS_LOCK_SIZE;
}
//get lock
void get_loss_flow_map_lock(flow_key_t flow_key) {
    int idx = get_lock_index_loss_flow_map(flow_key);
    request_mutex(&loss_flow_map.mutexs[idx]);
}
//release lock
void release_loss_flow_map_lock(flow_key_t flow_key) {
    int idx = get_lock_index_loss_flow_map(flow_key);
    release_mutex(&loss_flow_map.mutexs[idx]);
}
//get the loss_flow index of one flow
int get_index_in_loss_flow_map(flow_key_t flow_key) {
    return flow_key.srcip % LOSS_FIXED_SIZE;
}
//get loss rate of one flow 
double get_loss_rate(flow_key_t flow_key) {
    //if no loss rate data, return loss_rate=0
    int loss_rate = 0;
    int idx;
    //lock
    get_loss_flow_map_lock(flow_key);
    //get data
    idx = get_index_in_loss_flow_map(flow_key);
    if (loss_flow_map.loss_flows[idx].flow_key.srcip == flow_key.srcip) {
        //the flow exists 
        loss_rate = loss_flow_map.loss_flows[idx].loss_rate;
    }
    //unlock
    release_loss_flow_map_lock(flow_key);
    return loss_rate;
}
//put loss rate
void put_loss_rate(flow_key_t flow_key, double loss_rate) {
    int idx = 0;
    //lock
    get_loss_flow_map_lock(flow_key);
    //put data
    idx = get_index_in_loss_flow_map(flow_key);
    if (loss_flow_map.loss_flows[idx].flow_key.srcip
        && loss_flow_map.loss_flows[idx].flow_key.srcip != flow_key.srcip) {
        WARNING("loss_flow_map confilt happens");
    }
    loss_flow_map.loss_flows[idx].flow_key = flow_key;
    loss_flow_map.loss_flows[idx].loss_rate = loss_rate;
    //unlock
    release_loss_flow_map_lock(flow_key);
}
#endif
