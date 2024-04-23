

#include "RepublicanParty.h"
#include <iostream>
using namespace std;

/**
 * Constructor
 * @param party_name the party name, string
 */
RepublicanParty::RepublicanParty(string party_name): Party(party_name){};

/**
 * Destructor
 */
RepublicanParty::~RepublicanParty(){};



/**
 * the function print the republican party details as required
 */
void RepublicanParty::printParty() const {
    if(this->m_chairman== nullptr)
        cout << "Republican Party: " << this->m_party_name << ", chairman:None, Size:" << this->m_politicians.size() << "\n";
    else
        cout << "Republican Party: " << this->m_party_name << ", chairman:" << this->m_chairman->getChairmanName() << ", Size:" << this->m_politicians.size() << "\n";
    for (auto politician : this->m_politicians){
        cout << "\t";
        ((Politician *)politician)->printDetails();
    }
}

bool RepublicanParty::checkInsertDemo() const{
    return false;
}

bool RepublicanParty::checkInsertRepo() const {
    return true;
};