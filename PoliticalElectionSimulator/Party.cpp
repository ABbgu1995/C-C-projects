
#include "Party.h"
#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;

// handle inheritance section
/**
 * main constructor
 * @param party_name the name of new party, string
 */
Party::Party(string party_name): m_party_name(party_name){
    this->m_chairman= nullptr;
};
Party::Party(Party &party){
    this->m_chairman=party.m_chairman;
    this->m_party_name=party.m_party_name;
}
/**
 * Destructor
 */
Party::~Party(){}

/**
 * Generic print party name
 */
void Party::printParty() const {
    cout << this->m_party_name << " ";
}

/**
 * The function add a politician to the current party
 * @param politician the politician should add, Politician
 */
// handle inheritance section
void Party::AddPolitician(PoliticianInterface *politician){
    this->m_politicians.push_back(politician);

}

/**
 * The function remove politician from the party vector of politicians
 * @param politician the politician to remove from the party, Politician
 */
void Party::removePolitician(PoliticianInterface *politician){
    auto it = std::find(this->m_politicians.begin(), this->m_politicians.end(), politician);
    if (it !=this->m_politicians.end()) {
        // if the removed politician is the current chairman
        if(((Politician*)(*it))->m_chairman!= nullptr and ((Politician*)(*it))->id == this->m_chairman->id)
        {
            for (auto & m_politician : this->m_politicians) {
                m_politician->updateChairman(nullptr);
            }
            this->m_chairman= nullptr;
        }
        this->m_politicians.erase(it);
    }

}

/**
 * Notify function for observer pattern implementation. the function update each politician within the politician vector with the new chairman
 */
void Party::Notify() {
    PoliticianInterface * new_chairman;
    double max = std::numeric_limits<double>::lowest();

    // in order to identify a leader type politician, i compare the real power of the politician (using access to power member) to the
    // result of getPower() function which multiple by 2 the power member if the politician is social type
    for(auto it = m_politicians.begin(); it != m_politicians.end(); it++) {
        if(((Politician *)*it)->power == ((Politician *)*it)->getPower()  && ((Politician *)*it)->power > max) {
            max = ((Politician *)*it)->power ;
        }
    }

    if(max == std::numeric_limits<double>::lowest())
        new_chairman= nullptr;

    else {
        for (auto max_politician: this->m_politicians) { // find the first politician which has the max power we found
            if (((Politician *) (max_politician))->power == max and ((Politician *)max_politician)->power == ((Politician *)max_politician)->getPower() ) {
                new_chairman = max_politician;
                break; //check the next politician
            }
        }
    }

    for (auto & m_politician : this->m_politicians) {
        // update all the politicians with the new chairman
        m_politician->updateChairman(new_chairman);
    }
    this->m_chairman=(Politician *)new_chairman;
}


/**
 * The function calculate the total power of the party
 * @return total party, int
 */
int Party::powerElection() const {
    int temp_sum = std::accumulate(this->m_politicians.begin(), this->m_politicians.end(), 0,
                                   [](int sum, const auto &obj) {
                                       return sum + ((Politician *) obj)->getPower();
                                   });
    return temp_sum;
}

/**
 * The function return a pointer to the current chairman of the party. use for some other functions.
 * @return pointer to politician
 */
Politician * Party::getChairman() const{
    if (this->m_chairman!= nullptr)
        return this->m_chairman;
    else
        return nullptr;
}




