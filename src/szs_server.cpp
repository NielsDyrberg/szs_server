//
// Created by ncpd on 11-11-2021.
//

#include <thread>

#include "szs_server.h"

static char* slave_ips[] = {"192.168.1.47", "192.168.1.48", nullptr, nullptr,
                            nullptr, nullptr, nullptr, nullptr};

static long long int delay_time = 15000000; // Wait 15 s

/**********************************************************************************************************************
 * Public methods
 **********************************************************************************************************************/

SZS_server::SZS_server(){
    szp = new SZP_handler(NUMBER_OF_SLAVES, slave_ips);
    sync = new SYNC_handler(NUMBER_OF_SLAVES, slave_ips);
};

int SZS_server::run() {
    int err = 0;
    long long int time_storage;

    sync->run();
    time_storage = sync->get_time();

    err = make_play_time(&time_storage);
    if(err < 0){
        exit(1);
    }
    szp->run(time_storage);

    return 0;
}


/**********************************************************************************************************************
 * Private methods
 **********************************************************************************************************************/

int SZS_server::make_play_time(long long int *time_play){
    if((long long int)(*time_play + delay_time) < 0){
        std::cout << "Error: Overflow will happen, [szs_server.cpp, make_play_time(long long int *time_play)]"
        << std::endl;
        return -1;
    }
    *time_play += delay_time;
    return 0;
}