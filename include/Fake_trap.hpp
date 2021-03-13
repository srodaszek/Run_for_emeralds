#ifndef Fake_Trap_hpp
#define Fake_Trap_hpp
#include "Trap.hpp"

class Fake_Trap: public Trap{
private:
    int texture_id;
public:
    Fake_Trap(int x,int y,bool vis,float* tile_size);
    ~Fake_Trap();
    int get_important_value();
};
#endif