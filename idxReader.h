//
//  idxReader.h
//  
//
//  Created by Даниил on 09/09/2016.
//
//

#ifndef ____idxReader__
#define ____idxReader__

#define TRAINING_LABELS "/Users/daniil/Downloads/train-labels-idx1-ubyte"
#define TRAINING_VALUES "/Users/daniil/Downloads/train-images-idx3-ubyte"
#define TEST_LABELS "/Users/daniil/Downloads/t10k-labels-idx1-ubyte"
#define TEST_VALUES "/Users/daniil/Downloads/t10k-images-idx3-ubyte"

#define IMG_SIZE 784
#define TRGT_VCTR_SIZE 10
#define IMG_OFFSET 16L
#define LBL_OFFSET 8L
#define SIZE_OFFSET 4L
#define TRAINING 0x1

#define TEST 0x0

#include <stdio.h>
#include <stdlib.h>

struct data{
    double input[IMG_SIZE];
    double targetOutput[TRGT_VCTR_SIZE];
};

int prepareData(char);
struct data *getData(int);
void closeStreams(void);

#endif /* defined(____idxReader__) */


