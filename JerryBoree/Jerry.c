#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Jerry.h"
Planet * createPlanet(double x, double y, double z, char * planet_name)
{
    //The function receives arguments which required to create a planet and return a pointer to the new allocated planet object
    if(planet_name==NULL)return NULL;
    Planet * p = (Planet *) malloc(sizeof (Planet));
    if (p==NULL) return NULL;
    p->planet_name = (char *) malloc(sizeof(planet_name));
    if (p->planet_name==NULL) return NULL;
    p->x=x;
    p->y=y;
    p->z=z;
    strcpy(p->planet_name, planet_name);
    return p;
}

status DeletePlanet(Planet * pPlanet){
    //The function receives a pointer to a Planet object and delete it by free it memory allocation
    if(pPlanet==NULL) return failure;
    if(pPlanet->planet_name==0) return success;
    // first free the char pointer of its name
    free(pPlanet->planet_name);
    pPlanet->planet_name=NULL;
    free(pPlanet);
    pPlanet=NULL;
    return success;
}
PhysicalCharacteristic * createPhysicalCharacteristic (char * PhysicalCharacteristic_name,double PhysicalCharacteristic_value)
{
    //The function receives a pointer to physical characteristic name and its value, create PhysicalCharacteristic based on the parameters and return a pointer to the instance
    if(PhysicalCharacteristic_name==NULL)return NULL;
    PhysicalCharacteristic * p = (PhysicalCharacteristic *) malloc(sizeof ( PhysicalCharacteristic));
    if (p==NULL) return NULL;
    // Allocate memory for the physical characteristic name of the object
    p->PhysicalCharacteristic_name = (char *) malloc(sizeof (PhysicalCharacteristic_name));
    if (p->PhysicalCharacteristic_name==NULL) return NULL;
    strcpy(p->PhysicalCharacteristic_name,PhysicalCharacteristic_name);
    p->PhysicalCharacteristic_value=PhysicalCharacteristic_value;
    return p;
}

Origin * createOrigin(char * origin_name, Planet * p){
    // The function receives a pointer to origin name and a pointer to a planet, create Origin based on the parameters and return a pointer the instance
    if(origin_name==NULL)return NULL;
    if(p==NULL)return NULL;
    Origin * o = (Origin *) malloc(sizeof (Origin));
    if (o==NULL) return NULL;
    o->origin_name=(char *) malloc(sizeof (origin_name));
    if (o->origin_name==NULL) return NULL;
    strcpy(o->origin_name, origin_name);
    o->source_planet=p;
    return o;
}
status DeleteOrigin(Origin * pOrigin) {
    //The function receives a pointer to an Origin object and delete it by free it memory allocation
    if(pOrigin==NULL) return failure;
    //big change here! the delete origin doesn't free the planets
//    if(DeletePlanet(pOrigin->source_planet)==failure)
//        return failure;
    pOrigin->source_planet=NULL;
    free(pOrigin->origin_name);
    pOrigin->origin_name=NULL;
    free(pOrigin);
    pOrigin=NULL;
    // set freed memory blocks to 0 to avoid bugs during running in case to free the memory again
    return success;
}
Jerry * createJerry(char * jerry_name, int happy_level,Origin * source_origin)
{
    //the function receive a pointer to a name, int of happy level and pointer to an origin, create jerry and return it pointer
    if(jerry_name==NULL)return NULL;
    if(source_origin==NULL)return NULL;
    Jerry * j = (Jerry *) malloc(sizeof (Jerry));
    if (j==NULL) return NULL;
    j->jerry_name=(char *) malloc(sizeof (jerry_name));
    if (j->jerry_name==NULL) return NULL;
    strcpy(j->jerry_name, jerry_name);
    j->happy_level=happy_level;
    j->source_origin=source_origin;
    j->PhysicalCharacteristics_list=NULL;
    j->PhysicalCharacteristics_amount=0;
    return j;
}

status DeleteJerry(Jerry * pJerry){
    // the function receive a pointer to jerry and delete by free it memory by also using the DeleteOrigin function
    if(pJerry==NULL) return failure;
    if(DeleteOrigin(pJerry->source_origin)==success)
        pJerry->source_origin=NULL;
    free(pJerry->jerry_name);
    pJerry->jerry_name=NULL;
    DeleteAllCharacteristic(pJerry);
    free(pJerry);
    pJerry=NULL;
    return success;

}

