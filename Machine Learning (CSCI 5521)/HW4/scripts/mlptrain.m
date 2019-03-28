%{
m: number of hidden units
k: number of output units
z: an n × m matrix of hidden unit values 
w: a m × (d + 1) matrix of input unit weights
v: a k × (m + 1) matrix of hidden unit weights. 

The function also prints the training and validation error rates 
%}
function [z, w, v] = mlptrain(train_path, val_path, m, k)
    %The following code block gives:
    %trnMat, trnLbls, valMat, valLbls

    %Read the training matrix in
    rawTrainingMat = dlmread(train_path);
    [numDataPoints, width] = size(rawTrainingMat);
    trnMat = rawTrainingMat(:, 1:width-1);
    trnLbls = rawTrainingMat(:, width);
    
    %Read the validation matrix in
    rawValidMat = dlmread(val_path);
    [numDataPointsValid, width] = size(rawValidMat);
    valMat = rawValidMat(:, 1:width-1);
    valLbls = rawValidMat(:, width);
    
    [~, d] = size(trnMat);
    
    %Here we initialize the weight matrices...
    w = 0.02 * rand(m, d + 1) - 0.01;
    v = 0.02 * rand(k, m + 1) - 0.01;
    z = zeros(numDataPoints, m);
    
    
    trialNumber = 1;
    totalIters = 100;
    learnRate = 0.001;
    
    %Now we run the back-propogation algorithm
    while trialNumber <= totalIters
       perms = randperm(numDataPoints);
       for idx = 1:length(perms)
           i = perms(idx);
           xt = trnMat(i, :);
           
           %Update the hidden layer (RELU)
           zt = zeros(1, m);
           for h = 1:m
               val = dot(w(h, :), [1, xt]);
               if val >= 0
                   zt(h) = val;
               end
           end
           
           %Update the output layer
           o = zeros(k, 1);
           for j = 1:k
                o(j) = dot([1, zt], v(j, :));
           end
           
           %Compute y (softmax)
           y = softmax(o);
           
           %Define r vector
           actualDigit = trnLbls(i);
           r = zeros(k, 1);
           r(actualDigit + 1) = 1;

           %Find the hidden weight step (v-Step)
           vStep = learnRate * (r - y) * [1, zt];
           
           %Find the first-layer weight step (w-Step)  
           wStep = zeros(m, d + 1);
           for h = 1:m
               if dot([1, xt], w(h, :)) >= 0
                   wStep(h, :) = learnRate * (r - y)' * v(:, h) * [1, xt];
               end
           end
           
           %Update the hidden weights
           v = v + vStep;
           w = w + wStep; 
       end
       
       %Adjust the learn rate based on trial number
       if trialNumber > 30
           learnRate = 0.0001;
       end
       if trialNumber > 50
           learnRate = 0.00005;
       end
       if trialNumber > 75
           learnRate = 0.00001;
       end
       if trialNumber > 95
           learnRate = 0.000005;
       end
       
       trialNumber = trialNumber + 1;
    end
    
    
    
    %HERE TRAINING IS COMPLETE; THIS CODE HERE JUST FINDS THE
    %CLASSIFICATION ERROR ON THE TRAINING SET
    %Attempt to classify
    [errorRate, z] = computeMLPError(v, w, trnMat, trnLbls);
    
    disp("Train error rate: ");
    disp(errorRate);
    
    [errorRate, ~] = computeMLPError(v, w, valMat, valLbls);
    
    disp("Valid error rate: ");
    disp(errorRate);
end