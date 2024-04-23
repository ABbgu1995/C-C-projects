#ifndef UNTITLED7_PARTY_H
#define UNTITLED7_PARTY_H
#include<string>
#include <vector>
#include "PartyInterface.h"
using namespace std;
// abstract party
class Politician;
//Subject
class Party: public PartyInterface{
protected:
    string m_party_name;
    Politician * m_chairman;
public:
    Party(string party_name); // main constr
    Party(Party &party);
    virtual ~Party();
    void AddPolitician(PoliticianInterface *politician);
    void removePolitician(PoliticianInterface *politician);
    void Notify();
    void election();
    int powerElection() const;
    virtual void printParty()const=0;
    virtual bool checkInsertDemo() const=0;
    virtual bool checkInsertRepo() const=0;
    Politician * getChairman() const;
    friend class PoliticalSys;

};
#include "Politician.h"

#endif //UNTITLED7_PARTY_H
