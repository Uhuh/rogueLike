#include "map.h"
#include <iostream>

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

<<<<<<< HEAD
void map::outMap(WINDOW* game_win, const player& a, int row, int col)
=======
void map::outMap(WINDOW* game_win, const unit& a, int x, int y)
>>>>>>> 8e1a73b7822e458a3ce83dbc815d55e73747f91c
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
  mvwprintw(game_win, row, col, a.getMe().c_str());

  wrefresh(game_win);
  wclear(game_win);

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
  getxy(width+row-3, height+col) = '|';
  return;
}
