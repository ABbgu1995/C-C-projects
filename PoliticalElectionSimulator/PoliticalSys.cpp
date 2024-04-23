#include "PoliticalSys.h"
#include "string"
#include <vector>
#include <utility>
#include "algorithm"
#include "LeaderRepuPolitician.h"
#include "SocialRepuPolitician.h"
#include "LeaderDemoPolitician.h"
#include "SocialDemuPolitician.h"
#include "RepublicanParty.h"
#include "DemocraticParty.h"
#include <fstream>
#include <iostream>
#include <string>
#include<stdio.h>

#include <sstream>
#include "GeneralException.h"
using namespace std;

/**
 * Empty constructor which just init the all the class vectors
 */
PoliticalSys::PoliticalSys() {
    this->m_total_parties.clear();
    this->m_total_politicians.clear();
}
/**
 * Constructor which read information from the configuration file and create politicians and parties
 * @param file_path name of configuration file, string
 */
PoliticalSys::PoliticalSys ( const std::string& file_path) : file_path(file_path) {
    this->m_total_parties.clear();
    this->m_total_politicians.clear();
    std::ifstream file(file_path);
    if (!file) {
        throw std::runtime_error("Error: failed to open file: " + file_path);
    }
    std::string line;
    while (std::getline(file, line)) {
        line.resize(line.length()-1);
        if(line == "Politicians:"){
            std::getline(file, line);
            line.resize(line.length()-1);
            while (line!= "Parties:") {
                std::vector<string>politician_details;
                istringstream iss(line);
                string word;
                for (int i=0; i<6 ; i++){
                    iss >> word;
                    politician_details.push_back(word);
                }
                this->addPolitician(politician_details[0],politician_details[1], stoi(politician_details[2]),stoi(politician_details[3]),politician_details[4][0],politician_details[5][0]);
                std::getline(file, line);
                line.resize(line.length()-1);
                politician_details.clear();
            }
            while(std::getline(file, line)){
                line.resize(line.length()-1);
                std::vector<string>party_details;
                istringstream iss(line);
                string word;
                for (int i=0; i<2 ; i++){
                    iss >> word;
                    party_details.push_back(word);
                }
                this->addParty(party_details[0],party_details[1][0]);
                party_details.clear();
            }
        }
    }
    file.close();
}

/**
 * Destructor for the political system which delete each object from the main vector and clear all pointers from all of the vectors
 */
PoliticalSys::~PoliticalSys() {
    for (auto i : this->m_total_politicians){
        delete i;
        i= nullptr;
    }
    this->m_total_politicians.clear();

    for (auto i : this->m_total_parties){
        delete i;
        i= nullptr;
    }
    this->m_total_parties.clear();
    this->m_total_politicians.clear();

}

/**
 * The function create a new politician to the political system
 * In case of no arguments provided, the function ask input from the user to init the parameters and call the constructor of Politician
 * The function use default parameters in order to handle politician creation from both configuration file and user input
 * @param first_name first name of politician, string
 * @param last_name last name of politician, string
 * @param id id of politician, int
 * @param power power of politician, int
 * @param position position of the politician, democrat or republican, char
 * @param type type of politician. social or leader, char
 */
