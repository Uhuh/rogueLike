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


    int m_row, m_col;

  public:
    map(int rw, int cl): m_row(rw), m_col(cl), data(rw*cl, '.'), isVis(rw*cl, true){}

    std::map<std::tuple<int, int>, std::tuple<int, int>> rooms;


    const char& getxy(int row,int col) const { return data[row+col*m_row]; }
    char& getxy(int row,int col) { return data[row+col*m_row]; }

    const bool getVis(int row,int col) const { assert(row <= m_row && col <= m_col); return isVis[row+col*m_row]; }
    void setVis(int row,int col, bool vis);

    int getRow() const { return m_row; }
    int getCol() const { return m_col; }

    void outUser(WINDOW* game_win, const unit & a);
    void build(int row, int col);
    void buildRoom(const int row, const int col, const int m_row, const int m_col);
    void outMap(WINDOW*);
    void placeMonster(WINDOW*, const unit&);
    void moveMonster(unit & a, unit & b);
    bool monsterVision(unit& a, unit& b);

};

#endif
