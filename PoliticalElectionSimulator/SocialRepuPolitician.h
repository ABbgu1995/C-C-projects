
#ifndef UNTITLED7_SOCIALREPUPOLITICIAN_H
#define UNTITLED7_SOCIALREPUPOLITICIAN_H
#include "Politician.h"
#include "RepuPolitician.h"
#include <iostream>
using namespace std;
class SocialRepuPolitician: public RepuPolitician{
private:
public:
    SocialRepuPolitician(string first_name, string last_name, int id, int power, Party * party);
    SocialRepuPolitician();
    ~SocialRepuPolitician();
    void printDetails() const;
    int getPower() const override;

};

#endif //UNTITLED7_SOCIALREPUPOLITICIAN_H
