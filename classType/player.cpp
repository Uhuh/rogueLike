#include "player.h"
#include <iostream>

void player::setHealth(int hp)
{
  if(hp < 0)
  {
    std::cout << "Error, cannot set HP less than 0." << std::endl;

  }
  else
  {
    health = hp;
  }

  return;
}
