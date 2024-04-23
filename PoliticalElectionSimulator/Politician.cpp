#include "Politician.h"
#include <iostream>
#include <string>
using namespace std;


/**
 * the main constructor of the politician class
 * @param first_name the first name of the politician, string
 * @param last_name the last name of the politician, string
 * @param id the id of the politician, int
 * @param power the power of the politician, int
 * @param party the current party of the politician, nullptr
 */
Politician::Politician(string first_name, string last_name, int id, int power, Party * party): politician_party(party){
    this->first_name=first_name;
    this->last_name=last_name;
    this->power=power;
    this->id=id;
    this->m_chairman= nullptr;


}
/**
 * coy constructor
 * @param other Politician object to copy
 */
Politician::Politician(const Politician& other){
    this->setParty(other.politician_party);
    this->power=other.power;
    this->first_name=other.first_name;
    this->last_name=other.last_name;
    this->id=other.id;
    this->m_chairman=other.m_chairman;
}

/**
 * Empty constructor
 */
Politician::Politician(){
    this->first_name= nullptr;
    this->last_name=nullptr;
    this->power=0;
    this->id=0;
    this->m_chairman= nullptr;
    this->politician_party= nullptr;
}


/**
 * the function print the politician information
 */
void Politician::printDetails() const{ // implement printDetails of father class because its const
}
/**
 * the function return the name of the current chairman of the politician
 * @return name of the chairman, string
 */
string Politician::getChairmanName() const{
    return this->m_chairman->first_name;
}

/**
 * The function update the chairman for the current politician
 * @param chairman pointer to PoliticianInterface object in order to provide observer pattern implementation
 */
void Politician::updateChairman(PoliticianInterface * chairman){
    this->m_chairman=static_cast<Politician *>(chairman);

};

/**
 * The function return the current power for the politician
 */
int Politician::getPower() const {
    return this->power;
}

/**
 * The function set a party for the politician by set the pointer of the politician_party member
 * @param party pointer to a party, Party
 */
void Politician::setParty(Party *party) {
    if(party!= nullptr) {
        this->politician_party = party;
        this->m_chairman = party->getChairman();
        // add the politician to be subscriber
        this->politician_party->AddPolitician(this);
    }
    else {
        this->m_chairman = nullptr;
        this->politician_party= nullptr;
    }


}
// implement the virtual method of constructor
/**
 * Destructor
 */
Politician::~Politician(){};


