//---------------------------------------------------------------------------//

void OP_adam()
{
    double start = 5.0;
    double learning_rate = 0.1;
    int iterations = 100;

    // Adam hyperparameters
    double beta1 = 0.9;
    double beta2 = 0.999;
    double epsilon = 1e-8;

    double x = start;
    double m = 0.0;  // First moment
    double v = 0.0;  // Second moment
    double t = 0.0;  // Time step

    for (int i = 0; i < iterations; i++)
    {
        t += 1;

        // Gradient of f(x) = x^2
        double gradient = 2 * x;

        // Update biased first and second moments
        m = beta1 * m + (1 - beta1) * gradient;
        v = beta2 * v + (1 - beta2) * gradient * gradient;

        // Bias correction
        double m_hat = m / (1 - pow(beta1, t));
        double v_hat = v / (1 - pow(beta2, t));

        // Update parameters
        x -= learning_rate * m_hat / (sqrt(v_hat) + epsilon);
    }

    printf("%f\nADAM: ", x);
}

//---------------------------------------------------------------------------//