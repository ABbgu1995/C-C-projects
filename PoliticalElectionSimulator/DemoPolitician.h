#ifndef UNTITLED7_DEMOPOLITICIAN_H
#define UNTITLED7_DEMOPOLITICIAN_H
#include "Politician.h"


class DemoPolitician: public Politician{
private:
public:
    DemoPolitician(string first_name, string last_name, int id, int power, Party * party);
    DemoPolitician();
    ~DemoPolitician();
    void printDetails()const=0;
    bool canBeInParty(Party * party) override{
        return party->checkInsertDemo();
    }

};


#endif //UNTITLED7_DEMOPOLITICIAN_H
