#ifndef Confuse_Trap_hpp
#define Confuse_Trap_hpp
#include "Trap.hpp"

class Confuse_Trap: public Trap{
private:
    int duration_time;
public:
    Confuse_Trap(int x,int y,int dur_time,bool vis,float* tile_size);
    ~Confuse_Trap();
    int get_important_value();
};
#endif