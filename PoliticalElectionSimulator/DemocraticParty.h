
#ifndef UNTITLED7_DEMOCRATICPARTY_H
#define UNTITLED7_DEMOCRATICPARTY_H
#include "Party.h"
class DemocraticParty: public Party{
private:
public:
    DemocraticParty(string party_name);
    virtual ~DemocraticParty();
    virtual void printParty() const;
    virtual bool checkInsertDemo()const;
    virtual bool checkInsertRepo()const;
};

#endif //UNTITLED7_DEMOCRATICPARTY_H
