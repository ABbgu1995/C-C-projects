#include "Robot.h"
#include "Map.h"
#include <iostream>
#include <string>
using namespace std;

Robot::Robot():current_col(-1),current_row(-1),map_on(nullptr) {
    // constructor for robot class which init default values
    this->serial_number = ++total_robots;
}

Robot::Robot (const Robot& other) {
    // constructor for robot class
    this->setCoordinateLocation(other.current_col,other.current_row);
    this->setMap(other.map_on);
}

bool Robot::setMap(Map * map) {
    // the function set the map to a robot object using pointers
    // the function receive pointer to map and return a bool value
    if(map== nullptr) return false;
    this->map_on=map;
    return true;
}

void Robot::setCoordinateLocation(int col, int row) {
    // the function set the location of the robot within the map
    // the function return location by col and row
    this->current_col=col;
    this->current_row=row;

}

int Robot::getCoordinateCol() const {
    // the function return the col value of the robot
    return this->current_col;
}

int Robot::getCoordinateRow() const {
    // the function return the row value of the robot
    return this->current_row;
}

int Robot::getRobotNumber() const{
    // the function return the robot number of the robot
    return this->serial_number;
}


Robot::~Robot() {
    this->map_on= nullptr;
}

int Robot::getMapNumber() const{
    // the function return the map number of the robot
    return this->map_on->getMapNumber();
}
ostream& operator<<(ostream& os, const Robot& robot){
    // the function return the robot parameters as os stream file
    if(robot.out_of_range_flag==0) {
        os << "Robot: " << robot.serial_number << " Map: " << robot.map_on->getMapNumber() << " GPS: "
           << robot.getCoordinateCol() << "," << robot.getCoordinateRow() << "\n";
        return os;
    }
    return os;
}

void Robot::setOutFlag(){
    // the function set a flag which means that the robot is out of map borders and lost it signal connection
    this->out_of_range_flag=1;
}
int Robot::getOutFlag()const{
    // the function return the out of range flag of the current robot
    return this->out_of_range_flag;
};