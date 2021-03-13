#include "Main_Menu.hpp"
#include <set>
#include <utility>
extern sf::Image player_sprites;
Main_Menu::Main_Menu(int width,int height){
    this->width=width;
    this->height=height;
    font.loadFromFile("data/arial.ttf");
    
    for(int i=0;i<3;i++)
    {
        text[i].setFont(font);
        text[i].setCharacterSize(18);
        text[i].setFillColor(sf::Color::Black);
    }
    text[0].setString("Start Game");
    text[1].setString("Settings");
    text[2].setString("Exit");

    text[0].setPosition(width/2-60,80);
    text[1].setPosition(width/2-40,height/3+80);
    text[2].setPosition(width/2-20,2*height/3+80);

    button_texture.loadFromFile("data/button.png");
    button_sprite.setTexture(button_texture);
    
    arrow_texture.loadFromFile("data/arrow.png");

    arrow_sprite_right.setTexture(arrow_texture);
    arrow_sprite_right.setRotation(-90);
    arrow_sprite_right.setScale(4,4);

    arrow_sprite_down.setTexture(arrow_texture);
    arrow_sprite_down.setScale(4,4);
    
    arrow_sprite_up.setTexture(arrow_texture);
    arrow_sprite_up.setRotation(180);
    arrow_sprite_up.setScale(4,4);

    arrow_sprite_left.setTexture(arrow_texture);
    arrow_sprite_left.setRotation(90);
    arrow_sprite_left.setScale(4,4);
    arrow_sprite_left.setPosition(width/2+100,height/2-40);
    std::fstream file;
    file.open("data/settings.bin",std::ios::in|std::ios::binary);
    file.read((char*)settings,sizeof(settings));
    for(int i=0;i<21;i++)
    {      
        settings_text[i].setFont(font);
        settings_text[i].setCharacterSize(38);
        settings_text[i].setFillColor(sf::Color::White);
        settings_text[i].setPosition(60,height/2-40);
    }
    file.close();
    settings_text[0].setString("tiles width");
    settings_text[1].setString("tiles height");
    settings_text[2].setString("emeralds quantity");
    settings_text[3].setString("player quantity");
    settings_text[4].setString("player 1 skin");
    settings_text[5].setString("player 2 skin");
    settings_text[6].setString("player 3 skin");
    settings_text[7].setString("player 4 skin");
    settings_text[8].setString("player 5 skin");
    settings_text[9].setString("player 6 skin");
    settings_text[10].setString("player 7 skin");
    settings_text[11].setString("player 8 skin");
    settings_text[12].setString("player 9 skin");
    settings_text[13].setString("confused trap quantity");
    settings_text[14].setString("tar trap quantity");
    settings_text[15].setString("teleport trap quantity");
    settings_text[16].setString("fake trap quantity");
    settings_text[17].setString("confused trap power");
    settings_text[18].setString("tar trap power");
    settings_text[19].setString("teleport trap power");
    settings_text[20].setString("music on/off");

    for(int i=0;i<9;i++){
        skin_texture[i].loadFromImage(player_sprites,sf::IntRect(16*i,0,16,16));
        skin_sprite[i].setTexture(skin_texture[i]);
        skin_sprite[i].setScale(4,4);
        skin_sprite[i].setPosition(width/2+180,height/2-50);
    }


    window.create(sf::VideoMode(width,height),"Run for Emeralds!");
    menu();
}


void Main_Menu::save_settings(){
std::fstream file;
file.open("data/settings.bin",std::ios::out|std::ios::binary);
file.write((char*) &settings,sizeof(settings));

file.close();

}



