//
//  arrayShuffler.c
//  
//
//  Created by Даниил on 12/09/2016.
//
//

#include "arrayShuffler.h"

void shuffle(void *ar, int size, void (*swap)(void*, int, int)){
    for(int i = 0; i < size - 1; i++){
        float npf = i + 1 + ((float)rand()*((float)size - i - 2))/(float)RAND_MAX;
        int np = (int) npf;
        swap(ar, i, np);
    }
}

