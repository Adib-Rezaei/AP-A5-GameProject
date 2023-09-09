#include <bits/stdc++.h>
#include "main.hpp"
#include "FieldRunners.hpp"


using namespace std;

typedef vector<Point> PointTable;
typedef vector<Enemy*> EnemeyVec;
typedef vector<EnemeyVec> EnemyTable;
typedef vector<vector<Building*>> BuildingTable;

int calc_distance(Point src, Point des){
    return (int)sqrt(pow((des.y - src.y), 2) + pow((des.x - src.x), 2));
}
void draw_path(PointTable path, Window* window){
    for(auto position : path){
        position = coordinate_to_position(position);
        window->draw_rect(Rectangle(position, SQUARE_WIDTH, SQUARE_WIDTH), RED, 1);
    }
}
void draw_tower_img(Window* window, string filename, Point point){
    Point position = coordinate_to_position(point);
    window->draw_img(filename, Rectangle(position.x-15, position.y-15, TOWER_SIZE, TOWER_SIZE));
}

EnemyTable get_rand_troops(){
    EnemyTable troops;
    string line;

    while(getline(cin, line)){
        EnemeyVec enemy = initialize_enemy(line);
        EnemeyVec random_enemy = rand_enemy(enemy);
        troops.push_back(random_enemy);
    }
    return troops;
}

EnemeyVec rand_enemy(EnemeyVec enemy){
    srand(time(NULL));
    for(int i=0; i< MAX_SWAP; i++){
        int j = rand() % enemy.size();
        int k = rand() % enemy.size();
        swap(enemy[j], enemy[k]);
    }
    return enemy;
}

EnemeyVec initialize_enemy(string line){
    EnemeyVec enemies;
    
    int num;
    stringstream sstream(line);
    for(int i=0; i< 4; i++){
        sstream >> num;
        for(int j=0; j< num; j++){
            which_enemy(enemies, i);
        }
    }
    return enemies;
}

void free_memory(EnemyTable &allEnemies, EnemeyVec &enemies, BuildingTable &buildings){
    for(auto &enemyRow : allEnemies)
        for(auto &enemy : enemyRow)
            delete enemy;

    for(auto &enemy : enemies)
        delete enemy;
        
    for(auto &buildingRow : buildings)
        for(auto &building : buildingRow)
            delete building;
}

int which_health(string name){
    if(name == "Runner")
        return RUNNER_HEALTH;
    else if(name == "Stubborn")
        return STUBBORN_HEALTH;
    else if(name == "SuperTrooper")
        return SUPERTROOPER_HEALTH;
    else
        return SCRAMBLER_HELATH;
}

void which_enemy(EnemeyVec &enemies, int which){
    switch(which){
        case 0:{
            Runner* runner = new Runner();
            enemies.push_back(runner);
            break;
        }
        case 1:{
            Stubborn* stubborn = new Stubborn();
            enemies.push_back(stubborn);
            break;
        }
        case 2:{
            SuperTrooper* superTrooper = new SuperTrooper();
            enemies.push_back(superTrooper);
            break;
        }
        case 3:{
            Scrambler* scrambler = new Scrambler();
            enemies.push_back(scrambler);
            break;
        }
    }
}

PointTable get_path(){
    PointTable path;
    vector<int> vec;
    string line, num;

    getline(cin, line);
    stringstream sstream(line);

    while(sstream >> num){
        vec.push_back(stoi(num));
    }
    for(int i=1; i< vec.size(); i += 2){
        path.push_back(Point(vec[i-1], vec[i]));
    }
    return path;
}
Point next_position(Point position, PointTable path){
    if(position.x == -1){
        return Point(-1, -1);
    }

    position = position_to_coordinate(position);

    for(int i=0; i< path.size()-1; i++){
        if(path[i].x == position.x && path[i].y == position.y){
            return coordinate_to_position(path[i+1]);
        }
    }

    return Point(WIDTH, HEIGHT);
}
void draw_enemy(Window* window, string filename, int health, Point pos){
    int width = (double)health/250 * 20;
    window->fill_rect(Rectangle(pos.x, pos.y-10, width, 5), RED);
    window->draw_img(filename, Rectangle(pos, CHARACTER_SIZE, CHARACTER_SIZE));
}

Point coordinate_to_position(Point coordinate){
    int x = coordinate.x*SQUARE_WIDTH + ORIGIN_COORDINATE_X;
    int y = coordinate.y*SQUARE_WIDTH + ORIGIN_COORDINATE_Y;
    return Point(x, y); 
}

Point position_to_coordinate(Point position){
    int x = (position.x - ORIGIN_COORDINATE_X)/SQUARE_WIDTH;
    int y = (position.y - ORIGIN_COORDINATE_Y)/SQUARE_WIDTH;
    return Point(x, y);
}


EnemeyVec in_range_enemy(EnemeyVec enemies, Point shot_position, int range){
    EnemeyVec in_range;
    for(int i=0; i< enemies.size(); i++){
        int distance = calc_distance(shot_position, enemies[i]->get_pos());
        if(distance <= range){
            in_range.push_back(enemies[i]);
        }
    }
    return in_range;
}