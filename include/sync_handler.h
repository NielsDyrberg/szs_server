//
// Created by ncpd on 15-11-2021.
//

#ifndef SOUNDZONE_SERVER_LIB_SYNC_HANDLER_H
#define SOUNDZONE_SERVER_LIB_SYNC_HANDLER_H


#include "../extern/szs_time_sync/include/syncMaster.h"


class SYNC_handler{
private:
    int number_of_slaves;
    char** slave_ips;
    Sync_Master* slaves;


public:
    SYNC_handler(int number_of_slaves, char** slaves_ips);
    void run();
    int setup();
    int add_slave(int slave_number, char* host, bool is_ip);
    void reset_time();
    int synchronize();
    long long int get_time();
};

#endif //SOUNDZONE_SERVER_LIB_SYNC_HANDLER_H
