#include "LeaderDemoPolitician.h"
/**
 * main constructor
 * @param first_name the first name of the politician, string
 * @param last_name the last name of the politician, string
 * @param id the id of the politician, int
 * @param power the power of the politician, int
 * @param party the party of the politician. Party
 */
LeaderDemoPolitician::LeaderDemoPolitician(string first_name, string last_name, int id, int power, Party * party ): DemoPolitician(first_name, last_name, id, power, party){};


LeaderDemoPolitician::~LeaderDemoPolitician(){};

/**
 * the function print the leader republican information details as required
 */

void LeaderDemoPolitician::printDetails() const{
    if(this->m_chairman == nullptr)
        cout << "Democratic Person:" << this->first_name  << " " << this->last_name << ", Id:" << this->id << ", Power:" << this->power << ", Type:L, Chairman: None\n";
    else
        cout << "Democratic Person:" << this->first_name  << " " << this->last_name << ", Id:" << this->id << ", Power:" << this->power << ", Type:L, Chairman: " << this->getChairmanName() << "\n";
};

int LeaderDemoPolitician::getPower() const{
    return Politician::getPower();
}

