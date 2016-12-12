//
//  main.c
//  Shallow neural network
//
//  Created by Даниил on 09/09/2016.
//  Copyright (c) 2016 Даниил. All rights reserved.
//

#include <stdio.h>
#include "arrayShuffler.h"
#include "NeuralNetwork.h"
#include "idxReader.h"


void swapInt(void *ar, int j, int k){
    int* p = (int*)ar;
    int t = p[j];
    p[j] = p[k];
    p[k] = t;
}

int main(int argc, const char * argv[]) {
    printf("hello %d\n", 11);
    int fill, dataSize = prepareData(TRAINING) - 1;
    int ar[dataSize];
    int batchSize = 10;
    
    fill = 1;
    for (int i = 0; i < dataSize; i++){
        ar[i] = fill++;
    }
    printf("started");
    initialize();
    printf("initialized");
    for(;;){
        shuffle((void*)ar, dataSize, swapInt);
        int index = 0;
        double err = 0;
        while(index < dataSize){
            err = 0;
            for(int i = 0; i < batchSize; i++){
                struct data* d = getData(ar[index]);
                err += doCycle(d);
                index++;
            }
            printf("error is: %f\n", err/batchSize);
            if(err/batchSize < 0.0004)
                goto staph;
        }
        
    }
staph:
    closeStreams();
    printf("program finished");
}