void Main_Menu::settings_menu(){
    int option_id=0;
    bool state=0;
    arrow_sprite_down.setPosition(150,height/2+32);
    arrow_sprite_up.setPosition(214,height/2-52);
    arrow_sprite_right.setPosition(width/2+50,height/2+20);
    sf::Text field_value;
    field_value.setFont(font);
    field_value.setString(std::to_string(settings[0]));
    field_value.setFillColor(sf::Color::White);
    field_value.setCharacterSize(38);
    field_value.setPosition(width/2+200,height/2-40);

    while(window.isOpen()){



        while(window.pollEvent(event)){
            
            if(event.type==sf::Event::KeyPressed){
                if (state==0){
                if(event.key.code==sf::Keyboard::S){
                    option_id=(option_id+1)%21;
                    field_value.setString(std::to_string(settings[option_id]));
                  }
                
                else if(event.key.code==sf::Keyboard::W){
                    option_id=(21+option_id-1)%21;
                    field_value.setString(std::to_string(settings[option_id]));
                  }
                else if(event.key.code==sf::Keyboard::D){
                    state=1;
                    arrow_sprite_down.setPosition(width/2+180,height/2+20);
                    arrow_sprite_up.setPosition(width/2+245,height/2-50);

                }
            }
            else{
                if(event.key.code==sf::Keyboard::W){
                    if(++settings[option_id]>settings_max[option_id])settings[option_id]=settings_min[option_id];

                    field_value.setString(std::to_string(settings[option_id]));
                  }               
                else if(event.key.code==sf::Keyboard::S){
                    if(--settings[option_id]<settings_min[option_id])settings[option_id]=settings_max[option_id];
                    field_value.setString(std::to_string(settings[option_id]));
                  }
                else if(event.key.code==sf::Keyboard::A){
                    state=0;
                    arrow_sprite_down.setPosition(150,height/2+32);
                    arrow_sprite_up.setPosition(214,height/2-52);

                }
                


            }
            if(event.key.code==sf::Keyboard::Space){
                save_settings();
                return;

            }
            }
            if (event.type==sf::Event::Closed){
                save_settings();
                window.close();
                exit(0);
            }

        }
        window.clear(sf::Color(37,19,26,0));
        window.draw(arrow_sprite_down);
        window.draw(arrow_sprite_up);
        window.draw(settings_text[option_id]);
        if(option_id<4 || option_id>12){
            window.draw(field_value);
        }
        else{
            window.draw(skin_sprite[settings[option_id]]);
        }



        if(state==0){
            window.draw(arrow_sprite_right);
        }
        else
        {
            window.draw(arrow_sprite_left);
        }
        window.display();


    }


}




void Main_Menu::menu(){
int x_button_pos=width/3;
int button_id=0;
arrow_sprite_right.setPosition(x_button_pos-64,70+64);
while(window.isOpen()){

    while(window.pollEvent(event)){
        if(event.type==sf::Event::KeyPressed){
            if(event.key.code==sf::Keyboard::W){
                button_id=(3+button_id-1)%3;
                arrow_sprite_right.setPosition(x_button_pos-64,button_id*height/3+70+64);
            }
            if(event.key.code==sf::Keyboard::S){
                button_id=(button_id+1)%3;
                arrow_sprite_right.setPosition(x_button_pos-64,button_id*height/3+70+64);
            }
            if(event.key.code==sf::Keyboard::Space){
                if(button_id==0)start_game();
                else if(button_id==1){settings_menu();
                arrow_sprite_right.setPosition(x_button_pos-64,2*height/3+70+64);
                }
                else if(button_id==2){
                    window.close();
                    return;
                }

            }




        }

        if(event.type==sf::Event::Closed){
            window.close();
        }
    }
    window.clear(sf::Color(37,19,26,0));
    button_sprite.setPosition(x_button_pos,70);
    window.draw(button_sprite);
    button_sprite.setPosition(x_button_pos,height/3+70);
    window.draw(button_sprite);
    button_sprite.setPosition(x_button_pos,2*height/3+70);
    window.draw(button_sprite);
    window.draw(text[0]);
    window.draw(text[1]);
    window.draw(text[2]);
    window.draw(arrow_sprite_right);
    window.display();


}
}
void Main_Menu::start_game(){
    map_arr=new short int*[settings[1]];
    for(int i=0;i<settings[1];i++)map_arr[i]=new short int[settings[0]];
    for(int i=0;i<settings[1];i++)
    for(int j=0;j<settings[0];j++)map_arr[i][j]=0;
    std::vector<int> room_position;
    std::vector<int> nodes;    
  
    int emerald_quantity=generate_graph(nodes,room_position);
    for(int i=0;i<room_position.size();i++)std::cout<<room_position[i]<<std::endl;

    Game_Logic game_itself(768,768,map_arr,room_position,emerald_quantity,room_position[0]+1,room_position[1]+1,&window,settings);

    for(int i=0;i<settings[1];i++)delete[] map_arr[i];
    delete[] map_arr;





}



