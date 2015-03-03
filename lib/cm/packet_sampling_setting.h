#ifndef PACKET_SAMPLING_SETTING_H
#define PACKET_SAMPLING_SETTING_H

#include "global_setting.h"
#include "target_flow_setting.h"

//this function pointer is moved to sample_model.h, pls go there to modify it.
//bool (*get_pkt_sample_rate)(flow_key_t flow_key, packet_t* p_pkt) = &pkt_sample_rate_trad; //tradition

//interval information
const int OVER_SAMPLING_RATIO = 4;

//init every time
//value =  OVER_SAMPLING_RATIO / TARGET_VOLUME_THRESHOLD
double DEFAULT_BYTE_SAMPLE_RATE = 0;
//SH bucket size
//value = DEAFULT_BYTE_SAMPLE_RATE * VOLUME_IN_ONE_INTERVAL;
double SH_BUCKET_SIZE = 0;

void init_packet_sampling_setting(void);

void init_packet_sampling_setting(void) {
    DEFAULT_BYTE_SAMPLE_RATE =  1.0 * OVER_SAMPLING_RATIO / TARGET_VOLUME_THRESHOLD;

    SH_BUCKET_SIZE = DEFAULT_BYTE_SAMPLE_RATE * VOLUME_IN_ONE_INTERVAL;
}

#endif
