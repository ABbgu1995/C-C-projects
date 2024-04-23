
#include "KeyValuePair.h"
#include <string.h>
#include <stdio.h>
#include "malloc.h"
#include "LinkedList.h"


struct KeyValuePair_t{
    Element key;
    Element value;
    CopyFunction copy_key;
    FreeFunction free_key;
    EqualFunction equal_key;
    PrintFunction print_key;
    CopyFunction copy_value;
    FreeFunction free_value;
    PrintFunction print_value;
};

KeyValuePair createKeyValuePair(Element key, Element value,
                                CopyFunction copy_key, FreeFunction free_key, EqualFunction equal_key, PrintFunction print_key,
                                CopyFunction copy_value, FreeFunction free_value, PrintFunction print_value){
    if (key == NULL || value == NULL) return NULL;
    KeyValuePair keyValuePair = (KeyValuePair) malloc(sizeof(struct KeyValuePair_t));
    if(keyValuePair == NULL) return NULL;

    keyValuePair->value=copy_value(value);
    if(keyValuePair->value==NULL) {
        free(keyValuePair);
        return NULL;
    }
    keyValuePair->key=copy_key(key);
    if(keyValuePair->value==NULL) {
        free(keyValuePair);
        return NULL;
    }
    keyValuePair->copy_key=copy_key;
    keyValuePair->free_key=free_key;
    keyValuePair->equal_key=equal_key;
    keyValuePair->print_key=print_key;
    keyValuePair->copy_value=copy_value;
    keyValuePair->free_value=free_value;
    keyValuePair->print_value=print_value;
    return keyValuePair;
};

void destroyKeyValuePair (KeyValuePair keyValuePair){
    if(keyValuePair!=NULL) {
        keyValuePair->free_value(keyValuePair->value);
        keyValuePair->free_value=NULL;
        keyValuePair->free_key(keyValuePair->key);
        keyValuePair->free_key=NULL;
        free(keyValuePair);
        keyValuePair=NULL;
    }
};
status displayValue(KeyValuePair keyValuePair){
    if(keyValuePair==NULL) return failure;
    keyValuePair->print_value(keyValuePair->value);
    return success;
};

status displayKey(KeyValuePair keyValuePair){
    if(keyValuePair==NULL) return failure;
    keyValuePair->print_key(keyValuePair->key);
    return success;
};
Element getValue(KeyValuePair keyValuePair){
    // the function receive a KeyValuePair and return its value
    if(keyValuePair==NULL) return NULL;
    Element e;
    e = keyValuePair->copy_value(keyValuePair->value);
    if(e==NULL){
        free(e);
        e=NULL;
        return NULL;
    }
    return e;
};
Element getKey(KeyValuePair keyValuePair){
    // the function receive a KeyValuePair and return its key
    if(keyValuePair==NULL) return NULL;
    Element e;
    e = keyValuePair->copy_key(keyValuePair->key);
    if(e==NULL){
        free(e);
        e=NULL;
        return NULL;
    }
    return e;
};
enum e_bool isEqualKey(KeyValuePair keyValuePair, Element key){
    if(keyValuePair==NULL) return false;
    if(keyValuePair->equal_key(keyValuePair->key, key) == true)
        return true;
    return false;
}

KeyValuePair copyKeyValuePair(KeyValuePair pair){
    // flat_copy to a pair
    KeyValuePair copy_keyValuePair = pair;
    return copy_keyValuePair;
}

