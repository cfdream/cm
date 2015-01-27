#ifndef SAMPLE_MODEL_H
#define SAMPLE_MODEL_H

#include "measure_data_type.h"

//traditional sample and hold
bool is_sampled_trad(packet_t &pkt);

//linear adjusting
bool is_sampled_linear(packet_t &pkt);

//exponential adjusting 
bool is_sampled_exp(packet_t &pkt);

//log 
bool is_sampled_log(packet_t &pkt);

//polynominal
bool is_sampled_pol(packet_t &pkt);


#endif
