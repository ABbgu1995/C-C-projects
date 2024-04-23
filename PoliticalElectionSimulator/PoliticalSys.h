
#ifndef UNTITLED7_POLITICALSYS_H
#define UNTITLED7_POLITICALSYS_H

#include <vector>
#include <utility>
#include <iostream>
#include "Party.h"
using namespace std;
class PoliticalSys {
private:
    std::vector<Politician *>m_total_politicians;
    std::vector<Party *>m_total_parties;
    std::string file_path;
    Party * biggest_party;
public:
    PoliticalSys ();
    PoliticalSys (const std::string& filePath);
    ~PoliticalSys ();
    void addPolitician(string first_name= "", string last_name= "", int id=0, int power=0, char position= '\0', char type='\0');
    void addParty(string party_name ="" , char position = '\0');
    void removePolitician();
    void removeParty();
    void elections() const;
    void printPoliticians() const;
    void printParties() const;
    void BiggestParty() const;
    void updateBiggest();

};

#endif //UNTITLED7_POLITICALSYS_H