bool PhysicalCharacteristicExists(Jerry * j, char * name)
{
    //the function receive a pointer to a jerry and a pointer to a name and check if the physical characteristic name already exit in the physical characteristics list of the jerry
    if (j==NULL){
        printf("jerry pointer is empty");
        return false;
    }
    if (name==NULL){
        printf("name pointer is empty");
        return false;
    }
    for (int i=0; i<j->PhysicalCharacteristics_amount ;i++){
        char * temp = j->PhysicalCharacteristics_list[i]->PhysicalCharacteristic_name;
        if(strcmp(j->PhysicalCharacteristics_list[i]->PhysicalCharacteristic_name,name)==0)
            return true;
    }
    return false;
}

status AddPhysicalCharacteristic(Jerry * j, PhysicalCharacteristic * p)
{
    //the function receive a pointer to a jerry and a pointer to PhysicalCharacteristic object and add the PhysicalCharacteristic object to the jerry's PhysicalCharacteristics list
    if(j==NULL)return failure;
    if(p==NULL)return failure;
    if(j->PhysicalCharacteristics_amount==0){
        // in case of first PhysicalCharacteristic for the jerry, allocate the PhysicalCharacteristic array
        j->PhysicalCharacteristics_list=(PhysicalCharacteristic **) malloc(sizeof ( PhysicalCharacteristic *));
        if (j->PhysicalCharacteristics_list==NULL) return failure;
        j->PhysicalCharacteristics_list[j->PhysicalCharacteristics_amount]=p;
        j->PhysicalCharacteristics_amount++;
    }
    else {
        //use realloc in order to increase the memory allocation for one more PhysicalCharacteristic object
        j->PhysicalCharacteristics_list = (PhysicalCharacteristic **) realloc(j->PhysicalCharacteristics_list,
                                                                              (j->PhysicalCharacteristics_amount + 1) *
                                                                              sizeof(PhysicalCharacteristic *));
        if (j->PhysicalCharacteristics_list == NULL) return failure;
        j->PhysicalCharacteristics_list[j->PhysicalCharacteristics_amount] = p;
        j->PhysicalCharacteristics_amount++;
        return success;
    }
}
bool DeleteAllCharacteristic(Jerry * pJerry){
    //The function receive a pointer to a jerry and delete all of its PhysicalCharacteristics
    //An application call the function in case of free or delete a jerry instance and its PhysicalCharacteristics(before exit the program for example)
    for(int i=0; i<pJerry->PhysicalCharacteristics_amount; i++){
        //Free first the name which allocated dynamically and then the whole content of a PhysicalCharacteristics object within the list
        free(pJerry->PhysicalCharacteristics_list[i]->PhysicalCharacteristic_name);
        pJerry->PhysicalCharacteristics_list[i]->PhysicalCharacteristic_name=NULL;
        free(pJerry->PhysicalCharacteristics_list[i]);
        pJerry->PhysicalCharacteristics_list[i]= NULL;

    }
    free(pJerry->PhysicalCharacteristics_list);
    pJerry->PhysicalCharacteristics_list=NULL;
    return true;
}
status DeletePhysicalCharacteristic(Jerry * pJerry, char * name)
{
    //The function receives a pointer to a jerry and pointer to a name and remove an PhysicalCharacteristic which equal to the name from the PhysicalCharacteristic list of a jerry
    if (pJerry==NULL) return failure;
    if(name==NULL) return failure;
    if(PhysicalCharacteristicExists(pJerry,name)) {
        for (int i = 0; i < pJerry->PhysicalCharacteristics_amount; i++) {
            //check each name of the PhysicalCharacteristic from the list
            if (strcmp(pJerry->PhysicalCharacteristics_list[i]->PhysicalCharacteristic_name, name) == 0) {
                //in case of match, first free the allocated memory for the match PhysicalCharacteristic using its pointer
                free(pJerry->PhysicalCharacteristics_list[i]->PhysicalCharacteristic_name);
                pJerry->PhysicalCharacteristics_list[i]->PhysicalCharacteristic_name=NULL;
                free(pJerry->PhysicalCharacteristics_list[i]);
                pJerry->PhysicalCharacteristics_list[i]=NULL;
                //then, move all the PhysicalCharacteristic to the previous cell
                for (int j = i; j < pJerry->PhysicalCharacteristics_amount-1; j++) {
                    pJerry->PhysicalCharacteristics_list[j] = pJerry->PhysicalCharacteristics_list[j + 1];
                }
                pJerry->PhysicalCharacteristics_amount = pJerry->PhysicalCharacteristics_amount - 1;
                //in case no PhysicalCharacteristic left, free the memory allocated to the PhysicalCharacteristic list
                if(pJerry->PhysicalCharacteristics_amount==0){
                    free(pJerry->PhysicalCharacteristics_list);
                    pJerry->PhysicalCharacteristics_list=NULL;
                    return success;
                }
                //realloc the PhysicalCharacteristic size because the program shrink the list by 1 cell
                pJerry->PhysicalCharacteristics_list = (PhysicalCharacteristic **) realloc(pJerry->PhysicalCharacteristics_list,
                                                                                           (pJerry->PhysicalCharacteristics_amount) *
                                                                                           sizeof(PhysicalCharacteristic *));
            }
        }
        return success;
    }
    return failure;
}
void PrintJerry(Jerry * pJerry)
{
    //the function receive a pointer to a jerry and print it information as requested
    if (pJerry==NULL){
        printf("Empty pointer");
        return;
    }
    printf("Jerry , ID - %s : \n"
           "Happiness level : %d \n"
           "Origin : %s \n"
           "Planet : %s (%.2f,%.2f,%.2f) \n",
           pJerry->jerry_name,pJerry->happy_level,pJerry->source_origin->origin_name,
           pJerry->source_origin->source_planet->planet_name,
           pJerry->source_origin->source_planet->x,
           pJerry->source_origin->source_planet->y,
           pJerry->source_origin->source_planet->z);
    if (pJerry->PhysicalCharacteristics_amount!=0) {
        printf("Jerry's physical Characteristics available : \n\t");
        for (int i = 0; i < pJerry->PhysicalCharacteristics_amount - 1; i++) {
            printf("%s : %.2f , ",
                   pJerry->PhysicalCharacteristics_list[i]->PhysicalCharacteristic_name,
                   pJerry->PhysicalCharacteristics_list[i]->PhysicalCharacteristic_value);
        }
        printf("%s : %.2f \n",
               pJerry->PhysicalCharacteristics_list[pJerry->PhysicalCharacteristics_amount -
                                                    1]->PhysicalCharacteristic_name,
               pJerry->PhysicalCharacteristics_list[pJerry->PhysicalCharacteristics_amount -
                                                    1]->PhysicalCharacteristic_value);
    }

}

