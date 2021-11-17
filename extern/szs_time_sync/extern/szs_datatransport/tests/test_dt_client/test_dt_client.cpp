//
// Created by ncpd on 05-11-2021.
//
#include <iostream>

#include "udp_server.h"

#define PORT 1695

[[noreturn]] void test_recv_random_data(){
    uint8_t * bufPTR = nullptr;
    uint16_t size = 0;
    UDP_server dt(PORT);
    uint8_t msg[] = {0x50, 0x6f, 0x6e, 0x67};

    while (true) {
        if (dt.receive(false) > 0) {
            bufPTR = dt.GetBuffer(bufPTR, &size);
            if (*bufPTR == 0x50) {
                dt.send(msg, sizeof(msg));
            }
            for (int i = 0; i < size; i++) {
                std::cout << unsigned(*bufPTR) << std::endl;
                bufPTR++;
            }
            std::cout << "data" << std::endl;
        } else{
            std::cout << "Client rerun" << std::endl;
        }
    }
}

int main(){
    test_recv_random_data();
    return 0;
}