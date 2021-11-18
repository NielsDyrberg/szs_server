//
// Created by ncpd on 15-11-2021.
//

#include "sync_handler.h"


SYNC_handler::SYNC_handler(int number_of_slaves, char** slaves_ips) {
    this->number_of_slaves = number_of_slaves;
    this->slave_ips = slaves_ips;
    this->slaves = new Sync_Master[number_of_slaves];
    setup();


}

void SYNC_handler::run() {

    reset_time();
    synchronize();
}



int SYNC_handler::setup() {
    int err;

    for (int i = 0; i < number_of_slaves; i++) {
        err = add_slave(i ,slave_ips[i], true);
        if(err < 0){
            std::cout << "Slave " << i << " did not setup, [SZS_server, setup()]" << std::endl;
        }
    }
    return 0;
}


int SYNC_handler::add_slave(int slave_number, char* host, bool is_ip) {
    if (slave_number >= number_of_slaves){
        std::cout << "There can only be 8 slaves, [SZS_server, add_slave(int slave_number, char* host, bool is_ip)]" << std::endl;
        return -1;
    }
    slaves[slave_number] = Sync_Master(host, is_ip);


    return 0;
}

void SYNC_handler::reset_time(){
    for (int i = 0; i < number_of_slaves; i++) {
        slaves[i].Reset_Time();
    }
}


int SYNC_handler::synchronize(){

    for (int i = 0; i < number_of_slaves; i++) {
        jump :
        slaves[i].SyncReq_and_accept();
        slaves[i].Send_TS23();
        if (!slaves[i].Wait_for_Sync_OK()){
            goto jump;
        }
        std::cout<<"Successful sync to client: "<< i+1 << std::endl;
    }
    return 0;
}