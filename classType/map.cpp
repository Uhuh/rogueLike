#include "map.h"
#include <iostream>
#include <random>

// Function builds the great walls of trump
//lol

void map::build(int row, int col)
{
  for(int i = 0; i <= row; i++)
  {
    getxy(i, 0) = '#';
    getxy(i, col) = '#';
  }
  for(int i = 0; i <= col; i++)
  {
    getxy(0, i) = '#';
    getxy(row, i) = '#';
  }

  return;
}


void map::outMap(WINDOW* game_win)
{
  // (Make this a function)
  // Coloring the map white on black.
  wattron(game_win, COLOR_PAIR(2));

  for(int i = 0; i < getWidth(); i++)
  {
    for(int j = 0; j < getHeight(); j++)
    {
      mvwprintw(game_win, i,j, "%c", getxy(i, j));
    }
  }
  
  wrefresh(game_win);
 // wclear(game_win);

  return;
}

void map::outUser(WINDOW* game_win, const unit & a)
{
  wattron(game_win, COLOR_PAIR(1));
  //Outputting our guys symbol.
  mvwprintw(game_win, a.m_x, a.m_y, a.getMe().c_str());

  wrefresh(game_win);
 // wclear(game_win);
  return;
}

void map::moveMonster(unit & b)
{
  // Something that isn't rand()
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1, 4);

  // Picks a number from 1 to 4.
  switch(dis(gen))
  {
    case 1:
    // We need to stop the monster from leaving a trail.
    // So replace the last spot they were in with a dot (' . ')
      if((getxy( b.m_x - 1, b.m_y) == '.'))
      {
        b.m_x-=1;
        getxy(b.m_x + 1, b.m_y) = '.';
      }
      break;
    case 2:

      if((getxy( b.m_x + 1, b.m_y) == '.'))
      {
        b.m_x+=1;
        getxy(b.m_x - 1, b.m_y) = '.';
      }

      break;
    case 3:

      if((getxy( b.m_x , b.m_y + 1) == '.'))
      {
        b.m_y+=1;
        getxy(b.m_x, b.m_y - 1) = '.';
      }
      break;
    case 4:

      if((getxy( b.m_x, b.m_y - 1) == '.'))
      {
        b.m_y-=1;
        getxy(b.m_x, b.m_y + 1) = '.';
      }
      break;
  }

  return;
}




void map::placeMonster(WINDOW* game_win, const unit& b)
{
  /*
    Add checks to make sure we don't place in a wall or on the user, etc
  */

  if(getxy(b.m_x, b.m_y) != '#')
  {
    getxy(b.m_x, b.m_y) = b.getMe()[0];
    wattron(game_win, COLOR_PAIR(3));
    mvwprintw(game_win, b.m_x, b.m_y, b.getMe().c_str());
    wrefresh(game_win);
  }

	return;
}

void map::buildRoom(const int row, const int col, const int width, const int height)
{
  assert(row + width <= getWidth() && col + height <= getHeight());
  assert(row >= 0 && col >= 0 && width > 0 && height > 0);
  for(int i = row; i <= width+row; i++)
  {
    getxy(i, col) = '#';
    getxy(i, height+col) = '#';
  }
  for(int i = col; i <= height+col; i++)
  {
    getxy(row, i) = '#';
    getxy(width+row, i) = '#';
  }
  getxy(width+row-3, height+col) = '.';
  return;
}
