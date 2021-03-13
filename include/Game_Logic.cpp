#include "Game_Logic.hpp"
#include "Game_Graphic.hpp"
#include "Player.hpp"
#include <SFML/Graphics.hpp>
#include <fstream>
Game_Logic::Game_Logic(int width,int height,short int** map_arr,std::vector<int>& room_position,int emerald_quantity,int start_x,int start_y,sf::RenderWindow* window,int settings[21]){
    this->window=window;
    game_state=1;
    trap_power[0]=settings[17];
    trap_power[1]=settings[18];
    trap_power[2]=settings[19];
   // std::fstream map_file("map.txt",std::ios::in);
    width_in_tiles=settings[0];
    height_in_tiles=settings[1];
   // map=new short int*[height_in_tiles];
    //for(int i=0;i<height_in_tiles;i++)map[i]=new short int[width_in_tiles];
    this->emeralds_quantity=settings[2];
    map=map_arr;
/*
    for(int i=0;i<height_in_tiles;i++){
        for(int j=0;j<width_in_tiles;j++){
            map_file>>map[i][j];
        }
    }
  */
    //this->window.create(sf::VideoMode(width,height),"Run for Emeralds!");
    graphic=new Game_Graphic(height,width,map,window,settings[0],settings[1]);
    float* scale=graphic->get_scale();
    player_quantity=settings[3];
    player=new Player*[player_quantity];
    player_score=new int[player_quantity];
    for(int i=0;i<player_quantity;i++){
    player[i]=new Player(settings[4+i],settings[13],settings[14],settings[15],settings[16],start_x+i%3-1,start_y+i/3-1,i,scale);
    }
    for(int i=room_position.size()/2-emeralds_quantity;i<room_position.size()/2;i++){
        stones.push_back(new Stone(room_position[2*i],room_position[2*i+1],scale));
    }
    for(int i=0;i<player_quantity;i++)check_emerald(i);
    for(int i=0;i<player_quantity;i++)player_score[i]=0;
    active_player=0;

 
    game_chooser();


}

Game_Logic::~Game_Logic(){
    for (int i=0;i<player_quantity;i++)delete player[i];
    delete[] player;
    delete graphic;
    for(int i=0;i<con_trap.size();i++)delete con_trap[i];
    con_trap.clear();
    for(int i=0;i<tar_trap.size();i++)delete tar_trap[i];
    tar_trap.clear();
    for(int i=0;i<tp_trap.size();i++)delete tp_trap[i];
    tp_trap.clear();
    for(int i=0;i<fake_trap.size();i++)delete fake_trap[i];
    fake_trap.clear();
    for(int i=0;i<stones.size();i++)delete stones[i];
    stones.clear();
}

