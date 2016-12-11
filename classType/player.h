#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <cstdlib>

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
    int getHealth() const { return health; }
    void setHealth(int hp);
    void setMe(char m) { me = m; }
};

#endif
