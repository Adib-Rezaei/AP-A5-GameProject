#ifndef _MAIN_HPP_
#define _MAIN_HPP_


#define WIDTH 1365
#define HEIGHT 1024
#define ROW 11
#define COLUMN 19
#define ORIGIN_COORDINATE_X 120
#define ORIGIN_COORDINATE_Y 175
#define SQUARE_WIDTH 60
#define STARTING_MONEY 200
#define STARTING_HEART 20
#define FIRST_LEVEL 1
#define FONT "Source/Assets/fonts/MagicDreams.ttf"
#define ERROR1 "Log: Can't do that, Not enough money!"
#define ERROR2 "Log: Can't do that, Tower at max level!"
#define PUT_OBJECT "Music/Object.wav"
#define DEFAULT_POS Point(-1, -1)
#define DELAY 50
#define FRAME 20
#define OUT_OF_FIELD 1300
#define CHARACTER_SIZE 40
#define TOWER_SIZE 90
#define RANGE 150
#define SHOT_SPEED 10
#define SHOT_RADIUS 10
#define ENEMY_COOLDOWN 25
#define MAX_SWAP 20
#define ENEMY_RENDER 10
#define MAX_INT 1e9
#define NEXT_WAVE 3000
#define RUNNER_HEALTH 250
#define STUBBORN_HEALTH 400
#define SUPERTROOPER_HEALTH 500
#define SCRAMBLER_HELATH 100

#include "../src/rsdl.hpp"
#include "FieldRunners.hpp"


void draw_tower_img(Window* window, std::string filename, Point point);
EnemyTable get_rand_troops();
PointTable get_path();
Point next_position(Point position, PointTable path);
EnemeyVec initialize_enemy(std::string line);
void draw_enemy(Window* window, std::string filename, int health, Point pos);
Point coordinate_to_position(Point coordinate);
Point position_to_coordinate(Point position);
int calc_distance(Point src, Point des);
void draw_path(PointTable path, Window* window);
void which_enemy(EnemeyVec &enemies, int which);
EnemeyVec rand_enemy(EnemeyVec enemy);
EnemeyVec in_range_enemy(EnemeyVec enemies, Point shot_position, int range);
int which_health(std::string name);
void free_memory(EnemyTable &allEnemies, EnemeyVec &enemies, BuildingTable &buildings);

#endif