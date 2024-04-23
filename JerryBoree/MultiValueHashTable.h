#ifndef MULTIVALUEHASHTABLE_H
#define MULTIVALUEHASHTABLE_H
#include "Defs.h"
#include "HashTable.h"
#include "LinkedList.h"
typedef struct multiValueHashTable_s *multiValueHashTable;

multiValueHashTable createMultiValueHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey,
                                              CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue,
                                              EqualFunction equalKey, EqualFunction equalValue, TransformIntoNumberFunction transformIntoNumber, int hashNumber);
void destroyMultiValueHashTable(multiValueHashTable multiValueHashTable1);
status addToMultiValueHashTable(multiValueHashTable multiValueHashTable1, Element key,Element value);
LinkedList lookupInMultiValueHashTable(multiValueHashTable multiValueHashTable1, Element key);
status removeFromMultiValueHashTable(multiValueHashTable multiValueHashTable1, Element key, Element value);
status displayMultiValueHashElementsByKey(multiValueHashTable multiValueHashTable1, Element key);
#endif

