#include "unit/unit.h"
#include <ncurses.h>
#include <vector>
#include "map/map.h"
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

  world.buildRoom();
  world.buildRoom();
  //world.build(world.getRow()-1, world.getCol()-1);

 // world.buildRoom();
//  world.buildRoom();
  a.spawn(world);

  //Using x,y to update ncurses window.
  a.setMe('@');


  std::string name;
  std::cout << "Enter name: ";
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
  monster_win = newwin(10, 20, world.getRow()-10, world.getCol()+5);
  keypad(game_win, TRUE);

  while(true)
  {
  // Make stats window pretty.
  //Annoyingly have to call the wborder functions for the functions to even appear.
  // >:()

    wborder(stats_win, '|', '|', '=','=','*','*','*','*');
    wborder(monster_win, '|', '|', '=','=','*','*','*','*');
    a.outStats(stats_win);
    b.outStats(monster_win);

    //outputting the map to screen.
    world.outMap(game_win, a);
    world.outUser(game_win, a);
    world.placeMonster(game_win, b);
    a.moveUser(game_win, monster_win, b, world);
    world.setVis(a.m_x, a.m_y, false);
    world.moveMonster(a, b);
  }

  endwin();
  return 0;
}
