//
// Created by ncpd on 11-11-2021.
//

#ifndef SOUNDZONE_SERVER_SZS_SERVER_H
#define SOUNDZONE_SERVER_SZS_SERVER_H

#include "szs_server/szp_handler.h"
#include "szs_server/sync_handler.h"

//todo Update to 8 when ready
#define NUMBER_OF_SLAVES 1

class SZS_server{
private:
    SZP_handler* szp;
    SYNC_handler* sync;

    static void run_szp_handler(SZP_handler* szp_handler);
    static void run_sync_handler(SYNC_handler* sync_handler);

protected:
public:
    SZS_server();
    int run();

};

#endif //SOUNDZONE_SERVER_SZS_SERVER_H
