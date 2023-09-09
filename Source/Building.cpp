#include <bits/stdc++.h>
#include "main.hpp"
#include "ImportException.hpp"
#include "Building.hpp"

using namespace std;


Building::Building(string _name, int _damage, int _delay, int _cost, int _upgrade_cost,
    int _upgrade_damage, Point _position){
        damage = _damage; delay = _delay; cost = _cost; upgrade_cost = _upgrade_cost;
        upgrade_damage = _upgrade_damage; range = RANGE, level = FIRST_LEVEL, cooldown = delay,
        position = _position; name = _name;
    }


void Building::shoot(Enemy* enemy){
    if(cooldown >= delay){
        Point realPos = Point(position.x + SQUARE_WIDTH/2, position.y + SQUARE_WIDTH/2);
        shooting.push_back(Shooting(realPos, enemy));
        cooldown = 0;
    }
}
void Building::shooting_update(EnemeyVec enemies){     
    for(int i=0; i< shooting.size(); i++){
        if(!shooting[i].update()){
            this->special_building(enemies, shooting[i].get_enemy()->get_pos());
            if(if_stubborn(shooting[i].get_enemy()))
                shooting[i].get_enemy()->give_damage(damage);
            shooting.erase(shooting.begin() + i);
        }
    }
}

bool Building::if_stubborn(Enemy* enemy){
    if(name == "Missile")
        return false;
    if(enemy->get_name() == "Stubborn"){
        if(name == "Glue" || name == "Gatling"){
            return false;
        }
    }
    return true;
}

void Missile::special_building(EnemeyVec enemies, Point target){
    EnemeyVec inRange = in_range_enemy(enemies, target, 50);
    for(auto &enemy : inRange){
        enemy->give_damage(damage);
    }
}   

void Glue::special_building(EnemeyVec enemies, Point target){
    EnemeyVec inRange = in_range_enemy(enemies, target, 30);
    for(auto &enemy : inRange){
        if(enemy->get_name() != "Stubborn")
        enemy->glue_affect(affect_percentage, affect_duration);
    }
}

void Building::upgrade_tower(){
    if(level >= 3)
        throw ImportException(ERROR2);
    damage += upgrade_damage;
    level++;
}

void Glue::upgrade_tower(){
    affect_duration += duration_upgrade;
    affect_percentage += percentage_upgrade;
}

void Building::cooldown_counter() {
    if(cooldown < delay){
        cooldown += DELAY;
    }
}

void Gatling::draw_tower(Window* window, Point point){
    string filename = "Source/Assets/towers/gattling" + to_string(level) + ".png";
    draw_tower_img(window, filename, point);
}
void Gatling::draw_shot(Window* window){
    for(auto &shot : shooting){
        window->fill_circle(shot.get_pos_shot(), SHOT_RADIUS, BLUE);
    }
}

void Missile::draw_tower(Window* window, Point point){
    string filename = "Source/Assets/towers/missile" + to_string(level) + ".png";
    draw_tower_img(window, filename, point);
}
void Missile::draw_shot(Window* window){
    for(auto &shot : shooting){
        window->fill_circle(shot.get_pos_shot(), SHOT_RADIUS, RED);
    }
}

void Tesla::draw_tower(Window* window, Point point){
    string filename = "Source/Assets/towers/tesla" + to_string(level) + ".png";
    Point position = coordinate_to_position(point);
    window->draw_img(filename, Rectangle(position.x-7, position.y-10, TOWER_SIZE-15, TOWER_SIZE-15));
}
void Tesla::draw_shot(Window* window){
    for(auto &shot : shooting){
        window->fill_circle(shot.get_pos_shot(), SHOT_RADIUS, CYAN);
    }
}

void Glue::draw_tower(Window* window, Point point){
    string filename = "Source/Assets/towers/glue" + to_string(level) + ".png";
    draw_tower_img(window, filename, point);
}
void Glue::draw_shot(Window* window){
    for(auto &shot : shooting){
        window->fill_circle(shot.get_pos_shot(), SHOT_RADIUS, YELLOW);
    }
}