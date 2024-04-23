#include "RepuPolitician.h"
#include <iostream>
using namespace std;
RepuPolitician::RepuPolitician(string first_name, string last_name, int id, int power, Party * party ): Politician(first_name, last_name, id, power, party){
};



RepuPolitician::~RepuPolitician(){};

/**
 * the function print the politician position, Democratic
 */
void RepuPolitician::printDetails() const{
    cout << "Democratic";
    Politician::printDetails();

};
