#include "SocialDemuPolitician.h"
/**
 * main constructor
 * @param first_name the first name of the politician, string
 * @param last_name the last name of the politician, string
 * @param id the id of the politician, int
 * @param power the power of the politician, int
 * @param party the party of the politician. Party
 */
SocialDemuPolitician::SocialDemuPolitician(string first_name, string last_name, int id, int power, Party * party ): DemoPolitician(first_name, last_name, id, power, party){
};



void SocialDemuPolitician::setParty(Party * party){
    Politician::setParty(party);
}

/**
 * Destructor
 */
SocialDemuPolitician::~SocialDemuPolitician(){};

/**
 * the function print the social democratic information details as required
 */
void SocialDemuPolitician::printDetails() const{
    if(this->m_chairman== nullptr)
        cout << "Democratic Person:" << this->first_name  << " " << this->last_name << ", Id:" << this->id << ", Power:" << this->power << ", Type:S, Chairman: None\n";
    else
        cout << "Democratic Person:" << this->first_name  << " " << this->last_name << ", Id:" << this->id << ", Power:" << this->power << ", Type:S, Chairman: " << this->getChairmanName() << "\n";

};

/** The function return the power of the politician multiple by 2 because its social type politician
* @return politician's power multiple by 2
*/
int SocialDemuPolitician::getPower() const{
    return Politician::getPower()*2;
}

