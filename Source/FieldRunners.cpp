#include <bits/stdc++.h>
#include "main.hpp"
#include "FieldRunners.hpp"


using namespace std;

typedef vector<Point> PointTable;

FieldRunners::FieldRunners(PointTable _path, EnemyTable _all){
    buildings.resize(ROW);
    for(auto &build : buildings)
        build.resize(COLUMN, NULL);
    request.x = request.y = -1;
    money = STARTING_MONEY;
    heart = STARTING_HEART;
    exception.set(".");
    path = _path;
    frame_counter = 0;
    allEnemies = _all;
    wave_waiting = 0;
    wave_counter = 1;
    is_game_ended = false;
}

void FieldRunners::event_update(Window* window){
    while(window->has_pending_event()){
        Event event = window->poll_for_event();
        switch(event.get_type()){
            case Event::EventType::QUIT:
                free_memory(allEnemies, enemies, buildings);
                exit(0);
                break;
            case Event::EventType::LCLICK:
                request = position_to_coordinate(event.get_mouse_position());
                break;
            case Event::EventType::KEY_PRESS:
            try{
                exception.set(".");
                if(request.x == -1 && request.y == -1)
                    break;
                if(buildings[request.y][request.x] == NULL){
                    build_tower(event, window);
                }
                else{
                    upgrade_tower(event, window);
                }
            }catch(ImportException& ex){
                exception.set(ex.what());
                exception.play(window);
            }
                request.x = request.y = -1;
                break;
        }
    }
}


void FieldRunners::update(Window* window){
    event_update(window);
    add_enemy();
    glue_update();
    move_update();
    target_update();
    shoot_update();
    frame_update();
}

void FieldRunners::glue_update(){
    for(auto &enemy : enemies){
        enemy->glue_update();
    }
}

void FieldRunners::frame_update(){
    frame_counter++;
    if(frame_counter >= MAX_INT)
        frame_counter = 0;
}

void FieldRunners::add_enemy(){
    if(allEnemies.empty() && enemies.empty())
        is_game_ended = true;

    if(is_game_ended)
        return;

    if(wave_waiting > 0){
        wave_waiting -= DELAY;
        return;
    }

    if(frame_counter % ENEMY_COOLDOWN == 0){
        next_enemy();
    }
}

void FieldRunners::next_enemy(){
    if(!allEnemies.empty() && !allEnemies[0].empty()){
        enemies.push_back(allEnemies[0][0]);
        allEnemies[0].erase(allEnemies[0].begin());
    }
    else{
        if(!allEnemies.empty()){
            allEnemies.erase(allEnemies.begin());
            update_health();
            wave_waiting = NEXT_WAVE;
            wave_counter++;
        }

        
    }
}

void FieldRunners::update_health(){
    if(!allEnemies[0].empty()){
        for(auto &enemy : allEnemies[0]){
            int init_health = which_health(enemy->get_name());
            int health = (0.9 + 0.1*wave_counter)*init_health;
            enemy->set_health(health);
        }
    }
}

void FieldRunners::draw(Window* window){
    window->clear();
    window->draw_img("Source/Assets/pics/background.png");
    
    draw_path(path, window);
    show_info(window);
    draw_tower(window);
    draw_enemy(window);
    draw_shot(window);
    if_game_ended(window);
    window->update_screen();
}

void FieldRunners::if_game_ended(Window* window){
    if(is_game_ended){
        window->stop_music();
        
        if(heart > 0)
            window->show_text("You Win", Point(600, 500), GREEN, FONT, 60);
        else
            window->show_text("You lose", Point(600, 500), RED, FONT, 60);
        
        window->update_screen();
        free_memory(allEnemies, enemies, buildings);
        delay(3000);
        exit(0);
    }
}

