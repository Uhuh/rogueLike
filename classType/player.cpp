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

void player::outStats(WINDOW *stats_win)
{
  mvwprintw(stats_win, 1, 1, "Name: %s", getName().c_str());
  mvwprintw(stats_win, 2, 1, "Health: %i", getHealth());
  mvwprintw(stats_win, 3, 1, "Atk: %i", getAtk());
  mvwprintw(stats_win, 4, 1, "Def: %i", getDef());
  mvwprintw(stats_win, 5, 1, "Str: %i", getStr());

  wrefresh(stats_win);
  wclear(stats_win);

  return;
}