bool Game_Logic::can_player_move(int player_id,direction mv,int distance){
int x=player[player_id]->get_x();
int y=player[player_id]->get_y();
switch(mv){
    case 0:
        if(map[y][x-distance]==0)return true;
        break;

    case 1:
        if(map[y-distance][x]==0)return true;
        break;

    case 2:
        if(map[y][x+distance]==0)return true;
        break;

    case 3:
        if(map[y+distance][x]==0)return true;
        break;

}
return false;

}
void Game_Logic::move_player(int player_id,direction mv,int distance){
int x=player[player_id]->get_x();
int y=player[player_id]->get_y();
switch(mv){
    case 0:
        player[player_id]->set_x(x-distance);
        break;

    case 1:
        player[player_id]->set_y(y-distance);
        break;

    case 2:
        player[player_id]->set_x(x+distance);
        break;

    case 3:
        player[player_id]->set_y(y+distance);
        break;

}
check_emerald(player_id);
check_trap_activation(player_id);
if(distance==1)active_player=(active_player+1)%player_quantity;



}
void Game_Logic::teleport_player(int player_id,int distance){
    
    int pl_x=player[player_id]->get_x();
    int pl_y=player[player_id]->get_y();
    while(1){
        int curr_x=rand()%(distance*2+1)-distance;
        int curr_y=rand()%(((distance-abs(curr_x))*2+1))-(distance-abs(curr_x));
        if (map[pl_y+curr_y][pl_x+curr_x]==0){
            player[player_id]->set_x(pl_x+curr_x);
            player[player_id]->set_y(pl_y+curr_y);
            return;
        }




    }    



}
void Game_Logic::game_end(){
    sf::Font font;
    font.loadFromFile("data/arial.ttf");
    int max=-1;
    int max_id=-1;
    for(int i=0;i<player_quantity;i++){
        if (player_score[i]>max){max=player_score[i];max_id=i+1;}
    }
    std::vector<int> winners;
    for(int i=0;i<player_quantity;i++){
        if (player_score[i]==max)winners.push_back(i+1);
    }
    sf::String text;
    if (winners.size()>1){text="Tie on first place between players: ";
    for(int i=0;i<winners.size();i++){
    text+=std::to_string(winners[i]);
    text+=" ";
    }
    }
    else {text="The winner is player ";text+=std::to_string(winners[0]);}
    sf::String bottom_text="Click any key to continue";
    sf::Text text1,bottom_text1;
    text1.setString(text);
    bottom_text1.setString(bottom_text);
    text1.setFont(font);
    bottom_text1.setFont(font);
    text1.setCharacterSize(24);
    bottom_text1.setCharacterSize(24);
    text1.setFillColor(sf::Color::White);
    bottom_text1.setFillColor(sf::Color::White);
    //text1.setColor(sf::Color::Black);
    float* scale=graphic->get_scale();
    if(winners.size()>1)text1.setPosition((width_in_tiles*16*scale[0])/2-120,(height_in_tiles*16*scale[1])/2-40);
    else text1.setPosition((width_in_tiles*16*scale[0])/2-100,(height_in_tiles*16*scale[1])/2-40);
    bottom_text1.setPosition((width_in_tiles*16*scale[0])/2-100,(height_in_tiles*16*scale[1])/2+60);
    int start_x=(width_in_tiles*16*scale[0]/2)-32-64*(winners.size()-1);
    
    for(int i=0;i<winners.size();i++){
        sf::Sprite* temp=player[winners[i]-1]->get_sprite();
        temp->setScale(4,4);
        temp->setPosition(start_x,height_in_tiles*16*scale[1]/2);
        start_x+=64;
    }

    window->clear(sf::Color(37,19,26,0));
    window->draw(text1);
    for(int i=0;i<winners.size();i++)window->draw(*(player[winners[i]-1]->get_sprite()));
    window->draw(bottom_text1);
    window->display();
    while(window->isOpen()){
        while(window->pollEvent(event)){
            if(event.type==sf::Event::KeyPressed){
                return;
            }
            if(event.type==sf::Event::Closed){
                window->close();
                exit(0);
            }
        }
    
    }
}



void Game_Logic::check_trap_activation(int player_id){
    int x=player[player_id]->get_x();
    int y=player[player_id]->get_y();
    std::vector<Trap*>::iterator it;
    for(auto it=con_trap.begin();it!=con_trap.end();++it){
        if (x==(*it)->get_x() && y==(*it)->get_y()){
            player[player_id]->set_confused_time((*it)->get_important_value());
            delete (*it);
            con_trap.erase(it);
           --it; 
        }
    }

    for(auto it=tar_trap.begin();it!=tar_trap.end();++it){
        if (x==(*it)->get_x() && y==(*it)->get_y()){
            player[player_id]->set_wait_time((*it)->get_important_value());
            delete (*it);
            tar_trap.erase(it);
           --it; 
        }
    }

    for(auto it=tp_trap.begin();it!=tp_trap.end();++it){
        if (x==(*it)->get_x() && y==(*it)->get_y()){
            teleport_player(player_id,(*it)->get_important_value());
            delete (*it);
            tp_trap.erase(it);
           --it; 
           check_emerald(player_id);
        }
    }
    for(auto it=fake_trap.begin();it!=fake_trap.end();++it){
        if (x==(*it)->get_x() && y==(*it)->get_y()){
            delete (*it);
            fake_trap.erase(it);
           --it; 
        }
    }


}
void Game_Logic::wait_for_direction(){
while(window->isOpen()){

        
        while (window->pollEvent(event))
        {
            if (event.type== sf::Event::KeyPressed){
                if (event.key.code==sf::Keyboard::A){
                    std::cout<<"A"<<std::endl;
                    if(can_player_move(active_player,left,2)==true){move_player(active_player,left,2);
                    player[active_player]->set_jump_charge(0);
                    set_trap_to_visible();
                    return;}
                }
                if (event.key.code==sf::Keyboard::W){
                    if(can_player_move(active_player,up,2)==true){move_player(active_player,up,2);
                    player[active_player]->set_jump_charge(0);
                    set_trap_to_visible();
                    return;}
                }
                if (event.key.code==sf::Keyboard::D){
                    if(can_player_move(active_player,right,2)==true){move_player(active_player,right,2);
                    player[active_player]->set_jump_charge(0);
                    set_trap_to_visible();
                    return;}
                }
                if (event.key.code==sf::Keyboard::S){
                    if(can_player_move(active_player,down,2)==true){move_player(active_player,down,2);
                    player[active_player]->set_jump_charge(0);
                    set_trap_to_visible();
                    return;}
                }
            }
            if(event.type==sf::Event::Closed){window->close();exit(0);}


}
    graphic->draw_map();
    graphic->draw_traps(con_trap,tar_trap,tp_trap,fake_trap);
    graphic->draw_stones(stones);
    graphic->draw_player(player,player_quantity);
    graphic->draw_progress_bar(player,player_quantity);
    graphic->draw_fog_of_war(player,player_quantity);
    window->display();
}}




