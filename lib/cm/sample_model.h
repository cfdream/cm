#ifndef SAMPLE_MODEL_H
#define SAMPLE_MODEL_H

#include "global_setting.h"
#include "measure_data_type.h"


//traditional sample and hold
double pkt_sample_rate_trad(flow_key_t flow_key, packet_t* p_pkt);
/*
//linear adjusting
double pkt_sample_rate_linear(flow_key_t flow_key, packet_t* p_pkt);
//exponential adjusting 
double pkt_sample_rate_exp(flow_key_t flow_key, packet_t* p_pkt);
//log 
double pkt_sample_rate_log(flow_key_t flow_key, packet_t* p_pkt);
//polynominal
double pkt_sample_rate_pol(flow_key_t flow_key, packet_t* p_pkt);
*/

/*function pointer to get the right byte sampling model*/
bool (*get_pkt_sample_rate)(flow_key_t flow_key, packet_t* p_pkt) = &pkt_sample_rate_trad; //tradition


//traditional sample and hold
double pkt_sample_rate_trad(flow_key_t flow_key, packet_t* p_pkt) {
    double rate = DEAFULT_BYTE_SAMPLE_RATE * p_pkt->len;            
    return rate > 1 ? 1 : rate;
}
/*
//linear adjusting
double pkt_sample_rate_linear(flow_key_t flow_key, packet_t* p_pkt) {
    return 1;    
}

//exponential adjusting 
double pkt_sample_rate_exp(flow_key_t flow_key, packet_t* p_pkt) {
    return 1;    
}

//log 
double pkt_sample_rate_log(flow_key_t flow_key, packet_t* p_pkt) {
    return 1;    
}

//polynominal
double pkt_sample_rate_pol(flow_key_t flow_key, packet_t* p_pkt) {
    return 1;    
}
*/

#endif
