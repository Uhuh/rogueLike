#include "unit.h"
#include <ncurses.h>
#include <vector>
#include "map.h"
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <cstdlib>

/* Currently working on the vector part of the program.
   Trying to make the vector the map we can interact with and
   then we're outputting it with ncurses.

   *Fixed the dot in the right hand corner.

   *Fixed the walls, x and y can now be bigger than one another and build the walls fine.

*/


int main()
{
  srand(time(NULL));

  unit a, b;// a is us, b is monster.
  //going to be using a base class for both players and monster
  //just haven't changed class name.

  //constructor => map(width, height)
  //int 1 = row, int 2 = col
  map hi(40, 60);
  hi.build(hi.getWidth()-1, hi.getHeight()-1);

  //Check the rand.cpp for how this is made.
  // Trying out how to make the room by random.
  hi.buildRoom(hi.getWidth()/rand_int(2, 8), hi.getHeight()/rand_int(2, 8),
               hi.getWidth()/rand_int(2, 8), hi.getHeight()/rand_int(2, 8));


  // Random location for setting character. Make it a funct and check if spawn is on wall.
  int startx = hi.getWidth()/rand_int(2, 6), starty = hi.getHeight()/rand_int(2, 6);
  int x = startx, y = starty;
  a.setMe('@');
  a.m_x = startx;
  a.m_y = starty;

  std::string name;
  std::cout << "Speak your name friend and enter: ";
  std::getline(std::cin, name);
  a.setName(name);

  b.setName("Goblin");
  b.setMe('G');

  // Setting the monsters location is a work in progress.
  /*b.m_x = (hi.getWidth()-(hi.getWidth()/2)/rand_int(2, 8));
  b.m_y = (hi.getWidth()-(hi.getWidth()/2)/rand_int(2, 8));
*/
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

  game_win = newwin(hi.getWidth(), hi.getHeight(), 0, 0);
  stats_win = newwin(10, 20, 0, hi.getHeight()+5);
  monster_win = newwin(10, 20, 30, hi.getHeight()+5);

  while(true)
  {

  // Make stats window pretty.
    wborder(stats_win, '|', '|', '=','=','*','*','*','*');
    wborder(monster_win, '|', '|', '=','=','*','*','*','*');

    //Our guy can see wherever he has gone.""
    hi.setVis(a.m_x, a.m_y, true);

    //outputting the map to screen.
    hi.outMap(game_win);
    hi.placeMonster(game_win, b);
    hi.outUser(game_win, a);
    hi.moveMonster(a, b);
    //outputting the players stats in another window.
    a.outStats(stats_win);
    b.outStats(monster_win);

    if (getch() == '\033')
    { // if the first value is esc
      getch(); // skip the [
      switch(getch())
      {
        case 'A':

          if((hi.getxy(a.m_x - 1, a.m_y) == '.'))
          {
            a.m_x-=1;
            hi.getxy(a.m_x+1, a.m_y) = '.';
          }

          else if((hi.getxy(a.m_x - 1, a.m_y) == b.getMe()[0]))
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

          if((hi.getxy( a.m_x + 1, a.m_y) == '.'))
          {
            a.m_x+=1;
            hi.getxy(a.m_x-1, a.m_y) = '.';

          }

          else if((hi.getxy(a.m_x + 1, a.m_y) == b.getMe()[0]))
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

          if((hi.getxy( a.m_x , a.m_y + 1) == '.'))
          {
            a.m_y+=1;
            hi.getxy(a.m_x, a.m_y-1) = '.';

          }

          else if((hi.getxy(a.m_x, a.m_y + 1) == b.getMe()[0]))
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

          if((hi.getxy( a.m_x, a.m_y - 1) == '.'))
          {
            a.m_y-=1;
            hi.getxy(a.m_x, a.m_y+1) = '.';

          }

          else if((hi.getxy(a.m_x, a.m_y - 1) == b.getMe()[0]))
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
