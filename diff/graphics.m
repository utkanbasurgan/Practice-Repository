% Gradient Descent Example with Function Graph and Random Start
% Define the function and its gradient
f = @(x) x.^2;           % Function: f(x) = x^2
grad_f = @(x) 2*x;       % Gradient: f'(x) = 2x

% Gradient Descent Parameters
x_start = rand()*10 - 5; % Random start point in [-5, 5]
learning_rate = 0.1;
num_iters = 20;

% Initialize
x_vals = zeros(1, num_iters); 
x_vals(1) = x_start;

% Perform Gradient Descent
for i = 2:num_iters
    x_vals(i) = x_vals(i-1) - learning_rate * grad_f(x_vals(i-1));
end

% Plot 1: Function Graph with Start Point
x_range = -5:0.1:5;
y_range = f(x_range);

figure;
plot(x_range, y_range, '-b', 'LineWidth', 2); hold on;
plot(x_vals(1), f(x_vals(1)), 'ro', 'MarkerSize', 10, 'DisplayName', 'Start Point');
xlabel('x'); ylabel('f(x)');
title('Function Graph with Random Start');
grid on;
legend;

% Plot 2: Gradient Descent Path
figure;
plot(1:num_iters, f(x_vals), '-o', 'LineWidth', 2, 'MarkerSize', 6);
xlabel('Iteration'); ylabel('f(x)');
title('Gradient Descent Progress');
grid on;