//map creation functions-----------------------------------------------------
//---------------------------------------------------------------------------
void Main_Menu::walk_over_map(int start_x,int start_y){
    std::set<std::pair<int,int>> queue;
    queue.insert(std::pair<int,int>{start_x,start_y});
    while(1){
        std::cout<<queue.size()<<std::endl;
        if(queue.size()==0)break;
        std::pair<int,int> temp=*(queue.begin());
        queue.erase(queue.begin());
        visited[temp.second][temp.first]=1;
        if(temp.first>0)if(visited[temp.second][temp.first-1]==0 && map_arr[temp.second][temp.first-1]==1)queue.insert(std::pair<int,int>{temp.first-1,temp.second});
        if(temp.first<settings[0]-1)if(visited[temp.second][temp.first+1]==0 && map_arr[temp.second][temp.first+1]==1)queue.insert(std::pair<int,int>{temp.first+1,temp.second});
        if(temp.second>0) if(visited[temp.second-1][temp.first]==0 && map_arr[temp.second-1][temp.first]==1)queue.insert(std::pair<int,int>{temp.first,temp.second-1});
        if(temp.second<settings[1]-1)if(visited[temp.second+1][temp.first]==0 && map_arr[temp.second+1][temp.first]==1)queue.insert(std::pair<int,int>{temp.first,temp.second+1});



    }
}


