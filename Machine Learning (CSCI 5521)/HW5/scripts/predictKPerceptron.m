function [scores] = predictKPerceptron(xGrid, x, y, alphas, b)
    [N, ~] = size(xGrid);
    scores = zeros(N, 1);
    
    for t = 1:N
        scores(t) = predictOneKPerceptron(xGrid(t, :), x, y, alphas, b);  
    end
end

