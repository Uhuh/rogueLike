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
  init_pair(1,COLOR_RED, COLOR_BLACK);
  noecho();
  //cbreak();
  curs_set(FALSE);

  WINDOW *game_win;

  game_win = newwin(90, 90, 0, 0);

  while(true)
  {
    wattron(game_win, COLOR_PAIR(1));
    mvwprintw(game_win, x,y, a.getMe().c_str());
    wrefresh(game_win);
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
