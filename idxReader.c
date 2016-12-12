//
//  idxReader.c
//  
//
//  Created by Даниил on 09/09/2016.
//
//

#include "idxReader.h"

FILE *fpV, *fpL;
int n = 0;
struct data *p;

void closeStreams(){
    fclose(fpV);
    fclose(fpL);
}

int prepareData(char t){
    if(t == TRAINING){
        if((fpV = fopen(TRAINING_VALUES, "r")) == NULL){
            fprintf(stderr, "cannot open %s\n", TRAINING_VALUES);
            exit(1);
        }else if((fpL = fopen(TRAINING_LABELS, "r")) == NULL){
            fprintf(stderr, "cannot open %s\n", TRAINING_LABELS);
            exit(1);
        }else{
            fseek(fpV, SIZE_OFFSET, SEEK_SET);
            for(int i = 0; i < 4; i++)
                n = n << 8 | getc(fpV);
            p = malloc(sizeof(struct data));
            return n;
        }
    }else if(t == TEST){
        if((fpV = fopen(TEST_VALUES, "r")) == NULL){
            fprintf(stderr, "cannot open %s\n", TEST_VALUES);
            exit(1);
        }else if((fpL = fopen(TEST_LABELS, "r")) == NULL){
            fprintf(stderr, "cannot open %s\n", TRAINING_LABELS);
            exit(1);
        }else{
            fseek(fpV, SIZE_OFFSET, SEEK_SET);
            for(int i = 0; i < 4; i++)
                n = n << 8 | getc(fpV);
            p = malloc(sizeof(struct data));
            return n;
        }
    }else{
        return -1;
    }
}

struct data *getData(int position){
    fseek(fpV, IMG_OFFSET + (IMG_SIZE * position), SEEK_SET);
    fseek(fpL, LBL_OFFSET + position, SEEK_SET);
    
    for(int i = 0; i < TRGT_VCTR_SIZE; i++)
        p->targetOutput[i] = 0.0;
    int n;
    if((n = getc(fpL)) == EOF)
        return NULL;
    p->targetOutput[n] = 1.0;

    for(int i = 0; i < IMG_SIZE; i++){
        if((n = getc(fpV)) == EOF)
            return NULL;
        p->input[i] = (double)n;
    }
    return p;
}
