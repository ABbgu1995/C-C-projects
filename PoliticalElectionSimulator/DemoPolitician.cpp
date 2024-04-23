#include "DemoPolitician.h"
#include <iostream>
using namespace std;
DemoPolitician::DemoPolitician(string first_name, string last_name, int id, int power, Party * party ): Politician(first_name, last_name, id, power, party){
};



DemoPolitician::~DemoPolitician(){};

/**
 * the function print the politician position, Democratic
 */
void DemoPolitician::printDetails() const{
    cout << "Democratic";
    Politician::printDetails();

};
