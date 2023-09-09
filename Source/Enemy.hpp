#ifndef _ENEMY_HPP_
#define _ENEMY_HPP_

#include <bits/stdc++.h>

typedef std::vector<Point> PointTable;


class Enemy {
public:
    Enemy(std::string _name, int _health, int _speed, int _reward, int _heart_cost);

    void move(PointTable path);
    virtual void draw(Window* window, int frame) = 0;
    Point get_pos(){ return position; }
    void give_damage(int damage);
    int can_get_reward();
    int get_heart(){ return heart_cost; }
    int get_health(){ return health; }
    void set_health(int _health){ health = _health; }
    std::string get_name(){ return name; }

    void glue_affect(double affect_percentage, int duration);
    void glue_update();

protected:
    std::string name;
    int health;
    int speed;
    int reward;
    int heart_cost;
    double floatMovement;
    int glue_duration;
    int origin_speed;
    Point position;
    Point next;
};

class Runner : public Enemy{
public:
    Runner() : Enemy("Runner", 250, 50, 6, 1){}
    
    void draw(Window* window, int frame);
};

class Stubborn : public Enemy{
public:
    Stubborn() : Enemy("Stubborn", 400, 30, 10, 4){}

    void draw(Window* window, int frame);
};

class SuperTrooper : public Enemy{
public:
    SuperTrooper() : Enemy("SuperTrooper", 500, 25, 8, 4){}

    void draw(Window* window, int frame);
};

class Scrambler: public Enemy{
public: 
    Scrambler() : Enemy("Scrambler", 100, 90, 4, 2){}

    void draw(Window* window, int frame);
};

#endif