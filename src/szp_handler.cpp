//
// Created by ncpd on 15-11-2021.
//

#include "szs_server/szp_handler.h"

static char song[] = "/usr/local/music/epic_sax_guy.wav";

/**********************************************************************************************************************
 * Public methods
 **********************************************************************************************************************/

SZP_handler::SZP_handler(int number_of_slaves, char** slave_ips) {
    this->song_buffer = new uint8_t[SONG_BUFF_SIZE];
    this->song_fd = nullptr;
    this->number_of_slaves = number_of_slaves;
    this->slave_ips = slave_ips;
    this->slaves = new SZP_master[number_of_slaves];

    setup();
}

int SZP_handler::run() {
    int err;

    err = load_song(song);
    if(err < 0){
        std::cout << "Did not load song" << std::endl;
        return -1;
    }

    read_and_send_song();

    return 0;
}

/**********************************************************************************************************************
 * Private methods
 **********************************************************************************************************************/

int SZP_handler::load_song(char *song_path) {
    song_fd = fopen(song_path, "rb");
    if(song_fd == nullptr){
        std::cout << "Did not load song, [SZS_server, load_song(char *song_path)]" << std::endl;
        return -1;
    }

    return 0;
}

int SZP_handler::read_and_send_song() {
    unsigned int bytes_read = 0;
    int err = 0;

    while(err > -1){
        err = read_and_send_song_packet();
    }
    return 0;
}

int SZP_handler::read_and_send_song_packet() {
    unsigned int bytes_read = 0;

    bytes_read = fread(song_buffer, 1, SONG_BUFF_SIZE, song_fd);
    if (bytes_read > 0){
        for (int i = 0; i < number_of_slaves; i++) {
            slaves[i].send_sound_packet(song_buffer, bytes_read);
        }
    } else{
        fclose(song_fd);
        std::cout << "Song end, [szp_master, send_sound_packet()]" << std::endl;
        return -1;
    }
    return 0;
}

int SZP_handler::setup() {
    int err;

    for (int i = 0; i < number_of_slaves; i++) {
        err = add_slave(i ,slave_ips[i], true);
        if(err < 0){
            std::cout << "Slave " << i << " did not setup, [SZS_server, setup()]" << std::endl;
        }
    }
    return 0;
}


int SZP_handler::add_slave(int slave_number, char* host, bool is_ip) {
    if (slave_number >= number_of_slaves){
        std::cout << "There can only be 8 slaves, [SZS_server, add_slave(int slave_number, char* host, bool is_ip)]" << std::endl;
        return -1;
    }
    slaves[slave_number] = SZP_master(host, is_ip);
    //todo check successful with check_connection

    return 0;
}