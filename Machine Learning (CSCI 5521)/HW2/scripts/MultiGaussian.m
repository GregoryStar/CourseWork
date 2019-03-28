function [PC1, PC2, m1, m2, S1, S2] = MultiGaussian(training_data, test_data, model)
    if model == 1
        %S1 and S2 independent
        disp("Model 1: ");
        [PC1, PC2, m1, m2, S1, S2] = Model1(training_data, test_data);
        disp("Prior of class 1: " + PC1);
        disp("Prior of class 2: " + PC2);
        disp("Mean of class 1: ");
        disp(m1);
        disp("Mean of class 1: ");
        disp(m2);
        disp("Covariance of class 1: ");
        disp(S1);
        disp("Covariance of class 2: ");
        disp(S2);
        
    elseif model == 2
        %S1 = S2; compute them from common pool
        disp("Model 2: ");
        [PC1, PC2, m1, m2, S1, S2] = Model2(training_data, test_data);
        disp("Prior of class 1: " + PC1);
        disp("Prior of class 2: " + PC2);
        disp("Mean of class 1: ");
        disp(m1);
        disp("Mean of class 1: ");
        disp(m2);
        disp("Covariance of class 1: ");
        disp(S1);
        disp("Covariance of class 2: ");
        disp(S2);
        
    elseif model == 3
        %S1 and S2 are diagonal matrices
        disp("Model 3: ");
        [PC1, PC2, m1, m2, a1, a2] = Model3(training_data, test_data);
                disp("Prior of class 1: " + PC1);
        disp("Prior of class 2: " + PC2);
        disp("Mean of class 1: ");
        disp(m1);
        disp("Mean of class 1: ");
        disp(m2);
        disp("Alpha1: ");
        disp(a1);
        disp("Alpha2: ");
        disp(a2);
        
    end
end

function [PC1, PC2, m1, m2, S1, S2] = Model1(training_data, test_data)
    %Read the training matrix in
    rawDataMat = dlmread(training_data);
    [~, width] = size(rawDataMat);
    trnMat = rawDataMat(:, 1:width-1);
    trnLbls = rawDataMat(:, width);
    [n, d] = size(trnMat);
    
    %split data into two separate matrices
    %based on class label, so that we may
    %compute class distributions
    class1Mat = [];
    class2Mat = [];
    for i = 1:n
        %Append the current row to the label
        %it matches
        if trnLbls(i) == 1
            class1Mat = [class1Mat; trnMat(i, 1:d)];
        else
            class2Mat = [class2Mat; trnMat(i, 1:d)];
        end
    end
    
    %Get the covariance matrices
    S1 = cov(class1Mat);
    S2 = cov(class2Mat);
    
    %Compute the means
    m1 = mean(class1Mat);
    m2 = mean(class2Mat);
    
    %Compute the priors
    PC1 = 0;
    for i = 1:n
        if trnLbls(i) == 1
            PC1 = PC1 + 1;
        end
    end
    PC1 = PC1/n;
    PC2 = 1 - PC1;
    
    %Read the test matrix in
    rawDataMat = dlmread(test_data);
    [~, width] = size(rawDataMat);
    testMat = rawDataMat(:, 1:width-1);
    testLbls = rawDataMat(:, width);
    [n, d] = size(trnMat);
    
    %Attempt to classify
    numCorrect = 0;
    for i = 1:n
        %Compute discriminants
        x = testMat(i, :);
        b = (-1/2)*log(det(S1));
        c = -(1/2)*(x - m1);
        e = inv(S1);
        f = transpose(x - m1);
        h = log(PC1);
        
        d1 = b + c*e*f + h;
        
        b = (-1/2)*log(det(S1));
        c = -(1/2)*(x - m2);
        e = inv(S2);
        f = transpose(x - m2);
        h = log(PC2);
        
        d2 = b + c*e*f + h;
        
        %If the classifier agrees with the label
        %increment the correct counter
        if d1 >= d2 && testLbls(i) == 1
            numCorrect = numCorrect + 1;
        elseif d1 < d2 && testLbls(i) == 2
            numCorrect = numCorrect + 1;
        end
    end
    
    percentCorrect = numCorrect/n;
    disp("Classification error:");
    disp(1 - percentCorrect);
end

