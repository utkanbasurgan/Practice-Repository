//---------------------------------------------------------------------------//

void basitGradientDescent(float *x_matrix, float *w_matrix, double learning_rate, double tanvalue2)
{
    double gradient[IMAGE_SIZE];

    for (int i = 0; i < IMAGE_SIZE; i++)
    {
        gradient[i] = (tanvalue2 - 1) * (1 - pow(tanvalue2, 2)) * x_matrix[i];
    }

    for (int i = 0; i < IMAGE_SIZE; i++)
    {
        w_matrix[i] -= learning_rate * gradient[i];
    }
}

//---------------------------------------------------------------------------//

void OP_gradientDescent(float class_a[IMAGE_SIZE][IMAGE_SIZE], float class_b[IMAGE_SIZE][IMAGE_SIZE], float veriler[CLASS_COUNT][EXAMPLES_PER_CLASS][IMAGE_SIZE][IMAGE_SIZE], float k)
{
    //-----------------------------------------------------------------------//
    
    char filename[100];
    snprintf(filename, sizeof(filename), "../Results/gd-%f.txt", k);
    FILE *file = fopen(filename, "w");

    //-----------------------------------------------------------------------//

    float x_matrix[IMAGE_SIZE * IMAGE_SIZE + 1]; // x vektörü, sonuna 1 ekleyeceğiz bias için
    float w_matrix[IMAGE_SIZE * IMAGE_SIZE + 1]; // w vektörü (ağırlıklar)

    // w_matrix'i başlangıçta rastgele değerlerle dolduruyoruz
    DATASETS_w(IMAGE_SIZE * IMAGE_SIZE + 1, w_matrix, k); // w vektörünü başlat

    //-----------------------------------------------------------------------//





    float tanvalue;
    float tanvalue2;
    float error_a;
    float error_b;


    for (int i = 0; i < 10; i++)
    {
        MATH_linear(IMAGE_SIZE, veriler[0][i], x_matrix);

        tanvalue = MATH_product(IMAGE_SIZE, x_matrix, w_matrix);
        tanvalue2 = MATH_tanh(tanvalue);

        error_a = 0.5 * pow((1 - tanvalue2), 2);

        basitGradientDescent(x_matrix, w_matrix, 0.01, tanvalue2);

        fprintf(file, "Güncellenmiş Tanh: %f\n", tanvalue2);
        fprintf(file, "Güncellenmiş A-Hata: %f\n", error_a);
        fprintf(file, "-----------------------------\n");
    }



    for (int i = 0; i < 1; i++)
    {
        MATH_linear(IMAGE_SIZE, veriler[0][i], x_matrix);

        tanvalue = MATH_product(IMAGE_SIZE, x_matrix, w_matrix);
        tanvalue2 = MATH_tanh(tanvalue);

        error_b = 0.5 * pow((-1 - tanvalue2), 2);

        fprintf(file, "Güncellenmiş Tanh: %f\n", tanvalue2);
        fprintf(file, "Güncellenmiş B-Hata: %f\n", error_b);
        fprintf(file, "-----------------------------\n");
    }




    //-----------------------------------------------------------------------//

    fclose(file);

    //-----------------------------------------------------------------------//
}

//---------------------------------------------------------------------------//