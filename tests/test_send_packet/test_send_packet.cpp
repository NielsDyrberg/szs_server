//
// Created by ncpd on 11-11-2021.
//
#include <iostream>
#include "szs_server.h"

char slave_1_Ip[] = "192.168.0.103";

uint8_t msg[] = {3,12,42,3,43,25,23,235,21,162,113,64,0,111};

void test_send_sound_packet(){
    SZS_server server;
    server.sl.add_slave(1 ,slave_1_Ip, true);
    server.sl.slave_1->send_sound_packet(msg, sizeof(msg));
    std::cout << " " << std::endl;
}

int main(){
    test_send_sound_packet();
    return 0;
}
