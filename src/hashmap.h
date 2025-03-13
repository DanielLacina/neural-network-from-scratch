#ifndef HASHMAP_H  
#define HASHMAP_H

#include <stdio.h>
#include <stdlib.h>
#include "array.h" 

#define DEFINE_HASHMAP(TYPE) \
typedef struct {\
    Array_##TYPE *data;\
} HashMap;\
#endif