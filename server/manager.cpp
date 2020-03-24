#include "manager.h"

#include <vector>
#include <mutex>
#include <iostream>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>



#ifdef __WIN
#include <ctime>
#else
#include <sys/timerfd.h>
#include <unistd.h>
#endif


extern std::vector<pconnInfoT>  g_conns;
extern std::mutex               g_mutexQue;
extern bool                     g_bForce;
extern bool                     g_bMgrRun;
/*
This function provides the implementation of the manager.  This function does:
(1) periodically checks the size of the queue  
(2) starts a new game if it can
(3) monitors the state of `bForce` to force a game to start
*/
void manage()
{
    std::cout << "Manager thread alive and well" << std::endl;
    while (g_bMgrRun)
    {
        int ret;
        int fd = -1;
        struct itimerspec timeout;
        unsigned long long missed;

        fd = timerfd_create(CLOCK_MONOTONIC, 0);      // create a timer
        if (fd > 0)
        {
            ret = fcntl(fd, F_SETFL, O_NONBLOCK);
            if (!ret)
            {
                timeout.it_value.tv_sec = 5;            // 5 second time out
                timeout.it_value.tv_nsec = 0;
                timeout.it.interval.tv_sec = 5;         // recurring
                timeout.it.interval.tv_nsec = 0;

                ret = timerfd_settime(fd, 0, &timout, NULL);
                if (!ret)
                {
                    while (g_bMgrRun)
                    {
                        while (read(fd, &missed, sizeof(missed)) < 0)
                        {
                            prinf("no timer expiry\n");
                            sleep(1);
                        }
                    }

                }
                else
                {
                    fprintf(stderr, "falied to set timer duration, error is %d\n", errno);
                }

            }
            else
            {
                fprintf(stderr, "Failed to set to non-blocking mode, error: %d\n", errno);
            }

        }
        else
        {
            fprintf(stderr, "Failed to create timer, error is: %d\n", errno);
        }

        //tv.tv_sec = 5;            // set timeout for 5 sec
        //tv.tv_usec = 0;

        //FD_ZERO(&rdfs);
        //FD_SET(0, &rdfs);
        //FD_SET(sockfd, &rdfs);

        //ret = select(sockfd + 1, &rdfs, nullptr, nullptr, &tv);
    // TODO: set up a timer ....
    // TODO: when we break (~1 sec) check condition variable bForce
    // TODO: use a mutex to control access to queue
    // TODO: when we break (~1 sec) check queue size
	}


}

