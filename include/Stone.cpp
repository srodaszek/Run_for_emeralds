#include "Stone.hpp"
Stone::Stone(int x,int y,float* tile_size){
    this->x=x;
    this->y=y;
    texture.loadFromFile("data/Emerald.png");
    sprite.setTexture(texture);
    sprite.setScale(tile_size[0],tile_size[1]);
    sprite.setPosition(x*tile_size[0]*16,y*tile_size[1]*16);
}
int Stone::get_x(){return this->x;}
int Stone::get_y(){return this->y;}
void Stone::set_x(int new_x){this->x=new_x;}
void Stone::set_y(int new_y){this->y=new_y;}
sf::Sprite* Stone::get_sprite(){return &sprite;}