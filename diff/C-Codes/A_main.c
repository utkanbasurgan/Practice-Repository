//---------------------------------------------------------------------------//

#define STB_IMAGE_IMPLEMENTATION
#include "stb-master/stb_image.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <math.h>

//---------------------------------------------------------------------------//

#define N 3
#define IMAGE_SIZE 96   // 50x50 boyutunda görüntüler
#define CLASS_COUNT 2   // 2 sınıf
#define EXAMPLES_PER_CLASS 100 // Her sınıf için 100 örnek
#define TEST_RATIO 20 // Her sınıf için 100 örnek

//---------------------------------------------------------------------------//

#include "DATASETS_read.c"
#include "DATASETS_files.c"
#include "DATASETS_w.c"

#include "MATH_tanh.c"
#include "MATH_linear.c"
#include "MATH_product.c"

#include "OP_gradientDescent.c"
#include "OP_stochasticGradientDescent.c"
#include "OP_adam.c"

//---------------------------------------------------------------------------//

int main()
{
    //-----------------------------------------------------------------------//

    srand(time(NULL));

    // Veri kümesi tanımlanır
    float veriler[CLASS_COUNT][EXAMPLES_PER_CLASS][IMAGE_SIZE][IMAGE_SIZE];
    DATASETS_files(veriler);
    printf("Data: %f\n", veriler[0][3][39][48]);

    //-----------------------------------------------------------------------//
    
    // Optimizasyon yapılıp değerler dosyaya yazılacak.

    OP_gradientDescent(veriler, 1);
    OP_gradientDescent(veriler, 0.1);
    OP_gradientDescent(veriler, 0.01);
    OP_gradientDescent(veriler, 0.001);
    OP_gradientDescent(veriler, 0.0001);

    OP_stochasticGradientDescent(veriler, 1);
    OP_stochasticGradientDescent(veriler, 0.1);
    OP_stochasticGradientDescent(veriler, 0.01);
    OP_stochasticGradientDescent(veriler, 0.001);
    OP_stochasticGradientDescent(veriler, 0.0001);

    OP_adam(veriler, 1);
    OP_adam(veriler, 0.1);
    OP_adam(veriler, 0.01);
    OP_adam(veriler, 0.001);
    OP_adam(veriler, 0.0001);

    //-----------------------------------------------------------------------//

    return 0;

    //-----------------------------------------------------------------------//
}

//---------------------------------------------------------------------------//