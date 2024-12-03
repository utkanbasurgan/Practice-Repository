//---------------------------------------------------------------------------//

void OP_stochasticGradientDescent()
{
    double start = 5.0;
    double learning_rate = 0.1;
    int iterations = 100;

    double x = start;

    for (int i = 0; i < iterations; i++)
    {
        // Simulate stochasticity (e.g., sampling a random noisy gradient)
        double noise = ((double)rand() / RAND_MAX) * 0.1 - 0.05; // Noise in range [-0.05, 0.05]
        double gradient = 2 * x + noise; // Noisy derivative of f(x) = x^2
        x -= learning_rate * gradient;
    }

    printf("%f\nSGD: ", x);
}

//---------------------------------------------------------------------------//
