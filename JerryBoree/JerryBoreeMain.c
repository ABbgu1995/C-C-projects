#include "Defs.h"
#include "MultiValueHashTable.h"
#include "Jerry.h"
#include <math.h>

Element flatCopyPlanetValue(Element pPlanet){
    //flat copy for planet linked_list
    if(pPlanet==NULL) return NULL;
    return copyPlanet((Planet *)pPlanet);
}

status fullFreePlanetValue(Element pPlanet){
    // full free function which use the DeletePlanet to deallocate existing planet
    if(pPlanet == NULL) return failure;
    return DeletePlanet((Planet *)pPlanet);
}

enum e_bool comparePlanetValue(Element pPlanet1, Element pPlanet2){
    // the function receive pointers to planets and compare it by their names
    if(pPlanet2 == NULL || pPlanet1 == NULL) return false;
    char* temp1 = ((Planet*)pPlanet1)->planet_name;
    char* temp2 = ((Planet*)pPlanet2)->planet_name;
    if (strcmp(((Planet*)pPlanet1)->planet_name,((Planet*)pPlanet2)->planet_name) == 0)
        return true;
    return false;
}
status printPlanetValue(Element elem){
    if(elem==NULL) return failure;
    PrintPlanet((Planet *)elem);
    return success;
}

Element flatCopyJerryValue(Element elem){
    if (elem == NULL) return NULL;
    return copyJerry((Jerry *)elem);
}
Element deepCopyJerryValue(Element elem){
    if(elem==NULL) return NULL;
    Jerry *pJerry = createJerry(((Jerry *)elem)->jerry_name, ((Jerry *)elem)->happy_level, ((Jerry *)elem)->source_origin);
    for (int i=0; i<((Jerry *)elem)->PhysicalCharacteristics_amount; i++){
        AddPhysicalCharacteristic(pJerry,((Jerry *)elem)->PhysicalCharacteristics_list[i]);
    }
    return pJerry;
}
status freeJerryValue(Element elem){
    if (elem == NULL) return failure;
    Jerry * pJerry = (Jerry* )elem;
    pJerry = NULL;
    return success;
}

status deepFreeJerry(Element elem){
    if(elem == NULL) return failure;
    Jerry * temp = (Jerry *)elem;
    return DeleteJerry((Jerry *)elem);
}

enum e_bool compareJerryValue(Element elem1, Element elem2){
    if (elem1 == NULL || elem2 == NULL) return false;
    return compareJerry((Jerry *)elem1, (Jerry *)elem2);
}
status printJerryValue(Element elem){
    if(elem == NULL) return failure;
    PrintJerry((Jerry *)elem);
    return success;
}



Element deepCopyKey (Element key){
    if (key==NULL)
        return NULL;
    char* temp = (char*) key;
    char* tmp;
    tmp = (char*) malloc(strlen(temp) + 1);
    if (tmp == NULL){
        return NULL;
    }
    strcpy(tmp,temp);
    return (Element)tmp;
}
Element flatCopyKey(Element key) {
    // flat copy to a key
    if (key == NULL) return NULL;
    char * id_pointer=key;
    return id_pointer;
}

status freeCharKey(Element key){
    // deep free key as char
    if(key==NULL)
        return failure;
    char * check_value = (char*) key;
    if(strcmp(check_value,"")==0) return failure;
    free (check_value);
    check_value=NULL;
    key=NULL;
    return success;
}


enum e_bool compareCharKeys( Element key1, Element key2){
    // compare between 2 keys as chars
    if(key1 == NULL || key2 == NULL) return false;
    char * temp1 = (char *)key1;
    char * temp2 = (char *)key2;
    if(strcmp((char *)key1, (char*)key2)==0)
        return true;
    return false;
}

status printCharKey(Element key){
    if(NULL==key) return failure;
    char * id = (char*)key;
    printf("%s\n",id);
    return success;
}

int transformIntoNumber (Element key){
    // convert a key as char into a sum of all the chars
    if (key==NULL)
        return failure;
    int number = 0;
    for (int i = 0 ; i< strlen((char*)key);i++){
        number = number + ((char*)key)[i];
    }
    return number;

}

