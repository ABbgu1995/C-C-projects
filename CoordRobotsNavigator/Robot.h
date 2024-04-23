#include "Map.h"
#ifndef UNTITLED3_ROBOT_H
#define UNTITLED3_ROBOT_H
class Robot{
    Map * map_on;
    int current_col;
    int current_row;
    static int total_robots;
    int serial_number;
    int out_of_range_flag=0;
public:
    // basic functions
    // constructors

    Robot(); // empty or default constructor

    Robot (const Robot& robot); // copy constructor

    ~Robot();

    // help functions

    void setCoordinateLocation(int col, int row);
    bool setMap(Map * map);
    void setOutFlag();
    int getOutFlag() const;
    int getCoordinateCol() const;
    int getCoordinateRow() const;
    int getRobotNumber() const;
    int getMapNumber() const;

    friend ostream& operator<<(ostream& os, const Robot& robot);
    friend class Game;

};
#endif //UNTITLED3_ROBOT_H
