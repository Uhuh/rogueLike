#ifndef MAP_H
#define MAP_H
#include "unit.h"
#include "rand.h"
#include <cassert>
#include <vector>
#include <ncurses.h>
#include <unistd.h>


class map
{
  private:
    std::vector<char> data;
    int width, height;

  public:
    map(int wd, int ht): width(wd), height(ht), data(wd*ht, '.'), isVis(wd*ht, false){}

    std::vector<bool> isVis;


    const char& getxy(int row,int col) const { assert(row <= width && col <= height); return data[row+col*width]; }
    char& getxy(int row,int col) { assert(row <= width && col <= height); return data[row+col*width]; }

    const bool getVis(int row,int col) const { assert(row <= width && col <= height); return isVis[row+col*width]; }
    void setVis(int row,int col, bool vis) { assert(row <= width && col <= height); isVis[row+col*width] = vis; }


    int getWidth() const { return width; }
    int getHeight() const { return height; }

    void outUser(WINDOW* game_win, const unit & a);
    void build(int row, int col);
    void buildRoom(const int row, const int col, const int width, const int height);
    void outMap(WINDOW*);
    void placeMonster(WINDOW*, const unit&);
    void moveMonster(unit & b);

};

#endif
