#include "DemocraticParty.h"
#include <iostream>
using namespace std;

/**
 * Constructor
 * @param party_name party name, stirng
 */
DemocraticParty::DemocraticParty(string party_name): Party(party_name){};

/**
 * Destructor
 */
DemocraticParty::~DemocraticParty(){};

/**
 * the function print the democratic party details as required
 */
void DemocraticParty::printParty() const {
    if(this->m_chairman== nullptr)
        cout << "Democrat Party: " << this->m_party_name << ", chairman:None, Size:" << this->m_politicians.size() << "\n";
    else
        cout << "Democrat Party: " << this->m_party_name << ", chairman:" << this->m_chairman->getChairmanName() << ", Size:" << this->m_politicians.size() << "\n";
    for (auto politician : this->m_politicians){
        cout << "\t";
        ((Politician *)politician)->printDetails();
    }
}
bool DemocraticParty::checkInsertDemo() const{
    return true;
}
bool DemocraticParty::checkInsertRepo() const {
    return false;
}