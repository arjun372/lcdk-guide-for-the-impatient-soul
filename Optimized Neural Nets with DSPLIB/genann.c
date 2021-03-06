/*
 * GENANN - Minimal C Artificial Neural Network
 *
 * Copyright (c) 2015, 2016 Lewis Van Winkle
 *
 * http://CodePlea.com
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgement in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 */

#include "genann.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>

#define LOOKUP_SIZE 4096
#define MIN -15.0
#define MAX  15.0

inline float RoughSigmoid(const float value)
{
  const float x2 = value * value;
  const float sum = 1 + x2*0.555f + x2*x2*0.143f;
  if(value > 0)
  {
     const float e = sum + value;
     return 1.0f / (1 + (1.0f/e));
  }
  return 1.0f / (1 + (sum - value));
}



inline float genann_act_sigmoid(const float a) {
  return 1.0f / (1 + expf(-a));
  //return RoughSigmoid(a);
}

inline float genann_act_tanh(const float a) {
  return tanhf(a);
}

float genann_act_sigmoid_cached(const float a) {

  return genann_act_sigmoid(a);
    /* If you're optimizing for memory usage, just
     * delete this entire function and replace references
     * of genann_act_sigmoid_cached to genann_act_sigmoid
     */
    const float min = -15.0f;
    const float max = 15.0f;
    static float interval;
    static int initialized = 0;
    static float lookup[LOOKUP_SIZE];

    /* Calculate entire lookup table on first run. */
    if (!initialized) {
        interval = (max - min) / LOOKUP_SIZE;
        int i;
        for (i = 0; i < LOOKUP_SIZE; ++i) {
            lookup[i] = genann_act_sigmoid(min + interval * i);
        }
        /* This is down here to make this thread safe. */
        initialized = 1;
    }

    int i;
    i = (int)((a-min)/interval+0.5);
    if (i <= 0) return lookup[0];
    if (i >= LOOKUP_SIZE) return lookup[LOOKUP_SIZE-1];
    return lookup[i];
}


inline float genann_act_threshold(const float a) {
    return a > 0;
}


inline float genann_act_relu(const float a) {
    return (a >= 0) ? a : 0;
}

inline float genann_act_linear(const float a) {
    return a;
}


genann *genann_init(const size_t inputs, const size_t hidden_layers, const size_t hidden, const size_t outputs) {
    if (hidden_layers < 0) return 0;
    if (inputs < 1) return 0;
    if (outputs < 1) return 0;
    if (hidden_layers > 0 && hidden < 1) return 0;

    const size_t hidden_weights = hidden_layers ? (inputs+1) * hidden + (hidden_layers-1) * (hidden+1) * hidden : 0;
    const size_t output_weights = (hidden_layers ? (hidden+1) : (inputs+1)) * outputs;
    const size_t total_weights = (hidden_weights + output_weights);

    const size_t total_neurons = (inputs + hidden * hidden_layers + outputs);

    /* Allocate extra size for weights, outputs, and deltas. */
    const size_t size = sizeof(genann) + sizeof(float) * (total_weights + total_neurons + (total_neurons - inputs));
    genann *ret = malloc(size);
    if (!ret) return 0;

    ret->inputs = inputs;
    ret->hidden_layers = hidden_layers;
    ret->hidden = hidden;
    ret->outputs = outputs;

    ret->total_weights = total_weights;
    ret->total_neurons = total_neurons;

    /* Set pointers. */
    ret->weight = (float*)((char*)ret + sizeof(genann));
    ret->output = ret->weight + ret->total_weights;
    ret->delta = ret->output + ret->total_neurons;

    genann_randomize(ret);

    ret->activation_hidden = genann_act_sigmoid_cached;
    ret->activation_output = genann_act_sigmoid_cached;

    return ret;
}


genann *genann_read(FILE *in) {
    int inputs, hidden_layers, hidden, outputs;
    fscanf(in, "%d %d %d %d", &inputs, &hidden_layers, &hidden, &outputs);

    genann *ann = genann_init(inputs, hidden_layers, hidden, outputs);

    int i;
    for (i = 0; i < ann->total_weights; ++i) {
        fscanf(in, " %le", ann->weight + i);
    }

    return ann;
}


genann *genann_copy(genann const *ann) {
    const int size = sizeof(genann) + sizeof(float) * (ann->total_weights + ann->total_neurons + (ann->total_neurons - ann->inputs));
    genann *ret = malloc(size);
    if (!ret) return 0;

    memcpy(ret, ann, size);

    /* Set pointers. */
    ret->weight = (float*)((char*)ret + sizeof(genann));
    ret->output = ret->weight + ret->total_weights;
    ret->delta = ret->output + ret->total_neurons;

    return ret;
}


void genann_randomize(genann *ann) {
    int i;
    srand(time(NULL));
    for (i = 0; i < ann->total_weights; ++i)
    {
        /* Sets weights from -0.5 to 0.5. */
        ann->weight[i] = (GENANN_RANDOM() - 0.5f) * 2.0f;
    }
}


void genann_free(genann *ann) {
    /* The weight, output, and delta pointers go to the same buffer. */
    free(ann);
}


