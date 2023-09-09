#include <bits/stdc++.h>
#include "main.hpp"
#include "Enemy.hpp"
#include "Shooting.hpp"
using namespace std;

Shooting::Shooting(Point _pos_building, Enemy* _enemy){
    pos_building = _pos_building;
    enemy = _enemy;    pos_shot = _pos_building;    speed = SHOT_SPEED;
}

bool Shooting::update(){
    if(enemy == NULL){
        delete enemy;
        return false;
    }

    Point enemyPos = Point(enemy->get_pos().x + SQUARE_WIDTH/2, enemy->get_pos().y + SQUARE_WIDTH/2);
    double m;
    if(abs(pos_shot.x - enemyPos.x) < 1){
        if(pos_shot.y > enemyPos.y){
            pos_shot.y -= speed*2;
            if(pos_shot.y < enemyPos.y)
                return false;
        }
        else{
            pos_shot.y += speed*2;
            if(pos_shot.y > enemyPos.y)
                return false;
        }
    }
    else
        m = (pos_shot.y - enemyPos.y)/(pos_shot.x - enemyPos.x);


    if(enemyPos.x > pos_shot.x){
        pos_shot.x += speed;
        if(pos_shot.x > enemyPos.x)
            return false;
    }
    else{
        pos_shot.x += -speed;
        if(pos_shot.x < enemyPos.x)
            return false;
    }

    if(enemyPos.y > pos_shot.y)
        pos_shot.y += (int)abs(m*speed)%20;
    else 
        pos_shot.y += -(int)abs(m*speed)%20;
    
    return true;
}

Enemy* Shooting::get_enemy(){ return enemy; }