void FieldRunners::show_info(Window* window){
    window->draw_img("Source/Assets/pics/coin.png", Rectangle(Point(20, 20), 50, 50));
    window->draw_img("Source/Assets/pics/heart.png", Rectangle(Point(140, 20), 50, 50));
    window->show_text(to_string(money), Point(80, 30), YELLOW, FONT);
    window->show_text("Wave: " + to_string(wave_counter), Point(250, 30), BLUE, FONT);
    window->show_text(this->exception.what(), Point(1000, 30), WHITE, FONT);
    window->show_text(to_string(heart), Point(190, 30), RED, FONT);
}

void FieldRunners::move_update(){
    for(int i=0; i< enemies.size(); i++){
        try{
            enemies[i]->move(path);
        }catch(ImportException& ex){
            heart -= enemies[i]->get_heart();
            if(heart <= 0 )
                is_game_ended = true;
            enemies[i] = NULL;
            enemies.erase(enemies.begin() + i);
            i--;
        }
    }
}

void FieldRunners::target_update(){

    for(auto &buildingRow : buildings){
        for(auto &building : buildingRow){
            if(building == NULL)
                continue;
            building->cooldown_counter();
            Enemy* enemy = min_enemy_distance(building);
            if(enemy != NULL){
                building->shoot(enemy);
            }
        }
    }
}

void FieldRunners::shoot_update(){
    for(auto &buildingRow : buildings){
        for(auto &building : buildingRow){
            if(building == NULL)
                continue;
            building->shooting_update(enemies);
        }
    }
}


Enemy* FieldRunners::min_enemy_distance(Building* building){
    int min_distance = numeric_limits<int>::max();
    Enemy* enemy = NULL;
    for(int i=0; i< enemies.size(); i++){
        int distance = calc_distance(building->get_pos(), enemies[i]->get_pos());
        if(distance <= RANGE && distance < min_distance){
            min_distance = distance;
            enemy = enemies[i];
        }
    }
    return enemy;
}




void FieldRunners::draw_shot(Window* window){
    for(auto &buildingRow : buildings){
        for(auto &building : buildingRow){
            if(building == NULL)
                continue;
            building->draw_shot(window);
        }
    }
}
void FieldRunners::draw_enemy(Window* window){
    for(int i=0; i< enemies.size(); i++){
        int reward = enemies[i]->can_get_reward();
        if(!reward){
            enemies[i]->draw(window, frame_counter%ENEMY_RENDER);
            continue;
        }
        money += reward;
        enemies[i] = NULL;
        enemies.erase(enemies.begin() + i);
    }
}

void FieldRunners::draw_tower(Window* window){
    for(int i=0; i< buildings.size(); i++){
        for(int j=0; j< buildings[i].size(); j++){
            if(buildings[i][j] == NULL)
                continue;
            buildings[i][j]->draw_tower(window, Point(j, i));
        }
    }
}
void FieldRunners::build_tower(Event& event, Window* window){
    switch(event.get_pressed_key()){
        case 'g':{
            Gatling* gatling = new Gatling(coordinate_to_position(request));
            put_into_buildings(window, gatling);
            break;
        }
        case 'm':{
            Missile* missile = new Missile(coordinate_to_position(request));
            put_into_buildings(window, missile);
            break;
        }
        case 't':{
            Tesla* tesla = new Tesla(coordinate_to_position(request));
            put_into_buildings(window, tesla);
            break;
        }
        case 'l':{
            Glue* glue = new Glue(coordinate_to_position(request));
            put_into_buildings(window, glue);
            break;
        }
    }
}

void FieldRunners::put_into_buildings(Window* window, Building* building){
    if(money - building->get_cost() < 0){
        delete building;
        throw ImportException(ERROR1);
    }
    buildings[request.y][request.x] = building;
    money -= building->get_cost();
    window->play_sound_effect(PUT_OBJECT);
            
}

void FieldRunners::upgrade_tower(Event& event, Window* window){
    Building* buildng = buildings[request.y][request.x];
    switch(event.get_pressed_key()){
        case 'u':
            if(money - buildng->get_upgrade_cost() < 0)
                throw ImportException(ERROR1);
            buildng->upgrade_tower();
            money -= buildng->get_upgrade_cost();
            window->play_sound_effect(PUT_OBJECT);
            break;
    }
}