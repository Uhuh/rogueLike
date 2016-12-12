#include "player.h"
#include <ncurses.h>
#include <vector>
#include "map.h"
#include <iostream>
#include <unistd.h>
#include <cstring>

/* Currently working on the vector part of the program.
   Trying to make the vector the map we can interact with and
   then we're outputting it with ncurses.

   One issue where a dot appears in bottom right of map.

   Issue where x and y can't be different in the 'build' function.
   It will miss walls on the bottom or on the right depending if y or x is
   larger than the other.
*/


int main()
{
  player a, b;// a is us, b is monster.
  //going to be using a base class for both players and monster
  //just haven't changed class name.

  //constructor => map(width, height)
  //width = x, height = y
  map hi(20, 10);
  hi.build(hi.getWidth()-1, hi.getHeight()-1);


  // So the person starts in the middle of the map.
  int startx = hi.getWidth()/2, starty = hi.getHeight()/2;
  int x= startx, y = starty;

  std::string name;
  std::cout << "Speak your name friend and enter: ";
  std::getline(std::cin, name);
  a.setName(name);

  initscr();
  start_color();
  // (red is the char color, black is background)

  init_pair(1,COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_WHITE, COLOR_BLACK);
  noecho();
  curs_set(FALSE);

  WINDOW *game_win;
  WINDOW *stats_win;


  game_win = newwin(hi.getHeight(), hi.getWidth(), 0, 0);
  stats_win = newwin(10, 20, 0, 100);


  while(true)
  {

  // Make stats window pretty.
    wborder(stats_win, '|', '|', '=','=','*','*','*','*');

    //outputting the map to screen.
    hi.outMap(game_win, a, x, y);

    //outputting the players stats in another window.
    a.outStats(stats_win);




    if (getch() == '\033') { // if the first value is esc
      getch(); // skip the [
      switch(getch()) { // the real value
          case 'A':
              x--;
              // code for arrow up
              break;
          case 'B':
              x++;
              // code for arrow down
              break;
          case 'C':
              y++;
              // code for arrow right
              break;
          case 'D':
              y--;
              // code for arrow left
              break;
      }
    }
  }
  endwin();
  return 0;
}