void Game_Logic::game_itself(){

set_trap_to_visible();

    while (window->isOpen())
    {
        
        if(player[active_player]->get_wait_time()!=0){
            
                player[active_player]->set_wait_time(player[active_player]->get_wait_time()-1);
                active_player=(active_player+1)%player_quantity;
                
            
        }
        if(player[active_player]->get_confused_time()!=0){
            player[active_player]->set_confused_time(player[active_player]->get_confused_time()-1);
            while(1){
                direction mv= (direction)(rand()%4);
                if(can_player_move(active_player,mv,1)){move_player(active_player,mv,1);break;}
            }
        if(game_state==3)return;

        }
        if(player[active_player]->get_jump_charge()!=0){
            if (player[active_player]->get_jump_charge()==2){
            player[active_player]->set_jump_charge(1);
            wait_for_direction();
            if (game_state==3)return;
            player[active_player]->set_jump_charge(0);}
            else{player[active_player]->set_jump_charge(1);}
            active_player=(active_player+1)%player_quantity;
        }

        while (window->pollEvent(event))
        {
            if (event.type== sf::Event::KeyPressed){
                if (event.key.code==sf::Keyboard::A){
                    if(can_player_move(active_player,left)==true){move_player(active_player,left);
                        if (game_state==3)return;
                        set_trap_to_visible();}
                }
                else if (event.key.code==sf::Keyboard::W){
                    if(can_player_move(active_player,up)==true)
                    {move_player(active_player,up);
                        if (game_state==3)return;
                        set_trap_to_visible();                    }
                }
                else if (event.key.code==sf::Keyboard::D){
                    if(can_player_move(active_player,right)==true){move_player(active_player,right);
                    if (game_state==3)return;
                    set_trap_to_visible();}
                }
                else if (event.key.code==sf::Keyboard::S){
                    if(can_player_move(active_player,down)==true){
                        move_player(active_player,down);
                        if (game_state==3)return;
                        set_trap_to_visible();
                    }
                }
                else if(event.key.code=sf::Keyboard::Space){
                    player[active_player]->set_jump_charge(1);active_player=(active_player+1)%player_quantity;

                }



            }
            if (event.type == sf::Event::Closed){
                window->close();
                exit(0);
            }
        }
 
    graphic->draw_map();
    graphic->draw_traps(con_trap,tar_trap,tp_trap,fake_trap);
    graphic->draw_stones(stones);
    graphic->draw_player(player,player_quantity);
    graphic->draw_progress_bar(player,player_quantity);
    graphic->draw_arrow(player[active_player]->get_x(),player[active_player]->get_y());
    graphic->draw_fog_of_war(player,player_quantity);
    window->display();
        
    }




}

void Game_Logic::game_chooser(){
    while(window->isOpen()){
        switch(game_state)
        {
        case 0:
        break;
        case 1:
        trap_setting();
        break;
        case 2:
        game_itself();
        break;
        case 3:
            game_end();
            return;
        break;
        }
    }
}

void Game_Logic::set_trap(int trap_id,int x,int y){
switch(trap_id){
    case 0:
        con_trap.push_back(new Confuse_Trap(x,y,trap_power[0],true,graphic->get_scale()));
        break;
    case 1:
        tar_trap.push_back(new Tar_Trap(x,y,trap_power[1],true,graphic->get_scale()));
        break;
    case 2:
        tp_trap.push_back(new Teleport_Trap(x,y,trap_power[2],true,graphic->get_scale()));
        break;
    case 3:
        fake_trap.push_back(new Fake_Trap(x,y,true,graphic->get_scale()));
}
player[active_player]->set_trap(player[active_player]->get_trap()[trap_id]-1,trap_id);

}
void Game_Logic::set_trap_to_visible(){
    set_trap_to_invisible();
     for(int i=0;i<player_quantity;i++){
        std::cout<<i<<std::endl;
        for(int j=0;j<con_trap.size();j++)
            //if sum of difference of player position and trap position in both axis is smaller than 2 trap gets visible
            if((abs(con_trap[j]->get_x()-player[i]->get_x())+abs(con_trap[j]->get_y()-player[i]->get_y()))<2)con_trap[j]->set_visible(true);
        for(int j=0;j<tar_trap.size();j++)
            //if sum of difference of player position and trap position in both axis is smaller than 2 trap gets visible
            if((abs(tar_trap[j]->get_x()-player[i]->get_x())+abs(tar_trap[j]->get_y()-player[i]->get_y()))<2)tar_trap[j]->set_visible(true);

        for(int j=0;j<tp_trap.size();j++)
            //if sum of difference of player position and trap position in both axis is smaller than 2 trap gets visible
            if((abs(tp_trap[j]->get_x()-player[i]->get_x())+abs(tp_trap[j]->get_y()-player[i]->get_y()))<2)tp_trap[j]->set_visible(true);
        for(int j=0;j<fake_trap.size();j++)
            //if sum of difference of player position and trap position in both axis is smaller than 2 trap gets visible
            if((abs(fake_trap[j]->get_x()-player[i]->get_x())+abs(fake_trap[j]->get_y()-player[i]->get_y()))<2)fake_trap[j]->set_visible(true);
    }
    


}

