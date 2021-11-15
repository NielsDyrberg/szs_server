//
// Created by ncpd on 11-11-2021.
//

#include "szs_server.h"

static char* slave_ips[] = {"192.168.1.46", nullptr, nullptr, nullptr,
                            nullptr, nullptr, nullptr, nullptr};


static char song[] = "/usr/local/music/epic_sax_guy.wav";

/**********************************************************************************************************************
 * Public methods
 **********************************************************************************************************************/

SZS_server::SZS_server(){
    this->song_buffer = new uint8_t[SONG_BUFF_SIZE];
    this->comm_buffer = new uint8_t[COMM_BUFFER_SIZE];
    this->song_fd = nullptr;
    this->slaves = new SZP_master[NUMBER_OF_SLAVES];
    this->setup();

};

int SZS_server::run() {
    int err;

    err = load_song(song);
    if(err < 0){
        std::cout << "Did not load song" << std::endl;
        return -1;
    }
    // todo add multithreading, here it should begin sync

    read_and_send_song();
    return 0;
}


/**********************************************************************************************************************
 * Private methods
 **********************************************************************************************************************/

int SZS_server::setup() {
    int err;

    for (int i = 0; i < NUMBER_OF_SLAVES; i++) {
        err = add_slave(i ,slave_ips[i], true);
        if(err < 0){
            std::cout << "Slave " << i << " did not setup, [SZS_server, setup()]" << std::endl;
        }
    }
    return 0;
}


int SZS_server::add_slave(int slave_number, char* host, bool is_ip) {
    if (slave_number >= NUMBER_OF_SLAVES){
        std::cout << "There can only be 8 slaves, [SZS_server, add_slave(int slave_number, char* host, bool is_ip)]" << std::endl;
        return -1;
    }
    slaves[slave_number] = SZP_master(host, is_ip, comm_buffer, COMM_BUFFER_SIZE);

    return 0;
}


int SZS_server::load_song(char *song_path) {
    song_fd = fopen(song_path, "rb");
    if(song_fd == nullptr){
        std::cout << "Did not load song, [SZS_server, load_song(char *song_path)]" << std::endl;
        return -1;
    }

    return 0;
}

int SZS_server::read_and_send_song() {
    unsigned int bytes_read = 0;
    int err = 0;

    while(err > -1){
        err = read_and_send_song_packet();
    }
    return 0;
}

int SZS_server::read_and_send_song_packet() {
    unsigned int bytes_read = 0;

    bytes_read = fread(song_buffer, 1, SONG_BUFF_SIZE, song_fd);
    if (bytes_read > 0){
        for (int i = 0; i < NUMBER_OF_SLAVES; i++) {
            slaves[i].send_sound_packet(song_buffer, bytes_read);
        }
    } else{
        fclose(song_fd);
        std::cout << "Song end, [szp_master, send_sound_packet()]" << std::endl;
        return -1;
    }
    return 0;
}
