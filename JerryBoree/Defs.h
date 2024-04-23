
#ifndef DEFS_H
#define DEFS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum e_bool { false, true } bool;
typedef enum e_status { success, failure } status;

typedef void * Element; //Element is a pointer type void

typedef Element(*CopyFunction) (Element); //create new object in memory, copy the given element and return it address
typedef status(*FreeFunction) (Element); //free a node. because we don't know the node object type, we don't know its size, so we can't free it
typedef status(*PrintFunction) (Element);
typedef int(*TransformIntoNumberFunction) (Element);
typedef bool(*EqualFunction) (Element, Element);



#endif
