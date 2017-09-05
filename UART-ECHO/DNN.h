/*
 * DNN.h
 *
 *  Created on: Jun 12, 2017
 *      Author: root
 */

#ifndef DNN_H_
#define DNN_H_

#include <stdio.h>
#include "DSPF_sp_mat_mul.h"

#define W1 18432/4
#define W2 18432/4
#define W3 6144/4
#define W4 4096/4
#define W5 2048/4
#define W6 1024/4
#define W7 1024/4
#define W8 1024/4
#define WO 128/4

static float INPUT[48] = {0};
static int POS = 0;

static float INTER_1[48*2] = {0};
static float INTER_2[48*2] = {0};

//static unsigned char w_in[W1] = {0};
static float w_1[W1] = {0};
static float w_2[W2] = {0};
static float w_3[W3] = {0};
static float w_4[W4] = {0};
static float w_5[W5] = {0};
static float w_6[W6] = {0};
static float w_7[W7] = {0};
static float w_8[W8] = {0};
static float w_out[WO] = {0};

static void printAddress(){

    printf("w_1 : %x\n", w_1);
    printf("w_2 : %x\n", w_2);
    printf("w_3 : %x\n", w_3);
    printf("w_4 : %x\n", w_4);
    printf("w_5 : %x\n", w_5);
    printf("w_6 : %x\n", w_6);
    printf("w_7 : %x\n", w_7);
    printf("w_8 : %x\n", w_8);
    printf("w_out : %x\n", w_out);
}

static volatile int data_ready = 0;

static void reLU(float *x, const size_t N) {
    size_t i;
    for(i = 0; i < N; i++)
    {
        if (x[i] < 0)
            x[i] = 0;
    }
}

static size_t softmax(float *x, const size_t N) {
    size_t i;
    for(i = 0; i < N; i++)
    {
        printf("%f,", x[i]);
    }
    printf("\n");
    return 0;
}
static size_t predict(){

    // weights & activation for layer 1
    DSPF_sp_mat_mul_opt(INPUT, 1, 48, w_1, 48*2, INTER_1);
    reLU(INTER_1, 48*2);

    // weights & activation for layer 2
    DSPF_sp_mat_mul_opt(INTER_1, 1, 48*2, w_2, 48, INTER_2);
    reLU(INTER_2, 48);

    // weights & activation for layer 3
    DSPF_sp_mat_mul_opt(INTER_2, 1, 48, w_3, 32, INTER_1);
    reLU(INTER_1, 32);

    // weights & activation for layer 4
    DSPF_sp_mat_mul_opt(INTER_1, 1, 32, w_4, 32, INTER_2);
    reLU(INTER_2, 32);

    // weights & activation for layer 5
    DSPF_sp_mat_mul_opt(INTER_2, 1, 32, w_5, 16, INTER_1);
    reLU(INTER_1, 16);

    // weights & activation for layer 6
    DSPF_sp_mat_mul_opt(INTER_1, 1, 16, w_6, 16, INTER_2);
    reLU(INTER_2, 16);

    // weights & activation for layer 7
    DSPF_sp_mat_mul_opt(INTER_2, 1, 16, w_7, 16, INTER_1);
    reLU(INTER_1, 16);

    // weights & activation for layer 8
    DSPF_sp_mat_mul(INTER_1, 1, 16, w_8, 16, INTER_2);
    reLU(INTER_2, 16);

    // weights & activation for layer 6
    DSPF_sp_mat_mul(INTER_2, 1, 16, w_out, 4, INTER_1);
    return softmax(INTER_1, 4);

}
#endif /* DNN_H_ */
