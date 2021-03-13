#ifndef Game_Logic_hpp
#define Game_Logic_hpp
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Game_Graphic.hpp"
#include "Trap.hpp"
#include "Confuse_Trap.hpp"
#include "Teleport_Trap.hpp"
#include "Tar_Trap.hpp"
#include "Fake_Trap.hpp"
#include "Stone.hpp"
#include <vector>
enum direction{
left=0,
up=1,
right=2,
down=3
};

class Game_Logic{
private:
    sf::RenderWindow* window;
    Player** player;
    int* player_score;
    short int player_quantity;
    short int active_player;
    short int game_state;
    //game states
    //0-main menu
    //1-trap setting
    //2-game
    //3-game ending
    int width_in_tiles;
    int height_in_tiles;
    sf::Event event;
    short int** map;
    Game_Graphic* graphic;
    std::vector<Confuse_Trap*> con_trap; 
    std::vector<Tar_Trap*> tar_trap; 
    std::vector<Teleport_Trap*> tp_trap;
    std::vector<Fake_Trap*> fake_trap;
    //add stones
    int emeralds_quantity;
    std::vector<Stone*> stones;
    int trap_power[3];
public:
    Game_Logic(int width,int height,short int** map_arr,std::vector<int>& room_position,int emerald_quantity,int start_x,int start_y,sf::RenderWindow* window,int settings[21]);
    ~Game_Logic();
    void game_chooser();
    void game_itself();
    bool can_player_move(int player_id,direction mv,int distance=1);
    void game_end();
    void wait_for_direction();
    void move_player(int player_id,direction mv,int distance=1);
    void trap_setting();
    void set_trap(int trap_id,int x,int y);
    void set_trap_to_invisible();
    void set_trap_to_visible();
    void check_trap_activation(int player_id);
    void teleport_player(int player_id,int distance);
    void check_emerald(int player_id);
    




};
#endif