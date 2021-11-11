//
// Created by ncpd on 11-11-2021.
//

#include "slaves.h"

#define NUMBER_OF_SLAVES 8

slaves::slaves() {
    comm_buffer = new uint8_t[buffer_size];
    slave_1 = nullptr;
    slave_2 = nullptr;
    slave_3 = nullptr;
    slave_4 = nullptr;
    slave_5 = nullptr;
    slave_6 = nullptr;
    slave_7 = nullptr;
    slave_8 = nullptr;
}

int slaves::add_slave(int slave_number, char* host, bool is_ip) {
    switch (slave_number) {
        case 1:
            slave_1 = new SZP_master(host, is_ip, comm_buffer, buffer_size);
            return 0;
        default:
            return -1;
    }
}