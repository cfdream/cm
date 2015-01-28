#ifndef MEASURE_DATA_TYPE_H
#define MEASURE_DATA_TYPE_H

typedef struct flow_key_s {
    uint32_t srcip;
}flow_key_t;

typedef struct packet_s {
    uint32_t srcip;
    uint32_t dstip;
    uint16_t sport;
    uint16_t dport;
    uint16_t out_port;
    uint16_t len;
    double loss_rate;
}packet_t;

typedef struct info_packet_s {
    flow_key_t key;
    double loss_rate;
};

typedef struct sampled_volume_record_s {
    flow_key_t flow_key;
    uint64_t volume;
}sampled_record_t;

typedef struct loss_rate_record_s {
    flow_key_t flow_key;
    double loss_rate;
}loss_rate_record_t;

typedef struct loss_payload_s {
    uint32_t srcip;
    uint32_t dstip;
    uint16_t srcport;
    uint16_t dstport;
    double loss_rate;
}loss_payload_t;

#endif
