function [h, m, Q] = EMG(flag, filepath, k)
    [img_double,len, width] = readImageToMatrix(filepath);
    %Convert 3d image matrix to 2d matrix of pixels (rows are rgb values)
    rgbArray = convert3Dto2D(img_double);
    numPixels = len * width;
    
    %variables that need to be initialized:
    %priors, means, covariances
    
    %kmeans can give us class priors and means.
    %Since we know the classes, we can then
    %compute the covariances
    
    %NOTE: only do k-means to a few iterations; figure out how to do that
    %Perform k-means
    [clusterIndices, colorMap] = kmeans(rgbArray, k);
    
    %Split the data matrix into 10 matrices by class
    classes = cell(k);
    for i = 1:k
        classMat = [];
        classIndex = 1;
        for j = 1:numPixels
            if clusterIndices(j) == i
                classMat(classIndex, 1) = rgbArray(j, 1);
                classMat(classIndex, 2) = rgbArray(j, 2);
                classMat(classIndex, 3) = rgbArray(j, 3);
                classIndex = classIndex + 1;
            end
        end
        classes{i} = classMat;
    end
    
    %Initialize covariances
    covs = cell(k);
    for i = 1:k
        covs{i} = cov(classes{i});
    end
    
    %Initialize means
    means = colorMap;
    
    %Initialize class sizes
    classSizes = zeros(1, k);
    
    %Initialize priors
    priors = zeros(1, k);
    for i = 1:k
        [numInClass, ~] = size(classes{i});
        classSizes(i) = numInClass;
        priors(i) = numInClass/numPixels;
    end
    
    expOfResp = zeros(numPixels, k);

    Q = [];
    iterationNum = 0;
    qCount = 1;
    prevQ = -1;
    currentQ = 0;
    regularizer = diag(0.00000001 * ones(3, 1));
    while iterationNum < 100 && abs(currentQ - prevQ) > 0.01
        %E-step
        for i = 1:numPixels
            evidence = 0;
            for j = 1:k
                evidence = evidence + priors(j) * mvnpdf(rgbArray(i, :), means(j, :), covs{j});
            end
            
            for j = 1:k
                likelihoodPrior = priors(j) * mvnpdf(rgbArray(i, :), means(j, :), covs{j});
                expOfResp(i, j) = likelihoodPrior/evidence;
            end
        end
        
        %Compute Q
        qSum = 0;
        for i = 1:numPixels
            for j = 1:k
                logVal = log(mvnpdf(rgbArray(i, :), means(j, :), covs{j}));
                if isinf(logVal)
                    logVal = 0;
                end
                temp = log(priors(j)) + logVal;
                qSum = qSum + expOfResp(i, j)*temp;
            end
        end
        Q(qCount) = qSum;
        qCount = qCount + 1;
        
        %M-step
        %Update means (each mean should be an rgb vector)
        for i = 1:k
            sum = [0, 0, 0];
            for j = 1:numPixels
                sum = sum + expOfResp(j, i) * rgbArray(j, :);
            end
            sum = sum/classSizes(i);
            means(i, :) = sum;
        end

        %update class sizes
        for i = 1:k
            sum = 0;
            for j = 1:numPixels
                sum = sum + expOfResp(j, i);
            end
            classSizes(i) = sum;
        end

        %update priors
        for i = 1:k
            priors(i) = classSizes(i)/numPixels;
        end

        %update covariances
        for i = 1:k
            sum = zeros(3);
            for j = 1:numPixels
                distToMean = rgbArray(j, :) - means(i, :);
                sum = sum + expOfResp(j, i) * (distToMean' * distToMean);
            end
            covs{i} = sum/classSizes(i);
        end
        iterationNum = iterationNum + 1;
        
        %Regularize covariances
        for i = 1:k
            if flag == 1
                covs{i} = covs{i} + regularizer;
            end
        end
        
        %Compute Q
        qSum = 0;
        for i = 1:numPixels
            for j = 1:k
                logVal = log(mvnpdf(rgbArray(i, :), means(j, :), covs{j}));
                if isinf(logVal)
                    logVal = 0;
                end
                temp = log(priors(j)) + logVal;
                qSum = qSum + expOfResp(i, j)*temp;
            end
        end
        prevQ = currentQ;
        currentQ = qSum;
        Q(qCount) = qSum;
        qCount = qCount + 1;
    end
    
    h = expOfResp;
    m = means;
    
    %Print learned values to terminal
    disp("Learned h matrix: ");
    disp(h);
    disp("Learned means: ");
    disp(m);

    
    qLabels = [];
    X = [];
    for i = 1:qCount - 1
        if mod(i, 2) == 1
            qLabels(i) = 1;
        else
            qLabels(i) = 2;
        end
        X(i) = i;
    end
    
    %Generate plot of expected complete log likelihood values
    figure
    gscatter(X, Q, qLabels)
    title(['Expected Complete Log-Likelihood for ', filepath, ' with ', num2str(k), ' Clusters'])
    
    
    %%% DISPLAY THE COMPRESSED IMAGE %%%
    clusterIndices = [];
    
    %First assign class to each pixel based on h
    for i = 1:numPixels
        [~, argmax] = max(h(i, :));
        clusterIndices(i) = argmax;
    end

    %Now reformat pixel matrix to 3D image matrix for displaying
    indexCount = 1;
    compressedMat = [];
    
    for i = 1:len
        for j = 1:width
            currentColor = means(clusterIndices(indexCount), :);
            compressedMat(i, j, 1) = currentColor(1);
            compressedMat(i, j, 2) = currentColor(2);
            compressedMat(i, j, 3) = currentColor(3);
            indexCount = indexCount + 1;
        end
    end

    figure
    imagesc(compressedMat)
    title(['EM compression of ', filepath, ' with ', num2str(k), ' Colors'])
    
    Q = Q';
    disp("Expected complete log likelihood values: ");
    disp(Q);
    
    
end