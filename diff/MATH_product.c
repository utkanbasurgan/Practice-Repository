//---------------------------------------------------------------------------//

// Matrisin transpozunu al
float MATH_product(int size, float matrix1[size], float matrix2[size])
{
    float sum = 0.0f;
    for (int i = 0; i < size; i++)
    {
        sum += matrix1[i] * matrix2[i];
    }
    return sum;
}

//---------------------------------------------------------------------------//