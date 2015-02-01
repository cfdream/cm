#ifndef MEASURE_DATA_TYPE_H
#define MEASURE_DATA_TYPE_H

#define PORT_SIZE 5

typedef struct flow_key_s {
    uint32_t srcip;
}flow_key_t;

typedef struct condition_s {
    double loss_rate;
    uint64_t volume;    //TODO:detectPacketLoss should also send the volume to switches
}condition_t;

typedef struct packet_s {
    uint32_t srcip;
    uint32_t dstip;
    uint16_t sport;
    uint16_t dport;
    uint16_t out_port;
    uint16_t len;
    condition_t condition;
    int ith_interval;   //TODO genereate ith_interval at pcap_generator, and parse here
}packet_t;
/*
typedef struct info_packet_s {
    flow_key_t key;
    double loss_rate;
};
*/

typedef struct sampled_volume_record_s {
    flow_key_t flow_key;
    uint64_t port_volumes[PORT_SIZE];      //attention: at most 5 outports for one ovs
}sampled_record_t;

typedef struct condition_record_s {
    flow_key_t flow_key;
    condition_t condition;
}condition_record_t;

typedef struct condition_payload_s {
    uint32_t srcip;
    uint32_t dstip;
    uint16_t srcport;
    uint16_t dstport;
    double loss_rate;
    uint64_t volume;    //TODO add total volume of one flow from detect_loss
}condition_payload_t;

#endif
