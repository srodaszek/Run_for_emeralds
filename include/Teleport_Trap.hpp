#ifndef Teleport_Trap_hpp
#define Teleport_Trap_hpp
#include "Trap.hpp"

class Teleport_Trap: public Trap{
private:
    int distance;
public:
    Teleport_Trap(int x,int y,int distance,bool vis,float* tile_size);
    ~Teleport_Trap();
    int get_important_value();
};
#endif