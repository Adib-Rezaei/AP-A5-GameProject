#include <bits/stdc++.h>
#include "main.hpp"
#include "Enemy.hpp"


using namespace std;

typedef std::vector<Point> PointTable;

Enemy::Enemy(string _name, int _health, int _speed, int _reward, int _heart_cost){
        health = _health;   speed = _speed;
        reward = _reward;   heart_cost = _heart_cost;
        position = DEFAULT_POS; floatMovement = 0; glue_duration = 0; origin_speed = speed; name = _name;
    }
void Enemy::give_damage(int damage){
    health -= damage;
}
int Enemy::can_get_reward(){
    if(health <= 0)
        return reward;
    return 0;
}
void Enemy::glue_affect(double affect_percentage, int duration){
    if(glue_duration > 0)
        return;
    glue_duration = duration;
    speed = origin_speed * (1-affect_percentage);
}

void Enemy::glue_update(){
    if(glue_duration <= 0){
        speed = origin_speed;
    }
    else{
        glue_duration -= DELAY;
    }
}

void Enemy::move(PointTable path){

    next = next_position(position, path);
    if(next.x == -1){
        position = coordinate_to_position(path[0]);
        return;
    }
    
    int travel = speed/FRAME;
    if(floatMovement > 1){
        travel += (int)floatMovement;
        floatMovement -= (int)floatMovement;
    }
    floatMovement += (double)speed/(double)FRAME - (int)speed/FRAME;

    if(next.x == position.x){
        if(next.y > position.y)
            position.y += travel;
        else 
            position.y -= travel;
    }
    else{
        if(next.x > position.x)
            position.x += travel;
        else 
            position.x -= travel;
    }

    if(position.x > coordinate_to_position(path.back()).x){
        throw ImportException("Enemy out of range");
    }
}



void Runner::draw(Window* window, int frame){

    string filename;
    if(frame < ENEMY_RENDER/2)
        filename = "Source/Assets/extra/runner/039.png";
    else 
        filename = "Source/Assets/extra/runner/027.png";


    draw_enemy(window, filename, health, position);
}

void Stubborn::draw(Window* window, int frame){
    string filename;
    if(frame < ENEMY_RENDER/2)
        filename = "Source/Assets/extra/iceRunner/009.png";
    else 
        filename = "Source/Assets/extra/iceRunner/025.png";
        
    draw_enemy(window, filename, health, position);
}

void SuperTrooper::draw(Window* window, int frame){
    string filename;
    if(frame < ENEMY_RENDER/2)
        filename = "Source/Assets/extra/heavyRunner/031.png";
    else 
        filename = "Source/Assets/extra/heavyRunner/040.png";
        
    draw_enemy(window, filename, health, position);
}

void Scrambler::draw(Window* window, int frame){
    string filename;
    if(frame < ENEMY_RENDER/2)
        filename = "Source/Assets/extra/bike/009.png";
    else 
        filename = "Source/Assets/extra/bike/010.png";
        
    draw_enemy(window, filename, health, position);
}