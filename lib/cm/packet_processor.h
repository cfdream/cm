#ifndef PACKET_PROCESSOR_H
#define PACKET_PROCESSOR_H

#include "dpif.h"
#include "measure_data_type.h"
#include "debug_output.h"
#include "loss_rate_map.h"
#include "sampled_map.h"

const uint32_t LOSS_PACKET_DIP = 167837954; //10.1.1.2
const uint16_t LOSS_PACKET_DPORT = 65535;   //65535

void process_normal_packet(packet_t* pkt_ptr);
void process_loss_rate_packet(packet_t* pkt_ptr);
void process(struct dpif_execute *execute);

void process(struct dpif_execute *execute){
    //out_port
    int out_port;
    //pkt_len, allocated_len
    uint32_t pkt_len;  //bytes in use
    uint32_t allocated_len;  //allocated
    //sip, dip
    char* l3_start;
    uint32_t srcip;
    uint32_t dstip;
    //sport, dport
    char* l4_start;
    uint16_t sport;
    uint16_t dport;
    uint16_t plen;  //payload len
    char* payload_ptr;
    //seqid 
    uint32_t seqid;

    flow_key_t flow_key;
    packet_t pkt;
    loss_payload_t loss_payload;

    //for debug
    char buffer[1000];
    
    out_port=*(int*)((char*)execute->actions+4)-1;
    //pkt_len, allocated_len
    pkt_len = execute->packet->size_;  //bytes in use
    allocated_len = execute->packet->allocated;  //allocated
    //sip, dip
    l3_start = ofpbuf_l3(execute->packet);
    srcip = ntohl(*(int*)(l3_start+12));
    dstip = ntohl(*(int*)(l3_start+16));
    //sport, dport
    l4_start = ofpbuf_l4(execute->packet); 
    sport = ntohs(*(uint16_t*)l4_start);
    dport = ntohs(*(uint16_t*)(l4_start+2));
    plen = ntohs(*(uint16_t*)(l4_start+4));  //payload len 

    snprintf(buffer, 1000, "sip:%u dip:%u sport:%u dport:%u payload_len:%u len_in_use:%u allo_len:%u out_port:%d", 
        srcip, dstip, sport, dport, plen, pkt_len, allocated_len, out_port);
    DEBUG(buffer);

    //data pointer, frame pointer
    payload_ptr = l4_start + 8;

    //flow key
    flow_key.srcip = srcip;
    //get the packet
    pkt.srcip = srcip;
    pkt.dstip = dstip;
    pkt.sport = sport;
    pkt.dport = dport;
    pkt.out_port = out_port;
    pkt.len = pkt_len;

    if (dstip == LOSS_PACKET_DIP && dport == LOSS_PACKET_DPORT) {
        DEBUG("loss packet");
        //construct loss rate packet
        //memcpy(&loss_payload, payload_ptr, sizeof(loss_payload));
        loss_payload = *((loss_payload_t*)payload_ptr);

        if (plen < sizeof(loss_payload)) {
             ERROR("error: payload size < sizeof(loss_payload_t)");
            return;
        }
        snprintf(buffer, 1000, "loss info: srcip:%u, lossRate:%f", loss_payload.srcip, loss_payload.loss_rate);
        DEBUG(buffer);
        //set loss rate of the pkt
        pkt.loss_rate = loss_payload.loss_rate;
        //handle loss packet
        process_loss_rate_packet(&pkt);
    } else {
        seqid = ntohl(*(uint32_t*)payload_ptr);
        snprintf(buffer, 1000, "normal packet, seqid:%u", seqid);
        DEBUG(buffer);
        //construct normal packet 
        process_normal_packet(&pkt);
    }
}

void process_normal_packet(packet_t* pkt_ptr) {
    //check whether the flow exist in the sampled_flow_map
    //if yes, accumulate the packet length
    //else, try to sample the flow: succeed, record, else discard
}

void process_loss_rate_packet(packet_t* pkt_ptr) {
    //record the loss rate information of the flow in loss_flow_map
}
#endif
