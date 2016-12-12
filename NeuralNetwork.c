//
//  NeuralNetwork.c
//  
//
//  Created by Даниил on 16/09/2016.
//
//

#define sigmoid(in) 1.0/(1.0 + exp(-(in/(2*NUM_HIDDEN))))
#define sigmoid_derivative(s) = s * (1.0 - s)

#include "NeuralNetwork.h"

double error;
double eta = 0.1;
double *input;
double *trgtOut;
double sumH[1 + NUM_HIDDEN];
double sumO[1 + NUM_OUTPUT];
double sumDOW[1 + NUM_HIDDEN];
double hidden[1 + NUM_HIDDEN];
double output[1 + NUM_OUTPUT];
double deltaO[1 + NUM_OUTPUT];
double deltaH[1 + NUM_HIDDEN];
double weightIH[1 + NUM_INPUT][1 + NUM_HIDDEN];
double weightHO[1 + NUM_HIDDEN][1 + NUM_OUTPUT];

//TODO: make this normal distribution
void initialize(){
    srand(12345);
    for(int j = 1; j <= NUM_HIDDEN; j++){
        for(int i = 0; i <= NUM_INPUT; i++){
            weightIH[i][j] = 2.0 * ((float)rand()/(float)RAND_MAX - 0.5) * 0.5;
            //printf("weightIH is %f\n", weightIH[i][j]);
        }
    }
    
    for(int k = 1; k <= NUM_OUTPUT; k++){
        for(int j = 0; j <= NUM_HIDDEN; j++){
            weightHO[j][k] = 2.0 * ((float)rand()/(float)RAND_MAX - 0.5) * 0.5;
            //printf("weightHO is %f\n", weightIH[j][k]);
        }
    }
}

double doCycle(struct data* d){
    error = 0;
    input = d->input;
    trgtOut = d->targetOutput;
    
    for(int j = 1; j <= NUM_HIDDEN; j++){
        sumH[j] = weightIH[0][j];
        for(int i = 1; i <= NUM_INPUT; i++){
            sumH[j] += ((float)input[i]/100) * weightIH[i][j];
        }
      //  printf("sum is %f\n", exp(-(sumH[j]/NUM_INPUT)));
        hidden[j] = sigmoid(sumH[j]);
        // printf("hidden is %f\n", hidden[j]);
    }
    
    for(int k = 1; k <= NUM_OUTPUT; k++){
        sumO[k] = weightHO[0][k];
        for(int j = 1; j <= NUM_HIDDEN; j++){
            sumO[k] += hidden[j] * weightHO[j][k];
        }
        output[k] = sigmoid(sumO[k]);
        //printf("%f\n", output[k]);
        //printf("output: %f, target: %f\n", output[k], trgtOut[k]);
        //error += 0.5 * (trgtOut[k] - output[k]) * (trgtOut[k] - output[k]);
        if (output[k] == 0) output[k] = 0.00000001;
        error -= (trgtOut[k] * log(output[k]) + (1 - trgtOut[k]) * log(1 - output[k]));
        //printf("error: %f\n", error);
        //deltaO[k] = (trgtOut[k] - output[k]) * output[k] * (1.0 - output[k]);
        deltaO[k] = trgtOut[k] - output[k];
        //printf("output: %f, target: %f\n", output[k], trgtOut[k]);
    }
    
    for(int j = 1; j <= NUM_HIDDEN; j++){
        sumDOW[j] = 0.0;
        for(int k = 1; k <= NUM_OUTPUT; k++){
            sumDOW[j] += weightHO[j][k] * deltaO[k];
        }
        deltaH[j] = sumDOW[j] * hidden[j] * (1.0 - hidden[j]);
    }
    
    for(int j = 1; j <= NUM_HIDDEN; j++){
        weightIH[0][j] += eta * deltaH[j];
        for (int i = 0; i <= NUM_INPUT; i++){
            weightIH[i][j] += eta * ((float)input[i]/100) * deltaH[j];
        }
    }
    
    for(int k = 1; k <= NUM_OUTPUT; k++){
        weightHO[0][k] += eta * deltaO[k];
        for(int j = 1; j <= NUM_HIDDEN; j++){
            weightHO[j][k] += eta * hidden[j] * deltaO[k];
        }
    }
    return error;
}
