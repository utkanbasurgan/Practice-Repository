//---------------------------------------------------------------------------//

void OP_gradientDescent(float veriler[CLASS_COUNT][EXAMPLES_PER_CLASS][IMAGE_SIZE][IMAGE_SIZE])
{
    float x_matrix[IMAGE_SIZE * IMAGE_SIZE + 1];
    float w_matrix[IMAGE_SIZE * IMAGE_SIZE + 1];

    DATASETS_w(IMAGE_SIZE * IMAGE_SIZE + 1, w_matrix, 1);
    printf("%f\nDataset: ", w_matrix[0]);

    MATH_linear(IMAGE_SIZE, veriler[0][0], x_matrix);
    MATH_linear(IMAGE_SIZE, veriler[0][0], w_matrix);

    //printf("%f\nDataset: ", x_matrix[0]);
    //printf("%f\nDataset: ", x_matrix[IMAGE_SIZE]);
    
    float tanvalue = MATH_product(IMAGE_SIZE, x_matrix, w_matrix);

    float tanvalue2 = MATH_tanh(tanvalue);

    printf("%f\nDataset: ", tanvalue2);
}

//---------------------------------------------------------------------------//