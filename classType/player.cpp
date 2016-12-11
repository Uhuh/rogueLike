#include "player.h"
#include <iostream>
using namespace std;

void player::setHealth(int hp)
{
  if(hp < 0)
  {
    cout << "Error, cannot set HP less than 0." << endl;

  }
  else
  {
    health = hp;
  }

  return;
}
