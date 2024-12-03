//---------------------------------------------------------------------------//

void MATH_linear(int size, float matrix[size][size], float result[size * size + 1])
{
    int idx = 0;

    // Flatten the NxN matrix into the result vector
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            result[idx++] = matrix[i][j];
        }
    }

    // Append bias term (set to 1 or any other value as needed)
    result[idx] = 1.0f;  // Bias value is 1.0 (can be adjusted)
}

//---------------------------------------------------------------------------//