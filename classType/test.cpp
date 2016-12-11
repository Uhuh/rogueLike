#include "player.h"
#include <ncurses.h>
#include <iostream>
#include <unistd.h>
#include <cstring>
using namespace std;


int main()
{
  player a;
  char hi;
  cout << "Enter a letter: ";
  cin >> hi;
  a.setMe(hi);
  int x = 10, y = 10;
  initscr();
  start_color();
  // (red is the char color, black is background)
  init_pair(1,COLOR_RED, COLOR_BLACK);
  noecho();
  //cbreak();
  curs_set(FALSE);

  WINDOW *game_win;
  WINDOW *stats_win;
  //(100 x big, 90 y big, 0 for left top head, 0 head top y)
  game_win = newwin(100, 90, 0, 0);
  // same such
  stats_win = newwin(0, 0, 0, 90);
  while(true)
  {
    //Giving our guy color.
    wattron(game_win, COLOR_PAIR(1));
    //Outputting our guy
    mvwprintw(game_win, x,y, a.getMe().c_str());
    wrefresh(game_win);

    //Testing stats header! progress so far.
    mvwprintw(stats_win, 5, 0, "Me: %s", a.getMe().c_str());
    wrefresh(stats_win);
    wclear(stats_win);
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
