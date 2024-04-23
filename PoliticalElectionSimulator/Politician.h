#ifndef UNTITLED7_POLITICIAN_H
#define UNTITLED7_POLITICIAN_H


#include "PoliticianInterface.h"
#include <string>
using namespace std;

class Party;
// Observer
class Politician: public PoliticianInterface{
protected:
    string first_name;
    string last_name;
    int id;
    Politician * m_chairman;
    Party * politician_party;
    int power;
    //
public:
    Politician(string first_name, string last_name, int id, int power, Party * party); // main constr
    Politician();
    Politician(const Politician& other);
    virtual ~Politician();
    string getChairmanName() const;
    virtual void printDetails() const;
    virtual int getPower() const;
    virtual void updateChairman(PoliticianInterface * chairman);
    void setParty(Party * party);
    virtual bool canBeInParty(Party * party)=0;
    friend class Party;
    friend class PoliticalSys;
};
#include "Party.h"
#endif //UNTITLED7_POLITICIAN_H
