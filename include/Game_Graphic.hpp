#ifndef Game_Graphic_hpp
#define Game_Graphic_hpp
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Trap.hpp"
#include "Confuse_Trap.hpp"
#include "Teleport_Trap.hpp"
#include "Tar_Trap.hpp"
#include "Fake_Trap.hpp"
#include "Stone.hpp"

class Game_Graphic{
   //Logic class to draw everything on the screen
private:
    sf::RenderWindow* window;
    int width_in_tiles;
    int height_in_tiles;
    short int** map;//loaded from file.first id for width,second id to height
/* diffrent numbers represent diffrent tiles.
0-floor
1-black
2-left wall (on right side of tile)
3-up wall (on down side of tile)
4-right wall (you know where)
5-down wall (look at this DUUUUDE)
6-left bottom corner
7-right bottom corner
it is for now maybe add more later
*/
    int window_height;
    int window_width;
    std::string window_title;
    sf::Image tiles_image;
    sf::Texture tiles_textures[8];//without floor tiles because i want to make them diffrent.just substract 2 from map to get tile
    sf::Sprite tiles_sprites[8];
    sf::Texture floor_textures[12];
    sf::Sprite floor_sprites[12];
    char** floor_tiles;//number of floor tile. Randomized only once so we need table to keep this.
    // we lose some more memory but its easier to implement and understand.
    float tile_size[2];
    sf::Texture cursor_texture;
    sf::Sprite cursor;
    /*0 for width, 1 for height.
    scales textures from 16x16 to window_width/width_in_tiles x window_height/height_in_tiles*/
    sf::Texture fog_of_war_texture;
    sf::Sprite fog_of_war_sprite;
    sf::Texture progress_bar_texture[3];
    sf::Sprite progress_bar_sprite[3];
    sf::Texture arrow_texture;
    sf::Sprite arrow_sprite;
    sf::Texture current_trap_texture[4];
    sf::Sprite current_trap_sprite[4];
public:
    Game_Graphic(int height,int width,short int** map_pointer,sf::RenderWindow* window1,int width_tile,int height_tile);
    ~Game_Graphic();
    void randomized_floor();
    void draw_map();
    void draw_player(Player** player_list,int player_quantity);
    float* get_scale();
    void draw_traps(std::vector<Confuse_Trap*> &con_trap,std::vector<Tar_Trap*> &tar_trap,std::vector<Teleport_Trap*> &tp_trap,std::vector<Fake_Trap*> &fake_trap);
    void draw_cursor(int x,int y);
    void draw_stones(std::vector<Stone*> &stones);
    void draw_fog_of_war(Player** player,int player_quantity);
    void draw_progress_bar(Player** player,int player_quantity);
    void draw_arrow(int x,int y);
    void draw_current_trap(int trap_id);
    



};



#endif