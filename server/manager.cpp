#include "manager.h"

#include <vector>
#include <iostream>


extern std::vector<pconnInfoT>  g_conns;
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

