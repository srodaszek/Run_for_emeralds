#include "Confuse_Trap.hpp"
Confuse_Trap::Confuse_Trap(int x,int y,int dur_time,bool vis,float* tile_size){
    this->is_visible=vis;
    this->pos_x=x;
    this->pos_y=y;
    this->duration_time=dur_time;
    texture.loadFromFile("data/confused.png");
    sprite.setTexture(texture);
    sprite.setScale(tile_size[0],tile_size[1]);
    sprite.setPosition(x*tile_size[0]*16,y*tile_size[1]*16);
}
int Confuse_Trap::get_important_value(){return this->duration_time;}
Confuse_Trap::~Confuse_Trap(){}