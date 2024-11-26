#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//----------------------------------------//

#define N 3
#define IMAGE_SIZE 30          // 28x28 boyutunda görüntüler
#define CLASS_COUNT 2          // 2 sınıf
#define EXAMPLES_PER_CLASS 100 // Her sınıf için 100 örnek
#define DEBUG_SIZE 2           // Her sınıf için 100 örnek
#define TEST_SIZE 80
#define ACTUAL_SIZE 20

//----------------------------------------//

double dot_product(double *w, double *x, int size) {
  double result = 0.0;
  for (int i = 0; i < size; i++) {
    result += w[i] * x[i];
  }
  return result;
}

//----------------------------------------//

void createDataset(float dataset[CLASS_COUNT][EXAMPLES_PER_CLASS][IMAGE_SIZE]
                                [IMAGE_SIZE][DEBUG_SIZE]) {
  for (int c = 0; c < CLASS_COUNT; c++) {
    for (int ex = 0; ex < EXAMPLES_PER_CLASS; ex++) {
      for (int i = 0; i < IMAGE_SIZE; i++) {
        for (int j = 0; j < IMAGE_SIZE; j++) {

          int pixel = rand() % 256;
          // orijinal data, debug için
          dataset[c][ex][i][j][0] = pixel;

          // 0-1 arası normalize et
          float pixel2;
          pixel2 = pixel / 255.0f;
          dataset[c][ex][i][j][1] = pixel2;
        }
      }
    }
  }
}

//----------------------------------------//

double neural_network_classifier() {
  // Number of inputs (N2)
  const int N2 = 3;

  // Input vector x (N2+1 dimensions)
  double x[N2 + 1];

  // Weight vector w
  double w[N2 + 1];

  // Initialize input vector x
  x[0] = 0.5; // Example input values
  x[1] = 0.3;
  x[2] = 0.7;
  x[3] = 1.0; // Bias term

  // Initialize weight vector w
  w[0] = 0.2; // Example weight values
  w[1] = -0.4;
  w[2] = 0.6;
  w[3] = 0.1;

  // Compute weighted sum
  double weighted_sum = 0.0;
  for (int i = 0; i < N2 + 1; i++) {
    weighted_sum += w[i] * x[i];
  }

  // Apply hyperbolic tangent activation
  return tanh(weighted_sum);
}

//----------------------------------------//

int main() {
  srand(time(NULL)); // Seed the random number generator with the current time

  float dataset[CLASS_COUNT][EXAMPLES_PER_CLASS][IMAGE_SIZE][IMAGE_SIZE][2];
  createDataset(dataset);
  printf("Element at (1, 2): %f\n", dataset[1][1][2][3][0]);
  printf("Element at (1, 2): %f\n", dataset[1][1][2][3][1]);

  double output = neural_network_classifier();
  printf("Classification output: %f\n", output);

  return 0;
}

//----------------------------------------//
