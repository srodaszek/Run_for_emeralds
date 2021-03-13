#ifndef Stone_hpp
#define Stone_hpp
#include <SFML/Graphics.hpp>
class Stone{
private:
    int x;
    int y;
    sf::Texture texture;
    sf::Sprite sprite;
public:
    Stone(int x,int y,float* scale);
    int get_x();
    void set_x(int new_x);
    int get_y();
    void set_y(int new_y);
    sf::Sprite* get_sprite();
};
#endif