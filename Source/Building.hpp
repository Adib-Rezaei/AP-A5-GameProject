#ifndef _BUILDING_HPP_
#define _BUILDING_HPP_

#include "Shooting.hpp"


class Building {
public:
    Building(std::string _name, int _damage, int _delay, int _cost, int _upgrade_cost,
    int _upgrade_damage, Point _position);


    virtual void draw_tower(Window* window, Point point) = 0;
    virtual void special_building(EnemeyVec enemies, Point target){};

    void upgrade_tower();
    int get_upgrade_cost(){ return upgrade_cost; }
    int get_cost(){ return cost; }
    Point get_pos(){ return position; }
    std::string get_name(){ return name; }

    void shoot(Enemy* enemy);
    void shooting_update(EnemeyVec enemies);
    virtual void draw_shot(Window* window) = 0;
    void cooldown_counter();
    bool if_stubborn(Enemy* enemy);

protected:
    std::string name;
    int damage;
    int delay;
    int cost;
    int upgrade_cost;
    int upgrade_damage;
    int range;
    int level;
    int cooldown;
    Point position;
    std::vector<Shooting> shooting;
};


class Gatling : public Building {
public:
    Gatling(Point pos) : Building("Gatling", 35, 1000, 55, 40, 35, pos){}
    void draw_tower(Window* window, Point point);
    void draw_shot(Window* window);
};

class Missile : public Building {
public:
    Missile(Point pos) : Building("Missile", 75, 3000, 70, 60, 75, pos){}
    void draw_tower(Window* window, Point point);
    void draw_shot(Window* window);
    void special_building(EnemeyVec enemies, Point target);
};

class Tesla : public Building {
public:
    Tesla(Point pos) : Building("Tesla", 700, 1500, 120, 100, 1000, pos){}
    void draw_tower(Window* window, Point point);
    void draw_shot(Window* window);
};

class Glue : public Building {
public:
    Glue(Point pos) : Building("Glue", 0, 2000, 60, 45, 0, pos){
        affect_percentage = 0.40;
        percentage_upgrade = 0.10;
        affect_duration = 2500;
        duration_upgrade = 500;
    }
    void draw_tower(Window* window, Point point);
    void draw_shot(Window* window);
    void special_building(EnemeyVec enemies, Point target);
    void upgrade_tower();

private:
    double affect_percentage;
    double percentage_upgrade;
    int affect_duration;
    int duration_upgrade;
};


#endif