#ifndef MAP_H
#define MAP_H
#include "player.h"
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
    const char& getxy(int x,int y) const { assert(x <= width && y <= height); return data[x+y*width]; }

    char& getxy(int x,int y) { assert(x <= width && y <= height); return data[x+y*width]; }

    int getWidth() const { return width; }
    int getHeight() const { return height; }

    void outMap(WINDOW*, const player&, int, int);

    map(int wd, int ht): width(wd), height(ht), data(wd*ht, '.'){}
    void build(int x, int y);
};

#endif