float const *genann_run(genann const *ann, float const *inputs) {
    float const *w = ann->weight;
    float *o = ann->output + ann->inputs;
    float const *i = ann->output;

    /* Copy the inputs to the scratch area, where we also store each neuron's
     * output, for consistency. This way the first layer isn't a special case. */
    memcpy(ann->output, inputs, sizeof(float) * ann->inputs);

    int h, j, k;

    const genann_actfun act = ann->activation_hidden;
    const genann_actfun acto = ann->activation_output;

    /* Figure hidden layers, if any. */
    for (h = 0; h < ann->hidden_layers; ++h) {
        for (j = 0; j < ann->hidden; ++j) {
            float sum = 0;
            for (k = 0; k < (h == 0 ? ann->inputs : ann->hidden) + 1; ++k) {
                if (k == 0) {
                    sum += *w++ * -1.0;
                } else {
                    sum += *w++ * i[k-1];
                }
            }
            *o++ = act(sum);
        }


        i += (h == 0 ? ann->inputs : ann->hidden);
    }

    float const *ret = o;

    /* Figure output layer. */
    for (j = 0; j < ann->outputs; ++j) {
        float sum = 0;
        for (k = 0; k < (ann->hidden_layers ? ann->hidden : ann->inputs) + 1; ++k) {
            if (k == 0) {
                sum += *w++ * -1.0;
            } else {
                sum += *w++ * i[k-1];
            }
        }
        *o++ = acto(sum);
    }

    /* Sanity check that we used all weights and wrote all outputs. */
    assert(w - ann->weight == ann->total_weights);
    assert(o - ann->output == ann->total_neurons);

    return ret;
}


void genann_train(genann const *ann, float const *inputs, float const *desired_outputs, float learning_rate) {
    /* To begin with, we must run the network forward. */
    genann_run(ann, inputs);

    int h, j, k;

    /* First set the output layer deltas. */
    {
        float const *o = ann->output + ann->inputs + ann->hidden * ann->hidden_layers; /* First output. */
        float *d = ann->delta + ann->hidden * ann->hidden_layers; /* First delta. */
        float const *t = desired_outputs; /* First desired output. */


        /* Set output layer deltas. */
        if (ann->activation_output == genann_act_linear) {
            for (j = 0; j < ann->outputs; ++j) {
                *d++ = *t++ - *o++;
            }
        } else {
            for (j = 0; j < ann->outputs; ++j) {
                *d++ = (*t - *o) * *o * (1.0 - *o);
                ++o; ++t;
            }
        }
    }


    /* Set hidden layer deltas, start on last layer and work backwards. */
    /* Note that loop is skipped in the case of hidden_layers == 0. */
    for (h = ann->hidden_layers - 1; h >= 0; --h) {

        /* Find first output and delta in this layer. */
        float const *o = ann->output + ann->inputs + (h * ann->hidden);
        float *d = ann->delta + (h * ann->hidden);

        /* Find first delta in following layer (which may be hidden or output). */
        float const * const dd = ann->delta + ((h+1) * ann->hidden);

        /* Find first weight in following layer (which may be hidden or output). */
        float const * const ww = ann->weight + ((ann->inputs+1) * ann->hidden) + ((ann->hidden+1) * ann->hidden * (h));

        for (j = 0; j < ann->hidden; ++j) {

            float delta = 0;

            for (k = 0; k < (h == ann->hidden_layers-1 ? ann->outputs : ann->hidden); ++k) {
                const float forward_delta = dd[k];
                const int windex = k * (ann->hidden + 1) + (j + 1);
                const float forward_weight = ww[windex];
                delta += forward_delta * forward_weight;
            }

            *d = *o * (1.0-*o) * delta;
            ++d; ++o;
        }
    }


    /* Train the outputs. */
    {
        /* Find first output delta. */
        float const *d = ann->delta + ann->hidden * ann->hidden_layers; /* First output delta. */

        /* Find first weight to first output delta. */
        float *w = ann->weight + (ann->hidden_layers
                ? ((ann->inputs+1) * ann->hidden + (ann->hidden+1) * ann->hidden * (ann->hidden_layers-1))
                : (0));

        /* Find first output in previous layer. */
        float const * const i = ann->output + (ann->hidden_layers
                ? (ann->inputs + (ann->hidden) * (ann->hidden_layers-1))
                : 0);

        /* Set output layer weights. */
        for (j = 0; j < ann->outputs; ++j) {
            for (k = 0; k < (ann->hidden_layers ? ann->hidden : ann->inputs) + 1; ++k) {
                if (k == 0) {
                    *w++ += *d * learning_rate * -1.0;
                } else {
                    *w++ += *d * learning_rate * i[k-1];
                }
            }

            ++d;
        }

        assert(w - ann->weight == ann->total_weights);
    }


    /* Train the hidden layers. */
    for (h = ann->hidden_layers - 1; h >= 0; --h) {

        /* Find first delta in this layer. */
        float const *d = ann->delta + (h * ann->hidden);

        /* Find first input to this layer. */
        float const *i = ann->output + (h
                ? (ann->inputs + ann->hidden * (h-1))
                : 0);

        /* Find first weight to this layer. */
        float *w = ann->weight + (h
                ? ((ann->inputs+1) * ann->hidden + (ann->hidden+1) * (ann->hidden) * (h-1))
                : 0);


        for (j = 0; j < ann->hidden; ++j) {
            for (k = 0; k < (h == 0 ? ann->inputs : ann->hidden) + 1; ++k) {
                if (k == 0) {
                    *w++ += *d * learning_rate * -1.0;
                } else {
                    *w++ += *d * learning_rate * i[k-1];
                }
            }
            ++d;
        }

    }

}


void genann_write(genann const *ann, FILE *out) {
    fprintf(out, "%d %d %d %d", ann->inputs, ann->hidden_layers, ann->hidden, ann->outputs);

    int i;
    for (i = 0; i < ann->total_weights; ++i) {
        fprintf(out, " %.20e", ann->weight[i]);
    }
}