void PoliticalSys::addPolitician(string first_name, string last_name, int id, int power, char position, char type) {
    if (first_name.empty()) {
        // important!!! add an exception to handle the case of too big power which crash the program and should clean and release the memory
        if (!this->m_total_politicians.empty()) {
            cout << "---Create Politician---\n";
            std::getline(std::cin, first_name);
            while (true) {
                int error_flag = 0; //using error flag to check if there was any error during input process
                try {
                    cout << "First name:\n";
                    std::getline(std::cin, first_name);

                    std::cout << "Last name:\n";
                    std::getline(std::cin, last_name);

                    std::cout << "ID:\n";
                    string temp_id;
                    std::getline(std::cin, temp_id);
                    id = stoi(temp_id);

                    auto it13 = std::find_if(this->m_total_politicians.begin(), this->m_total_politicians.end(),
                                             [&id](const auto &obj) {
                                                 return ((Politician *) obj)->id == id;
                                             }); // check of the politician exist in the total politicians vector

                    if (it13 != this->m_total_politicians.end() || id < 0) {   //it means the party is not exist
                        error_flag = 1;
                    }
                    std::cout << "Power:\n";
                    string temp_power;
                    std::getline(std::cin, temp_power);
                    power = stoi(temp_power);
                    if (power < 0 or power - (double) power != 0) {
                        error_flag = 1;
                    }

                    std::cout << "Republican or Democratic person\n";
                    string temp_position;
                    std::getline(std::cin, temp_position);
                    position = temp_position[0];
                    if (position != 'R' and position != 'D') {
                        error_flag = 1;
                    }

                    std::cout << "Leader or Social\n";
                    string temp_type;
                    std::getline(std::cin, temp_type);
                    type = temp_type[0];
                    if (type != 'L' and type != 'S') {
                        error_flag = 1;
                    }
                    if (error_flag == 1)
                        throw invalidDetailsException();
                    break;
                } catch (Error &e) {
                    e.handle();
                }
            }
        }
    }


    Party *temp_party;
    Politician *temp_politician = nullptr;
    try { //create new politician object
        if (position == 'R') {
            if (type == 'L')
                temp_politician = new LeaderRepuPolitician(first_name, last_name, id, power, nullptr);
            else
                temp_politician = new SocialRepuPolitician(first_name, last_name, id, power, nullptr);
        } else {
            if (type == 'L')
                temp_politician = new LeaderDemoPolitician(first_name, last_name, id, power, nullptr);
            else
                temp_politician = new SocialDemuPolitician(first_name, last_name, id, power, nullptr);
        }
    } catch (const std::bad_alloc &e) { // check if the allocation of new politician failed using exception.
        delete temp_politician;
        throw MemoryErrors();
    }

        // insert the politician to a party
    if(!this->m_total_parties.empty()) {
        for (auto it = this->m_total_parties.begin(); it != this->m_total_parties.end(); it++) {
            if (temp_politician->canBeInParty((Party *) (*it))) {
                if (temp_politician->politician_party == nullptr) { //if there is no party for current politician
                        temp_politician->setParty(*it);
                        this->m_total_politicians.push_back(temp_politician);
                    } else {
                        if ((*it)->m_politicians.size() < temp_politician->politician_party->m_politicians.size()) {
                            temp_politician->politician_party->removePolitician(temp_politician);
                            temp_politician->setParty(*it);
                        }
                    }
            }
        }
    }
        else {
            this->m_total_politicians.push_back(temp_politician);
        }
        updateBiggest(); // update the biggest party for O(1) return for the largest party
}
/**
 * The function create new party and add it to the political system. the function using default parameters
 * In case of none default parameters provided, the function ask for user input
 * @param party_name the new party name, string
 * @param position  the party position, republican or democratic, char
 */
void PoliticalSys::addParty(string party_name, char position){
    if(party_name.empty()) { // verify if the function call from the file read constructor or from the user
        cout << "---Create Party---\n";
        std::getline(std::cin, party_name);
        while (true) {
            int error_flag = 0; //using error flag to check if there was any error during input process
            try {
                cout << "Name:\n";
                std::getline(std::cin, party_name);
                // using find_if and iterator to verify if the party already exists
                auto it13 = std::find_if(this->m_total_parties.begin(), this->m_total_parties.end(),
                                         [party_name](const auto &obj) {
                                             return ((Party *) obj)->m_party_name == party_name;
                                         });
                if (it13 != this->m_total_parties.end()) // means that the party exist
                    error_flag=1;
                std::cout << "Republican or Democratic party\n";
                string temp_position;
                std::getline(std::cin, temp_position);
                position = temp_position[0];
                if (position != 'R' and position != 'D') {
                    error_flag=1;
                }
                if (error_flag==1)
                    throw invalidDetailsException();
                break;
            } catch (Error& e){
                e.handle();
            }
        }
    }
    Party * temp_party;
    try {
        if (position == 'R') { // if the position is R, it means its republicans so insert the party to the repo vector and to the total vector
            temp_party = new RepublicanParty(party_name);
            //this->m_repo_parties.push_back(temp_party);
            this->m_total_parties.push_back(temp_party);
        } else { // if the position is not R which means it only can be D, it means its democrat so insert the party to the demo vector and to the total vector
            temp_party = new DemocraticParty(party_name);
            //this->m_demo_parties.push_back(temp_party);
            this->m_total_parties.push_back(temp_party);
        }
    }catch(const std::bad_alloc &e) {
        delete temp_party;
        throw MemoryErrors();
    }

    for (auto politician : this->m_total_politicians) {
        if (politician->canBeInParty(temp_party) == true) {
            if (politician->politician_party == nullptr)
                politician->setParty(temp_party);
            else {
                if (politician->politician_party->m_politicians.size() > temp_party->m_politicians.size()) {
                    politician->politician_party->removePolitician(politician);
                    politician->setParty(temp_party);
                }
            }
        }
    }
    updateBiggest(); // update the biggest party for O(1) return for the largest party
}
/**
 * The function remove a politician from the political system
 * The function ask input from the user (party name)
 */
