//
// Created by amit on 1/12/23.
//

#ifndef UNTITLED7_LEADERDEMOPOLITICIAN_H
#define UNTITLED7_LEADERDEMOPOLITICIAN_H
#include "Politician.h"
#include "DemoPolitician.h"
#include <iostream>
using namespace std;
class LeaderDemoPolitician: public DemoPolitician{
private:
public:
    LeaderDemoPolitician(string first_name, string last_name, int id, int power, Party * party);
    LeaderDemoPolitician();
    ~LeaderDemoPolitician();
    void printDetails() const;
    int getPower() const override;


};
#endif //UNTITLED7_LEADERDEMOPOLITICIAN_H
