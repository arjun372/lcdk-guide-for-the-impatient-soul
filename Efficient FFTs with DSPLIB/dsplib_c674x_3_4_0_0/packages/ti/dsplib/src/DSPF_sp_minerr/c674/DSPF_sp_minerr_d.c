/* ======================================================================= */
/* DSPF_sp_minerr_d.c -- Vocoder Codebook Search                           */
/*                Driver code; tests kernel and reports result in stdout   */
/*                                                                         */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/  */ 
/*                                                                         */
/*                                                                         */
/*  Redistribution and use in source and binary forms, with or without     */
/*  modification, are permitted provided that the following conditions     */
/*  are met:                                                               */
/*                                                                         */
/*    Redistributions of source code must retain the above copyright       */
/*    notice, this list of conditions and the following disclaimer.        */
/*                                                                         */
/*    Redistributions in binary form must reproduce the above copyright    */
/*    notice, this list of conditions and the following disclaimer in the  */
/*    documentation and/or other materials provided with the               */
/*    distribution.                                                        */
/*                                                                         */
/*    Neither the name of Texas Instruments Incorporated nor the names of  */
/*    its contributors may be used to endorse or promote products derived  */
/*    from this software without specific prior written permission.        */
/*                                                                         */
/*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS    */
/*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT      */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR  */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT   */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,  */
/*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT       */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,  */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY  */
/*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT    */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE  */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.   */
/*                                                                         */
/* ======================================================================= */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <c6x.h>

/* ======================================================================= */
/* Interface header files for the natural C and optimized C code           */
/* ======================================================================= */
#include "DSPF_sp_minerr_cn.h"
#include "DSPF_sp_minerr.h"

/* Defines */
#if defined(__TI_EABI__)
#define kernel_size _kernel_size
#endif

extern char kernel_size;

/* ======================================================================= */
/* Tell compiler arrays are double word alligned                           */
/* ======================================================================= */
#pragma DATA_ALIGN(y_opt, 8);
#pragma DATA_ALIGN(y_cn, 8);
#pragma DATA_ALIGN(maxidx_opt, 8);
#pragma DATA_ALIGN(maxidx_cn, 8);
#pragma DATA_ALIGN(ptr_err, 8);
#pragma DATA_ALIGN(ptr_x, 8);

/* ======================================================================= */
/* Parameters of fixed dataset                                             */
/* ======================================================================= */
#define GSP0_NUM    (256)
#define GSP0_TERMS    (9)

float y_cn, y_opt;
int maxidx_cn, maxidx_opt;

/* ======================================================================= */
/* Initilized arrays with fixed test data                                  */
/* ======================================================================= */
float ptr_err[GSP0_TERMS] = 
{
    3.010612, 0.3254118, -3.472238, 3.235523, -7.648690, -7.043652, -9.604707, 9.285835, 9.407459
};

