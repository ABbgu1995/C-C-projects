#include "SocialRepuPolitician.h"
/**
 * main constructor
 * @param first_name the first name of the politician, string
 * @param last_name the last name of the politician, string
 * @param id the id of the politician, int
 * @param power the power of the politician, int
 * @param party the party of the politician. Party
 */
SocialRepuPolitician::SocialRepuPolitician(string first_name, string last_name, int id, int power, Party * party ): RepuPolitician(first_name, last_name, id, power, party){};

/**
 * Destructor
 */
SocialRepuPolitician::~SocialRepuPolitician(){};

/**
 * the function print the social republicans information details as required
 */
void SocialRepuPolitician::printDetails() const{
    if(this->m_chairman== nullptr)
        cout << "Republican Person:" << this->first_name  << " " << this->last_name << ", Id:" << this->id << ", Power:" << this->power << ", Type:S, Chairman: None\n";
    else
        cout << "Republican Person:" << this->first_name  << " " << this->last_name << ", Id:" << this->id << ", Power:" << this->power << ", Type:S, Chairman: " << this->getChairmanName() << "\n";
};

/**
 * The function return the power of the politician multiple by 2 because its social type politician
 * @return politician's power multiple by 2
 */
int SocialRepuPolitician::getPower() const{
    return Politician::getPower()*2;
}



