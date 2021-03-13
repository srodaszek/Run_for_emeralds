#include "Fake_Trap.hpp"
Fake_Trap::Fake_Trap(int x,int y,bool vis,float* tile_size){
    this->is_visible=vis;
    this->pos_x=x;
    this->pos_y=y;
    texture_id=rand()%3;
    if(texture_id==0)texture.loadFromFile("data/confused.png");
    if(texture_id==1)texture.loadFromFile("data/tar.png");
    if(texture_id==2)texture.loadFromFile("data/hole.png");
    sprite.setTexture(texture);
    sprite.setScale(tile_size[0],tile_size[1]);
    sprite.setPosition(x*tile_size[0]*16,y*tile_size[1]*16);
}
int Fake_Trap::get_important_value(){return this->texture_id;}
Fake_Trap::~Fake_Trap(){};