function [alphas, b] = kernPercGD(trnMat, trnLbls)
    x = trnMat;
    y = trnLbls;
    [N, ~] = size(trnMat);
    a = zeros(1, N);
    b = 0;
    
    
    iterNum = 1;
    notConverged = true;
    while notConverged && iterNum <= 50
        notConverged = false;
        for t = 1:N
            prediction = predictOneKPerceptron(x(t, :), trnMat, trnLbls, a, b);
            if prediction * y(t) <= 0
                notConverged = true;
                a(t) = a(t) + 1;
                b = b + y(t);
            end
        end
        iterNum = iterNum + 1;
    end
    
    alphas = a';
end