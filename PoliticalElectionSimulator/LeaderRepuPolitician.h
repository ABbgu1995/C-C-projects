#ifndef UNTITLED7_LEADERREPUPOLITICIAN_H
#define UNTITLED7_LEADERREPUPOLITICIAN_H
#include "Politician.h"
#include "RepuPolitician.h"
#include <iostream>
using namespace std;
class LeaderRepuPolitician: public RepuPolitician{
private:
public:
    LeaderRepuPolitician(string first_name, string last_name, int id, int power, Party * party);
    LeaderRepuPolitician();
    ~LeaderRepuPolitician();
    void printDetails() const;
    int getPower() const override;


};

#endif //UNTITLED7_LEADERREPUPOLITICIAN_H
