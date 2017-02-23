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
  }while(area.getxy(m_x, m_y) == '#');
  return;
}



void unit::moveUser(WINDOW* game_win, WINDOW* monster_win, unit & monster, map &world)
{
  //read in user input for movement.
  const auto key = wgetch(game_win);
  switch(key)
  {
    case KEY_UP:
      if((world.getxy(m_x - 1, m_y) == '.'))
      {
        m_x-=1;
        world.getxy(m_x+1, m_y) = '.';
        world.getxy(m_x, m_y) = getMe()[0];

      }

      else if((world.getxy(m_x - 1, m_y) == monster.getMe()[0]))
      {
        monster.setHealth(monster.getHealth()-1);
        monster.outStats(monster_win);
      }

      if(monster.getHealth() == 0)
      {
        monster.setMe('.');
      }
      break;

    case KEY_DOWN:
      if((world.getxy(m_x + 1, m_y) == '.'))
      {
        m_x+=1;
        world.getxy(m_x-1, m_y) = '.';
        world.getxy(m_x, m_y) = getMe()[0];

      }

      else if((world.getxy(m_x + 1, m_y) == monster.getMe()[0]))
      {
        monster.setHealth(monster.getHealth()-1);
        monster.outStats(monster_win);
      }

      if(monster.getHealth() == 0)
      {
        monster.setMe('.');
      }

      break;

    case KEY_LEFT:
      if((world.getxy(m_x, m_y - 1) == '.'))
      {
        m_y-=1;
        world.getxy(m_x, m_y+1) = '.';
        world.getxy(m_x, m_y) = getMe()[0];

      }

      else if((world.getxy(m_x, m_y - 1) == monster.getMe()[0]))
      {
        monster.setHealth(monster.getHealth()-1);
        monster.outStats(monster_win);
      }

      if(monster.getHealth() == 0)
      {
        monster.setMe('.');
      }

      break;

    case KEY_RIGHT:
      if((world.getxy(m_x , m_y + 1) == '.'))
      {
        m_y+=1;
        world.getxy(m_x, m_y-1) = '.';
        world.getxy(m_x, m_y) = getMe()[0];


      }

      else if((world.getxy(m_x, m_y + 1) == monster.getMe()[0]))
      {
        monster.setHealth(monster.getHealth()-1);
        monster.outStats(monster_win);
      }

      if(monster.getHealth() == 0)
      {
        monster.setMe('.');
      }

      break;
  }
  return;
}
