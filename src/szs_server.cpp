//
// Created by ncpd on 11-11-2021.
//

#include <thread>

#include "szs_server.h"

static char* slave_ips[] = {"192.168.0.103", nullptr, nullptr, nullptr,
                            nullptr, nullptr, nullptr, nullptr};

/**********************************************************************************************************************
 * Public methods
 **********************************************************************************************************************/

SZS_server::SZS_server(){
    szp = new SZP_handler(NUMBER_OF_SLAVES, slave_ips);
    sync = new SYNC_handler(NUMBER_OF_SLAVES, slave_ips);
};

int SZS_server::run() {

    sync->run();
    szp->run();

    return 0;
}


/**********************************************************************************************************************
 * Private methods
 **********************************************************************************************************************/

