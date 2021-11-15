//
// Created by ncpd on 11-11-2021.
//
#include <iostream>
#include "szs_server.h"

#define SZS_DEBUG

void test_send_sound_packet(){
    SZS_server server;

    server.run();

    std::cout << " " << std::endl;
}

int main(){
    test_send_sound_packet();
    return 0;
}
