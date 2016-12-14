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
  hi.buildRoom(20, 13, 10, 15);
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
	
	b.m_x = rand()%(hi.getWidth()-(hi.getWidth()/2))+1;
	b.m_y = rand()%(hi.getHeight()-(hi.getHeight()/2))+1;
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





    if (getch() == '\033') { // if the first value is esc
      getch(); // skip the [
      switch(getch()) { // the real value
          case 'A':
            if(!(hi.getxy(x-1,y) == '#'))
              a.m_x-=1;
              // code for arrow up
            break;
          case 'B':
            if(!(hi.getxy(x+1,y) == '#'))
              a.m_x+=1;
              // code for arrow down
            break;
          case 'C':
            if(!(hi.getxy(x,y+1) == '#'))
              a.m_y+=1;
              // code for arrow right
            break;
          case 'D':
            if(!(hi.getxy(x, y-1) == '#'))
              a.m_y-=1;
              // code for arrow left
            break;
      }
    }
  }
  endwin();
  return 0;
}
