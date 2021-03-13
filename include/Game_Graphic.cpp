#include "Game_Graphic.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>


Game_Graphic::Game_Graphic(int height,int width,short int** map_pointer,sf::RenderWindow* window1,int width_tile,int height_tile){
        this->window=window1;
        this->map=map_pointer;
        
        width_in_tiles=width_tile;
        height_in_tiles=height_tile;

        window_height=height;
        window_width=width;
        floor_tiles=new char*[height_in_tiles];
        for(int i=0;i<height_in_tiles;i++)floor_tiles[i]=new char[width_in_tiles];
        tile_size[0]=static_cast <float>((static_cast <float>(window_width)/static_cast <float>(width_in_tiles))/16);
        tile_size[1]=static_cast <float>((static_cast <float>(window_height)/static_cast <float>(height_in_tiles))/16);
        sf::Image fog_of_war_image;
        fog_of_war_image.create(16*tile_size[0],16*tile_size[1],sf::Color(0,0,0,128));
        fog_of_war_texture.loadFromImage(fog_of_war_image);
        fog_of_war_sprite.setTexture(fog_of_war_texture);
        cursor_texture.loadFromFile("data/cursor.png");
        cursor.setTexture(cursor_texture);
        cursor.setScale(tile_size[0],tile_size[1]);

        current_trap_texture[0].loadFromFile("data/confused.png");
        current_trap_texture[1].loadFromFile("data/tar.png");
        current_trap_texture[2].loadFromFile("data/hole.png");
        current_trap_texture[3].loadFromFile("data/fake.png");
        for(int i=0;i<4;i++){
            current_trap_sprite[i].setTexture(current_trap_texture[i]);
            current_trap_sprite[i].setScale(2*tile_size[0],2*tile_size[1]);
            current_trap_sprite[i].setPosition(0,0);
        }

        arrow_texture.loadFromFile("data/arrow.png");
        arrow_sprite.setTexture(arrow_texture);
        arrow_sprite.setScale(tile_size[0],tile_size[1]);

        progress_bar_texture[0].loadFromFile("data/progress_bar1.png");
        progress_bar_texture[1].loadFromFile("data/progress_bar2.png");
        progress_bar_texture[2].loadFromFile("data/progress_bar3.png");

        progress_bar_sprite[0].setTexture(progress_bar_texture[0]);
        progress_bar_sprite[1].setTexture(progress_bar_texture[1]);
        progress_bar_sprite[2].setTexture(progress_bar_texture[2]);

        progress_bar_sprite[0].setScale(tile_size[0],tile_size[1]);
        progress_bar_sprite[1].setScale(tile_size[0],tile_size[1]);
        progress_bar_sprite[2].setScale(tile_size[0],tile_size[1]);

        tiles_image.loadFromFile("data/Dungeon2.png");
        tiles_textures[0].loadFromImage(tiles_image,sf::IntRect(0,16,16,16)); 
        tiles_textures[1].loadFromImage(tiles_image,sf::IntRect(16,0,16,16)); 
        tiles_textures[2].loadFromImage(tiles_image,sf::IntRect(80,16,16,16)); 
        tiles_textures[3].loadFromImage(tiles_image,sf::IntRect(16,64,16,16));
        tiles_textures[4].loadFromImage(tiles_image,sf::IntRect(0,64,16,16));
        tiles_textures[5].loadFromImage(tiles_image,sf::IntRect(80,64,16,16));
        tiles_textures[6].loadFromImage(tiles_image,sf::IntRect(0,80,16,16));
        tiles_textures[7].loadFromImage(tiles_image,sf::IntRect(16,80,16,16));

        for(int i=0;i<3;++i){
           for(int j=0;j<4;++j){
           floor_textures[i*4+j].loadFromImage(tiles_image,sf::IntRect(16+j*16,16+i*16,16,16));
           }}
        for(int i=0;i<8;i++){tiles_sprites[i].setTexture(tiles_textures[i]);tiles_sprites[i].setScale(tile_size[0],tile_size[1]);}
        for(int i=0;i<12;i++){floor_sprites[i].setTexture(floor_textures[i]);floor_sprites[i].setScale(tile_size[0],tile_size[1]);}
        randomized_floor();
        
   

       }
Game_Graphic::~Game_Graphic(){
for(int i=0;i<height_in_tiles;++i)delete[] floor_tiles[i];
delete[] floor_tiles;

}; 
void Game_Graphic::randomized_floor(){
        for(int i=0;i<height_in_tiles;++i){
            for(int j=0;j<width_in_tiles;++j){
                if (map[i][j]==0)
                    floor_tiles[i][j]=std::rand() % 12;
                else floor_tiles[i][j]=-1;
            }
        }
    }
