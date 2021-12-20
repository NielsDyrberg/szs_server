//
// Created by ncpd on 11-11-2021.
//
#include <iostream>
#include "szs_server.h"
#include "sync_handler.h"
#include <fstream>
#include <string>
#include "../extern/szs_time_sync/include/timeKeeper.h"

static char* slave_ips[] = {"192.168.0.103", nullptr, nullptr, nullptr,
                            nullptr, nullptr, nullptr, nullptr};
int port = 1696;
int NOS = 1;


int main(){


     sleep(2);
TimeKeeper T;
SYNC_handler sync(NOS, slave_ips);
sync.setup();
sync.reset_time();
T.resetTime();
    for(int i=0; i < 10;i++){
        T.resetTime();
        sync.synchronize();
        sleep(1); // adjust to match slave delay time (should be the same)
    }








    return 0;
}
