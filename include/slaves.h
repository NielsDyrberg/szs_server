//
// Created by ncpd on 11-11-2021.
//

#ifndef SOUNDZONE_SERVER_SLAVES_H
#define SOUNDZONE_SERVER_SLAVES_H

#include <cstdint>
#include "szp_master.h"


#define BUFFER_SIZE 1028;
//uint8_t comm_buffer[buffer_size] = {0};

class slaves {
private:
    static const uint16_t buffer_size = BUFFER_SIZE;
    uint8_t* comm_buffer;

protected:


public:
    SZP_master* slave_1;
    SZP_master* slave_2;
    SZP_master* slave_3;
    SZP_master* slave_4;
    SZP_master* slave_5;
    SZP_master* slave_6;
    SZP_master* slave_7;
    SZP_master* slave_8;

    slaves();
    // host, bool is_ip, uint8_t *comm_buffer, uint16_t buffer_size
    int add_slave(int slave_number, char* host, bool is_ip);
};

#endif //SOUNDZONE_SERVER_SLAVES_H
