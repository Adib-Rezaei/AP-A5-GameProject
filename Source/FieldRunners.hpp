
#ifndef _FIELDRUNNERS_HPP_
#define _FIELDRUNNERS_HPP_

#include "../src/rsdl.hpp"
#include "Enemy.hpp"
#include "ImportException.hpp"
#include "Shooting.hpp"
#include "Building.hpp"


typedef std::vector<std::vector<Building*>> BuildingTable;
typedef std::vector<Point> PointTable;
typedef std::vector<Enemy*> EnemeyVec;
typedef std::vector<EnemeyVec> EnemyTable;

class FieldRunners {
public:
    FieldRunners(PointTable _path, EnemyTable _all);
    void update(Window* window);
    void draw(Window* window);

private:
    void draw_tower(Window* window);
    void draw_enemy(Window* window);
    void draw_shot(Window* window);
    void show_info(Window* widnow);
    void if_game_ended(Window* window);
    void build_tower(Event& event, Window* window);
    void upgrade_tower(Event& event, Window* window);
    void event_update(Window* widnow);
    void move_update();
    void target_update();
    void shoot_update();
    void add_enemy();
    void frame_update();
    void put_into_buildings(Window* window, Building* building);
    void glue_update();
    void next_enemy();
    void update_health();
    
    Enemy* min_enemy_distance(Building* building);

    BuildingTable buildings;
    EnemeyVec enemies;
    EnemyTable allEnemies;

    PointTable path;
    Point request;
    int money;
    int heart;
    ImportException exception;
    int frame_counter;

    int wave_waiting;
    int wave_counter;
    bool is_game_ended;
};

#endif