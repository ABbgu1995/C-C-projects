// the Game class is used to manage a game with 2 maps and an array of objects type robot
#include "Game.h"
#include <string>
using namespace std;

Game::Game(Map& map1,Map& map2){
    // constructor method
    // the method receive 2 references to maps
    this->map1=&map1;
    this->map2=&map2;
    this->robot_amount=0;
    this->array_of_robots= nullptr;
};

Game::~Game() {
    // destructor method
    for (int i = 0; i < this->robot_amount; i++) {
        delete this->array_of_robots[i];
        this->array_of_robots[i] = nullptr;
    }
    delete[] this->array_of_robots;
    this->array_of_robots= nullptr;

};

bool Game::AddRobot(int map, int col, int row) {
    // the function add a robot to the game and assign it to the relevant map
    // the map receive map number and location of the robot within the map
    // the function return true if the assign success and false otherwise
    Map *robot_map;
    if (map == 1)
        robot_map = map1;
    if (map == 2)
        robot_map = map2;
    if (robot_map->validCoordinate(col, row)!=0)
        return false;

        // create the robot and adding it to the robots array
    else {
        Robot **temp_array;
        temp_array = new Robot * [this->robot_amount + 1];
        if (!temp_array) return false;
        for (int i = 0; i < this->robot_amount; i++)
            temp_array[i] = this->array_of_robots[i];
        temp_array[this->robot_amount] = new Robot();
        if (!temp_array[this->robot_amount]) {
            delete[]temp_array;
            temp_array= nullptr;
            return false;
        }

        temp_array[this->robot_amount]->setMap(robot_map);
        temp_array[this->robot_amount]->setCoordinateLocation(col, row);
        if(this->robot_amount>0){
            delete[] array_of_robots;
            array_of_robots= nullptr;
        }

        array_of_robots = temp_array;
        this->robot_amount++;
        return true;
    }
}
bool Game::DeleteRobot(int robot_number) {
    // the function delete a robot from the game means the function remove it from its map and from the array of robots
    // the map receive a robot number and return true if the delete action success and false otherwise
    // check if the robot number is valid
    if (robot_number < 0)
        return false;
    // check if the robot number exist
    if (!RobotFinder(robot_number)) return false;
    int j = 0;
    Robot *delete_robot = nullptr;
    Robot **temp;
    if (robot_amount - 1 > 0) {
        temp = new Robot *[robot_amount - 1];
        if (!temp)
            return false;
    }
    else
        temp= nullptr;

    for (int i=0; i< this->robot_amount; i++){
        if (this->array_of_robots[i]->serial_number == robot_number){
            delete_robot = array_of_robots[i];
            continue;
        }
        temp[j] = this->array_of_robots[i];
        j++;
    }
    delete delete_robot;
    delete_robot= nullptr;
    delete[] this->array_of_robots;
    this->array_of_robots= nullptr;

    this->array_of_robots=temp;
    this->robot_amount--;
    return true;




}
bool Game::MoveRobot(int robot_number, char direction) {
    // the function move the robot means its change its location within it's map
    // the function receive a robot number and a char represent direction and return bool if the move action success
    // verify the robot number is valid
    if (robot_number > this->robot_amount || robot_number < 0)
        return false;


    // find the relevant robot base on robot id number
    Robot *found_robot;
    for (int i = 0; i < this->robot_amount; i++) {
        if (this->array_of_robots[i]->serial_number == robot_number) {
            found_robot = array_of_robots[i];
            // check if the robot still connect to map
            if(found_robot->getOutFlag()==1)
                //if(found_robot->getCoordinateCol() == -1 && found_robot -> getCoordinateRow() == -1)
                return false;
            break;
        }
    }


    // change the robot coordinates
    if (direction == 'D') {
        // check the new requested location of the robot and verify the reason of violation in case there is one.
        if(found_robot->map_on->validCoordinate(found_robot->getCoordinateCol(),found_robot->getCoordinateRow() - 1)==2)
            return false;
        if(found_robot->map_on->validCoordinate(found_robot->getCoordinateCol(),found_robot->getCoordinateRow() - 1)==1) {
            found_robot->setCoordinateLocation(-1, -1);
            found_robot->setOutFlag();
        }
        else {
            found_robot->setCoordinateLocation(found_robot->getCoordinateCol(),found_robot->getCoordinateRow() - 1);
            return true;
        }
    }
    if (direction == 'U') {
        // check the new requested location of the robot and verify the reason of violation in case there is one.
        if(found_robot->map_on->validCoordinate(found_robot->getCoordinateCol(),found_robot->getCoordinateRow() + 1)==2)
            return false;
        if(found_robot->map_on->validCoordinate(found_robot->getCoordinateCol(),found_robot->getCoordinateRow() + 1)==1) {
            found_robot->setCoordinateLocation(-1, -1);
            found_robot->setOutFlag();
        }
        else {
            found_robot->setCoordinateLocation(found_robot->getCoordinateCol(),found_robot->getCoordinateRow() + 1);
            return true;
        }
    }

    if (direction == 'L') {
        // check the new requested location of the robot and verify the reason of violation in case there is one.
        if(found_robot->map_on->validCoordinate(found_robot->getCoordinateCol()-1,found_robot->getCoordinateRow())==2)
            return false;
        if(found_robot->map_on->validCoordinate(found_robot->getCoordinateCol()-1,found_robot->getCoordinateRow())==1) {
            found_robot->setCoordinateLocation(-1, -1);
            found_robot->setOutFlag();
        }
        else {
            found_robot->setCoordinateLocation(found_robot->getCoordinateCol()-1,found_robot->getCoordinateRow());
            return true;
        }
    }
    if (direction == 'R') {
        // check the new requested location of the robot and verify the reason of violation in case there is one.
        if(found_robot->map_on->validCoordinate(found_robot->getCoordinateCol()+1,found_robot->getCoordinateRow())==2)
            return false;
        if(found_robot->map_on->validCoordinate(found_robot->getCoordinateCol()+1,found_robot->getCoordinateRow())==1) {
            found_robot->setCoordinateLocation(-1, -1);
            found_robot->setOutFlag();
        }
        else {
            found_robot->setCoordinateLocation(found_robot->getCoordinateCol()+1,found_robot->getCoordinateRow());
            return true;
        }
    }
    return true;
}

Robot * Game::RobotFinder(int robot_number) const{
    // the function return a pointer to robot within the game so function basically find a robot
    // the function receive a robot number and return a its pointer
    Robot *found_robot;
    for (int i = 0; i < this->robot_amount; i++) {
        if (this->array_of_robots[i]->serial_number == robot_number) {
            found_robot = array_of_robots[i];
            return found_robot;
        }
    }
    return nullptr;
}

Robot ** Game::getRobotArray() const {
    // the function return a pointer to the array of robots
    return this->array_of_robots;
}

Map& Game::getMap(int map_number) const{
    // the function return a reference to a map based on the map number

    if(map_number==1)
        return *this->map1;
    else
        return *this->map2;
}

int Game::getRobotAmount() const{
    // the function return the amount of robots within the game
    return this->robot_amount;
}







