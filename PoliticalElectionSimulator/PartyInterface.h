#ifndef UNTITLED7_PARTYINTERFACE_H
#define UNTITLED7_PARTYINTERFACE_H

#include "PoliticianInterface.h"
#include <vector>
using namespace std;
// ISubject,
class PartyInterface{
protected:
    // vector of politicians
    std::vector<PoliticianInterface *> m_politicians;
public:
    virtual ~PartyInterface(){
        m_politicians.clear();
    };
    // 3 mains functions in order to implement the observer patter
    virtual void AddPolitician(PoliticianInterface *politician) = 0;//Add
    virtual void removePolitician(PoliticianInterface *politician) = 0;//Remove
    virtual void Notify() = 0;
};

#endif //UNTITLED7_PARTYINTERFACE_H
