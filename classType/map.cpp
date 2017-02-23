#include "map.h"
#include <iostream>
#include <random>

// Function builds the great walls of trump
//lol

void map::build(int row, int col)
{
  for(int i = 0; i <= row; i++)
  {
    //Setting the borders as seeable.
    isVis[i+0*m_row] = true;
    isVis[i+col*m_row] = true;

    getxy(i, 0) = '#';
    getxy(i, col) = '#';
  }
  for(int i = 0; i <= col; i++)
  {
    //setting the borders as seeable.
    isVis[0+i*m_row] = true;
    isVis[row+i*m_row] = true;

    getxy(0, i) = '#';
    getxy(row, i) = '#';
  }

  return;
}


void map::setVis(int row, int col, bool vis)
{
  assert(row <= m_row && col <= m_col);
  // Just like the vector being used to display the map
  // we want the visual vector to mirror it, in size
  // and how we show it, so like the getxy() funct.
  // we make this 1d vector into 2d.
  // row+col*m_row;
  isVis[row+col*m_row] = vis;
  isVis[row+1+col*m_row] = vis;
  isVis[row-1+col*m_row] = vis;
  isVis[row+(col+1)*m_row] = vis;
  isVis[row+(col-1)*m_row] = vis;
}


void map::outMap(WINDOW* game_win, const unit& a)
{
  // (Make this a function)
  // Coloring the map white on black.
  wattron(game_win, COLOR_PAIR(2));
  //setVis(a.m_x, a.m_y, true);

  for(int i = 0; i < getRow(); i++)
  {
    for(int j = 0; j < getCol(); j++)
    {
      if(getVis(i, j))
      {
        mvwprintw(game_win, i,j, "%c", getxy(i, j));
      }
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
  /*if(monsterVision(a, b))
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

  else*/
  {

    // Picks a number from 1 to 4.
    switch(rand_int(1, 4))
    {
      case 1:
        // We need to stop the monster from leaving a trail.
        // So replace the last spot they were in with a dot (' . ')
        if(getxy(b.m_x - 1, b.m_y) == '.')
        {
          b.m_x-=1;
          getxy(b.m_x + 1, b.m_y) = '.';

        }
        break;
      case 2:

        if(getxy(b.m_x + 1, b.m_y) == '.')
        {
          b.m_x+=1;
          getxy(b.m_x - 1, b.m_y) = '.';

        }

        break;
      case 3:

        if(getxy(b.m_x , b.m_y + 1) == '.')
        {
          b.m_y+=1;
          getxy(b.m_x, b.m_y - 1) = '.';

        }
        break;
      case 4:

        if(getxy(b.m_x, b.m_y - 1) == '.')
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


void map::buildRoom()
{
  // bRow means bottom row (bottom wall), and rCol means right collum, (right wall)
  //           (top)row
  //     _ _ _ _ _ _ _ _ _ _
//(left) | . . . . . . . . |(right) col
  //col  | . . . . . . . . |
  //     = = = = = = = = = =
  //          (Bottom)row
  int row = getRow()/rand_int(1, 6), bRow = getRow()/rand_int(1, 6);
  int col = getCol()/rand_int(2, 8), rCol = getCol()/rand_int(2, 8);


  for(int i = row; i <= bRow+row; i++)
  {
    getxy(i, col) = '#';
    getxy(i, rCol+col) = '#';
  }
  for(int i = col; i <= rCol+col; i++)
  {
    getxy(row, i) = '#';
    getxy(bRow+row, i) = '#';
  }

  getxy(bRow+row-3, rCol+col) = '.';
  return;
}
