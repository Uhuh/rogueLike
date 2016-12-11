#include "player.h"
#include <ncurses.h>
#include <iostream>
#include <unistd.h>
#include <cstring>

int main()
{
  player a, b;// a is us, b is monster.
  //going to be using a base class for both players and monster
  //just haven't changed class name.
	std::string name;
	std::cout << "Speak your name friend and enter: ";
	std::getline(std::cin, name);
	a.setName(name);
  int x = 10, y = 10;
  initscr();
  start_color();
  // (red is the char color, black is background)
  init_pair(1,COLOR_RED, COLOR_BLACK);
  noecho();
  curs_set(FALSE);

  WINDOW *game_win;
  WINDOW *stats_win;
  //(100 x big, 90 y big, 0 for left top head, 0 head top y)
  game_win = newwin(50, 90, 0, 0);
  // same such
  stats_win = newwin(10, 20, 0, 100);
  while(true)
  {
    wborder(game_win, '|', '|', '-','-','+','+','+','+');
    wborder(stats_win, '|', '|', '=','=','*','*','*','*');

    //Giving our guy color.
    wattron(game_win, COLOR_PAIR(1));
    //Outputting our guy
    mvwprintw(game_win, x,y, a.getMe().c_str());
    wrefresh(game_win);

    //Testing stats header! progress so far.
    a.outStats(stats_win);
    wclear(game_win);
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
