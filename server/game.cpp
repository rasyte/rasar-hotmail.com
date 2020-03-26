#include "manager.h"

#include <vector>
#include <iostream>

void game(std::vector<pconnInfoT> vecPlayers)
{
  bool bWinner = false;

  std::cout << "[game] nbr of players: " << vecPlayers.size() << std::endl;

  std::vector<pconnInfoT>::iterator    iter = vecPlayers.begin();

  while(vecPlayers.end() != iter)
  {
    // TODO : sent welcome message
    // TODO : send init message
    
    ++iter;
  }

  // TODO : perform initialization
  int Player = 0;                  // should be the person that choose Miss Scarlet

  while(!bWinner)
  {
    // run turn for first player....



    player = (player + 1) % vecPlayers.size();
  }
 
  
  


  // TODO : send game closing message
  // TODO : close all player sockets



  std::cout << "[game] bottom of game loop" << std::endl;
}
