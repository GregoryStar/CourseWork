train_path = "optdigits_train.txt";
val_path = "optdigits_valid.txt";

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

trnErrors = zeros(1, 6);
valErrors = zeros(1, 6);
index = 1;
mVals = [3, 6, 9, 12, 15, 18];
for m = mVals
    disp(m + " Hidden Nodes: ");
    [z, w, v] = mlptrain(train_path, val_path, m, 10);
    
    %Compute errors
    [error, ~] = computeMLPError(v, w, trnMat, trnLbls);
    trnErrors(index) = error;
    [error, ~] = computeMLPError(v, w, valMat, valLbls);
    valErrors(index) = error;
    
    index = index + 1;    
end

figure
plot(mVals, trnErrors);
hold on
plot(mVals, valErrors);
title('Error vs Number of Hidden Nodes');
legend('Training Error','Validation Error');
xlabel('# of Hidden Nodes');
ylabel('Error Rate');


