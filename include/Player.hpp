#ifndef Player_hpp
#define Player_hpp
#include <SFML/Graphics.hpp>
class Player{
private:
    sf::Sprite player_sprite;
    sf::Texture player_texture;
    int wait_time;
    int trap_quantity[4];
    int double_jump_charge;
    int position_x;
    int position_y;
    int player_id;
    int confused_time;
public:
    Player(int texture_id,int trap1,int trap2,int trap3,int trap4,int start_x,int start_y,int player_id,float* player_size);
    int get_x();
    int get_y();
    sf::Sprite* get_sprite();
    void set_x(int new_x);
    void set_y(int new_y);
    int get_jump_charge();
    void set_jump_charge(int mode);//if mode is zero then set jump_charge to 0.If mode is one then increment.
    int* get_trap();
    void set_trap(int value,int id);
    int get_wait_time();
    void set_wait_time(int new_time);
    int get_confused_time();
    void set_confused_time(int new_time);
};
#endif