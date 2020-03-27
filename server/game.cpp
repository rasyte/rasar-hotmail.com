#include "manager.h"
#include "../common/common.h"

#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

const char* szWelcomeMsg = "Welcome to Clue-less, game starting soon";

void game(std::vector<pconnInfoT> vecPlayers)
{
    bool bWinner = false;
    std::ostream_iterator<int> out_it(std::cout, ", ");
    unsigned char  avatar[6] = { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };  // 0x00 - avatar is available, 0xFF avatar is not available

    std::cout << "[game] nbr of players: " << vecPlayers.size() << std::endl;

    std::vector<pconnInfoT>::iterator    iter = vecPlayers.begin();

    while(vecPlayers.end() != iter)
    {
        int fdClient = (*iter)->connfd; 
        msgT  msg;
            
        // build welcome message...
        std::cout << "[game] sending welcome message to player " << std::endl;
        msg.msgLen = (short)(3 + strlen(szWelcomeMsg));
        msg.chCode = CMD_GAME_BEGIN;
        strcpy(msg.szMsg, szWelcomeMsg);
            
        send(fdClient, (const char*)&msg, msg.msgLen, 0);           // sent welcome message

        // build avatar select message...
        std::cout << "[game] sending select message to player " << std::endl;
        std::cout << "[game] available avatars are: ";
        std::copy(avatar, avatar + NBR_SUSPECTS, out_it);
        std::cout << std::endl;
        msg.msgLen = 3 + NBR_SUSPECTS;
        msg.chCode = CMD_GAME_SELECT;
        memcpy(msg.szMsg, avatar, NBR_SUSPECTS);
        send(fdClient, (const char*)&msg, msg.msgLen, 0);           // send init message

        recv(fdClient, (char*)&msg, msg.msgLen, 0);                 // get response from the client
        memcpy(avatar, msg.szMsg, NBR_SUSPECTS);                    // update the avatar array
        std::cout << "[game] new list of avatars are: ";
        std::copy(avatar, avatar + NBR_SUSPECTS, out_it);
        std::cout << std::endl;
        ++iter;
    }

    // TODO : perform initialization
    int player = 0;                  // should be the person that choose Miss Scarlet

    while(!bWinner)
    {
        // run turn for first player....



        player = (player + 1) % vecPlayers.size();
    }
 
  
  


    // TODO : send game closing message
    // TODO : close all player sockets



    std::cout << "[game] bottom of game loop" << std::endl;
}