//recursive version
/*void Main_Menu::walk_over_map(int curr_x,int curr_y){
    visited[curr_y][curr_x]=1;
    if(curr_x>0)if(visited[curr_y][curr_x-1]==0 && map_arr[curr_y][curr_x-1]==1)walk_over_map(curr_x-1,curr_y);
    if(curr_x<settings[0]-1)if(visited[curr_y][curr_x+1]==0 && map_arr[curr_y][curr_x+1]==1)walk_over_map(curr_x+1,curr_y);
    if(curr_y>0) if(visited[curr_y-1][curr_x]==0 && map_arr[curr_y-1][curr_x]==1)walk_over_map(curr_x,curr_y-1);
    if(curr_y<settings[1]-1)if(visited[curr_y+1][curr_x]==0 && map_arr[curr_y+1][curr_x]==1)walk_over_map(curr_x,curr_y+1);
}*/
void Main_Menu::add_new_hole(int start_x,int start_y,int dest_x,int dest_y){
direction dr_horizontal;//left,right
direction dr_vertical;//up,down
if(start_x<dest_x)dr_horizontal=right;
else dr_horizontal=left;

if(start_y<dest_y)dr_vertical=down;
else dr_vertical=up;

int distance_x=abs(dest_x-start_x);
int distance_y=abs(dest_y-start_y);
bool going_direction;//0 for horizontal,1 for vertical
while(1){
    going_direction=rand()%2;
    if(distance_y==0 && distance_x==0)break;
    
    if (distance_y==0)going_direction=0;
    else if(distance_x==0)going_direction=1;
    
    if(going_direction==0 && dr_horizontal==left)start_x--;
    else if(going_direction==0 && dr_horizontal==right)start_x++;
    else if(going_direction==1 && dr_vertical==up)start_y--;
    else if(going_direction==1 && dr_vertical==down)start_y++;
    map_arr[start_y][start_x]=1;
    if(going_direction==0)distance_x--;
    else distance_y--;
}
}
void Main_Menu::repair(){
while(1){
    visited=new short int*[settings[1]];
    for(int i=0;i<settings[1];i++)visited[i]=new short int[settings[0]];
    for(int i=0;i<settings[1];i++)
    for(int j=0;j<settings[0];j++)visited[i][j]=0;



    int start_x,start_y;
    bool stop=false;
    for(int i=0;i<settings[1];i++){
        for(int j=0;j<settings[0];j++){
            if (map_arr[i][j]==1){
                 start_x=j;
                 start_y=i;
                 stop=true;
                 break;
            }


        }
    if (stop)break;
    }

    stop=false;
    walk_over_map(start_x,start_y);
    for(int i=0;i<settings[1];i++){
        for(int j=0;j<settings[0];j++){
            if(map_arr[i][j]!=visited[i][j]){
                stop=true;
                break;
            }
        }
            if(stop)break;
    }
    bool stop1=false;
    int dest_x;
    int dest_y;
    for(int i=0;i<settings[1];i++){
        for(int j=0;j<settings[0];j++){
            if(visited[i][j]==0 && map_arr[i][j]==1){
                dest_x=j;
                dest_y=i;
                stop1=true;
                break;
            }
        }
            if(stop1)break;
    }
    std::cout<<start_x<<" "<<start_y<<" "<<dest_x<<" "<<dest_y<<std::endl;
    for(int i=0;i<settings[1];i++){
        for(int j=0;j<settings[0];j++){
            std::cout<<visited[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    for(int i=0;i<settings[1];i++)delete visited[i];
    delete visited;
    if (!(stop))return;
    add_new_hole(start_x,start_y,dest_x,dest_y);
    std::cout<<start_x<<" "<<start_y<<" "<<dest_x<<" "<<dest_y<<std::endl;
    for(int i=0;i<settings[1];i++){
        for(int j=0;j<settings[0];j++){
            std::cout<<map_arr[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}    


}

void Main_Menu::polish(){
while(1){
    bool changed=false;
    for(int i=1;i<settings[1]-1;i++){
        for(int j=1;j<settings[0]-1;j++){
            
                if(map_arr[i-1][j]+map_arr[i+1][j]+map_arr[i][j-1]+map_arr[i][j+1]>=3 && map_arr[i][j]==0){
                    map_arr[i][j]=1;
                    changed=true;
                    
                }
        }
    }
    if (!changed)return;
}



}

void Main_Menu::make_walls(){
for(int i=0;i<settings[1];i++)
    {
        for(int j=0;j<settings[0];j++){
            if(map_arr[i][j]==1)continue;
            else if(i==0 && j==0){if (map_arr[i+1][j+1]==1)map_arr[i][j]=2;}
            else if(i==0 && j==settings[0]-1){if (map_arr[i+1][j-1]==1)map_arr[i][j]=4;}
            else if(i==settings[1]-1 && j==0){if (map_arr[i-1][j+1]==1)map_arr[i][j]=7;}
            else if(i==settings[1]-1 && j==settings[0]-1){if (map_arr[i-1][j-1]==1)map_arr[i][j]=6;}
            /*
            else if(i==0 && j==0 && map_arr[i+1][j+1]==1)map_arr[i][j]=2;  
            else if(i==0 && j==23 && map_arr[i+1][j-1]==1)map_arr[i][j]=4;  
            else if(i==23 && j==0 && map_arr[i-1][j+1]==1)map_arr[i][j]=6;  
            else if(i==23 && j==23 && map_arr[i-1][j-1]==1)map_arr[i][j]=7;
            */
           else if(i==0){
            if(map_arr[i+1][j+1]==1)map_arr[i][j]=2;
            else if(map_arr[i+1][j-1]==1)map_arr[i][j]=4;
            if(map_arr[i+1][j]==1)map_arr[i][j]=3;
           }
           else if(i==settings[1]-1){
            if(map_arr[i-1][j]==1)map_arr[i][j]=5;
            else if(map_arr[i-1][j-1]==1)map_arr[i][j]=7;
            else if(map_arr[i-1][j+1]==1)map_arr[i][j]=6;
           }
           else if(j==0){
           if(map_arr[i+1][j+1]==1 && map_arr[i-1][j+1]==1 && map_arr[i][j+1]!=1)map_arr[i][j]=2;
           else if(map_arr[i][j+1]==1)map_arr[i][j]=2;
           else if(map_arr[i-1][j+1]==1)map_arr[i][j]=6; 
           else if(map_arr[i+1][j+1]==1)map_arr[i][j]=2; 
           }
           else if(j==settings[0]-1){
           if(map_arr[i+1][j-1]==1 && map_arr[i-1][j-1]==1)map_arr[i][j]=4;
           else if(map_arr[i-1][j-1]==1)map_arr[i][j]=7; 
           else if(map_arr[i+1][j-1]==1)map_arr[i][j]=4; 
           else if(map_arr[i][j-1]==1)map_arr[i][j]=4;
           }

            else{
                if(map_arr[i+1][j+1]==1 && map_arr[i-1][j+1]==1 && map_arr[i][j+1]!=1 && map_arr[i][j-1]!=1 &&map_arr[i-1][j]!=1 &&map_arr[i+1][j]!=1)map_arr[i][j]=2;
                else if(map_arr[i+1][j-1]==1 && map_arr[i-1][j-1]==1 && map_arr[i][j+1]!=1 && map_arr[i][j-1]!=1 &&map_arr[i-1][j]!=1 &&map_arr[i+1][j]!=1)map_arr[i][j]=4;
                else if(map_arr[i+1][j-1]==1 && map_arr[i-1][j-1]==1 && map_arr[i-1][j]==1 && map_arr[i][j-1]!=1 &&map_arr[i][j+1]!=1 &&map_arr[i+1][j]!=1)map_arr[i][j]=9;
                else if(map_arr[i+1][j+1]==1 && map_arr[i-1][j+1]==1 && map_arr[i-1][j]==1 && map_arr[i][j-1]!=1 &&map_arr[i][j+1]!=1 &&map_arr[i+1][j]!=1)map_arr[i][j]=8;
                else if(map_arr[i-1][j]==1 && map_arr[i][j+1]==1)map_arr[i][j]=8;
                else if(map_arr[i-1][j]==1 && map_arr[i][j-1]==1)map_arr[i][j]=9;
                else if(map_arr[i+1][j]==1)map_arr[i][j]=3;
                else if(map_arr[i-1][j]==1)map_arr[i][j]=5;
                else if(map_arr[i+1][j]==1 && map_arr[i][j+1]==1)map_arr[i][j]=2;
                else if(map_arr[i+1][j]==1 && map_arr[i][j-1]==1)map_arr[i][j]=4;
                else if(map_arr[i][j+1]==1)map_arr[i][j]=2;
                else if(map_arr[i][j-1]==1)map_arr[i][j]=4;
                else if(map_arr[i-1][j-1]==1)map_arr[i][j]=7;
                else if(map_arr[i-1][j+1]==1)map_arr[i][j]=6;
                else if(map_arr[i+1][j-1]==1)map_arr[i][j]=4;
                else if(map_arr[i+1][j+1]==1)map_arr[i][j]=2;



            }


        }


    }
    for(int i=0;i<settings[1];i++){
        for(int j=0;j<settings[0];j++){
            if(map_arr[i][j]==1)map_arr[i][j]=0;
            else if(map_arr[i][j]==0)map_arr[i][j]=1;
            
        }

    }





}





int Main_Menu::find_closest(int x,int y,std::vector<int> room_position,std::vector<int> edges){
int min=2147483646;//max int value
int min_id=-1;
bool in_edges=0;
for(int i=0;i<room_position.size()/2;i++){
for(int j=0;j<edges.size();j++){
    if (i==edges[j]){in_edges=1;break;}
}
if(in_edges){in_edges=0;continue;}
if(x!=room_position[i*2] && y!=room_position[i*2+1] && abs(x-room_position[i*2])+abs(y-room_position[i*2+1])<min)
{min=abs(x-room_position[i*2])+abs(y-room_position[i*2+1]);min_id=i;}
}
return min_id;
}



void Main_Menu::set_holes(std::vector<int>& nodes,int node_id,std::vector<int>& room_position,std::vector<int>* edges){
int edge_value_difference[]={0,1,2,0,1};
std::cout<<"nodes:"<<nodes.size()<<std::endl;

int closest_id=find_closest(room_position[2*node_id],room_position[2*node_id+1],room_position,edges[node_id]);
if(closest_id==-1){
    repair();
    polish();
    make_walls();
    return;
}
edges[closest_id].push_back(node_id);
direction dr_horizontal;//left,right
direction dr_vertical;//up,down


int start_x=room_position[2*node_id]+edge_value_difference[nodes[node_id]];
int start_y=room_position[2*node_id+1]+edge_value_difference[nodes[node_id]];
int dest_x=room_position[2*closest_id]+edge_value_difference[nodes[closest_id]];
int dest_y=room_position[2*closest_id+1]+edge_value_difference[nodes[closest_id]];
add_new_hole(start_x,start_y,dest_x,dest_y);

if(node_id+1==nodes.size()){
    repair();
    polish();
    make_walls();
    return;}
set_holes(nodes,node_id+1,room_position,edges);






}





bool Main_Menu::check_if_possible(int curr_x,int curr_y,int room_id){
switch(room_id){
    case 0:
        for(int i=0;i<1;i++){
            for(int j=0;j<1;j++){
                if(map_arr[curr_y+i][curr_x+j]!=0 ||map_arr[curr_y+i][curr_x+j+1]!=0 ||map_arr[curr_y+i][curr_x+j-1]!=0 ||map_arr[curr_y+i+1][curr_x+j]!=0 ||map_arr[curr_y+i-1][curr_x+j]!=0)return 0;
            
            }
        }
        return 1;
        break;

    case 1:
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(map_arr[curr_y+i][curr_x+j]!=0 ||map_arr[curr_y+i][curr_x+j+1]!=0 ||map_arr[curr_y+i][curr_x+j-1]!=0 ||map_arr[curr_y+i+1][curr_x+j]!=0 ||map_arr[curr_y+i-1][curr_x+j]!=0)return 0;
            
            }
        }
        return 1;
        break;
    case 2:
        for(int i=0;i<5;i++){
            for(int j=0;j<5;j++){
                if(map_arr[curr_y+i][curr_x+j]!=0 ||map_arr[curr_y+i][curr_x+j+1]!=0 ||map_arr[curr_y+i][curr_x+j-1]!=0 ||map_arr[curr_y+i+1][curr_x+j]!=0 ||map_arr[curr_y+i-1][curr_x+j]!=0)return 0;
            
            }
        }
        return 1;
        break;
    case 3:
        for(int i=0;i<1;i++){
            for(int j=0;j<1;j++){
                if(map_arr[curr_y+i][curr_x+j]!=0)return 0;
            
            }
        }
        return 1;
        break;

    case 4:
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(map_arr[curr_y+i][curr_x+j]!=0 ||map_arr[curr_y+i][curr_x+j+1]!=0 ||map_arr[curr_y+i][curr_x+j-1]!=0 ||map_arr[curr_y+i+1][curr_x+j]!=0 ||map_arr[curr_y+i-1][curr_x+j]!=0)return 0;
            
            }
        }
        return 1;
        break;
    default:
    return 0;
    break;

}

}



void Main_Menu::write_room(int curr_x,int curr_y,int room_id,int mode){
switch(room_id){
    case 0:
        for(int i=0;i<1;i++){
            for(int j=0;j<1;j++){
                map_arr[curr_y+i][curr_x+j]=mode;
            
            }
        }
        break;

    case 1:
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                map_arr[curr_y+i][curr_x+j]=mode;
            
            }
        }
        break;
    case 2:
        for(int i=0;i<5;i++){
            for(int j=0;j<5;j++){
                map_arr[curr_y+i][curr_x+j]=mode;
            
            }
        }
        break;
    case 3:
        for(int i=0;i<1;i++){
            for(int j=0;j<1;j++){
                map_arr[curr_y+i][curr_x+j]=mode;
            
            }
        }
        break;

    case 4:
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                map_arr[curr_y+i][curr_x+j]=mode;
            
            }
        }
        break;

}
}


