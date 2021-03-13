#ifndef Trap_hpp
#define Trap_hpp
#include <SFML/Graphics.hpp>

class Trap{
protected:
    int pos_x;
    int pos_y;
    sf::Texture texture;
    sf::Sprite sprite;
    bool is_visible;
public:
    int get_x();   
    int get_y();
    void set_x(int new_x,float tile_size);
    void set_y(int new_y,float tile_size);
    virtual int get_important_value()=0;  
    sf::Sprite* get_sprite();
    void set_visible(bool new_v);
    bool get_visible();





};


#endif