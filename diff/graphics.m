% Gradient Descent Comparison: GD, Adam, SGD
% Define the function and its gradient
f = @(x) x.^2;           % Function: f(x) = x^2
grad_f = @(x) 2*x;       % Gradient: f'(x) = 2x

% Shared Parameters
x_start = rand()*10 - 5; % Random start point in [-5, 5]
num_iters = 50;          % Number of iterations
x_range = -5:0.1:5;      % Function plot range
y_range = f(x_range);

% Initialize Results for All Methods
gd_vals = zeros(1, num_iters);
adam_vals = zeros(1, num_iters);
sgd_vals = zeros(1, num_iters);
gd_vals(1) = x_start;
adam_vals(1) = x_start;
sgd_vals(1) = x_start;

% Hyperparameters for Adam
alpha = 0.1;  % Learning rate
beta1 = 0.9;  % Momentum term
beta2 = 0.999; % RMSProp term
eps = 1e-8;
m = 0; v = 0; % Adam terms

% SGD noise factor
noise_factor = 0.2;

% Perform Iterations
for i = 2:num_iters
    % Gradient Descent
    gd_vals(i) = gd_vals(i-1) - alpha * grad_f(gd_vals(i-1));
    
    % Adam
    g = grad_f(adam_vals(i-1));
    m = beta1 * m + (1 - beta1) * g;
    v = beta2 * v + (1 - beta2) * g^2;
    m_hat = m / (1 - beta1^(i));
    v_hat = v / (1 - beta2^(i));
    adam_vals(i) = adam_vals(i-1) - alpha * m_hat / (sqrt(v_hat) + eps);
    
    % Stochastic Gradient Descent
    noisy_grad = grad_f(sgd_vals(i-1)) + noise_factor * randn;
    sgd_vals(i) = sgd_vals(i-1) - alpha * noisy_grad;
end

% Plot
figure;

% Function Graph: Gradient Descent
subplot(2, 3, 1);
plot(x_range, y_range, '-b', 'LineWidth', 2); hold on;
plot(gd_vals, f(gd_vals), 'r.-');
title('GD Function');
xlabel('x'); ylabel('f(x)');
grid on;

% Iterations: Gradient Descent
subplot(2, 3, 4);
plot(1:num_iters, f(gd_vals), 'r.-');
title('GD Progress');
xlabel('Iteration'); ylabel('f(x)');
grid on;

% Function Graph: Adam
subplot(2, 3, 2);
plot(x_range, y_range, '-b', 'LineWidth', 2); hold on;
plot(adam_vals, f(adam_vals), 'g.-');
title('Adam Function');
xlabel('x'); ylabel('f(x)');
grid on;

% Iterations: Adam
subplot(2, 3, 5);
plot(1:num_iters, f(adam_vals), 'g.-');
title('Adam Progress');
xlabel('Iteration'); ylabel('f(x)');
grid on;

% Function Graph: SGD
subplot(2, 3, 3);
plot(x_range, y_range, '-b', 'LineWidth', 2); hold on;
plot(sgd_vals, f(sgd_vals), 'm.-');
title('SGD Function');
xlabel('x'); ylabel('f(x)');
grid on;

% Iterations: SGD
subplot(2, 3, 6);
plot(1:num_iters, f(sgd_vals), 'm.-');
title('SGD Progress');
xlabel('Iteration'); ylabel('f(x)');
grid on;
