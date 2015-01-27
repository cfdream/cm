#ifndef FIXED_SIZE_HASH_MAP_H
#define FIXED_SIZE_HASH_MAP_H

#include <pthread.h>
#include "measure_data_type.h"


/* sampled hashtable*/
const int SAMPLE_FIXED_SIZE = 1200007; //1.2 Mbytes
const int SAMPLE_LOCK_SIZE = 1000;     //lock size

struct sampled_flows_map_s {
    sampled_record_t sampled_flows[SAMPLE_FIXED_SIZE];
    pthread_mutex_t mutexs[SAMPLE_LOCK_SIZE];

}sampled_flow_map_t;

extern sampled_flow_map_t sampled_flow_map;

void initial_sampled_map();

int get_sampled_flow_index(flow_key_t flow_key);

void get_sampled_map_lock();

void release_sampled_map_lock();

uint64_t get_sampled_flow(flow_key_t flow_key);

void put_sampled_flows_map(flow_key_t flow_key, uint64_t volume);


#endif
