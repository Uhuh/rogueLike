#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <ncurses.h>
class map;

class unit
{
  private:
    int health, atk, def, str;
    std::string name;
    std::string me;
  public:
    // These are the x/y co-ordinates, we made them public because
    // we got sick of making getters/setters
    int m_x;
    int m_y;

    // The idea of this var is to user it for the monsters.
    int visionLimit;

    unit(): health(10), atk(1), def(1), str(1),
            name("Gurk"), me("@"), visionLimit(6) {};

    //This could probably be removed since x/y cords are more important than
    //names. TODO: Make name and me public.
    std::string getName() const { return name; }
    std::string getMe() const { return me; }


    //Oh lord this is a mess, to many parameters.
    void moveUser(WINDOW* game_win, WINDOW* monster_win, unit & monster, map &world);
    void spawn(const map & area);
    // will be used when str/def/atk are actually being used to calculate dmg and such.
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
