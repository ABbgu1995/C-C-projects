Ass5: DemocraticParty.o DemoPolitician.o LeaderDemoPolitician.o LeaderRepuPolitician.o main.o Party.o PoliticalSys.o Politician.o RepublicanParty.o RepuPolitician.o SocialDemuPolitician.o SocialRepuPolitician.o
	g++ -o Ass5 DemocraticParty.o DemoPolitician.o LeaderDemoPolitician.o LeaderRepuPolitician.o main.o Party.o PoliticalSys.o Politician.o RepublicanParty.o RepuPolitician.o SocialDemuPolitician.o SocialRepuPolitician.o


DemocraticParty.o: DemocraticParty.cpp DemocraticParty.h Party.h PartyInterface.h PoliticianInterface.h Politician.h
	g++ -c DemocraticParty.cpp
DemoPolitician.o: DemoPolitician.cpp DemoPolitician.h Politician.h PoliticianInterface.h Party.h PartyInterface.h
	g++ -c DemoPolitician.cpp
LeaderDemoPolitician.o: LeaderDemoPolitician.cpp LeaderDemoPolitician.h Politician.h PoliticianInterface.h Party.h PartyInterface.h
	g++ -c LeaderDemoPolitician.cpp
LeaderRepuPolitician.o: LeaderRepuPolitician.cpp LeaderRepuPolitician.h Politician.h PoliticianInterface.h Party.h PartyInterface.h
	g++ -c LeaderRepuPolitician.cpp
main.o: main.cpp Politician.h PoliticianInterface.h Party.h PartyInterface.h DemocraticParty.h SocialRepuPolitician.h RepublicanParty.h LeaderRepuPolitician.h PoliticalSys.h GeneralException.h
	g++ -c main.cpp
Party.o: Party.cpp Party.h PartyInterface.h PoliticianInterface.h Politician.h
	g++ -c Party.cpp
PoliticalSys.o: PoliticalSys.cpp PoliticalSys.h Party.h PartyInterface.h PoliticianInterface.h Politician.h LeaderRepuPolitician.h SocialRepuPolitician.h LeaderDemoPolitician.h SocialDemuPolitician.h RepublicanParty.h DemocraticParty.h
	g++ -c PoliticalSys.cpp
Politician.o: Politician.cpp Politician.h PoliticianInterface.h Party.h PartyInterface.h
	g++ -c Politician.cpp
RepublicanParty.o: RepublicanParty.cpp RepublicanParty.h Party.h PartyInterface.h PoliticianInterface.h Politician.h
	g++ -c RepublicanParty.cpp
RepuPolitician.o: RepuPolitician.cpp
	g++ -c RepuPolitician.cpp
SocialDemuPolitician.o: SocialDemuPolitician.cpp SocialDemuPolitician.h Politician.h PoliticianInterface.h Party.h PartyInterface.h
	g++ -c SocialDemuPolitician.cpp
SocialRepuPolitician.o: SocialRepuPolitician.cpp SocialRepuPolitician.h Politician.h PoliticianInterface.h Party.h PartyInterface.h
	g++ -c SocialRepuPolitician.cpp

clean:
	rm -f *.o 