#include <utils.h>
#include "map.h"


int32_t hash(const char* key, int32_t bounds){
    int32_t index = 0;
    for (int32_t i = 0; *(key++) != '\0'; i++){
        // c = index - (31 * i)
        index += (31 * i) + (int8_t) *key;
    }
    return index % bounds;
}


void swap(char* c, char* k){
    char temp = *c;
    *c = *k;
    *k = temp;
}

void testHash(){
    const char* alphabet = "abcdefghijklmnopqrstuvwxyz";
    uint32_t len = strlen(alphabet);
    int32_t index = hash(alphabet, len);
    printf("%d", index);
}

const char* permute(char* key){
    uint32_t len = strlen(key);
    uint32_t first = rand() % len;
    uint32_t second = rand() % len;
    swap(&key[first], &key[second]);
}

