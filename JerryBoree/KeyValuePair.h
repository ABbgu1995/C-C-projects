
#ifndef KEYVALUEPAIR_H
#define KEYVALUEPAIR_H

#include "Defs.h"

typedef struct KeyValuePair_t *KeyValuePair; //

KeyValuePair createKeyValuePair(Element key, Element value,
                                CopyFunction copy_key, FreeFunction free_key, EqualFunction equal_key, PrintFunction print_key,
                                CopyFunction copy_value, FreeFunction free_value, PrintFunction print_value);
void destroyKeyValuePair (KeyValuePair keyValuePair);
status displayValue(KeyValuePair keyValuePair);
status displayKey(KeyValuePair keyValuePair);
Element getValue(KeyValuePair keyValuePair);
Element getKey(KeyValuePair keyValuePair);
bool isEqualKey(KeyValuePair keyValuePair, Element key);
KeyValuePair copyKeyValuePair(KeyValuePair pair);
#endif
