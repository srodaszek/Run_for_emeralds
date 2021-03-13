#include "Trap.hpp"
#include <SFML/Graphics.hpp>
int Trap::get_x(){return pos_x;}
int Trap::get_y(){return pos_y;}
void Trap::set_x(int new_x,float tile_size){
    this->pos_x=new_x;
    sprite.setPosition(new_x*tile_size,sprite.getPosition().y);
}
void Trap::set_y(int new_y,float tile_size){
    this->pos_y=new_y;
    sprite.setPosition(sprite.getPosition().x,new_y*tile_size);
    }
void Trap::set_visible(bool new_v){this->is_visible=new_v;}
bool Trap::get_visible(){return this->is_visible;}
sf::Sprite* Trap::get_sprite(){return &sprite;}