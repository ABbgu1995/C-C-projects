//============================================================================
// Name        : politicalSystem.cpp
// Author      : ADP 23
// Version     : 0.0.0
// Copyright   : Your copyright notice
// Description : Assignment 5 in C++, Ansi-style
//============================================================================
#include <iostream>
using namespace std;

#include "Politician.h"
#include "DemocraticParty.h"
#include "SocialRepuPolitician.h"
#include "RepublicanParty.h"
#include "LeaderRepuPolitician.h"
#include "PoliticalSys.h"
#include <iostream>
#include <fstream>
#include "GeneralException.h"


int main(int argc, char* argv[]) {


    PoliticalSys* politicalSys = new PoliticalSys(argv[1]);
    char menuOption = '\0';
    while(menuOption!='0')
    {
        cout<< "1. Add Politician" << endl;
        cout<< "2. Add Party" << endl;
        cout<< "3. Remove Politician" << endl;
        cout<< "4. Remove Party" << endl;
        cout<< "5. Elections" << endl;
        cout<< "6. Print Politicians" << endl;
        cout<< "7. Print Parties" << endl;
        cout<< "8. Biggest Party" << endl;
        cout<< "0. Exit" << endl;
        cin >> menuOption;
        try {
            switch (menuOption) {
                case '1':
                    politicalSys->addPolitician();
                    break;
                case '2':
                    politicalSys->addParty();
                    break;
                case '3':
                    politicalSys->removePolitician();
                    break;
                case '4':
                    politicalSys->removeParty();
                    break;
                case '5':
                    politicalSys->elections();
                    break;
                case '6':
                    politicalSys->printPoliticians();
                    break;
                case '7':
                    politicalSys->printParties();
                    break;
                case '8':
                    politicalSys->BiggestParty();
                    break;
                case '0':
                    delete politicalSys;
                    break;
                default: {
                    printf("Invalid input \n");
                    break;
                }
            }
        }catch (Error& e){
            e.handle();
            delete politicalSys;
        }
    }
    return 0;
}