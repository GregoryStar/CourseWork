function [error, z] = computeMLPError(v, w, x, lbls)
    [numDataPoints, ~] = size(x);
    [m, ~] = size(w);
    [k, ~] = size(v);
    
    z = zeros(numDataPoints, m);

    numCorrect = 0;
    for t = 1:numDataPoints
        xt = x(t, :);
           
       %Compute z
       zt = zeros(1, m);
       for h = 1:m
           val = dot(w(h, :), [1, xt]);
           if val >= 0
               zt(h) = val;
           end
       end

       %Update the output layer
       y = zeros(k, 1);
       for j = 1:k
           y(j) = exp(dot([1, zt], v(j, :)));
       end
       
       [~, argmax] = max(y);
       
       if argmax - 1 == lbls(t)
           numCorrect = numCorrect + 1;
       end
              
       z(t, :) = zt;
    end 
    
    error = 1 - (numCorrect/numDataPoints);
end

