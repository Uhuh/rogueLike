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


  // So the person starts in the middle of the map.
  int startx = hi.getWidth()/2, starty = hi.getHeight()/2;
  int x = startx, y = starty;

	a.m_x = startx;
	a.m_y = starty;

  std::string name;
  std::cout << "Speak your name friend and enter: ";
  std::getline(std::cin, name);
  a.setName(name);

  b.setName("Goblin");
  b.setMe('G');

	b.m_x = (hi.getWidth()-(hi.getWidth()/2)/rand_int(2, 8));
	b.m_y = (hi.getWidth()-(hi.getWidth()/2)/rand_int(2, 8));
  initscr();
  start_color();
  // (red is the char color, black is background)

  init_pair(1,COLOR_RED, COLOR_BLACK);
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

    //outputting the map to screen.
    hi.outMap(game_win, a);
		hi.placeMonster(game_win, b);
    //outputting the players stats in another window.
    a.outStats(stats_win);
    b.outStats(monster_win);


//    hi.moveMonster(b);


    if (getch() == '\033')
    { // if the first value is esc
      getch(); // skip the [
      switch(getch())
      { // the real value
          case 'A':
            if((hi.getxy(a.m_x - 1, a.m_y) == '.'))
              a.m_x-=1;
						else if((hi.getxy(a.m_x - 1, a.m_y) == b.getMe()[0]))
							b.setHealth(b.getHealth()-1);
							b.outStats(monster_win);
							if(b.getHealth() == 0)
								//endwin();
								return 0;
              // code for arrow up
            break;
          case 'B':
            if((hi.getxy( a.m_x + 1, a.m_y) == '.'))
              a.m_x+=1;
						else if((hi.getxy(a.m_x + 1, a.m_y) == b.getMe()[0]))
							b.setHealth(b.getHealth()-1);
							b.outStats(monster_win);
							if(b.getHealth() == 0)
								//endwin();
								return 0;
              // code for arrow down
            break;
          case 'C':
            if((hi.getxy( a.m_x , a.m_y + 1) == '.'))
              a.m_y+=1;
						else if((hi.getxy(a.m_x, a.m_y + 1) == b.getMe()[0]))
							b.setHealth(b.getHealth()-1);
							b.outStats(monster_win);
							if(b.getHealth() == 0)
								//endwin();
								return 0;
              // code for arrow right
            break;
          case 'D':
            if((hi.getxy( a.m_x, a.m_y - 1) == '.'))
              a.m_y-=1;
						else if((hi.getxy(a.m_x, a.m_y - 1) == b.getMe()[0]))
							b.setHealth(b.getHealth()-1);
							b.outStats(monster_win);
							if(b.getHealth() == 0)
								//endwin();
								return 0;
              // code for arrow left
            break;
      }
    }
  }
  endwin();
  return 0;
}
