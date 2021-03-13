#include "Player.hpp"
sf::Color colors[]={sf::Color(0,0,255,255),sf::Color(255,0,0,255),sf::Color(0,255,0,255),
                    sf::Color(204,104,232,255),sf::Color(127,138,240,255),sf::Color(179,86,177,255),
                    sf::Color(237,220,64,255),sf::Color(64,237,142,255),sf::Color(214,167,17,255)};
sf::Image player_sprites;
Player::Player(int texture_id,int trap1,int trap2,int trap3,int trap4,int start_x,int start_y,int player_id,float* player_size){
        sf::Image player_image;
        player_texture.loadFromImage(player_sprites,sf::IntRect(texture_id*16,0,16,16));
        player_image=player_texture.copyToImage();
        player_image.setPixel(0,0,colors[player_id]);
        player_image.setPixel(0,1,colors[player_id]);
        player_image.setPixel(1,0,colors[player_id]);
        player_image.setPixel(15,0,colors[player_id]);
        player_image.setPixel(14,0,colors[player_id]);
        player_image.setPixel(15,1,colors[player_id]);
        player_image.setPixel(0,15,colors[player_id]);
        player_image.setPixel(0,14,colors[player_id]);
        player_image.setPixel(1,15,colors[player_id]);
        player_image.setPixel(15,15,colors[player_id]);
        player_image.setPixel(14,15,colors[player_id]);
        player_image.setPixel(15,14,colors[player_id]);
        player_texture.loadFromImage(player_image,sf::IntRect(0,0,16,16));
        player_sprite.setTexture(player_texture);
        player_sprite.setScale(player_size[0],player_size[1]);
        wait_time=0;
        confused_time=0;
        double_jump_charge=0;
        trap_quantity[0]=trap1;
        trap_quantity[1]=trap2;
        trap_quantity[2]=trap3;
        trap_quantity[3]=trap4;
        position_x=start_x;
        position_y=start_y;
        this->player_id=player_id;
    }
int Player::get_x(){return this->position_x;}
int Player::get_y(){return this->position_y;}
sf::Sprite* Player::get_sprite(){return &player_sprite;}
void Player::set_x(int new_x){this->position_x=new_x;}
void Player::set_y(int new_y){this->position_y=new_y;}
int Player::get_jump_charge(){return this->double_jump_charge;}
void Player::set_jump_charge(int mode){double_jump_charge=(double_jump_charge+mode)*mode;}
int* Player::get_trap(){return trap_quantity;}
void Player::set_trap(int value,int id){trap_quantity[id]=value;}
int Player::get_confused_time(){return confused_time;}
int Player::get_wait_time(){return wait_time;}
void Player::set_confused_time(int new_time){confused_time=new_time;}
void Player::set_wait_time(int new_time){wait_time=new_time;}