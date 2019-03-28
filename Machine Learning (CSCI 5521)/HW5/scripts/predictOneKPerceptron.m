function [score] = predictOneKPerceptron(datum, x, y, alphas, b)
    a = alphas;
    [M, ~] = size(x);
    
    sum = 0;
    for i = 1:M
        dotProd = a(i) * y(i) * (1 + x(i, :) * datum')^2;
        sum = sum + dotProd;
    end
    sum = sum + b;
    score = sum;
end