void Game_Graphic::draw_map(){
    window->clear(sf::Color(37,19,26,0));
    for(int i=0;i<height_in_tiles;++i){
        for(int j=0;j<width_in_tiles;++j){
        
          
           if(map[i][j]==0){
                char tile_id=floor_tiles[i][j];
                floor_sprites[tile_id].setPosition(16*tile_size[0]*j,16*tile_size[1]*i);
               
                window->draw(floor_sprites[tile_id]);
           }
            
            
            
            if(map[i][j]>1 && map[i][j]<10){
            tiles_sprites[map[i][j]-2].setPosition(16*tile_size[0]*j,16*tile_size[1]*i);
            window->draw(tiles_sprites[map[i][j]-2]);
            }


        }


    }
 //   window->display();
}
void Game_Graphic::draw_player(Player** player_list,int player_quantity){
        for(int i=0;i<player_quantity;i++){
            sf::Sprite* temp_player=player_list[i]->get_sprite();
            temp_player->setPosition(player_list[i]->get_x()*16*tile_size[0],player_list[i]->get_y()*16*tile_size[1]);
            window->draw(*temp_player);
           // window->display();

        }
}
float* Game_Graphic::get_scale(){return (tile_size);}

void Game_Graphic::draw_traps(std::vector<Confuse_Trap*> &con_trap,std::vector<Tar_Trap*> &tar_trap,std::vector<Teleport_Trap*> &tp_trap,std::vector<Fake_Trap*>& fake_trap){
for(int i=0;i<con_trap.size();i++){
if (con_trap[i]->get_visible())window->draw(*(con_trap[i]->get_sprite()));    
}

for(int i=0;i<tar_trap.size();i++){
if (tar_trap[i]->get_visible())window->draw(*(tar_trap[i]->get_sprite()));    
}

for(int i=0;i<tp_trap.size();i++){
if (tp_trap[i]->get_visible())window->draw(*(tp_trap[i]->get_sprite()));    
}
for(int i=0;i<fake_trap.size();i++){
if (fake_trap[i]->get_visible())window->draw(*(fake_trap[i]->get_sprite()));    
}

}
void Game_Graphic::draw_cursor(int x,int y){
cursor.setPosition(x*16*tile_size[0],y*16*tile_size[1]);
window->draw(cursor);
}


void Game_Graphic::draw_stones(std::vector<Stone*> &stones){
    for(int i=0;i<stones.size();i++)window->draw(*(stones[i]->get_sprite()));
}
void Game_Graphic::draw_fog_of_war(Player** player,int player_quantity){
bool is_in_player_view;
int x,y;
for(int i=0;i<height_in_tiles;i++){
    for(int j=0;j<width_in_tiles;j++){
        bool is_in_player_view=true;
        for(int k=0;k<player_quantity;k++){
            x=player[k]->get_x();
            y=player[k]->get_y();
            if((j==x && i==y) ||(j-1==x && i==y) ||(j+1==x && i==y) ||(j==x && i-1==y) ||(j==x && i+1==y))is_in_player_view=false;
        }
        if(is_in_player_view){
        fog_of_war_sprite.setPosition(j*16*tile_size[0],i*16*tile_size[1]);
        window->draw(fog_of_war_sprite);
        }
    }
}
}

void Game_Graphic::draw_progress_bar(Player** player,int player_quantity){
    for(int i=0;i<player_quantity;i++){
        int time=player[i]->get_jump_charge();
        
        int x=player[i]->get_x();
        int y=player[i]->get_y();
        switch(time){
            case 0:
                continue;
                break;
            case 1:
                progress_bar_sprite[0].setPosition(16*x*tile_size[0],16*y*tile_size[1]);
                window->draw(progress_bar_sprite[0]);
                break;
            case 2:
                progress_bar_sprite[1].setPosition(16*x*tile_size[0],16*y*tile_size[1]);
                window->draw(progress_bar_sprite[1]);
                break;
            case 3:
                progress_bar_sprite[2].setPosition(16*x*tile_size[0],16*y*tile_size[1]);
                window->draw(progress_bar_sprite[2]);
                break;

        }
    }
}
void Game_Graphic::draw_arrow(int x,int y){
    if(y==0);
    y--;
    arrow_sprite.setPosition(x*16*tile_size[0],y*16*tile_size[1]);
    window->draw(arrow_sprite);


}
void Game_Graphic::draw_current_trap(int trap_id){
window->draw(current_trap_sprite[trap_id]);
}