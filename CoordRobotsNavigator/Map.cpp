#include "Map.h"
#include <iostream>
#include <string>
using namespace std;


Map::Map(){
    // constructor to of map class
    for (auto & i : this->map_matrix){
        for (int & j : i)
            j=0;
    }
}

Map::Map(const Map &other){
    // copy constructor of map class
    // the function receive a reference to map and copy
    setMapNumber(other.map_number);
    for(int i=0; i<7; i++)
    {
        for (int j=0; j<7; j++)
            this->setCoordinate(i,j,other.getCoordinate(i,j));
    }
}

int Map::validCoordinate(int col, int row) const {
    // the function verify if the coordinate are valid and by using numbers, the function return the reason if no valid
    // 0 -> the location is valid
    // 1 -> the location is out of range
    // 2 -> the location has a wall
    if ( row >= 7 || row < 0) return 1;
    if (col >= 7 || col < 0) return 1;

    if (this->getCoordinate(col, row)==1) return 2;
    return 0;

}

void Map::setMapNumber(int map_number_arg){
    // the function set the map number
    this->map_number=map_number_arg;
}

Map::~Map() {}

void Map::setCoordinate(int col, int row, int value){
    // the function set the value of a cell within the map
    // the function receive index within a map and a value to put in
    this->map_matrix[row][col]=value;

}

int Map::getCoordinate(int col, int row) const {
    // the function return the value of the given cell base on col and row

    return this->map_matrix[row][col];
}
Map& Map::operator=(const Map &mSource)  {
    // the function receive a reference to map and complete the = operator
    if (this == &mSource) return *this;
    for (int i=0; i<7; i++)
    {
        for (int j=0; j<7 ; j++)
            this->map_matrix[i][j]=mSource.map_matrix[i][j];
    }
    return *this;
}

Map Map::operator+(const Map &map_source)const{
    // the function receive a reference to map and complete the + operator
    if (this == &map_source) return *this;
    Map new_map;

    for (int i=0; i<7; i++)
    {
        for (int j=0; j<7 ; j++)
            if (this->getCoordinate(j, i) == 0 and map_source.getCoordinate(j, i) == 0)
                new_map.setCoordinate(j, i, 0);
            else
                new_map.setCoordinate(j, i, 1);
    }
    return new_map;
}

const Map& Map::operator+=(const Map &map_source) {
    // the function receive a reference to map and complete the += operator
    //if (this == &map_source) return *this;
    for (int i=0; i<7; i++)
    {
        for (int j=0; j<7 ; j++)
            if (this->getCoordinate(j,i) == 0 and map_source.getCoordinate(j, i) == 0)
                this->setCoordinate(j,i, 0);
            else
                this->setCoordinate(j, i, 1);
    }
    return *this;
}
bool Map::operator==(const Map& map_source) const{
    // the function receive a reference to map and complete the == operator
    if (this == &map_source) return true;
    for (int i=0; i<7; i++)
    {
        for (int j=0; j<7 ; j++)
            if(this->getCoordinate(j,i)!= map_source.getCoordinate(j,i))
                return false;
    }
    return true;

}

int Map::getMapNumber() const{
    return this->map_number;
}
ostream& operator<<(ostream& os, const Map& map_source){
    // the function receive a reference to a map and object of stream and return complete the << operator for map
    for (int i=6; i>=0; i--)
    {
        os << "[";
        for (int j=0; j<6; j++)
            cout << map_source.getCoordinate(j,i) << " ";
        os << map_source.getCoordinate(6,i) << "]\n";
    }
    return os;
}