void Main_Menu::check_if_any_possible(int left_x,int top_y,int right_x,int bottom_y,int room_id,std::vector<int>& temp){

for(int i=left_x;i<right_x;i++){
    for(int j=top_y;j<bottom_y;j++){
        if (check_if_possible(i,j,room_id)==1){temp.push_back(i);temp.push_back(j);
    }
    
}
}
}












bool Main_Menu::set_rooms(std::vector<int> &nodes,int node_id,std::vector<int> &room_position){
std::vector<int> possibles;
switch(nodes[node_id]){
    case 0:
        check_if_any_possible(1,1,settings[0]-2,settings[1]-2,0,possibles);
        break;
    
    case 1:
        check_if_any_possible(1,1,settings[0]-4,settings[1]-4,1,possibles);
        break;

    case 2:
        check_if_any_possible(1,1,settings[0]-6,settings[1]-6,2,possibles);
        break;

    case 3:
        check_if_any_possible(1,1,settings[0]-4,settings[1]-4,3,possibles);
        break;

    case 4:
        check_if_any_possible(3,3,settings[0]-6,settings[1]-6,4,possibles);
        break;

}
while(1){
std::cout<<node_id<<std::endl;
if(possibles.size()==0)return 0;
int temp=rand()%(possibles.size()/2);
int x=possibles[temp*2];
int y=possibles[temp*2+1];
std::vector<int>::iterator it;
int i=0;
for(it=possibles.begin();i<temp*2+1;i++)++it;
possibles.erase(it);
possibles.erase(--it);
write_room(x,y,nodes[node_id],1);
room_position.push_back(x);
room_position.push_back(y);

if (node_id+1==nodes.size()){
    
    for(int i=0;i<settings[1];i++){
        for(int j=0;j<settings[0];j++)std::cout<<map_arr[i][j]<<" ";
        std::cout<<std::endl;
    }
    std::vector<int>* edges=new std::vector<int>[nodes.size()];
    set_holes(nodes,0,room_position,edges);
    return 1;}
if(set_rooms(nodes,node_id+1,room_position)==1)return 1;
else {write_room(x,y,nodes[node_id],0);room_position.pop_back();room_position.pop_back();}
}
}


int Main_Menu::generate_graph(std::vector<int>& nodes,std::vector<int>& room_position){
    int edge_value[]={1,1,1,3,4};
    int edge_difference[]={0,1,2,0,1};
    int number_of_rooms=settings[2];
    //std::vector<int> nodes;
    int temp=number_of_rooms;
    temp-=edge_value[4];
    nodes.push_back(4);
    while(temp>0){
        int nd=rand()%2+3;
        temp-=edge_value[nd];
        nodes.push_back(nd);
    }
    for(int i=0;i<number_of_rooms;++i)nodes.push_back(rand()%3);
   
   //std::vector<int> room_position;
   set_rooms(nodes,0,room_position);
    for(int i=0;i<settings[1];i++){
        for(int j=0;j<settings[0];j++)std::cout<<map_arr[i][j]<<" ";
        std::cout<<std::endl;
    }
    for(int i=2;i<room_position.size();i++){
        room_position[i]+=edge_difference[nodes[i/2]];

    }
   return number_of_rooms; 



}
//end of map creation functions
//---------------------------------------------------

