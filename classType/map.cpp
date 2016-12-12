#include "map.h"
#include <iostream>

// Function builds the great walls of trump
//lol

void map::build(int x, int y)
{
  for(int i = 0; i <= x; i++)
  {
    getxy(i, 0) = '#';
    getxy(i, y) = '#';
  }
  for(int i = 0; i <= y; i++)
  {
    getxy(0, i) = '#';
    getxy(x, i) = '#';
  }
  return;
}

void map::outMap(WINDOW* game_win, const player& a, int x, int y)
{
  // (Make this a function)
  // Coloring the map white on black.
  wattron(game_win, COLOR_PAIR(2));
  for(int i = 0; i < getWidth(); i++)
    for(int j = 0; j < getHeight(); j++)
      mvwprintw(game_win, i,j, "%c", getxy(i, j));

  // Making the little guy red.
  wattron(game_win, COLOR_PAIR(1));
  //Outputting our guys symbol.
  mvwprintw(game_win, x, y, a.getMe().c_str());

  wrefresh(game_win);
  wclear(game_win);

  return;
}
