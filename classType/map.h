#ifndef MAP_H
#define MAP_H
#include "unit.h"
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
    const char& getxy(int row,int col) const { assert(row <= width && col <= height); return data[row+col*width]; }

    char& getxy(int row,int col) { assert(row <= width && col <= height); return data[row+col*width]; }

    int getWidth() const { return width; }
    int getHeight() const { return height; }

    void buildRoom(const int row, const int col, const int width, const int height);

    void outMap(WINDOW*, const unit&, int, int);

		void placeMonster(WINDOW*, const unit&, int, int);

    map(int wd, int ht): width(wd), height(ht), data(wd*ht, '.'){}
    void build(int row, int col);
};

#endif
