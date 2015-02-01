#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

#include "sampled_map.h"
#include "condition_map.h"

bool g_sampled_buffer_condition_buffer_initialized = false;
int g_current_interval = 1;           //the present time interval, the starting interval is "1": should be sychonized with pcapGenerator

//socket information
int server_port = 8888;
char server_ip[20] = "10.1.0.254";


//rand() mod number
const int RAND_MOD_NUMBER = 1000000;


#endif
