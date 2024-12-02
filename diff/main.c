#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <math.h>

//---------------------------------------------------------------------------//

#define N 3
#define IMAGE_SIZE 28   // 28x28 boyutunda görüntüler
#define CLASS_COUNT 2   // 2 sınıf
#define EXAMPLES_PER_CLASS 100 // Her sınıf için 100 örnek

//---------------------------------------------------------------------------//

// Görüntü veri kümesini oluştur ve normalize et
void createDataset(float dataset[CLASS_COUNT][EXAMPLES_PER_CLASS][IMAGE_SIZE][IMAGE_SIZE])
{
    for (int c = 0; c < CLASS_COUNT; c++)
    {
        for (int ex = 0; ex < EXAMPLES_PER_CLASS; ex++)
        {
            for (int i = 0; i < IMAGE_SIZE; i++)
            {
                for (int j = 0; j < IMAGE_SIZE; j++)
                {
                    // 0-255 arasında rastgele piksel değeri oluştur
                    int pixel = rand() % 256;
                    // 0-1 arası normalize et
                    dataset[c][ex][i][j] = pixel / 255.0f;
                }
            }
        }
    }
}

//---------------------------------------------------------------------------//

// Tanh aktivasyon fonksiyonu
float tanh_activation(float x)
{
    return tanh(x);
}

//---------------------------------------------------------------------------//

// Matrisin transpozunu al
void transpose(float *input, float *output, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            output[j * rows + i] = input[i * cols + j];
        }
    }
}

//---------------------------------------------------------------------------//

// Model için ağırlıklar ve giriş vektörü ile çıkışı hesapla
float calculate_output(float *x, float *w, int input_size)
{
    float result = 0.0;
    for (int i = 0; i < input_size; i++)
    {
        result += x[i] * w[i];
    }
    return tanh_activation(result);
}

//---------------------------------------------------------------------------//

// Öğrenme oranı ve doğru etiketle ağırlıkları güncelle
void update_weights(float *x, float *w, float learning_rate, float expected_output, float output, int input_size)
{
    float error = expected_output - output;
    for (int i = 0; i < input_size; i++)
    {
        w[i] += learning_rate * error * x[i];
    }
}

//---------------------------------------------------------------------------//

int main()
{
    // Dataset tanımlanır
    float dataset[CLASS_COUNT][EXAMPLES_PER_CLASS][IMAGE_SIZE][IMAGE_SIZE];

    // Rastgelelik için
    srand(time(NULL));

    // Dataset doldurma
    createDataset(dataset);

    // Example to flatten an image into a vector
    float x[N * N];  // Flattened input vector
    int input_size = N * N + 1;  // +1 for the bias term

    // Initialize weights with small random values
    float w[input_size];
    for (int i = 0; i < input_size; i++)
    {
        w[i] = (rand() % 2000 - 1000) / 1000.0;  // Random values between -1 and 1
    }

    // Training: example for one image
    for (int epoch = 0; epoch < 1000; epoch++)
    {
        // Example image from class 0
        for (int i = 0; i < IMAGE_SIZE; i++)
        {
            for (int j = 0; j < IMAGE_SIZE; j++)
            {
                x[i * IMAGE_SIZE + j] = dataset[0][0][i][j];  // Flatten the image
            }
        }
        
        // Add bias term
        x[input_size - 1] = 1.0f;

        // Calculate output for class 0 (expected output = 1)
        float output = calculate_output(x, w, input_size);

        // Update weights
        float learning_rate = 0.01;
        update_weights(x, w, learning_rate, 1.0f, output, input_size);
    }

    // Print a sample output
    printf("Output for a sample image: %f\n", calculate_output(x, w, input_size));

    return 0;
}
