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
    //data is what's being used for the map storing.
    std::vector<char> data;
    //isVis is a vector that marks where the user has traveled on the map
    //so we can output the areas they've been too.
    std::vector<bool> isVis;

    // m_row is also the width of the vector.
    int m_row, m_col;

  public:
    map(int rw, int cl): m_row(rw), m_col(cl), data(rw*cl, '.'), isVis(rw*cl, false){}


    const char& getxy(int row,int col) const { return data[row+col*m_row]; }
    char& getxy(int row,int col) { return data[row+col*m_row]; }

    const bool getVis(int row,int col) const { assert(row <= m_row && col <= m_col); return isVis[row+col*m_row]; }
    void setVis(int row,int col, bool vis);

    int getRow() const { return m_row; }
    int getCol() const { return m_col; }

    void outUser(WINDOW* game_win, const unit & a);
    void build(int row, int col);

    void buildRoom();

    void outMap(WINDOW*);
    void placeMonster(WINDOW*, const unit&);
    void moveMonster(unit & a, unit & b);
    bool monsterVision(unit& a, unit& b);

};

#endif
