
#ifndef UNTITLED2_MAP_H
#define UNTITLED2_MAP_H
#include <iostream>
using namespace std;

class Map{
private:
    int map_matrix[7][7]{};
    int map_number;


public:

    // constructors
    Map();
    Map(int map_number_arg): map_number(map_number_arg){}; //full constructor
    Map(const Map &mSource); // copy constructor, send by reference

    // destructor
    ~Map();

    // operators methods
    Map& operator=(const Map& map_source);

    Map operator+(const Map &map_source) const;

    const Map& operator+=(const Map &map_source);

    bool operator==(const Map& map_source_2) const;

    friend ostream& operator<<(ostream& os, const Map& map);


    // help functions
    void setCoordinate(int col, int row, int value);
    void setMapNumber(int map_number);
    int getMapNumber() const;

    int getCoordinate(int col, int row) const;
    int validCoordinate(int col, int row) const;



};

#endif //UNTITLED3_MAP_H
