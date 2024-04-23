
#ifndef JERRY_H
#define JERRY_H
#include "Defs.h"

typedef struct Planet_t{
    double x;
    double y;
    double z;
    char * planet_name;
} Planet;
typedef Planet *pPlanet;

typedef struct Origin_t {
    Planet * source_planet;
    char * origin_name;
} Origin;
typedef Origin *pOrigin;

typedef struct PhysicalCharacteristic_t {
    char * PhysicalCharacteristic_name;
    double PhysicalCharacteristic_value;
} PhysicalCharacteristic;
typedef PhysicalCharacteristic *pPhysicalCharacteristics;

typedef struct Jerry_t {
    char * jerry_name;
    int happy_level;
    Origin * source_origin;
    PhysicalCharacteristic ** PhysicalCharacteristics_list;
    int  PhysicalCharacteristics_amount;
} Jerry;
typedef Jerry *pJerry;
Planet * createPlanet(double x, double y, double z, char * planet_name);
PhysicalCharacteristic * createPhysicalCharacteristic (char * PhysicalCharacteristic_name,double PhysicalCharacteristic_value);
Origin * createOrigin(char * origin_name, Planet * p);
Jerry * createJerry(char * jerry_name, int happy_level,Origin * source_origin);
bool PhysicalCharacteristicExists(Jerry * pJerry, char * p);
status AddPhysicalCharacteristic(Jerry * pJerry, PhysicalCharacteristic * p);
status DeletePhysicalCharacteristic(Jerry * pJerry, char * name);
status DeletePlanet(Planet * pPlanet);
status DeleteOrigin(Origin * pOrigin);
status DeleteJerry(Jerry * pJerry);
void PrintJerry(Jerry * pJerry);
void PrintPlanet(Planet * pPlanet);
void PlanetRead(char * filename, Planet ** planet_array);
bool DeleteAllCharacteristic(Jerry * pJerry);
Planet * copyPlanet(Planet * pPlanet);
Jerry * copyJerry(Jerry * pJerry);
bool comparePlanets(Planet* pPlanet1, char * name);
bool compareJerry(Jerry * j1, Jerry * j2);
Planet * PlanetUnique(Planet ** planet_array, char * test_name, int numberOfPlanets);
double valueOfPhysicalCharacteristicByJerry(Jerry * pJerry, char * physical_characteristic_name);

#endif
