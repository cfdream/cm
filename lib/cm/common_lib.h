#ifndef COMMON_LIB_H
#define COMMON_LIB_H

#include <pthread.h>
#include "global_setting.h"


void request_mutex(pthread_mutex_t* p_mutex);
void release_mutex(pthread_mutex_t* p_mutex);
int get_interval_id(uint64_t timestamp);

void request_mutex(pthread_mutex_t* p_mutex) {
    if (OPEN_LOCK ) {
        pthread_mutex_lock(p_mutex);
    }
}

void release_mutex(pthread_mutex_t* p_mutex) {
    if (OPEN_LOCK) {
        pthread_mutex_unlock(p_mutex);
    }
}

int get_interval_id(uint64_t timestamp) {
    return (timestamp - FIRST_INTERVAL_START_USECOND) / USECONDS_IN_ONE_INTERVAL + 1;
}

#endif
