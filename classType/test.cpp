#include "unit.h"
#include <ncurses.h>
#include <vector>
#include "map.h"
#include <iostream>
#include <unistd.h>
#include <cstring>


int main()
{
  unit a, b;// a is us, b is monster.
  //going to be using a base class for both players and monster
  //just haven't changed class name.

  //constructor => map(rows, cols)
  //int 1 = row, int 2 = col
  map world(40, 60);
  world.build(world.getRow()-1, world.getCol()-1);

  //Check the rand.cpp for how this is made.
  // Trying out how to make the room by random.
  world.buildRoom(world.getRow()/rand_int(2, 8),
                  world.getCol()/rand_int(2, 8),
                  world.getRow()/rand_int(2, 8),
                  world.getCol()/rand_int(2, 8));

  world.buildRoom(world.getRow()/rand_int(2, 8),
                  world.getCol()/rand_int(2, 8),
                  world.getRow()/rand_int(2, 8),
                  world.getCol()/rand_int(2, 8));



  a.spawn(world);
  //Using x,y to update ncurses window.
  int x = a.m_x, y = a.m_y;
  a.setMe('@');

  std::string name;
  std::cout << "Speak your name friend and enter: ";
  std::getline(std::cin, name);
  a.setName(name);

  b.setName("Goblin");
  b.setMe('G');
  b.spawn(world);

  initscr();
  start_color();
  // Using red for the users char, green for the monster
  // and white to make the map white.

  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_WHITE, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);

  noecho();
  curs_set(FALSE);

  WINDOW *game_win;
  WINDOW *stats_win;
  WINDOW *monster_win;

  game_win = newwin(world.getRow(), world.getCol(), 0, 0);
  stats_win = newwin(10, 20, 0, world.getCol()+5);
  monster_win = newwin(10, 20, 30, world.getCol()+5);

  while(true)
  {

  // Make stats window pretty.
    wborder(stats_win, '|', '|', '=','=','*','*','*','*');
    wborder(monster_win, '|', '|', '=','=','*','*','*','*');

    //Our guy can see wherever he has gone.""
    world.setVis(a.m_x, a.m_y, true);

    //outputting the map to screen.
    world.outMap(game_win);
    world.placeMonster(game_win, b);
    world.outUser(game_win, a);
    world.moveMonster(a, b);
    //outputting the players stats in another window.
    a.outStats(stats_win);
    b.outStats(monster_win);

    if (getch() == '\033')
    { // if the first value is esc
      getch(); // skip the [
      switch(getch())
      {
        case 'A':

          if((world.getxy(a.m_x - 1, a.m_y) == '.'))
          {
            a.m_x-=1;
            world.getxy(a.m_x+1, a.m_y) = '.';
          }

          else if((world.getxy(a.m_x - 1, a.m_y) == b.getMe()[0]))
          {
            b.setHealth(b.getHealth()-1);
            b.outStats(monster_win);
          }

          if(b.getHealth() == 0)
          {
            b.setMe('.');
          }

          break;

        case 'B':

          if((world.getxy( a.m_x + 1, a.m_y) == '.'))
          {
            a.m_x+=1;
            world.getxy(a.m_x-1, a.m_y) = '.';

          }

          else if((world.getxy(a.m_x + 1, a.m_y) == b.getMe()[0]))
          {
            b.setHealth(b.getHealth()-1);
            b.outStats(monster_win);
          }

          if(b.getHealth() == 0)
          {
            b.setMe('.');
          }

          break;

        case 'C':

          if((world.getxy( a.m_x , a.m_y + 1) == '.'))
          {
            a.m_y+=1;
            world.getxy(a.m_x, a.m_y-1) = '.';

          }

          else if((world.getxy(a.m_x, a.m_y + 1) == b.getMe()[0]))
          {
            b.setHealth(b.getHealth()-1);
            b.outStats(monster_win);
          }

          if(b.getHealth() == 0)
          {
            b.setMe('.');
          }

          break;

        case 'D':

          if((world.getxy( a.m_x, a.m_y - 1) == '.'))
          {
            a.m_y-=1;
            world.getxy(a.m_x, a.m_y+1) = '.';

          }

          else if((world.getxy(a.m_x, a.m_y - 1) == b.getMe()[0]))
          {
            b.setHealth(b.getHealth()-1);
            b.outStats(monster_win);
          }

          if(b.getHealth() == 0)
          {
            b.setMe('.');
          }

          break;
      }
    }
  }

  endwin();
  return 0;
}
