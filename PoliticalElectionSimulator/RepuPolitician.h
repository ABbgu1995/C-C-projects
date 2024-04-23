
#ifndef UNTITLED7_REPUPOLITICIAN_H
#define UNTITLED7_REPUPOLITICIAN_H

#include "Politician.h"


class RepuPolitician: public Politician{
private:
public:
    RepuPolitician(string first_name, string last_name, int id, int power, Party * party);
    RepuPolitician();
    ~RepuPolitician();
    void printDetails()const=0;
    bool canBeInParty(Party * party) override{
        return party->checkInsertRepo();
    }

};


#endif //UNTITLED7_REPUPOLITICIAN_H
