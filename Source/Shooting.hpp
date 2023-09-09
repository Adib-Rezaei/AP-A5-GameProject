#ifndef _SHOOTING_HPP_
#define _SHOOTING_HPP_

#define SHOT_RADIUS 10

#include "../src/rsdl.hpp"
#include "Enemy.hpp"
#include "main.hpp"



class Shooting {
public:
    Shooting(Point _pos_building, Enemy* _enemy);
    bool update();
    Enemy* get_enemy();
    Point get_pos_shot(){ return pos_shot; }

private:
    Point pos_building;
    Point pos_shot;
    int speed;
    Enemy* enemy;
};

#endif