float ptr_x[GSP0_NUM * GSP0_TERMS] =
{
    6.294474, 3.582711, 0.8777189, -3.238046, -6.387662, 8.874630, 9.231171, 6.018417, -5.021010,
    8.115839, -2.089696, 4.420933, -4.120539, -9.098978, 0.9831619, 5.248289, -7.149814, -0.4842873,
    -7.460264, -2.651267, 0.4499063, 4.926270, 4.463470, 4.567737, -9.853026, -0.4305105, -2.018495,
    8.267517, 9.759640, 9.874092, -9.793267, -3.051247, 1.535167, 3.600773, -4.863293, 1.988765,
    2.647185, -9.245223, -5.626468, -9.031054, 3.212337, -9.482851, 4.119015, -2.618166, 6.010454,
    -8.049191, 7.703360, -7.884035, 3.358322, -2.322628, -1.069381, 2.902575, 3.235298, -7.898624,
    -4.430036, 8.265736, -7.806051, 2.069360, 2.546930, 2.926040, 1.046198, -6.607823, 6.428844,
    0.9376297, 5.923677, -8.728172, 0.5220499, -9.567003, 0.4240599, -5.637825, -4.424320, 6.821726,
    9.150137, -8.025755, -1.908400, 4.594189, 8.211399, -2.553747, 5.447325, -6.035564, -2.909875,
    9.297770, -4.762576, -1.032542, 4.145069, 6.011173, 8.742693, -5.439434, -6.098569, -1.398610,
    -6.847738, -3.292863, -2.683677, 5.627542, 4.916949, 6.590656, -2.582705, -3.463207, 1.444784,
    9.411856, 3.594560, 5.270092, -4.240460, 6.262257, 6.981709, 7.818577, 7.606756, 4.016495,
    9.143339, -7.268937, 2.557927, 3.850640, -2.333874, -2.549315, 7.127537, -0.5779629, 4.849395,
    -0.2924871, 4.424551, 5.439608, 1.133396, 2.345585, 1.863691, -1.951329, -1.920612, 5.157682,
    6.005610, -7.864763, 8.657072, -2.069584, 1.509897, 7.451052, -3.639617, -6.415370, -2.217424,
    -7.162273, 3.075147, 9.454817, -8.768187, 0.6010342, 8.670033, 2.172709, 9.378500, -1.413950,
    -1.564775, -0.1165209, -6.159433, 5.603510, -4.498605, 3.369286, 8.203905, -1.850885, 9.126894,
    8.314711, 5.581035, -7.222516, -3.248322, -5.027421, -5.864471, 8.181965, 6.889748, 1.459427,
    5.844146, 4.300742, 3.925327, 2.157318, -0.9672251, 3.077012, 1.831888, 2.306501, 6.994440,
    9.189850, 8.074411, -8.123599, 4.825081, -5.445744, -8.558969, -3.348572, -2.467778, -4.473094,
    3.114814, 7.818449, 0.5080881, -7.903735, 6.088991, -1.865461, 7.061274, 7.543636, 2.446472,
    -9.285767, -3.316739, 0.6068850, -7.442232, 9.722084, 3.338631, -1.152042, 5.697049, 1.767234,
    6.982586, 3.974916, 7.222797, 0.9908018, -9.400161, 8.674513, 8.087109, -0.7009144, 9.269369,
    8.679865, -6.043803, -0.3029337, -0.2954121, 0.7132835, 6.219002, -9.336411, 6.279539, -8.281946,
    3.574703, -9.389181, -2.130873, 7.809513, -8.258455, -0.3090343, 0.6485291, 7.968882, 0.009977341,
    5.154802, 4.881486, 3.428622, 5.979205, 6.041828, 5.134984, 4.329947, -1.415229, 0.4317942,
    4.862650, 0.0004482269, 4.825159, 4.686822, 9.782898, -1.659051, -6.413963, -3.313412, -8.196680,
    -2.155459, -0.4015570, 0.4010496, -8.973362, -8.661075, 9.435720, -3.269341, 1.932941, 8.093330,
    3.109558, 8.094444, -3.045747, -8.542294, 8.787968, 9.759495, -6.245741, 8.039816, 7.687778,
    -6.576266, 2.197332, -7.000055, -8.229450, -9.636450, 7.282951, -3.561456, 4.041328, -1.220206,
    4.120922, 2.353327, 1.721841, 5.967017, 3.676772, -2.222324, -1.922866, -2.450898, 5.634452,
    -9.363343, 7.188847, -4.757094, 8.860163, 5.674729, -0.9051628, 0.9713259, 4.699118, -7.030700,
    -4.461541, 6.109789, -9.110918, 3.674312, 0.6827507, -5.066256, -9.025229, 9.082056, 2.396318,
    -9.076572, 1.534430, 5.098665, -7.358341, 7.707190, 5.688462, 1.054642, 0.8562622, -4.787526,
    -8.057364, -6.341551, -5.144293, 4.454491, 7.980097, 7.656752, -4.503772, 0.8021164, -1.086876,
    6.469156, -5.201360, -1.151954, -7.792931, 2.518753, 8.274233, -5.169965, -3.777807, 6.879990,
    3.896572, 7.730238, 3.755921, -7.650143, -7.242620, 1.165699, -5.137096, -8.575309, -6.075902,
    -3.658010, -9.426517, -2.815435, 2.814359, -5.643968, 1.977363, -6.916811, -6.360391, -3.922967,
    9.004442, -0.2019720, 4.726801, -3.423716, -6.357179, -7.022466, 9.128326, -8.140222, -0.3341084,
    -9.311078, -6.641457, -2.105851, 3.076241, -9.163603, 7.994268, 8.713228, -0.7302151, -3.243759,
    -1.225113, 9.573614, 3.668318, 4.982629, -7.861167, -0.9921284, 6.374289, -9.813350, 5.969716,
    -2.368831, 4.253889, 4.080949, 1.663714, 2.328871, -5.886553, 4.565237, 8.300518, 9.749752,
    5.310336, 0.009432793, -1.153892, 4.800646, 8.793221, 7.993019, -6.483766, 2.854835, -6.819049,
    5.903998, -0.5782328, -9.608447, -5.303462, -2.910885, 5.251711, -2.792581, -9.971619, -5.262404,
    -6.262548, -8.807623, -3.382843, 4.699150, -1.787418, 7.649725, -6.224200, -9.392295, 4.044733,
    -0.2047119, 3.639439, -1.513810, 9.411970, 9.686989, -4.300995, -9.976032, -5.830595, -2.490567,
    -1.088276, -9.151377, -4.594591, 7.338606, 8.911583, 3.464520, -3.671610, -0.9006767, 9.474098,
    2.926260, -8.571091, -6.058924, -8.275310, 3.532894, 3.285598, 3.992339, -7.454679, 9.446110,
    4.187297, 0.4329967, 6.434423, -2.671268, 9.766047, -7.543700, 2.505103, -9.827046, 2.873960,
    5.093733, -8.065399, -1.401571, -2.616024, 5.336628, -1.853632, 0.8612432, 4.541593, 7.201979,
    -4.479498, 6.362970, 7.755419, 3.700570, -3.266015, -4.494261, -1.219255, -2.917671, -1.962332,
    3.594054, 6.350941, -2.176340, 1.958833, 3.247638, 4.333395, -4.251454, 5.608919, 2.638616,
    3.101960, 4.448792, 5.382288, 5.787278, -5.116694, -4.332313, 0.03318214, -1.266867, 9.704733,
    -6.747766, -7.002691, -2.064170, -2.646942, -4.089855, 7.923977, 5.230924, -1.268904, 1.189548,
    -7.620047, 3.192105, 6.170282, -5.879443, 3.603567, 6.531578, 5.248161, -9.015737, 8.671839,
    -0.03271866, 0.3718987, 5.101542, -8.266669, 0.5569363, -2.199470, 1.521118, -9.007362, 4.406864,
    9.194880, 9.459492, -2.452089, 5.438679, -1.768129, -0.04194164, 4.953257, -8.177997, -0.3192301,
    -3.192286, 2.979830, -5.679622, -5.886510, 2.052765, 3.896104, 2.910690, 1.880741, 2.780622,
    1.705355, 6.006611, 5.808145, -2.234568, 5.010401, 6.687380, -7.535610, -5.178319, 7.752737,
    -5.523761, -0.9240456, 8.986078, 1.035571, 1.670664, 2.192594, 0.08795738, 6.827381, -6.025265,
    5.025341, -1.352170, -3.448691, -5.420935, 1.035851, 1.494742, -3.054774, 7.144257, -2.092674,
    -4.898098, 6.506275, 3.425287, 2.838812, 1.671412, -3.479156, -8.157046, 9.272243, 9.843506,
    0.1191416, -8.330604, -1.227100, -0.3103924, 0.2363977, -0.8715076, -7.043011, -0.2220039, -1.952968,
    3.981534, -7.336580, 6.670013, -6.963089, -8.348145, 4.275912, -6.036606, -5.593798, 3.177129,
    7.818066, -6.532228, 5.377085, 5.638639, 4.391403, 7.688101, 3.445405, -5.475827, 8.026962,
    9.185827, -2.181244, -6.654929, -7.987874, 9.923122, 4.417113, -1.369776, 0.7357559, 9.907635,
    0.9443102, 6.627596, 7.239611, -4.118673, -2.909314, -9.627745, 3.888078, 5.242194, 3.063265,
    -7.227511, 6.067287, 9.797443, -5.252540, 9.425177, 3.495530, -4.864309, -3.048657, -7.831271,
    -7.014120, -8.790576, 0.2884684, 0.6174459, -3.071025, -1.229823, -9.804827, -0.7753649, -9.277719,
    -4.849835, -2.014844, 7.685621, -8.170025, 7.730877, -1.243597, 0.6456614, 2.786475, 2.361824,
    6.814344, 0.5375175, 1.760521, -1.893691, -0.9061031, -7.659264, -4.412160, 8.346722, 1.342887,
    -4.914356, -1.664011, -6.904953, -7.903075, -1.731454, 6.293634, 8.924603, -6.768548, 9.239294,
    6.285696, 3.137197, -6.002744, -7.754321, -5.645359, -3.502891, 8.128864, 4.312708, 4.922110,
    -5.129500, 2.559467, -1.860904, 5.688558, -7.486908, -5.075438, -2.146308, 1.554777, 3.250322,
    8.585274, -4.160318, 4.974115, -4.168594, -3.821708, -3.145736, -9.502895, -1.334021, 0.4662666,
    -3.000325, -1.366977, 6.511677, 2.070669, 4.522089, -2.486157, 3.428736, 7.684856, -4.802114,
    -6.068095, -9.690257, 5.799260, 9.288452, 5.657442, 0.9310760, 6.743414, -2.138965, 9.239876,
    -4.978323, 9.681274, -3.629515, -1.350300, 3.875752, 1.238403, 9.429993, -6.420497, 0.8040810,
    2.320894, -6.656632, 0.6812820, 3.895044, -9.803955, -2.083555, -8.861342, 2.666672, -9.394597,
    -0.5342236, -7.875673, -8.200987, 5.161985, 6.864265, -2.037382, -0.9935236, 2.480011, 3.926289,
    -2.966810, -2.551805, -7.765885, -1.347153, 8.446640, 0.3073444, 1.649406, -3.441168, 0.3943233,
    6.616571, -6.037632, -7.274149, 3.109961, 5.419084, 3.150611, 3.732757, 6.059307, -8.819389,
    1.705282, -0.2062473, 3.573046, -7.804899, -9.146803, 9.018305, 4.388656, 9.989557, 7.800724,
    0.9944725, -3.210132, -0.09645939, 8.675198, -2.436277, 4.446970, 3.000814, 9.619562, -3.395955,
    8.343872, 9.032610, -6.205792, -6.250784, 4.086792, -1.998405, 4.538290, -7.459261, -5.405976,
    -4.283219, 8.406641, -0.09988403, -4.676423, 4.590261, 6.637426, -2.523046, -5.355197, -7.721027,
    5.144005, -8.946460, -7.047835, 5.956606, -5.514459, -7.313233, 1.631641, -9.527350, -3.781546,
    5.074582, 4.757162, -8.900517, -0.2479248, -4.618905, -8.790665, -7.677629, 2.148652, -5.431354,
    -2.391083, -4.617612, 7.014254, 5.379166, 3.460623, -8.315059, -8.846912, -7.783813, 3.039943,
    1.356432, -1.543287, 1.211190, -2.079865, -0.4501562, -6.722034, 9.595304, -1.850810, -8.676798,
    -8.482914, 0.9574175, 8.592178, -4.541224, 2.474328, -3.515602, -4.303526, 7.681538, -4.491372,
    -8.920998, 8.854740, 3.933344, -9.255307, -5.271101, -3.965464, 1.899486, 0.9626560, -4.363595,
    0.6159506, -1.645118, 1.655819, 3.465899, -6.457525, -9.766380, 9.243219, -2.619938, 7.601326,
    5.583344, 9.661049, 6.307943, -1.408711, 6.592867, 0.7981014, -6.284435, -5.833080, -1.113393,
    8.680214, -3.970901, 7.580278, -0.9652157, 5.338432, -8.092546, -6.139204, -1.181134, 5.118282,
    -7.401876, 4.021975, 9.778233, 2.197143, 8.689566, -7.069703, -3.167118, 9.123922, 2.065928,
    1.376472, 3.326777, -9.989552, -8.811934, -7.842222, 2.622824, 8.657959, -7.519482, 5.665319,
    -0.6121874, 0.7825289, 7.308771, -3.683772, -6.355450, 7.186409, -2.186649, -0.5847349, -7.721387,
    -9.761959, 3.962111, 2.251329, 5.454443, -8.018094, 9.484432, -4.535666, 7.137926, 9.571278,
    -3.257547, 3.330559, 9.799004, 3.928660, -0.2047243, 1.416769, -6.961059, -9.132191, 6.971933,
    -6.756354, -6.437351, 0.5536022, -7.493357, -6.135093, 9.937004, -2.057823, 3.832502, -8.987070,
    5.885691, -7.439712, -0.4095325, -7.396971, 7.917831, 1.070832, -2.505550, 9.579710, -0.6759634,
    -3.775699, 9.981609, 6.026953, -8.152953, -8.018207, 0.3091698, -7.377706, -4.334642, -3.486934,
    0.5706635, -6.577579, -5.443141, -9.843595, -9.116689, -3.386359, -1.299186, -7.324390, 2.604103,
    -6.687026, -9.347983, -0.03811455, -1.537812, 1.145903, -1.399964, -8.169737, 3.705593, -5.394017,
    2.039639, 1.223995, 8.017050, 3.111464, 5.449902, -0.1638756, 2.292539, 8.189091, 1.597699,
    -4.740574, 7.637331, 1.493224, 4.458450, -3.761199, -8.579258, -9.780418, 2.217380, 2.063127,
    3.081581, 3.383507, 6.903564, 0.6241856, -6.420350, 7.754786, 1.465207, 7.999657, 1.997581,
    3.784290, -6.191335, 4.772806, -7.823641, -3.220887, -8.707328, 5.794597, -6.131325, -1.031443,
    4.963032, -2.621669, 1.719741, 2.635327, -5.797087, -1.276301, -5.292665, 5.088491, -9.291531,
    -0.9891682, -0.7854815, -5.065310, -7.470003, 0.2030506, 6.532591, -1.039606, -3.074785, 0.2762966,
    -8.323572, 9.632759, 3.328324, -7.313934, 8.127287, -2.109306, 1.387163, -1.627492, -1.845397,
    -5.420461, -6.871901, -8.330343, -8.028118, 2.578479, 2.269498, -8.771971, -6.885603, -7.839079,
    8.266747, 7.110456, 2.519197, -7.159455, -7.969322, 6.372814, -0.07422256, 6.380013, -0.8024874,
    -6.952439, 2.895290, 3.218891, -6.634974, -2.182905, 7.724701, 2.846304, 2.498470, -0.9823446,
    6.516340, -2.474556, 4.595037, -6.075022, -8.907667, 8.622232, -5.574685, 4.771209, 1.022806,
    0.7668486, -6.181526, 7.815042, -3.650404, 0.02565861, -6.184307, 6.741129, 6.102249, 6.108086,
    9.922693, -1.434940, 9.646065, -3.671420, -1.365577, -4.828355, 9.421505, -8.655547, 4.017001,
    -8.436489, -0.3595591, 5.380582, -5.648734, 9.951206, 7.957314, 6.927458, 9.015806, 7.444710,
    -1.146435, -7.587768, 1.628929, -4.979163, 6.232052, 1.867237, 0.1199894, -0.04846001, -8.956157,
    -7.866945, 1.790150, 8.566261, 7.858448, -0.2869663, 0.07680130, -4.422488, 5.102919, -5.606374,
    9.237961, -5.476246, 1.601807, 4.064465, 7.888954, 2.256192, 4.932344, 4.848101, -0.8071594,
    -9.907315, -2.307618, -9.660341, 1.114759, -7.249068, 6.388445, -5.261392, 6.622591, 9.170671,
    5.498209, 1.659727, -7.582808, -6.311327, -2.199902, 0.6377831, 9.146906, -6.869963, 5.800907,
    6.346066, -4.963878, 7.254215, -5.759383, 8.547125, -5.958498, 2.405201, -0.8538256, -0.9625072,
    7.373894, -4.191186, -0.3140697, -8.453064, 8.349876, -0.9221306, 2.005243, 2.362011, -3.331437,
    -8.311283, 2.341818, 6.897114, 8.276009, 4.271480, -1.441782, -6.547910, 8.643667, -8.818094,
    -2.004347, -4.694382, -5.811898, 4.134304, 2.366748, 9.321056, -8.193066, 6.701765, 4.818106,
    -4.802592, 6.487526, 1.045827, 1.155779, -3.134242, 2.401102, -4.894756, 7.908470, 0.1358900,
    6.001369, 9.653267, 2.597668, -3.731420, 8.720547, 3.907799, 7.171410, 1.650371, -6.001492,
    -1.371723, 4.604977, -9.360180, -6.675929, -7.504519, 4.403292, 8.221342, 1.654936, -1.456129,
    8.212952, -3.122459, 2.294269, 2.449945, 4.611707, -3.062096, 3.992676, 7.098518, -6.626194,
    -6.363060, 1.681386, -2.751770, 9.758694, 2.929549, 0.3398085, 4.503647, -9.302686, 5.033893,
    -4.723942, -7.844620, -9.009349, -6.591360, 6.663040, 1.133892, -5.402278, 7.708401, -2.632983,
    -7.089220, 8.126163, -0.2086000, -4.844155, -2.034355, -6.870096, 1.521069, -1.845384, 8.836357,
    -7.278629, 7.593075, -6.149792, -2.064013, 4.996444, 1.241121, 6.212563, -9.272360, -9.656549,
    7.385843, 6.355211, -7.538325, -8.520104, 6.704411, 3.896066, -1.923133, 4.922958, 6.581118,
    1.594091, -4.785440, -5.890117, 3.681921, -3.550792, -1.470889, 9.768785, -6.903424, 2.531819,
    0.9972038, 1.887125, -7.069702, -1.952233, 1.045232, 6.725409, -8.200024, -7.121834, 0.7749310,
    -7.100904, -9.549748, -6.218556, 9.656704, 9.582582, 4.627742, -3.581180, 2.119181, 3.010153,
    7.060621, -1.494814, -9.146952, -1.956321, 0.9861708, -2.799379, 0.2281780, -4.910383, 4.532591,
    2.441102, -3.745622, 2.703959, 2.413439, -3.391528, -0.9157524, -8.787872, -3.516916, -8.110229,
    -2.980952, -6.770305, -4.362663, -6.912604, 2.389431, -2.272202, 4.513759, -1.964182, 7.551477,
    0.2649899, -6.424676, 0.7719336, -2.373096, -2.787269, 5.511093, 1.131115, -1.872534, -9.712757,
    -1.963840, -1.542286, 3.903260, -6.777320, 5.130191, 4.685422, 0.5871973, -2.276177, -4.113948,
    -8.480666, -8.115414, -0.01768017, 5.162249, -1.721985, -1.394443, 6.599649, 2.196036, -6.401702,
    -5.201677, 1.970473, 0.7160206, 7.422222, -0.1530981, 3.875051, 7.175180, -6.662186, 8.525885,
    -7.533621, -0.5815144, -1.096336, -2.984466, 3.894864, 8.904270, 5.780579, -6.238159, -8.636392,
    -6.321844, 3.918986, -7.521355, 3.710714, 9.454678, 5.684652, -3.643339, -8.107423, 1.621865,
    -5.200950, 3.997757, -0.1928539, -4.117027, -3.444901, 4.111437, -0.9558506, -3.536274, 2.743025,
    -1.654659, 2.770615, 7.059963, 0.6125851, 6.756063, -7.813315, 5.044559, 5.391939, 3.025385,
    -9.006911, -9.327923, 7.478548, 6.648468, 4.781445, -2.201386, -7.802766, -5.317640, 7.292440,
    8.054321, -8.623878, -4.594113, 1.949804, 9.083488, 1.818094, -7.805153, 4.807309, -8.880949,
    8.895744, -3.608005, -5.830773, -3.293774, -9.361547, -0.8123989, -4.602327, 3.856368, 6.337105,
    -0.1827183, 0.6172857, 1.299591, -4.015499, -2.862620, -8.993200, 0.4927464, 6.481564, 0.5784492,
    -0.2149477, 3.088914, 2.806236, -0.9481487, 3.253078, -5.426249, 9.453022, 6.559551, 3.887011,
    -3.245612, -1.847616, -1.659421, -1.547087, -4.369969, 6.683781, 4.208174, -4.132642, -5.751902,
    8.001078, 6.399624, -5.880490, -2.807874, -5.392339, -9.687106, -3.762801, -3.812615, 0.8655987,
    -2.615065, 4.367179, 8.958662, 1.166384, 4.222570, 7.274218, -4.170857, 0.4605961, 4.050406,
    -7.775945, 9.372986, -8.358576, 4.850907, 2.491459, -8.438619, 7.007147, -3.494020, 9.128691,
    5.605041, 0.6266785, -7.885812, -1.513304, 1.812173, 3.380852, 8.232948, 6.636850, -1.109157,
    -2.205224, -3.497086, -7.159178, -1.412884, 3.208759, 0.004225731, 2.785522, 6.205896, -8.292044,
    -5.166174, -7.887416, -6.670791, -7.502545, -9.048906, -5.640124, -4.892594, 1.139965, -8.853197,
    -1.921757, 2.219172, 2.419172, -9.511320, -3.024304, 1.432314, -8.226683, -4.740719, 2.589010,
    -8.070910, 5.576044, 1.474195, -4.196295, -0.9731884, -7.556217, 6.765112, 3.611324, 5.923581,
    -7.360534, -1.530942, -8.958443, -3.649588, -5.181900, 3.423325, 1.694373, -5.326937, 3.823826,
    8.841011, -8.183535, 8.624027, 3.073803, 4.300900, 1.991711, 8.962175, -0.8714924, -3.093843,
    9.122692, -4.670570, 4.573233, 9.138720, 7.123646, -8.880477, -8.779422, -2.308662, 8.936333,
    1.504172, -6.926866, 4.756833, 8.714617, -4.369846, -8.873139, 1.692825, 0.7720289, 0.4038057,
    -8.804409, -4.379894, -8.731910, -0.8422737, 4.621017, -6.949987, -4.297838, 9.834076, 9.076260,
    -5.304402, -1.198298, 7.208811, -5.190432, -7.244742, -9.607578, 6.554644, 5.104408, -8.528088,
    -2.936829, 0.5428553, 8.688103, 5.277959, 6.734455, -1.296490, -6.180271, 9.609097, -5.859361,
    6.423882, -0.8515129, 9.687965, 5.186548, -7.227965, 6.644428, -1.149401, -5.304347, 5.500556,
    -9.691931, 7.507431, 7.178776, 4.812962, 1.764188, 2.347803, -2.131770, 0.5711823, 8.283756,
    -9.139524, 0.3610420, 5.711180, 4.873767, -2.676864, 0.4025888, 6.531479, -8.971279, 5.651012,
    -6.620199, 8.872454, 0.2675486, -7.881592, 6.135191, 7.277365, 3.537422, 5.137509, -4.089316,
    2.982310, 2.754182, -6.447951, 3.631209, 0.07561588, -8.046041, -5.847939, 2.039596, -6.963086,
    4.634448, 9.153879, -2.028210, -0.7347879, -0.2081127, 8.161045, -3.637906, 7.143375, 6.958210,
    2.954920, -5.185859, -7.321375, -5.756736, 7.540974, -7.839666, -7.323780, 9.765543, 5.697092,
    -0.9815254, 3.522446, -9.382209, -8.029625, -2.937164, 0.3399353, 3.429258, 8.589689, -4.583370,
    0.9401779, -4.218708, 8.782833, 6.471489, -1.011129, -7.136879, 1.419822, -1.809701, -5.443786,
    -4.073584, 3.436164, -3.973879, -6.499805, 9.270607, 1.187411, -6.604659, -9.993171, -3.579535,
    4.893856, 3.902809, -4.089323, -6.728601, -9.154044, -9.908407, -7.046885, 0.8175659, 6.591236,
    -6.220900, -8.640144, -3.341274, 3.319744, 9.459167, 5.333639, -0.4784050, -5.845387, 6.443644,
    3.735509, -4.904197, -0.6586361, 7.887787, -6.215863, 6.974184, 8.162048, -5.614328, 1.413656,
    -6.329777, -5.519199, 2.963968, 0.3311644, 3.342405, 8.336426, 1.043501, -3.483875, 1.436592,
    -2.630308, 3.356655, -9.495437, 4.054046, 1.728792, 9.739365, -9.341202, -8.081012, -4.279634,
    2.512371, 6.887844, 6.844131, -6.928192, 3.502249, 0.1026621, -8.922742, 4.950674, 3.982672,
    5.604548, -3.110752, 1.180651, 9.069141, -2.779559, -4.571568, 6.101265, 4.970179, 5.925159,
    -8.377484, 5.610394, 7.081999, 0.8176813, 2.405568, -7.984990, -0.9725027, 0.8659887, -1.168219,
    8.587719, 3.506641, -3.042416, 3.594677, 6.223019, 0.1569767, -2.347075, -3.237353, -1.075688,
    5.514254, -9.865694, -1.079467, -9.268740, -9.614850, 1.712183, 5.792874, 6.646673, -0.6867514,
    -0.2641668, 2.043409, -8.915211, 6.184078, -8.322530, 5.257742, -2.714262, 1.051444, -4.419217,
    -1.282828, -2.264576, -6.457850, 4.972378, 9.496033, -8.340747, 0.6469994, 9.150864, 3.507507,
    -1.064325, 8.319824, 3.256161, -7.596260, 3.026991, 3.231924, 4.233133, 7.856667, 8.073290,
    -3.873010, -9.976979, -3.383420, 0.5009031, -5.375244, 0.3395805, 7.429531, -2.869928, 8.170517,
    0.1701736, -0.7510166, 7.969723, -3.483328, -1.930178, -6.579040, -3.426208, 0.9280386, 4.943939,
    0.2154312, -1.513020, -7.636896, 0.9289885, -7.559589, 8.771156, 3.002361, -3.066365, -4.789770,
    6.352554, -0.7816725, 9.768358, -2.022385, -4.631224, 1.809664, 9.496723, 2.456056, 3.792757,
    5.896627, 5.403194, 0.7996416, -1.698133, -4.843077, -1.187306, -8.480653, 5.932493, -7.363387,
    2.886362, -3.550564, 4.138348, -6.385245, -3.366695, 8.838379, 1.740383, 4.917498, -7.529984,
    -2.427812, 5.694786, 9.989832, -4.892265, -6.955319, 3.118277, -1.722270, -7.489275, -6.181943,
    6.231609, -0.5728569, -4.243013, -9.589285, -3.039847, -0.9610853, -3.817272, 6.447880, -7.085358,
    0.6565113, -9.284745, -1.709549, 8.473513, -7.566831, 6.793949, -4.723320, -9.496990, 1.700872,
    -2.985458, -6.482512, -0.7032013, 3.073997, 7.683062, 0.6524706, 5.175325, -1.711422, -8.532766,
    8.780031, 4.435160, 5.279141, 8.652271, -8.114432, 1.077742, 9.904320, 4.628149, 6.446526,
    7.518856, -0.5302801, 6.364080, -6.729753, 8.600811, 3.601311, -6.268571, 5.627480, 4.458059,
    1.003127, -6.945576, -7.995569, 8.421946, -2.019601, -2.656202, 5.622906, -2.654282, 8.517160,
    2.449502, -3.177508, -6.437661, 5.893158, -9.051970, -5.214188, -6.084041, 4.897357, -0.1472282,
    1.740894, 2.147784, -2.807302, 1.547884, -3.152530, 1.578469, 9.847179, 7.845343, 3.097658,
    -5.845154, -6.165095, -8.865906, -1.199288, 4.719323, 7.337740, 6.045231, -5.147932, 7.802469,
    -3.975073, 4.768538, 0.4377136, -4.847725, 5.893642, -1.864465, -1.515466, -7.408061, 0.7705116,
    -0.5815334, -5.143008, -3.283020, 5.038928, 0.8981180, -7.747697, 4.577278, -5.498642, -4.355897,
    -5.390237, 8.348486, -6.486619, -5.426610, 3.724469, -1.123083, -0.03292847, -2.999722, 9.519150,
    6.886175, -4.618768, -5.821066, -8.716258, 7.872654, -3.996312, 6.179806, -4.258308, -9.271490,
    -6.104714, 5.310000, 8.103071, 5.346590, -8.904164, -1.972263, -2.869821, 8.549761, -3.475109,
    -5.481565, -6.226760, 3.507824, 3.424044, -3.926773, 6.667273, -8.535131, -8.973724, 9.460274,
    -6.585839, -4.250036, -0.6306362, 4.304251, -9.076169, -1.927426, 1.819829, 1.853334, -2.699347,
    -5.446714, -8.177731, 8.242649, 2.841216, -6.090465, -2.196481, 8.203756, -6.742022, -3.817008,
    -1.286026, 1.524187, -7.919768, -1.619035, 4.403316, -2.791022, -6.124681, 6.768116, -7.581752,
    -3.777954, 3.667265, 4.910922, -2.184758, 4.435066, -7.194893, -1.352644, -6.648781, 8.315313,
    8.467594, 0.9318628, 4.725349, 6.322802, 7.555983, -4.797396, 4.983195, 0.04401207, -7.290436,
    -1.395852, -1.485423, 1.237228, -3.651443, 1.648660, -8.263698, -9.216311, 9.986589, -3.357642,
    -6.303674, 2.888856, -6.316118, 6.290796, -8.586313, -1.412053, 8.926500, -2.891857, 7.949598,
    8.097618, 2.952353, 1.944227, 5.781470, 8.454891, -4.854344, 5.273466, -9.058446, -0.007024765,
    9.594967, 3.580336, -4.001260, 7.045277, 6.007441, -4.048892, 1.176411, -5.726789, 2.305765,
    -1.222600, 2.715734, -7.317541, 0.1127329, -4.281063, -1.502831, -6.323141, -2.043218, 1.662660,
    -7.777616, 8.903482, -5.747970, 2.713227, 0.8732643, -7.615855, -0.04102325, -3.326636, 3.965078,
    -4.838706, -5.821301, 7.898834, 9.017889, 9.695526, -0.09866142, 0.3569117, -5.407949, -9.413353,
    -1.825603, 4.185634, -8.570944, -1.120717, 4.313562, 4.128145, 9.884861, 8.722403, 0.5576534,
    1.897922, -5.275388, -5.150269, -8.799623, 6.779392, -5.128532, 7.097033, 3.663776, -9.358543,
    -4.755765, -7.612075, -8.924912, 7.334997, -1.334789, 5.701401, 9.248079, 9.242275, 6.542847,
    2.056862, 2.146078, -1.165559, 2.623775, -0.5875053, -8.518209, 3.578820, -1.240537, -3.200276,
    4.224316, -0.9972458, -9.734336, -2.898527, 1.214268, -2.122331, -1.929972, 8.806732, 6.934219,
    -5.565065, -0.8254900, 7.943827, 9.940065, -4.618169, -9.932117, 8.699581, -9.883313, -5.078609,
    -7.651647, 3.238895, -6.066836, -5.516570, 4.980370, -5.586462, -0.4103088, 2.206141, 1.629825,
    -4.066483, 5.405710, -8.132589, 3.049022, 0.07775497, -9.973989, -5.364168, 6.021515, 8.753538,
    -3.624434, -2.995639, -3.852662, 2.099813, 2.936193, -6.216407, -2.074195, -5.340369, -9.044254,
    -1.516665, 3.240192, -0.8788471, -2.255092, -3.845088, -7.150319, 4.101549, 8.649372, -8.920446,
    0.1571655, -1.676828, -7.966612, -7.156257, -7.225507, -4.638480, 1.171181, 5.265255, -9.587639,
    -8.289684, 6.838583, 9.907795, -9.497300, -0.4885406, -6.502159, 5.132614, 6.528990, 3.629570,
    -4.750356, 6.658337, -3.358144, -1.577755, -2.750814, -7.227020, 9.909622, 1.469271, 1.972570,
    6.020292, -4.871180, -4.053063, -6.317994, 5.762268, 1.977712, 9.248629, 5.851633, -7.719399,
    -9.415594, 2.269215, -8.759095, 4.515505, 5.605917, 8.021158, 0.7013416, -3.419176, 5.924907,
    8.577084, 1.644983, -4.035120, -2.592746, 3.370245, 8.787596, 9.277403, -5.530761, 2.357012,
    4.606618, 0.8147869, -9.072975, 6.831202, -7.329923, -5.576311, -7.687482, -3.752274, -8.595730,
    -0.2278204, 7.398821, 0.1085625, 4.684593, -9.568882, -0.3465729, -8.971034, 1.690470, -8.614421,
    1.570501, -4.704419, 5.228518, 1.420517, 1.196814, -2.479778, -3.913021, 6.598284, -7.279852,
    -5.254329, -3.638518, 2.621401, -6.462899, -3.983620, 0.4756012, 1.603837, -4.190750, 5.777826,
    -0.8230228, -7.615709, -8.202168, 9.147680, 8.788195, -4.702549, 0.6192884, -1.948912, -8.152031,
    9.261770, 8.796589, -8.382751, -4.693560, 9.618073, -8.632855, 8.024162, 7.241146, -5.242624,
    0.9361153, 2.911037, 5.544810, 8.491617, -4.267592, -1.273458, 0.8110085, 2.294790, -5.127042,
    0.4227161, -0.4107361, 8.102695, -5.524592, 6.016405, -6.522939, -1.360388, 9.823757, -7.903556,
    -5.368113, 2.786340, 0.6754389, -2.528724, 7.922228, -9.477858, 0.8533392, -5.926023, 7.167055,
    -0.2220449, 0.8943224, -7.816916, -8.249993, 1.950531, 9.093567, 4.248296, 6.544182, 3.963995,
    2.481202, 2.946230, 6.516178, 2.802332, 7.680336, -1.388069, -9.666506, 3.517232, 4.674843
};

