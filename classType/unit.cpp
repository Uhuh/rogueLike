#include "unit.h"
#include "map.h"
#include <iostream>


void unit::setHealth(int hp)
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

void unit::outStats(WINDOW *stats_win)
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

void unit::spawn(const map & area)
{
  do
  {
    m_x = (area.getRow()-(area.getRow()/2)/rand_int(2, 8));
    m_y = (area.getRow()-(area.getRow()/2)/rand_int(2, 8));
  }while(area.getxy(m_x, m_y) != '.');
  return;
}
