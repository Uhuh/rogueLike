#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <cstdlib>
using namespace std;
class player
{
  private:
    int health;
    string name;
    string me;
  public:
    string getName() const { return name; }
    string getMe() const { return me; }
    int getHealth() const { return health; }
    void setHealth(int hp);
    void setMe(char m) { me = m; }
};

#endif
