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

    // Think of row as the y axes, and col as the x axis.
    // Also height/width.
    int m_row, m_col;

  public:
    map(int rw, int cl): m_row(rw), m_col(cl), data(rw*cl, '.'), isVis(rw*cl, true){}

    // Const version for output, (don't want to change on accident...)
    const char& getxy(int row,int col) const { return data[row+col*m_row]; }
    // This one for changing the vector.
    char& getxy(int row,int col) { return data[row+col*m_row]; }

    const bool getVis(int row,int col) const { assert(row <= m_row && col <= m_col); return isVis[row+col*m_row]; }
    void setVis(int row,int col, bool vis);

    int getRow() const { return m_row; }
    int getCol() const { return m_col; }

    // Using ncurses to output the user.
    void outUser(WINDOW* game_win, const unit & a);

    //Builds the mao.
    void build(int row, int col);
    //Builds rooms. (NEEDS TO BE FIXED)
    void buildRoom();

    //ncurses for outputting the map.
    void outMap(WINDOW*);
    //Places monster in the vector.
    void placeMonster(WINDOW*, const unit&);

    //We move our monster.
    void moveMonster(unit & a, unit & b);
    bool monsterVision(unit& a, unit& b);

};

#endif
