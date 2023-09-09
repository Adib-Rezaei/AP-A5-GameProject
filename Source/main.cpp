#include "../src/rsdl.hpp"
#include <bits/stdc++.h>
#include "main.hpp"
#include "FieldRunners.hpp"


using namespace std;


int main(int argc, char* argv[]){
    Window* window = new Window(WIDTH, HEIGHT, "FieldRunners");
    window->play_music("Music/background.wav");
    
    PointTable path = get_path();
    EnemyTable Troops = get_rand_troops();
    
    FieldRunners fieldRunner(path, Troops);

    while(true){
        fieldRunner.update(window);
        fieldRunner.draw(window);
        delay(DELAY);
    }
}