//
// Created by amit on 1/3/23.
//

#ifndef UNTITLED3_GAME_H
#define UNTITLED3_GAME_H


#include "Robot.h"
#include "Map.h"

class Game {
    Robot **array_of_robots;
    Map *map1;
    Map *map2;
    int robot_amount;

public:

    // constructor
    Game(Map &map1, Map &map2);

    // destructor
    ~Game();

    // methods
    bool AddRobot(int map, int col, int row) ;
    bool DeleteRobot(int robot_number);
    bool MoveRobot(int robot_number, char direction);
    Robot ** getRobotArray() const;
    Map& getMap(int map_number) const;
    int getRobotAmount() const;
    Robot * RobotFinder(int robot_number) const;
};


#endif //UNTITLED3_GAME_H