void PoliticalSys::removePolitician() {

    if (!this->m_total_politicians.empty()) {
        int id;
        string temp_id;
        cout << "---Remove Politician---\n";
        std::getline(std::cin, temp_id);
        while (true) {
            try {
                cout << "Enter the ID:\n";
                std::getline(std::cin, temp_id);
                id = stoi(temp_id);
                auto it13 = std::find_if(this->m_total_politicians.begin(), this->m_total_politicians.end(),
                                         [&id](const auto &obj) {
                                             return ((Politician *) obj)->id == id;
                                         }); // find a politician with the same id
                if (it13 == this->m_total_politicians.end() || id<0) {   //it means the party is not exist
                    throw invalidIDException();
                }
                break;
            } catch (Error& e) {
                e.handle();
            }
        }

        auto it = std::find_if(this->m_total_politicians.begin(), this->m_total_politicians.end(),
                               [&id](const auto &obj) { return ((Politician *) obj)->id == id; });
        if (it != this->m_total_politicians.end()) { //it means that the politician found
            // remove the politician from its party(for subscription uses)
            ((Politician *) (*it))->politician_party->removePolitician(((PoliticianInterface *) (*it)));
            delete *it;
            this->m_total_politicians.erase(it);
        }
        updateBiggest(); // update the biggest party for O(1) return for the largest party
    }
}
/**
 * The function remove a party from the political system by request input from the user for party name
 */
void PoliticalSys::removeParty() {
    // the following code block insert the politician the oldest party with the minimum amounts of the politicians
    // As I understood from the assignment requirements, in case if there are more than 1 parties which shared the same
    // amount of politicians, the politician should insert to the oldest one. but based on this logic, test 8 (Remove a party with prints)
    // from the model is failed and its seems that real requirement is to insert the politician to the newest party.
    // So if I understood correctly, I keep here the code (solution) which insert the politician to the oldest party
    if (!this->m_total_parties.empty()) {
        string name;
        cout << "---Remove Party---\n";
        std::getline(std::cin, name);
        while (true) {
            int error_flag=0;
            try {
                cout << "Enter party name:\n";
                std::getline(std::cin, name);
                auto it13 = std::find_if(this->m_total_parties.begin(), this->m_total_parties.end(),
                                         [&name](const auto &obj) {
                                             return ((Party *) obj)->m_party_name == name;
                                         });
                if (it13 == this->m_total_parties.end()) {   //it means the party is not exist
                    throw invalidNameException();
                }
                break;
            } catch (Error& e) {
                e.handle();
            }
        }
        auto it1 = std::find_if(this->m_total_parties.begin(), this->m_total_parties.end(),
                                [&name](const auto &obj) { return ((Party *) obj)->m_party_name == name; });
        if (it1 != this->m_total_parties.end()) {  //it means that the party
            Party *deleted_party = *it1;
            this->m_total_parties.erase(it1); // delete the party from the parties
            Politician *politician;
            while (!deleted_party->m_politicians.empty()) {
                politician = (Politician *) deleted_party->m_politicians[0];
                ((Politician *) politician)->politician_party->removePolitician(politician); // remove the politician from the current party
                if (this->m_total_parties.size() > 0) {
                    auto result = std::min_element(this->m_total_parties.begin(),
                                                   this->m_total_parties.end(), //find the amount of smallest party
                                                   [](const auto &a, const auto &b) {
                                                       return ((Party *) a)->m_politicians.size() <
                                                              ((Party *) b)->m_politicians.size();
                                                   });
                    int min = (int) ((Party *) *result)->m_politicians.size();
                    Party * insert_party;
                    for (auto min_party: this->m_total_parties) { // find the first party which have the minimum politicians
                        if (min_party->m_politicians.size() == min) {
                            insert_party=min_party;
                        }
                    }
                    ((Politician *) politician)->setParty(insert_party);
                }
                else{
                    ((Politician *) politician)->setParty(nullptr);
                }
            }
            this->m_total_parties.erase(
                    std::remove(this->m_total_parties.begin(), this->m_total_parties.end(), deleted_party),
                    this->m_total_parties.end());
            delete deleted_party; // delete the party
        }

        updateBiggest(); // update the biggest party for O(1) return for the largest party
    }
}
/**
 * The function calculate the election for the current political system and print out each party chairman and the prime minister
 * if the there is no chairman for a party of no prime minister, the function print None
 */
