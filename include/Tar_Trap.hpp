#ifndef Tar_Trap_hpp
#define Tar_Trap_hpp
#include "Trap.hpp"

class Tar_Trap: public Trap{
private:
    int duration_time;
public:
    Tar_Trap(int x,int y,int dur_time,bool vis,float* tile_size);
    ~Tar_Trap();
    int get_important_value();
};
#endif