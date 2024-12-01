//---------------------------------------------------------------------------//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

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

int add(int a, int b)
{
    return a + b;
}

//---------------------------------------------------------------------------//

void test_add()
{
    assert(add(2, 3) == 5);
    assert(add(-1, 1) == 0);
    assert(add(0, 0) == 0);
    printf("All tests passed!\n");
}

//---------------------------------------------------------------------------//

int main()
{
    // Define dataset array
    float dataset[CLASS_COUNT][EXAMPLES_PER_CLASS][IMAGE_SIZE][IMAGE_SIZE];

    // Seed random number generator
    srand(time(NULL));

    // Create and normalize dataset
    createDataset(dataset);

    // Example access to dataset
    printf("Dataset example, Class 0, Example 0, Pixel (0,0): %f\n", dataset[0][0][0][0]);
    printf("Dataset example, Class 0, Example 0, Pixel (0,0): %f\n", dataset[0][0][0][4]);
    printf("Dataset example, Class 0, Example 0, Pixel (0,0): %f\n", dataset[0][0][10][10]);

    // Run tests
    test_add();

    return 0;
}

//---------------------------------------------------------------------------//
