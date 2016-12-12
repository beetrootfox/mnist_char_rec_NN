//
//  NeuralNetwork.h
//  
//
//  Created by Даниил on 16/09/2016.
//
//

#ifndef ____NeuralNetwork__
#define ____NeuralNetwork__

#define NUM_INPUT 784
#define NUM_HIDDEN 30
#define NUM_OUTPUT 10

#include <stdio.h>
#include <stdLib.h>
#include <math.h>
#include "idxReader.h"

void initialize(void);
double doCycle(struct data*);

#endif /* defined(____NeuralNetwork__) */
