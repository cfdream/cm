#ifndef GLOBAL_SETTING_H
#define GLOBAL_SETTING_H

const bool OPEN_DEBUG = true;
const bool OPEN_NOTICE = true;
const bool OPEN_WARNING = true;
const bool OPEN_ERROR = true;

const bool OPEN_LOCK = false;

const bool OPEN_REPLACE_MECHANISM = true;

//target flow description
const double TARGET_LOSS_RATE_THRESHOLD = 0.2;      //target flow loss rate threshold: 0.2
const double TARGET_VOLUME_THRESHOLD = 20000;       //target flow volume threshold: 20k

//sampling algorithm
const double DEAFULT_BYTE_SAMPLE_RATE = 2e-4;             //loss rate v1
//this function pointer is moved to sample_model.h, pls go there to modify it.
//bool (*get_pkt_sample_rate)(flow_key_t flow_key, packet_t* p_pkt) = &pkt_sample_rate_trad; //tradition

//interval information
//about time interval
const uint64_t FIRST_INTERVAL_START_USECOND = 21600000000;
const uint64_t SECOND_2_USECOND = 1000000;
const int INTERVAL_SECONDS = 30;
const uint64_t USECONDS_IN_ONE_INTERVAL = 30000000;  //SECOND_2_USECOND * INTERVAL_SECONDS;

#endif
