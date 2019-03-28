train_path = "optdigits_train.txt";
val_path = "optdigits_valid.txt";

%Best val = 18
optimalNumOfHidden = 18;

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

combMat = [trnMat ; valMat];
combLbls = [trnLbls ; valLbls];
[totalDataPoints, ~] = size(combMat);


%Train the network with the optimal number of hidden nodes
[~, w, v] = mlptrain(train_path, val_path, optimalNumOfHidden, 10);

%Compute error of the combined set
[error, z] = computeMLPError(v, w, combMat, combLbls);
disp("Combined error rate: " + error);

mlptest('optdigits_test.txt', w, v);

%Apply PCA to the hidden layers
[PCs, ~] = myPCA(z, 3);

%Project the hidden layers onto the principle components
centeredZ = z - mean(z);
projHiddenLayers = transpose(transpose(PCs) * transpose(centeredZ));

X = projHiddenLayers(:, 1);
Y = projHiddenLayers(:, 2);
Z = projHiddenLayers(:, 3);

colors = [
  0.25 0.75 0.36;
  1 1 0.3;
  1 0 1;
  0 0.2 1;
  1 0 0;
  0.76 0 0.4;
  0.5 0.38, 0.6;
  0 1 0;
  0.8 0.5 0.3;
  0 0.86 0.3
];

figure;
title('Optdigits with 2 Principle Components');
for i = 1:totalDataPoints
    currCol = colors(combLbls(i) + 1, :);
    currX = X(i);
    currY = Y(i);
    loglog(currX, currY, '.', 'Color', currCol);
    
    if i <= 500
        digit = int2str(combLbls(i));
        text(currX, currY, digit);
    end
    
    hold on;
end

for i = 1:totalDataPoints
    currCol = colors(combLbls(i) + 1, :);
    if i <= 500
        digit = int2str(combLbls(i));
        h = text(currX, currY, digit);
        set(h, 'Color', currCol)
    end
    
    hold on;
end
hold off;

figure;
title('Optdigits with 3 Principle Components');
for i = 1:totalDataPoints
    currCol = colors(combLbls(i) + 1, :);
    currX = X(i);
    currY = Y(i);
    currZ = Z(i);
    
    set(gca, 'XScale', 'log')
    set(gca, 'YScale', 'log')
    plot3(currX, currY, currZ, '.', 'Color', currCol);
    
    if i <= 500
        digit = int2str(combLbls(i));
        text(currX, currY, currZ, digit);
    end
    
    hold on;
end
hold off;