void PoliticalSys::elections() const{
    cout << "----Primaries----\n";
    for (auto party : this->m_total_parties){
        party->Notify();
        if(party->m_chairman== nullptr) //it means there is no chairman for the party
            cout << "None is the chairman of " << party->m_party_name << "\n";
        else
            cout << party->m_chairman->first_name << " is the chairman of " << party->m_party_name << "\n";
    }
    cout << "----Elections----\n";
    for (auto party : this->m_total_parties){
        cout << "Party: " << party->m_party_name << ",Power: " << party->powerElection() << "\n";
    }

    auto result = std::max_element(this->m_total_parties.begin(), this->m_total_parties.end(), //find the amount of smallest party
                                   [](const auto &a, const auto &b) {
                                       return ((Party *)a)->powerElection() < ((Party *)b)->powerElection();
                                   });
    int max= (int)((Party *)*result)->powerElection();

    cout << "----Elections Results----\n";
    for (auto won_party : this->m_total_parties){ // find the first party(oldest) which has the maximum power
        if(won_party->powerElection()==max){
            if(won_party->m_chairman== nullptr){
                cout << won_party->m_party_name << "party on the elections and None is the prime minister\n";
            }
            else
                cout << won_party->m_party_name << " party won the elections and " << won_party->m_chairman->first_name << " is the prime minister\n";
            break;
        }
    }
}

/**
 * The function print all of the politicians exists in the system
 */
void PoliticalSys::printPoliticians() const{
    cout << "----Politicians----\n";
    for (auto Politician : this->m_total_politicians) {
        Politician->printDetails();
    }
}
void PoliticalSys::printParties() const{
    cout << "----Parties----\n";
    for (auto party : this->m_total_parties) {
        party->printParty();
    }
}

/**
 * The function update the private member biggest_party and may call in case of amount changes (parties or politicians)
 * The main purpose for this function is to provide O(1) print the current biggest party in case of BiggestParty function call
 */
void PoliticalSys::updateBiggest()  {
    if(!this->m_total_parties.empty()) {
        Party *temp_bigger = m_total_parties[0];
        for (const auto &candidate_party: m_total_parties) {
            if (candidate_party->m_politicians.size() > temp_bigger->m_politicians.size()) {
                temp_bigger = candidate_party;
            } else if (candidate_party->m_politicians.size() == temp_bigger->m_politicians.size()) {
                if (candidate_party->m_party_name.length() > temp_bigger->m_party_name.length()) {
                    temp_bigger = candidate_party;
                }
            }
        }
        this->biggest_party = temp_bigger;
    }else // its means there is no bigger party
        this->biggest_party = nullptr;

}

/**
 * The function print the current biggest party name its size. O(1)
 */
void PoliticalSys::BiggestParty() const{
    if(this-> biggest_party!= nullptr) {
        cout << "----Biggest Party----\n";
        cout << "[" << this->biggest_party->m_party_name << "," << this->biggest_party->m_politicians.size() << "]\n";
    }
}