/* ======================================================================= */
/* Prototypes for timing functions                                         */
/* ======================================================================= */
clock_t time_opt();
clock_t time_cn();

/* ======================================================================= */
/* Main -- Top level driver for testing the algorithm                      */
/* ======================================================================= */
void main()
{
    clock_t t_overhead, t_start, t_stop, t_opt, t_cn;
    float pct_diff = 0, max_pct_diff = 0;

    /* ------------------------------------------------------------------- */
    /* Compute the overhead of calling clock twice to get timing info      */
    /* ------------------------------------------------------------------- */
    /* Initialize timer for clock */
    TSCL= 0,TSCH=0;
    t_start = _itoll(TSCH, TSCL);
    t_stop = _itoll(TSCH, TSCL);
    t_overhead = t_stop - t_start;

    /* ------------------------------------------------------------------- */
    /*  Clear state/output buffers with fixed values.                      */
    /* ------------------------------------------------------------------- */

    /* ------------------------------------------------------------------- */
    /* Call the individual timing routines                                 */
    /* ------------------------------------------------------------------- */
    t_opt = time_opt() - t_overhead;
    t_cn  = time_cn()  - t_overhead;

    printf("DSPF_sp_minerr\tIter#: %d\t", 1);

    /* ------------------------------------------------------------------- */
    /* compute percent difference and track max difference                 */
    /* ------------------------------------------------------------------- */
    pct_diff = (y_cn - y_opt) / y_cn * 100.0;
    if (pct_diff < 0) pct_diff *= -1;
    if (pct_diff > max_pct_diff) max_pct_diff = pct_diff;
    if (max_pct_diff > 0.02)
      printf("Result Failure, max_pct_diff=%f\n", max_pct_diff);
    else
      printf("Result Successful ");         
          
    /* ------------------------------------------------------------------- */
    /* Print timing results                                                */
    /* ------------------------------------------------------------------- */
    printf("\tGSP0_NUM = %d\tGSP0_TERMS = %d\tnatC: %d\toptC: %d\n", GSP0_NUM, GSP0_TERMS, t_cn, t_opt);

    /* Provide memory information */
#ifdef __TI_COMPILER_VERSION__            // for TI compiler only
    printf("Memory:  %d bytes\n", &kernel_size);
#endif
    
    /* Provide profiling information */
    printf("Cycles:  %d\n", t_opt);
}

/* ======================================================================= */
/* Prototypes for timing functions                                         */
/* ======================================================================= */
clock_t time_cn()
{
    clock_t t_start, t_stop;

    /* ------------------------------------------------------------------- */
    /* Measure the cycle count                                             */
    /* ------------------------------------------------------------------- */
    t_start = _itoll(TSCH, TSCL);
    y_cn = DSPF_sp_minerr_cn(ptr_x, ptr_err, &maxidx_cn);
    t_stop = _itoll(TSCH, TSCL);

    return t_stop - t_start;
}

clock_t time_opt()
{
    clock_t t_start, t_stop;
    
    /* ------------------------------------------------------------------- */
    /* Measure the cycle count                                             */
    /* ------------------------------------------------------------------- */
    t_start = _itoll(TSCH, TSCL);
    y_opt = DSPF_sp_minerr(ptr_x, ptr_err, &maxidx_opt);
    t_stop = _itoll(TSCH, TSCL);

    return t_stop - t_start;
}

/* ======================================================================= */
/*  End of file:  DSPF_sp_minerr_d.c                                       */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2011 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

