#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <ncurses.h>

class player
{
  private:
    int health, atk, def, str;
    std::string name;
    std::string me;
  public:
    player(): health(10), atk(1), def(1), str(1),
              name("Gurk"), me("@") {};
    std::string getName() const { return name; }
    std::string getMe() const { return me; }
    int getStr() const { return str; }
    int getDef() const { return def; }
    int getAtk() const { return atk; }
    int getHealth() const { return health; }
    void setHealth(const int hp);
    void setName(const std::string n) { name = n; }
    void setMe(const char m) { me = m; }

    void outStats(WINDOW*);
};

#endif
