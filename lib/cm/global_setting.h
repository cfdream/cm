#ifndef GLOBAL_SETTING_H
#define GLOBAL_SETTING_H

const bool OPEN_DEBUG = true;
const bool OPEN_NOTICE = true;
const bool OPEN_WARNING = true;
const bool OPEN_ERROR = true;

const bool OPEN_LOCK = true;

const bool OPEN_REPLACE_MECHANISM = true;

//target flow description
const double TARGET_LOSS_RATE_THRESHOLD = 0.2;      //target flow loss rate threshold: 0.2
const double TARGET_VOLUME_THRESHOLD = 20000;       //target flow volume threshold: 20k

//sampling algorithm
double DEAFULT_BYTE_SAMPLE_RATE = 2e-4;             //loss rate v1
//this function pointer is moved to sample_model.h, pls go there to modify it.
//bool (*get_pkt_sample_rate)(flow_key_t flow_key, packet_t* p_pkt) = &pkt_sample_rate_trad; //tradition

#endif
