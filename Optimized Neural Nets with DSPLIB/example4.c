#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "genann.h"
#include "dataset.h"


/* This example is to illustrate how to use GENANN.
 * It is NOT an example of good machine learning techniques.
 */

dataset *test_data;
dataset *train_data;

size_t findMaxIdx(const float *guess, const size_t len) {
  float max = -1.f;
  size_t i,idx = 0;
  for(i = 0; i<len; i++)
  {
    if(guess[i] > max)
    {
      max = guess[i];
      idx = i;
    }
  }
  return idx;
}

float validate(genann *ann, const dataset *data) {
  size_t correct = 0;
  size_t j,k;
  for (j = 0; j < data->nSamples; ++j)
  {
    const float *example = data->input + j*(data->nInputs);
    const float *guess = genann_run(ann, example);
    const float *class = data->labels + j*(data->nLabels);

    const size_t maxIdx = findMaxIdx(guess, data->nLabels);

    if(class[maxIdx] == 1.0)
    {
      correct++;
    }
  }
  return ((float)correct/(float)data->nSamples);
}

int main(int argc, char *argv[])
{
    printf("GENANN example 5.\n");
    printf("Train an ANN on the iris dataset using backpropagation.\n");

    const char *iris_data = "example/iris.data";

    const char *class_names[3] = {"Iris-setosa", "Iris-versicolor", "Iris-virginica"};

    train_data = load_dataset("example/iris.data", 4, class_names, 3);
    test_data  = load_dataset("example/iris_test.csv", 4, class_names, 3);

    /* 4 inputs.
     * 1 hidden layer(s) of 4 neurons.
     * 3 outputs (1 per class)
     */
    printf("Training inputs: %lu, classes:%lu\n", train_data->nInputs, train_data->nLabels);
    genann *ann = genann_init(train_data->nInputs, 5, 32, train_data->nLabels);

    //ann->activation_hidden = genann_act_tanh;
    //ann->activation_output = genann_act_tanh;
  //ann->activation_hidden = genann_act_relu;
    int i, j;
    int loops = 500000;
    const float learning_rate = 0.03f;
    float tacc = -1.0f, Tacc = -1.0f;

    /* Train the network with backpropagation. */
    printf("Training for %d loops over data.\n", loops);
    for (i = 0; i < loops; ++i)
    {
        for (j = 0; j < train_data->nSamples; ++j)
        {
            const float *example = train_data->input + j*(train_data->nInputs);
            const float *label = train_data->labels  + j*(train_data->nLabels);
            genann_train(ann, example, label, learning_rate);
        }

        const float train_acc = validate(ann, train_data);
        const float test_acc = validate(ann, test_data);
        if(tacc != test_acc || Tacc !=train_acc)
        {
          tacc = test_acc;
          Tacc = train_acc;
          printf("Epoch %i: Train Accuracy: %f, Test Accuracy: %f\n", i, train_acc, test_acc);
        }

        /* printf("%1.2f ", xor_score(ann)); */
    }

    genann_free(ann);
    free_dataset(train_data);
    free_dataset(test_data);
    return 0;
}
