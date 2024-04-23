
#ifndef UNTITLED7_SOCIALDEMUPOLITICIAN_H
#define UNTITLED7_SOCIALDEMUPOLITICIAN_H
#include "Politician.h"
#include "DemoPolitician.h"
#include <iostream>
using namespace std;
class SocialDemuPolitician: public DemoPolitician{
private:
public:
    SocialDemuPolitician(string first_name, string last_name, int id, int power, Party * party);
    SocialDemuPolitician();
    ~SocialDemuPolitician();
    void printDetails() const;
    int getPower() const override;
    virtual void setParty(Party * party);

};


#endif //UNTITLED7_SOCIALDEMUPOLITICIAN_H
