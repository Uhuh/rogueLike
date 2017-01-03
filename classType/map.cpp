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


void map::setVis(int row, int col, bool vis)
{
  assert(row <= m_row && col <= m_col);
  isVis[row+col*m_row] = vis;
  isVis[row+1+col*m_row] = vis;
  isVis[row-1+col*m_row] = vis;
  isVis[row+(col+1)*m_row] = vis;
  isVis[row+(col-1)*m_row] = vis;
}


void map::outMap(WINDOW* game_win)
{
  // (Make this a function)
  // Coloring the map white on black.
  wattron(game_win, COLOR_PAIR(2));

  for(int i = 0; i < getRow(); i++)
  {
    for(int j = 0; j < getCol(); j++)
    {
      if(getVis(i, j))
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
  getxy(a.m_x, a.m_y) = a.getMe()[0];
  wrefresh(game_win);
  return;
}

bool map::monsterVision(unit& a, unit& b)
{
  for(int i = 1; i < 6; i++)
  {
    if(getxy(b.m_x+i, b.m_y) == a.getMe()[0])
    {
      return true;
    }
    else if (getxy(b.m_x, b.m_y+i) == a.getMe()[0])
    {
      return true;
    }
    else if (getxy(b.m_x-i, b.m_y) == a.getMe()[0])
    {
      return true;
    }
    else if (getxy(b.m_x, b.m_y-i) == a.getMe()[0])
    {
      return true;
    }
  }
  // If the for loops done, we haven't found the user. So false for we can't see him
  return false;
}

void map::moveMonster(unit & a,  unit & b)
{
  if(monsterVision(a, b))
  {
    if((b.m_x - a.m_x) >= 0 && (getxy(b.m_x-1, b.m_y) != '#'))
    {
      b.m_x -= 1;
      getxy(b.m_x + 1, b.m_y) = '.';
    }

    else if((b.m_x - a.m_x) <= 0 && (getxy(b.m_x+1, b.m_y) != '#'))
    {
      b.m_x += 1;
      getxy(b.m_x - 1, b.m_y) = '.';
    }

    else if((b.m_y - a.m_y) >= 0 && (getxy(b.m_x, b.m_y -1) != '#'))
    {
      b.m_y -= 1;
      getxy(b.m_x, b.m_y + 1) = '.';
    }

    else if((b.m_y - a.m_y) <= 0 && (getxy(b.m_x, b.m_y+1) != '#'))
    {
      b.m_y += 1;
      getxy(b.m_x, b.m_y-1) = '.';
    }
  }

  else
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
        if((getxy(b.m_x - 1, b.m_y) == '.'))
        {
          b.m_x-=1;
          getxy(b.m_x + 1, b.m_y) = '.';

        }
        break;
      case 2:

        if((getxy(b.m_x + 1, b.m_y) == '.'))
        {
          b.m_x+=1;
          getxy(b.m_x - 1, b.m_y) = '.';

        }

        break;
      case 3:

        if((getxy(b.m_x , b.m_y + 1) == '.'))
        {
          b.m_y+=1;
          getxy(b.m_x, b.m_y - 1) = '.';

        }
        break;
      case 4:

        if((getxy(b.m_x, b.m_y - 1) == '.'))
        {
          b.m_y-=1;
          getxy(b.m_x, b.m_y + 1) = '.';
        }
        break;
    }
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
    // Using this, if the monster is in the area that the user has found.
    if(getVis(b.m_x, b.m_y))
      mvwprintw(game_win, b.m_x, b.m_y, b.getMe().c_str());

    wrefresh(game_win);
  }

  return;
}


void map::buildRoom(const int row, const int col, const int m_row, const int m_col)
{
  assert(row + m_row <= getRow() && col + m_col <= getCol());
  assert(row >= 0 && col >= 0 && m_row > 0 && m_col > 0);
  bool test = false;
/*
  for(int i = 1; i < (getCol() - row); i++)
  {
    if(getxy(col, row + i) == '#' || getxy(col, row - i) == '#')
    {
      buildRoom(getRow()/rand_int(2, 8),
                getCol()/rand_int(2, 8),
                getRow()/rand_int(2, 8),
                getCol()/rand_int(2, 8));
      return;
    }
  }

  for(int i = 1; i < (getRow() - col); i++)
  {
    if(getxy(col + 1, row) == '#' || getxy(col - i, row) == '#')
    {
      buildRoom(getRow()/rand_int(2, 8),
                getCol()/rand_int(2, 8),
                getRow()/rand_int(2, 8),
                getCol()/rand_int(2, 8));
      return;
    }
  }*/

  for(int i = row; i <= m_row+row; i++)
  {
    getxy(i, col) = '#';
    getxy(i, m_col+col) = '#';
  }
  for(int i = col; i <= m_col+col; i++)
  {
    getxy(row, i) = '#';
    getxy(m_row+row, i) = '#';
  }

  getxy(m_row+row-3, m_col+col) = '.';
  return;
}
