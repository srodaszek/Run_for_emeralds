#ifndef Main_Menu_hpp
#define Main_Menu_hpp
#include <SFML/Graphics.hpp>
#include "Game_Logic.hpp"
#include <vector>
#include <fstream>
class Main_Menu{
private:
    short int** map_arr;
    short int** visited;
    int width;
    int height;
    sf::RenderWindow window;
    int settings[21];
    int settings_max[21]={64,64,8,9,8,8,8,8,8,8,8,8,8,99,99,99,99,99,99,10,1};//including value
    int settings_min[21]={16,16,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//including value
    //settings_arr_values
    //0-width_in_tiles
    //1-height_in_tiles
    //2-emerald quantity
    //3-player_quantity
    //4-12 player_skin
    //13-confused trap quantity
    //14-tar trap quantity
    //15-teleport trap quantity
    //16-fake_trap quantity
    //17-confused trap power
    //18-tar trap power
    //19-teleport trap power
    //20-music on/off
    sf::Font font;
    sf::Text settings_text[21];
    sf::Texture button_texture;
    sf::Sprite button_sprite;
    sf::Text text[3];
    sf::Texture arrow_texture;
    sf::Sprite arrow_sprite_right;
    sf::Sprite arrow_sprite_down;
    sf::Sprite arrow_sprite_left;
    sf::Sprite arrow_sprite_up;
    sf::Texture skin_texture[9];
    sf::Sprite skin_sprite[9];
    sf::Event event;
public:
    Main_Menu(int width,int height);
    void menu();
    void start_game();
    void settings_menu();
    void save_settings();
    //map creation functions
    void walk_over_map(int curr_x,int curr_y);
    void add_new_hole(int start_x,int start_y,int dest_x,int dest_y);
    void repair();
    void polish();
    void make_walls();
    int find_closest(int x,int y,std::vector<int> room_position,std::vector<int> edges);
    void set_holes(std::vector<int>& nodes,int node_id,std::vector<int>& room_position,std::vector<int>* edges);
    bool check_if_possible(int curr_x,int curr_y,int room_id);
    void write_room(int curr_x,int curr_y,int room_id,int mode);
    void check_if_any_possible(int left_x,int top_y,int right_x,int bottom_y,int room_id,std::vector<int>& temp);
    bool set_rooms(std::vector<int> &nodes,int node_id,std::vector<int> &room_position);
    int generate_graph(std::vector<int>& nodes,std::vector<int>& room_position);
    //end of map creation functions
};
#endif