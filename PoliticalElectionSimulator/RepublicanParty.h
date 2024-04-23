
#ifndef UNTITLED7_REPUBLICANPARTY_H
#define UNTITLED7_REPUBLICANPARTY_H
#include "Party.h"
#include <iostream>
using namespace std;
class RepublicanParty: public Party {
private:
public:
    RepublicanParty(string party_name);

    virtual ~RepublicanParty();

    virtual void printParty() const;

    virtual bool checkInsertDemo() const;

    virtual bool checkInsertRepo() const;
};

#endif //UNTITLED7_REPUBLICANPARTY_H
