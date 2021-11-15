//
// Created by ncpd on 11-11-2021.
//

#include <thread>

#include "szs_server.h"

static char* slave_ips[] = {"192.168.1.46", nullptr, nullptr, nullptr,
                            nullptr, nullptr, nullptr, nullptr};

/**********************************************************************************************************************
 * Public methods
 **********************************************************************************************************************/

SZS_server::SZS_server(){
    szp = new SZP_handler(NUMBER_OF_SLAVES, slave_ips);
    sync = new SYNC_handler();
};

int SZS_server::run() {

    std::thread t_szp(&SZS_server::run_szp_handler, szp);
    std::thread t_alsa(&SZS_server::run_sync_handler, sync);

    t_szp.join();
    t_alsa.join();

    return 0;
}


/**********************************************************************************************************************
 * Private methods
 **********************************************************************************************************************/

void SZS_server::run_szp_handler(SZP_handler* szp_handler) {
    szp_handler->run();
}

void SZS_server::run_sync_handler(SYNC_handler* sync_handler){
    sync_handler->run();
}
