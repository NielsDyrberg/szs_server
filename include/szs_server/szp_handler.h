//
// Created by ncpd on 15-11-2021.
//

#ifndef SOUNDZONE_SERVER_LIB_SONG_HANDLER_H
#define SOUNDZONE_SERVER_LIB_SONG_HANDLER_H

#include <fstream>

#include "szp_master.h"

#define SONG_BUFF_SIZE 1028

class SZP_handler{
private:
    int number_of_slaves;
    char** slave_ips;
    SZP_master* slaves;
    FILE* song_fd;
    uint8_t* song_buffer;

    int load_song(char* song_path);
    int read_and_send_song();
    int read_and_send_song_packet();
    int setup();
    int add_slave(int slave_number, char* host, bool is_ip);

public:
    SZP_handler(int number_of_slaves, char** slaves_ips);
    int run();


};

#endif //SOUNDZONE_SERVER_LIB_SONG_HANDLER_H
