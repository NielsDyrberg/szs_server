//
// Created by ncpd on 11-11-2021.
//

#ifndef SOUNDZONE_SERVER_SZS_SERVER_H
#define SOUNDZONE_SERVER_SZS_SERVER_H

#include "szp_handler.h"
#include "sync_handler.h"

//todo Update to 8 when ready
#define NUMBER_OF_SLAVES 2

class SZS_server{
private:
    SZP_handler* szp;
    SYNC_handler* sync;

    /**
     * @brief Addeds a time delay to play_time
     * @param[in,out] play_time in - time_now, out - time_new + delay
     * @return 0
     */
    static int make_play_time(long long int *time_play);

protected:
public:
        SZS_server();
    int run();

};

#endif //SOUNDZONE_SERVER_SZS_SERVER_H
