#include "rand.h"

int rand_int(int low, int high)
{
   static std::random_device rd;
   static std::mt19937 gen(rd());
   static std::uniform_int_distribution<> dist;
   dist = std::uniform_int_distribution<>{low, high};
   return dist(gen);
}