void PrintPlanet(Planet * pPlanet)
{
    printf("Planet : %s (%.2f,%.2f,%.2f) \n",
           pPlanet->planet_name,pPlanet->x,pPlanet->y,pPlanet->z);
}

Planet * PlanetUnique(Planet ** planet_array, char * test_name, int numberOfPlanets) {
    //the function receives a pointer to pointer of planets objects which is planet array, pointer to a name and amount of planets
    //if the planet name already exist in the array, the function return its pointer
    // the function verify if the planet name is already exist in the array in order to avoid planet duplications
    for (int i=0; i<numberOfPlanets ;  i++) {
        if (strcmp(planet_array[i]->planet_name, test_name) == 0)
            return planet_array[i];
    }
    return NULL;
}

Jerry * copyJerry(Jerry * pJerry){
    Jerry* copy_jerry = pJerry;
    return copy_jerry;
}
Planet * copyPlanet(Planet * pPlanet){
    // no deep copy
    Planet* copy_planet = pPlanet;
    return copy_planet;
}

bool comparePlanets(Planet* pPlanet1, char * name){
    if(strcmp(pPlanet1->planet_name, name)!=0)
        return false;
    return true;
}

bool compareJerry(Jerry * j1, Jerry * j2){
    if(strcmp(j1->jerry_name, j2->jerry_name)!=0)
        return false;
    return true;
}

double valueOfPhysicalCharacteristicByJerry(Jerry * pJerry, char * physical_characteristic_name){
    for (int i=0; i<pJerry->PhysicalCharacteristics_amount; i++){
        if(strcmp(pJerry->PhysicalCharacteristics_list[i]->PhysicalCharacteristic_name, physical_characteristic_name)==0)
            return pJerry->PhysicalCharacteristics_list[i]->PhysicalCharacteristic_value;
    }
    return 0;
}