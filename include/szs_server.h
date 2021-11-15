//
// Created by ncpd on 11-11-2021.
//

#ifndef SOUNDZONE_SERVER_SZS_SERVER_H
#define SOUNDZONE_SERVER_SZS_SERVER_H

#include "szp_master.h"

#define COMM_BUFFER_SIZE 4096
#define SONG_BUFF_SIZE 1028

//todo Update to 8 when ready
#define NUMBER_OF_SLAVES 1

class SZS_server{
private:
    uint8_t* comm_buffer;
    FILE* song_fd;
    uint8_t* song_buffer;
    SZP_master* slaves;

    int setup();
    int add_slave(int slave_number, char* host, bool is_ip);
    int load_song(char* song_path);
    int read_and_send_song();
    int read_and_send_song_packet();

protected:
public:
    SZS_server();
    int run();

};

#endif //SOUNDZONE_SERVER_SZS_SERVER_H