void Game_Logic::set_trap_to_invisible(){
for(int i=0;i<con_trap.size();i++){
con_trap[i]->set_visible(false);   
}
for(int i=0;i<tar_trap.size();i++){
tar_trap[i]->set_visible(false);   
}
for(int i=0;i<tp_trap.size();i++){
tp_trap[i]->set_visible(false);   
}
for(int i=0;i<fake_trap.size();i++){
    fake_trap[i]->set_visible(false);
}
}



void Game_Logic::trap_setting(){
int cur_x=10;
int cur_y=10;
int trap_id=0;
while(window->isOpen()){

while(window->pollEvent(event)){
 if (event.type== sf::Event::KeyPressed){
                if (event.key.code==sf::Keyboard::A){
                    if(cur_x!=0)cur_x-=1;

                }
                else if (event.key.code==sf::Keyboard::W){
                    if(cur_y!=0)cur_y-=1;
                }
                else if (event.key.code==sf::Keyboard::D){
                    if(cur_x!=width_in_tiles-1)cur_x+=1;
                }
                else if (event.key.code==sf::Keyboard::S){
                    if(cur_y!=height_in_tiles-1)cur_y+=1;
                }
                else if(event.key.code=sf::Keyboard::Space){
                    if(map[cur_y][cur_x]==0){
                        bool is_ok=true;
                        for(int i=0;i<player_quantity;i++)
                        if(player[i]->get_x()==cur_x && player[i]->get_y()==cur_y){is_ok=0;break;}
                        for(int i=0;i<stones.size();i++)
                        if(stones[i]->get_x()==cur_x && stones[i]->get_y()==cur_y){is_ok=0;break;}
                        if(is_ok){
                        set_trap(trap_id,cur_x,cur_y);
                        if (player[active_player]->get_trap()[trap_id]==0)
                        {
                            int* tr=player[active_player]->get_trap();
                            std::cout<<"1:"<<tr[0]<<std::endl;
                            std::cout<<"2:"<<tr[1]<<std::endl;
                            std::cout<<"3:"<<tr[2]<<std::endl;
                            std::cout<<"pl:"<<active_player<<std::endl;
                            //std::cout<<"trap:"<<trap_id<<std::endl;
                            if (++trap_id>3){
                            std::cout<<"trap:"<<trap_id<<std::endl;
                                active_player++;
                                trap_id=0;
                                set_trap_to_invisible();
                                if(active_player>=player_quantity){active_player=0;game_state=2;return;}
                            }
                        }
                        }
                    }
                }
            }

if(event.type==sf::Event::Closed){
window->close();
exit(0);
}
}
graphic->draw_map();
if(!((cur_x==0 && cur_y==0) || (cur_x==1 && cur_y==0) || (cur_x==0 && cur_y==1) || (cur_x==1 && cur_y==1)))graphic->draw_current_trap(trap_id);
graphic->draw_traps(con_trap,tar_trap,tp_trap,fake_trap);
graphic->draw_player(player,player_quantity);
graphic->draw_stones(stones);
graphic->draw_cursor(cur_x,cur_y);
graphic->draw_arrow(player[active_player]->get_x(),player[active_player]->get_y());
window->display();


}
}

void Game_Logic::check_emerald(int player_id){
    int x=player[player_id]->get_x();
    int y=player[player_id]->get_y();
    std::vector<Stone*>::iterator it;
    for(it=stones.begin();it!=stones.end();++it){
        if(x==(*it)->get_x() && y==(*it)->get_y()){
            delete *it;
            stones.erase(it);
            it--;
            player_score[player_id]++;
        }
    }
    if (stones.size()==0)game_state=3;
}