void memoryCleaner(hashTable jerry_hashTable, multiValueHashTable characteristic_multiValueHashTable, LinkedList planet_linkedList, LinkedList jerry_linkedList, int errorFlag){
    // if enter with error flag 1 its means there was an allocation error
    destroyMultiValueHashTable(characteristic_multiValueHashTable);
    destroyHashTable(jerry_hashTable);
    destroyList(planet_linkedList);
    destroyList(jerry_linkedList);
    if(errorFlag==1){
        printf("Memory allocation error ! \n");
    }
}
char * readInput(char * buffer){
    // the to use to read information which might insert to data structures
    scanf("%s", buffer);
    char *temp_pointer = (char *) malloc(sizeof(strlen(buffer) + 1));
    strcpy(temp_pointer, buffer);
    return temp_pointer;
}
int main(int argc, char *argv[]) {

    // set the data structures that support that program
    int numberOfPlanets = atoi(argv[1]);
    hashTable jerry_hashTable = createHashTable(flatCopyKey, freeCharKey, printCharKey,flatCopyJerryValue,freeJerryValue, printJerryValue, compareCharKeys, transformIntoNumber,13);
    if(jerry_hashTable==NULL) memoryCleaner(jerry_hashTable,NULL, NULL, NULL,1);

    multiValueHashTable characteristic_multiValueHashTable = createMultiValueHashTable(flatCopyKey, freeCharKey, printCharKey, flatCopyJerryValue,freeJerryValue, printJerryValue, compareCharKeys, compareJerryValue, transformIntoNumber,13);
    if(jerry_hashTable==NULL) memoryCleaner(jerry_hashTable,characteristic_multiValueHashTable, NULL, NULL,1);

    LinkedList planet_linkedList = createLinkedList(fullFreePlanetValue, printPlanetValue,flatCopyPlanetValue,comparePlanetValue);
    if(planet_linkedList==NULL) memoryCleaner(jerry_hashTable,characteristic_multiValueHashTable, planet_linkedList, NULL,1);

    LinkedList jerry_linkedList = createLinkedList(deepFreeJerry, printJerryValue, flatCopyJerryValue, compareJerryValue);
    if(jerry_hashTable==NULL) memoryCleaner(jerry_hashTable, characteristic_multiValueHashTable, planet_linkedList, jerry_linkedList,1);

    char buffer[300];
    char* Planet_details[4];
    char* Jerry_details[4];
    char *temp_chars[2];
    FILE *inf = fopen(argv[2], "r");
    if (inf==NULL) {
        printf("Error opening file");
        exit(1);
    }

    while (fscanf(inf, "%s", buffer)>=1){
        if(strcmp(buffer,"Planets")==0) {
            for (int j = 0; j < numberOfPlanets; j++) {
                for (int i = 0; i < 4; i++) {
                    fscanf(inf, "\n%[^,\n$], ", buffer);
                    Planet_details[i] = (char *) malloc(strlen(buffer) + 1);
                    if(Planet_details[i]==NULL) {
                        free(Planet_details[i]);
                        memoryCleaner(jerry_hashTable, characteristic_multiValueHashTable, planet_linkedList, jerry_linkedList, 1);
                    }
                    strcpy(Planet_details[i], buffer);
                }
                Planet *p = createPlanet(atof(Planet_details[1]), atof(Planet_details[2]),
                                         atof(Planet_details[3]), Planet_details[0]);
                if(p==NULL) exit(0);
                appendNode(planet_linkedList, p);
                for (int i=0; i<4; i++) {
                    free(Planet_details[i]);
                    Planet_details[i]=NULL;
                }

            }
        }
        if (strcmp(buffer, "Jerries") == 0) {//if the line contains the word "Jerries" it means the program should read Jerries info and fill up the planet_array
            while(inf->_IO_read_ptr[0] != '\0'){
                for (int i = 0; i < 4; i++) {
                    fscanf(inf, "\n%[^,\n$], ", buffer);
                    Jerry_details[i] = (char *) malloc(strlen(buffer) + 1);
                    if(Jerry_details[i]==NULL) {
                        // allocation check and free memory if fail
                        free(Jerry_details[i]);
                        memoryCleaner(jerry_hashTable, characteristic_multiValueHashTable, planet_linkedList, jerry_linkedList, 1);
                    }
                    strcpy(Jerry_details[i], buffer);
                }

                // using empty planet because the compare function of both planet is getting planets as arguments
                Planet * empty_planet = createPlanet(0,0,0,Jerry_details[2]);
                if(empty_planet==NULL) {
                    // allocation check and free memory if fail
                    free(empty_planet);
                    for (int i = 0; i < 4; i++) {
                        free(Planet_details[i]);
                    }
                    memoryCleaner(jerry_hashTable, characteristic_multiValueHashTable, planet_linkedList,
                                  jerry_linkedList, 1);
                }
                Planet *p = searchByKeyInList(planet_linkedList,(Element)empty_planet);
                DeletePlanet(empty_planet);

                // create the Origin using the planet
                Origin *o = createOrigin(Jerry_details[1], p);
                if(o==NULL) exit(0);
                //create a new jerry and locate it in the jerry_array
                Jerry* temp_jerry = createJerry(Jerry_details[0], atoi(Jerry_details[3]), o);
                for (int i=0; i<4; i++){
                    free(Jerry_details[i]);
                    Jerry_details[i]=NULL;
                }
                //read the physical characteristics information. by using inf->_IO_read_ptr[0] the program check if the next char is tab without extract it from the file
                getc(inf);


                while(inf->_IO_read_ptr[0] =='\t') {
                    //adding the characteristics to the current jerry
                    getc(inf);
                    for (int i=0; i<2; i++) {
                        // read 2 input: the characteristics name and its value
                        fscanf(inf, "\n%[^:\n$]: ", buffer);
                        temp_chars[i] = (char *) malloc(sizeof(strlen(buffer) + 1));
                        strcpy(temp_chars[i], buffer);
                    }

                    // create new pointer to the new characteristic
                    PhysicalCharacteristic *temp_physicalCharacteristic= createPhysicalCharacteristic(temp_chars[0], atof(temp_chars[1]));

                    if(AddPhysicalCharacteristic(temp_jerry, temp_physicalCharacteristic)==failure){
                        //in case of1 add new physical characteristic fail, the program clean it memory and exit
                        exit(0);
                    }

                    // free the input helper
                    for (int i=0; i<2; i++) {
                        free(temp_chars[i]);
                        temp_chars[i]=NULL;
                    }
                    getc(inf);
                }
                // insert each one of the physical characteristics to the multiValueHashTable for current jerry
                for (int i=0; i<temp_jerry->PhysicalCharacteristics_amount; i++) {
                    char *new_key_PhysicalCharacteristic_name = (char *) malloc(sizeof strlen(temp_jerry->PhysicalCharacteristics_list[i]->PhysicalCharacteristic_name) + 1);
                    strcpy(new_key_PhysicalCharacteristic_name,temp_jerry->PhysicalCharacteristics_list[i]->PhysicalCharacteristic_name);
                    addToMultiValueHashTable(characteristic_multiValueHashTable, new_key_PhysicalCharacteristic_name,temp_jerry);

                }

                // insert the jerry into the jerry HashTable and linkedlist of jerries
                char * temp_key = (char *) malloc(sizeof(strlen(temp_jerry->jerry_name)+1));
                strcpy(temp_key,temp_jerry->jerry_name);
                addToHashTable(jerry_hashTable,temp_key, temp_jerry);
                appendNode(jerry_linkedList, temp_jerry);


            }
        }
    }
    fclose(inf);

    char ch[1];
    while(strcmp(&ch[0],"0") !=0 ) {
        printf("Welcome Rick, what are your Jerry's needs today ? \n");
        printf("1 : Take this Jerry away from me \n");
        printf("2 : I think I remember something about my Jerry \n");
        printf("3 : Oh wait. That can't be right \n");
        printf("4 : I guess I will take back my Jerry now \n");
        printf("5 : I can't find my Jerry. Just give me a similar one \n");
        printf("6 : I lost a bet. Give me your saddest Jerry \n");
        printf("7 : Show me what you got \n");
        printf("8 : Let the Jerries play \n");
        printf("9 : I had enough. Close this place \n");
        scanf( "%s", ch );
        if (atoi(&ch[0]) < 1 || atoi(&ch[0]) > 9 || strlen(&ch[0])>1) {
            printf("Rick this option is not known to the daycare ! \n");
            continue;
        }

        switch (ch[0]) {
            case '1': {
                printf("What is your Jerry's ID ? \n");
                char *jerry_name = readInput(buffer);
                if (jerry_name == NULL)
                    memoryCleaner(jerry_hashTable, characteristic_multiValueHashTable, planet_linkedList,
                                  jerry_linkedList, 1);

                // check if jerry exists already
                Jerry *jerry_temp = lookupInHashTable(jerry_hashTable, jerry_name);
                if (jerry_temp != NULL) {
                    printf("Rick did you forgot ? you already left him here ! \n");
                    free(jerry_name);
                    jerry_name = NULL;
                    break;
                } else //means that jerry exists in hashtable
                {
                    printf("What planet is your Jerry from ? \n");
                    char *planet_name = readInput(buffer);
                    if (planet_name == NULL)
                        memoryCleaner(jerry_hashTable, characteristic_multiValueHashTable, planet_linkedList,
                                      jerry_linkedList, 1);

                    // use empty planet because the planet compare getting pointer to planets
                    Planet *empty_planet = createPlanet(0, 0, 0, planet_name);
                    Planet *planet_temp = searchByKeyInList(planet_linkedList,
                                                            empty_planet); //pointer to planet if exists in list
                    DeletePlanet(empty_planet);
                    if (planet_temp == NULL) {
                        printf("%s is not a known planet ! \n", planet_name);
                        free(jerry_name);
                        jerry_name = NULL;
                        free(planet_name);
                        planet_name = NULL;
                        break;
                    } else {
                        printf("What is your Jerry's dimension ? \n");
                        char *dimension_name = readInput(buffer);
                        //clear the memory and exit the program in case of NULL return from allocation function
                        if (dimension_name == NULL) {
                            free(jerry_name);
                            jerry_name = NULL;
                            free(planet_name);
                            planet_name = NULL;
                            free(dimension_name);
                            dimension_name=NULL;
                            memoryCleaner(jerry_hashTable, characteristic_multiValueHashTable, planet_linkedList,
                                          jerry_linkedList, 1);

                        }
                        Origin *temp_origin = createOrigin(dimension_name, planet_temp);
                        if (dimension_name == NULL) {
                            free(jerry_name);
                            jerry_name = NULL;
                            free(planet_name);
                            planet_name = NULL;
                            free(dimension_name);
                            dimension_name=NULL;
                            DeleteOrigin(temp_origin);
                            memoryCleaner(jerry_hashTable, characteristic_multiValueHashTable, planet_linkedList,
                                          jerry_linkedList, 1);

                        }

                        printf("How happy is your Jerry now ? \n");
                        char *happiness_level = readInput(buffer);
                        //clear the memory and exit the program in case of NULL return from allocation function
                        if (happiness_level == NULL) {
                            free(jerry_name);
                            jerry_name = NULL;
                            free(planet_name);
                            planet_name = NULL;
                            free(dimension_name);
                            dimension_name = NULL;
                            free(happiness_level);
                            happiness_level=NULL;
                            DeleteOrigin(temp_origin);
                            memoryCleaner(jerry_hashTable, characteristic_multiValueHashTable, planet_linkedList,
                                          jerry_linkedList, 1);
                        }


                        Jerry *pJerry_temp = createJerry(jerry_name, atoi(happiness_level), temp_origin);
                        //clear the memory and exit the program in case of NULL return from createJerry function which uses memory allocation
                        if (pJerry_temp == NULL) {
                            free(jerry_name);
                            jerry_name = NULL;
                            free(planet_name);
                            planet_name = NULL;
                            free(dimension_name);
                            dimension_name = NULL;
                            free(happiness_level);
                            happiness_level = NULL;
                            DeleteOrigin(temp_origin);
                            DeleteJerry(pJerry_temp);
                            memoryCleaner(jerry_hashTable, characteristic_multiValueHashTable, planet_linkedList,
                                          jerry_linkedList, 1);
                        }

                        else {
                            char *temp_key_jerry = (char *) malloc(sizeof(pJerry_temp->jerry_name) + 1);
                            if (temp_key_jerry == NULL) {
                                free(jerry_name);
                                jerry_name = NULL;
                                free(planet_name);
                                planet_name = NULL;
                                free(dimension_name);
                                dimension_name = NULL;
                                free(happiness_level);
                                happiness_level = NULL;
                                DeleteOrigin(temp_origin);
                                DeleteJerry(pJerry_temp);
                                memoryCleaner(jerry_hashTable, characteristic_multiValueHashTable, planet_linkedList,
                                              jerry_linkedList, 1);
                            }

                            // if the input process success, insert the jerry to the HashTable
                            strcpy(temp_key_jerry, pJerry_temp->jerry_name);
                            addToHashTable(jerry_hashTable, temp_key_jerry, pJerry_temp);
                            appendNode(jerry_linkedList, pJerry_temp);
                            PrintJerry(pJerry_temp);
                        }

                        // Delete input helper allocations
                        free(jerry_name);
                        jerry_name = NULL;
                        free(planet_name);
                        planet_name = NULL;
                        free(dimension_name);
                        dimension_name = NULL;
                        free(happiness_level);
                        happiness_level = NULL;
                        break;
                    }
                }
            }
            case '2': {
                printf("What is your Jerry's ID ? \n");
                char *jerry_name = readInput(buffer);
                if (jerry_name == NULL) {
                    free(jerry_name);
                    jerry_name=NULL;
                    memoryCleaner(jerry_hashTable, characteristic_multiValueHashTable, planet_linkedList,
                                  jerry_linkedList, 1);
                }
                Jerry *jerry_temp = lookupInHashTable(jerry_hashTable, jerry_name); // no need to free
                if (jerry_temp == NULL) {
                    // the jerry does not exist in the hashTable
                    printf("Rick this Jerry is not in the daycare ! \n");
                    free(jerry_name);
                    jerry_name = NULL;
                    break;
                } else {
                    printf("What physical characteristic can you add to Jerry - %s ? \n", jerry_name);
                    char *temp_PhysicalCharacteristic_name = readInput(buffer);
                    if (temp_PhysicalCharacteristic_name == NULL) {
                        free(jerry_name);
                        jerry_name=NULL;
                        free(temp_PhysicalCharacteristic_name);
                        temp_PhysicalCharacteristic_name=NULL;
                        memoryCleaner(jerry_hashTable, characteristic_multiValueHashTable, planet_linkedList,
                                      jerry_linkedList, 1);

                    }

                    if (PhysicalCharacteristicExists(jerry_temp, temp_PhysicalCharacteristic_name) == true) {
                        // the jerry have the physical characteristic name
                        printf("The information about his %s already available to the daycare ! \n",
                               temp_PhysicalCharacteristic_name);
                        free(jerry_name);
                        jerry_name = NULL;
                        free(temp_PhysicalCharacteristic_name);
                        temp_PhysicalCharacteristic_name = NULL;
                        break;
                    } else {
                        printf("What is the value of his %s ? \n", temp_PhysicalCharacteristic_name);
                        char *temp_PhysicalCharacteristic_value = readInput(buffer);
                        if (temp_PhysicalCharacteristic_value == NULL) {
                            free(jerry_name);
                            jerry_name=NULL;
                            free(temp_PhysicalCharacteristic_name);
                            temp_PhysicalCharacteristic_name=NULL;
                            free(temp_PhysicalCharacteristic_name);
                            temp_PhysicalCharacteristic_name=NULL;
                            memoryCleaner(jerry_hashTable, characteristic_multiValueHashTable, planet_linkedList,
                                          jerry_linkedList, 1);
                        }
                        PhysicalCharacteristic *temp_full_PhysicalCharacteristic = createPhysicalCharacteristic(
                                temp_PhysicalCharacteristic_name, atof(temp_PhysicalCharacteristic_value));
                        AddPhysicalCharacteristic(jerry_temp, temp_full_PhysicalCharacteristic);


                        char * temp_key = (char *) malloc(sizeof(strlen(temp_PhysicalCharacteristic_name)) + 1);
                        if (temp_key == NULL) {
                            free(jerry_name);
                            jerry_name=NULL;
                            free(temp_PhysicalCharacteristic_name);
                            temp_PhysicalCharacteristic_name=NULL;
                            free(temp_PhysicalCharacteristic_name);
                            temp_PhysicalCharacteristic_name=NULL;
                            free(temp_key);
                            temp_key=NULL;
                            memoryCleaner(jerry_hashTable, characteristic_multiValueHashTable, planet_linkedList,
                                          jerry_linkedList, 1);

                        }

                        strcpy(temp_key, temp_PhysicalCharacteristic_name);
                        addToMultiValueHashTable(characteristic_multiValueHashTable, temp_key, jerry_temp);
                        printf("%s : \n", temp_key);
                        displayMultiValueHashElementsByKey(characteristic_multiValueHashTable,
                                                           temp_PhysicalCharacteristic_name);


                        free(jerry_name); // not sure about this free
                        jerry_name = NULL;

                        free(temp_PhysicalCharacteristic_name);
                        temp_PhysicalCharacteristic_name = NULL;

                        free(temp_PhysicalCharacteristic_value);
                        temp_PhysicalCharacteristic_value = NULL;

                        free(temp_key);
                        temp_key=NULL;


                        break;
                    }
                }
            }
            case '3': {
                printf("What is your Jerry's ID ? \n");
                char *jerry_name = readInput(buffer);
                if (jerry_name == NULL)
                    memoryCleaner(jerry_hashTable, characteristic_multiValueHashTable, planet_linkedList,
                                  jerry_linkedList, 1);
                Jerry *jerry_temp = lookupInHashTable(jerry_hashTable, jerry_name); // no need to free
                if (jerry_temp == NULL) {
                    // the jerry does not exist in the hashTable
                    printf("Rick this Jerry is not in the daycare ! \n");
                    free(jerry_name);
                    jerry_name = NULL;
                    break;
                } else {
                    printf("What physical characteristic do you want to remove from Jerry - %s ? \n", jerry_name);
                    char *temp_PhysicalCharacteristic_name = readInput(buffer);
                    if(temp_PhysicalCharacteristic_name==NULL) {
                        free(jerry_name);
                        jerry_name=NULL;
                        memoryCleaner(jerry_hashTable, characteristic_multiValueHashTable, planet_linkedList,
                                      jerry_linkedList, 1);
                    }
                    if (PhysicalCharacteristicExists(jerry_temp, temp_PhysicalCharacteristic_name) == false) {
                        // the jerry not have the physical characteristic name
                        printf("The information about his %s not available to the daycare ! \n",
                               temp_PhysicalCharacteristic_name);
                        free(jerry_name);
                        jerry_name = NULL;
                        free(temp_PhysicalCharacteristic_name);
                        temp_PhysicalCharacteristic_name = NULL;
                        break;
                    } else
                        // the jerry have the physical characteristic name
                    {
                        removeFromMultiValueHashTable(characteristic_multiValueHashTable,
                                                      temp_PhysicalCharacteristic_name, jerry_temp);
                        DeletePhysicalCharacteristic(jerry_temp, temp_PhysicalCharacteristic_name);
                        PrintJerry(jerry_temp);


                        free(jerry_name);
                        jerry_name = NULL;
                        free(temp_PhysicalCharacteristic_name);
                        temp_PhysicalCharacteristic_name = NULL;
                        break;
                    }
                }
            }
            case '4':{
                printf("What is your Jerry's ID ? \n");
                char *jerry_name = readInput(buffer);
                if (jerry_name== NULL)memoryCleaner(jerry_hashTable, characteristic_multiValueHashTable, planet_linkedList,
                                                    jerry_linkedList, 1);
                Jerry *jerry_temp = lookupInHashTable(jerry_hashTable, jerry_name); // no need to free
                if (jerry_temp == NULL) {
                    // the jerry does not exist in the hashTable
                    printf("Rick this Jerry is not in the daycare ! \n");
                    free(jerry_name);
                    jerry_temp = NULL;
                    break;
                }

                // remove the jerry and clean its memory
                removeFromHashTable(jerry_hashTable, jerry_name);
                for (int i = 0; i < jerry_temp->PhysicalCharacteristics_amount; i++) {
                    removeFromMultiValueHashTable(characteristic_multiValueHashTable,
                                                  jerry_temp->PhysicalCharacteristics_list[i]->PhysicalCharacteristic_name,
                                                  jerry_temp);
                }
                deleteNode(jerry_linkedList, jerry_temp);
                free(jerry_name);
                jerry_name = NULL;
                printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
                break;
            }
            case '5':{
                printf("What do you remember about your Jerry ? \n");
                char* temp_PhysicalCharacteristic_name = readInput(buffer);
                if (temp_PhysicalCharacteristic_name==NULL){
                    memoryCleaner(jerry_hashTable, characteristic_multiValueHashTable, planet_linkedList,
                                  jerry_linkedList, 1);
                }

                LinkedList list_of_jerries = lookupInMultiValueHashTable(characteristic_multiValueHashTable,temp_PhysicalCharacteristic_name);
                // if the search within the multialevaluehashtable is empty, its means physical characteristic doesn't exist
                if (list_of_jerries == NULL) {
                    printf("Rick we can not help you - we do not know any Jerry's %s ! \n",temp_PhysicalCharacteristic_name);
                    free(temp_PhysicalCharacteristic_name);
                    temp_PhysicalCharacteristic_name=NULL;
                    break;
                }
                else{
                    printf("What do you remember about the value of his %s ? \n",temp_PhysicalCharacteristic_name);
                    double iteration_diff=0;
                    char* temp_PhysicalCharacteristic_value = readInput(buffer);
                    double min_diff = fabs(valueOfPhysicalCharacteristicByJerry((Jerry *) getDataByIndex(list_of_jerries,1),temp_PhysicalCharacteristic_name)-atof(temp_PhysicalCharacteristic_value));

                    // the program uses 2 for loop. first to find the lowest diff and then to find the jerry which match the founded diff
                    for (int i=2; i<=getLengthList(list_of_jerries); i++){
                        iteration_diff=fabs(valueOfPhysicalCharacteristicByJerry((Jerry *) getDataByIndex(list_of_jerries,i),temp_PhysicalCharacteristic_name)-atof(temp_PhysicalCharacteristic_value));
                        if(iteration_diff<min_diff)
                            min_diff=iteration_diff;
                    }
                    for (int i=1; i<=getLengthList(list_of_jerries); i++){
                        iteration_diff=fabs(valueOfPhysicalCharacteristicByJerry((Jerry *) getDataByIndex(list_of_jerries,i),temp_PhysicalCharacteristic_name)-atof(temp_PhysicalCharacteristic_value));
                        if(iteration_diff==min_diff){
                            printf("Rick this is the most suitable Jerry we found : \n");
                            Jerry * pJerry_temp =  getDataByIndex(list_of_jerries,i);
                            printJerryValue(pJerry_temp);

                            // clean and delete it memory section
                            removeFromHashTable(jerry_hashTable,pJerry_temp->jerry_name);
                            for (int j=0; j<pJerry_temp->PhysicalCharacteristics_amount; j++){
                                removeFromMultiValueHashTable(characteristic_multiValueHashTable,pJerry_temp->PhysicalCharacteristics_list[j]->PhysicalCharacteristic_name,pJerry_temp);
                            }
                            deleteNode(jerry_linkedList,pJerry_temp);
                            // clean and delete it memory section

                            printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
                            free(temp_PhysicalCharacteristic_name);
                            temp_PhysicalCharacteristic_name=NULL;
                            free(temp_PhysicalCharacteristic_value);
                            temp_PhysicalCharacteristic_value=NULL;
                            pJerry_temp=NULL;
                            break;
                        }
                    }
                    break;
                }
            }
            case '6':{
                if(getLengthList(jerry_linkedList)==0){
                    printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
                    break;
                }
                else {
                    // look of the jerry with lowest happy_level by searching in the linked list of each index of the hashtable
                    Jerry * saddest_jerry = getDataByIndex(jerry_linkedList,1);
                    Jerry * current_jerry;
                    for(int i=2; i<=getLengthList(jerry_linkedList); i++){
                        current_jerry= getDataByIndex(jerry_linkedList,i);
                        if((current_jerry->happy_level)<saddest_jerry->happy_level){
                            saddest_jerry=current_jerry;
                        }
                    }
                    printf("Rick this is the most suitable Jerry we found : \n");
                    PrintJerry(saddest_jerry);
                    printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");

                    // remove the jerry and clean up its relevant memory
                    removeFromHashTable(jerry_hashTable,saddest_jerry->jerry_name);
                    for (int i=0; i<saddest_jerry->PhysicalCharacteristics_amount; i++){
                        removeFromMultiValueHashTable(characteristic_multiValueHashTable,saddest_jerry->PhysicalCharacteristics_list[i]->PhysicalCharacteristic_name,saddest_jerry);
                    }
                    deleteNode(jerry_linkedList,saddest_jerry);
                    current_jerry = NULL;
                    break;
                }
            }
            case '7': {
                char choice[1];
                printf("What information do you want to know ? \n1 : All Jerries \n2 : All Jerries by physical characteristics \n3 : All known planets \n");
                scanf("%s",choice);
                if (atoi(&choice[0])< 1 || atoi(&choice[0]) > 3 || strlen(&choice[0])>1) {
                    printf("Rick this option is not known to the daycare ! \n");
                    break;
                }
                else {
                    switch (choice[0]) {
                        case '1': {
                            if(getLengthList(jerry_linkedList)==0){
                                printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
                                break;
                            }
                            displayList(jerry_linkedList);
                            break;
                        }
                        case '2': {
                            // find the physical characteristics within the multivaluehashtable and return its list of values
                            printf("What physical characteristics ? \n");
                            char* temp_physical_char=readInput(buffer);
                            if(lookupInMultiValueHashTable(characteristic_multiValueHashTable, temp_physical_char)==NULL){
                                printf("Rick we can not help you - we do not know any Jerry's %s ! \n",temp_physical_char);
                                free(temp_physical_char);
                                break;
                            }
                            printf("%s : \n",temp_physical_char);
                            displayMultiValueHashElementsByKey(characteristic_multiValueHashTable, temp_physical_char);
                            free(temp_physical_char);
                            break;
                        }
                        case '3': {
                            displayList(planet_linkedList);
                            break;
                        }
                    }
                }
                break;
            }

            case '8':{
                char choice[1];
                if(getLengthList(jerry_linkedList)==0){
                    printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
                    break;
                }
                printf("What activity do you want the Jerries to partake in ? \n1 : Interact with fake Beth \n2 : Play golf \n3 : Adjust the picture settings on the TV \n");
                scanf("%s",choice);
                // verify that the input choice is the right format
                if (atoi(&choice[0])< 1 || atoi(&choice[0]) > 3 || strlen(&choice[0])>1) {
                    printf("Rick this option is not known to the daycare ! \n");
                    break;
                }
                switch (choice[0]) {
                    case '1': {
                        Jerry *current_jerry;
                        for (int i = 1; i <= getLengthList(jerry_linkedList); i++) {
                            current_jerry = ((Jerry *) getDataByIndex(jerry_linkedList, i));
                            if (current_jerry->happy_level >= 20) {
                                current_jerry->happy_level += 15;
                                if(current_jerry->happy_level>100)
                                    current_jerry->happy_level=100;
                            }
                            else {
                                current_jerry->happy_level = current_jerry->happy_level - 5;
                                if(current_jerry->happy_level<0)
                                    current_jerry->happy_level=0;
                            }
                        }
                        break;
                    }
                    case '2': {
                        Jerry *current_jerry;
                        for (int i = 1; i <= getLengthList(jerry_linkedList); i++) {
                            current_jerry = ((Jerry *) getDataByIndex(jerry_linkedList, i));
                            if (current_jerry->happy_level >= 50) {
                                current_jerry->happy_level = current_jerry->happy_level + 10;
                                if(current_jerry->happy_level>100)
                                    current_jerry->happy_level=100;
                            }
                            else {
                                current_jerry->happy_level = current_jerry->happy_level - 10;
                                if(current_jerry->happy_level<0)
                                    current_jerry->happy_level=0;
                            }
                        }
                        break;
                    }
                    case '3': {
                        Jerry *current_jerry;
                        for (int i = 1; i <= getLengthList(jerry_linkedList); i++) {
                            current_jerry = ((Jerry *) getDataByIndex(jerry_linkedList, i));
                            current_jerry->happy_level += 20;
                            if(current_jerry->happy_level>100)
                                current_jerry->happy_level=100;
                        }
                        break;
                    }
                }
                printf("The activity is now over ! \n");
                displayList(jerry_linkedList);
                break;
            }
            case '9':{
                // clear the memory and exist
                printf("The daycare is now clean and close ! \n");
                memoryCleaner(jerry_hashTable, characteristic_multiValueHashTable, planet_linkedList, jerry_linkedList,0);
                exit(0);
            }
        }
    }
}
