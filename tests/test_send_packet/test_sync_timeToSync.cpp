//
// Created by ncpd on 11-11-2021.
//
#include <iostream>
#include "szs_server.h"
#include "sync_handler.h"
#include <fstream>
#include <string>
#include "../extern/szs_time_sync/include/timeKeeper.h"

static char* slave_ips[] = {"192.168.0.103", "192.168.0.105", nullptr, nullptr,
                            nullptr, nullptr, nullptr, nullptr};
int port = 1696;
int nos = 2;


int main(){
    freopen("/home/pi/szs_server/testResultNoFilter.txt","w",stdout);
    long long  slut[100];
    long long runTIme ;
    sleep(2);
TimeKeeper T;
SYNC_handler sync(nos, slave_ips);
sync.setup();
sync.reset_time();
T.resetTime();
    for(int i=0; i < 100;i++){
        T.resetTime();
        sync.synchronize();
        slut[i] = T.getTime();
    }

    for(int i=0; i < 100;i++){
        std::cout<<slut[i]<<std::endl;
    }






    return 0;
}
