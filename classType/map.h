#ifndef MAP_H
#define MAP_H
#include "unit.h"
#include "rand.h"
#include <cassert>
#include <vector>
#include <ncurses.h>
#include <unistd.h>
#include <map>
#include <tuple>

class map
{
  private:
    std::vector<char> data;
    std::vector<bool> isVis;


    int width, height;

  public:
    map(int wd, int ht): width(wd), height(ht), data(wd*ht, '.'), isVis(wd*ht, true){}

    std::map<std::tuple<int, int>, std::tuple<int, int>> rooms;


    const char& getxy(int row,int col) const { return data[row+col*width]; }
    char& getxy(int row,int col) { return data[row+col*width]; }

    const bool getVis(int row,int col) const { assert(row <= width && col <= height); return isVis[row+col*width]; }
    void setVis(int row,int col, bool vis);

    int getWidth() const { return width; }
    int getHeight() const { return height; }

    void outUser(WINDOW* game_win, const unit & a);
    void build(int row, int col);
    void buildRoom(const int row, const int col, const int width, const int height);
    void outMap(WINDOW*);
    void placeMonster(WINDOW*, const unit&);
    void moveMonster(unit & a, unit & b);
    bool monsterVision(unit& a, unit& b);

};

#endif