function [PC1, PC2, m1, m2, S1, S2] = Model2(training_data, test_data)
    %Read the training matrix in
    rawDataMat = dlmread(training_data);
    [~, width] = size(rawDataMat);
    trnMat = rawDataMat(:, 1:width-1);
    trnLbls = rawDataMat(:, width);
    [n, d] = size(trnMat);
    
    %split data into two separate matrices
    %based on class label, so that we may
    %compute class distributions
    class1Mat = [];
    class2Mat = [];
    for i = 1:n
        %Append the current row to the label
        %it matches
        if trnLbls(i) == 1
            class1Mat = [class1Mat; trnMat(i, 1:d)];
        else
            class2Mat = [class2Mat; trnMat(i, 1:d)];
        end
    end
        
    %Compute the means
    m1 = mean(class1Mat);
    m2 = mean(class2Mat);
    
    %Compute the priors
    PC1 = 0;
    for i = 1:n
        if trnLbls(i) == 1
            PC1 = PC1 + 1;
        end
    end
    PC1 = PC1/n;
    PC2 = 1 - PC1;
    
    %Get the covariance matrices
    S1 = cov(class1Mat);
    S2 = cov(class2Mat);
    
    %Now set S to be the weighted sum of the covariances
    S = PC1 * S1 + PC2 * S2;
    
    %Read the test matrix in
    rawDataMat = dlmread(test_data);
    [~, width] = size(rawDataMat);
    testMat = rawDataMat(:, 1:width-1);
    testLbls = rawDataMat(:, width);
    [n, d] = size(trnMat);
    
    %Attempt to classify
    numCorrect = 0;
    for i = 1:n
        %Compute discriminants
        x = testMat(i, :);
        c = -(1/2)*(x - m1);
        e = inv(S);
        f = transpose(x - m1);
        h = log(PC1);
        
        d1 = c*e*f + h;
        
        c = -(1/2)*(x - m2);
        e = inv(S);
        f = transpose(x - m2);
        h = log(PC2);
        
        d2 = c*e*f + h;
        
        %If the classifier agrees with the label
        %increment the correct counter
        if d1 >= d2 && testLbls(i) == 1
            numCorrect = numCorrect + 1;
        elseif d1 < d2 && testLbls(i) == 2
            numCorrect = numCorrect + 1;
        end
    end
    
    S1 = S;
    S2 = S;
    
    percentCorrect = numCorrect/n;
    disp("Classification error:");
    disp(1 - percentCorrect);
end


function [PC1, PC2, m1, m2, a1, a2] = Model3(training_data, test_data)
    %Read the training matrix in
    rawDataMat = dlmread(training_data);
    [~, width] = size(rawDataMat);
    trnMat = rawDataMat(:, 1:width-1);
    trnLbls = rawDataMat(:, width);
    [n, d] = size(trnMat);
    
    %split data into two separate matrices
    %based on class label, so that we may
    %compute class distributions
    class1Mat = [];
    class2Mat = [];
    for i = 1:n
        %Append the current row to the label
        %it matches
        if trnLbls(i) == 1
            class1Mat = [class1Mat; trnMat(i, 1:d)];
        else
            class2Mat = [class2Mat; trnMat(i, 1:d)];
        end
    end
   
    %Compute the means
    m1 = mean(class1Mat);
    m2 = mean(class2Mat);
    
    [n, d] = size(class1Mat);
    alpha1 = 0;
    for i = 1:n
        dataPoint = class1Mat(i, :);
        temp = dataPoint - m1;
        alpha1 = alpha1 + norm(temp)^2;
    end
    alpha1 = alpha1/(d * n);
    a1 = alpha1;
    S1 = alpha1 * eye(d);
    
    [n, d] = size(class2Mat);
    alpha2 = 0;
    for i = 1:n
        dataPoint = class2Mat(i, :);
        temp = dataPoint - m2;
        alpha2 = alpha2 + norm(temp)^2;
    end
    alpha2 = alpha2/(d * n);
    a2 = alpha2;
    S2 = alpha2 * eye(d);
    
    %Compute the priors
    PC1 = 0;
    for i = 1:n
        if trnLbls(i) == 1
            PC1 = PC1 + 1;
        end
    end
    PC1 = PC1/n;
    PC2 = 1 - PC1;
   
    %Read the test matrix in
    rawDataMat = dlmread(test_data);
    [~, width] = size(rawDataMat);
    testMat = rawDataMat(:, 1:width-1);
    testLbls = rawDataMat(:, width);
    [n, d] = size(trnMat);
    
    
    %Attempt to classify
    numCorrect = 0;
    for i = 1:n
        %Compute discriminants
        x = testMat(i, :);
        b = (-d/2)*log(a1);
        g = (1/(2*a1));
        c = (x - m1);
        f = transpose(x - m1);
        h = log(PC1);
        
        d1 = -b - g*c*f + h ;
        
        b = (-d/2)*log(a2);
        g = (1/(2*a2));
        c = (x - m2);
        f = transpose(x - m2);
        h = log(PC2);
        
        d2 = -b - g*c*f + h ;
        
        %If the classifier agrees with the label
        %increment the correct counter
        if d1 >= d2 && testLbls(i) == 1
            numCorrect = numCorrect + 1;
        elseif d1 < d2 && testLbls(i) == 2
            numCorrect = numCorrect + 1;
        end
    end
    
    percentCorrect = numCorrect/n;
    disp("Classification error:");
    disp(1 - percentCorrect);
end