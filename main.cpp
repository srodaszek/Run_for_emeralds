#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "include/Main_Menu.hpp"
extern sf::Image player_sprites;



int main()
{   time_t timer=time(NULL);//1604542588,1604775622
    std::cout<<timer<<std::endl;
    std::srand(timer);
    player_sprites.loadFromFile("data/Dungeon_Character1.png");
    Main_Menu game(768,768);
    return 0; 
}
