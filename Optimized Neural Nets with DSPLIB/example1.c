#include <stdio.h>
#include "genann.h"

int main(int argc, char *argv[])
{
    printf("GENANN example 1.\n");
    printf("Train a small ANN to the XOR function using backpropagation.\n");

    /* Input and expected out data for the XOR function. */
    const float input[4][2] = {{0., 0.}, {0., 1.}, {1., 0.}, {1., 1.}};
    const float output[4] = {0., 1., 1., 0.};
    int i,j;

    /* New network with 2 inputs,
     * 1 hidden layer of 2 neurons,
     * and 1 output. */
    genann *ann = genann_init(2, 1, 4, 1);

    ann->activation_hidden = genann_act_tanh;

    const float learning_rate = 0.1f;
    /* Train on the four labeled data points many times. */
    for (i = 0; i < 500000; ++i)
    {
      for (j = 0; j < 4; ++j)
      {
        genann_train(ann, input[j], output + j, learning_rate);
      }
    }

    const float random[1][1] = {{0.5, 0.5}};
    /* Run the network and see what it predicts. */
    printf("Output for [%1.f, %1.f] is %f.\n", input[0][0], input[0][1], *genann_run(ann, input[0]));
    printf("Output for [%1.f, %1.f] is %f.\n", input[1][0], input[1][1], *genann_run(ann, input[1]));
    printf("Output for [%1.f, %1.f] is %f.\n", input[2][0], input[2][1], *genann_run(ann, input[2]));
    printf("Output for [%1.f, %1.f] is %f.\n", input[3][0], input[3][1], *genann_run(ann, input[3]));

    genann_free(ann);
    return 0;
}
