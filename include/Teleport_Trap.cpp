#include "Teleport_Trap.hpp"
Teleport_Trap::Teleport_Trap(int x,int y,int dist,bool vis,float* tile_size){
this->is_visible=vis;    
    this->pos_x=x;
    this->pos_y=y;
    this->distance=dist;
    texture.loadFromFile("data/hole.png");
    sprite.setTexture(texture); 
    sprite.setScale(tile_size[0],tile_size[1]);
    sprite.setPosition(x*tile_size[0]*16,y*tile_size[1]*16);
}
int Teleport_Trap::get_important_value(){return this->distance;}
Teleport_Trap::~Teleport_Trap(){}