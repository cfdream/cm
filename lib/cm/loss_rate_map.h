#ifndef LOSS_RATE_MAP_H
#define LOSS_RATE_MAP_H


#include <pthread.h>
#include "measure_data_type.h"

/*loss rate hashtable*/
//TODO: find some prime number here
const int LOSS_FIXED_SIZE = 12000007; //12 Mbytes
const int LOSS_LOCK_SIZE = 1000;     //lock size

struct loss_flows_map_s {
    loss_rate_record_s loss_flows[LOSS_FIXED_SIZE];
    pthread_mutex_t mutexs[LOSS_LOCK_SIZE];

}loss_flow_map_t;

extern loss_rate_map_t loss_rate_map;

void initial_loss_rate_map();

int get_loss_rate_flow_index(flow_key_t flow_key);

void get_loss_rate_map_lock();

void release_loss_rate_map_lock();

uint64_t get_loss_rate_flow(flow_key_t flow_key);

void put_loss_rate_flows_map(flow_key_t flow_key, uint64_t volume);

#endif
