training_data = "face_train_data_960.txt";
test_data = "face_test_data_960.txt";

%Read training data in
rawTrnMat = dlmread(training_data);
[~, width] = size(rawTrnMat);
trnMat = rawTrnMat(:, 1:width-1);
trnLbls = rawTrnMat(:, width);

%Read test data in
rawTestMat = dlmread(test_data);
[~, width] = size(rawTestMat);
testMat = rawTestMat(:, 1:width-1);
testLbls = rawTestMat(:, width);

trnMean = mean(trnMat);
cntrTrnMat = trnMat - trnMean;
for K = [10, 50, 100]
    %Perform PCA and project to lower dimensional space
    [W, pcEigs] = myPCA(trnMat, K);
    projTrnMat = transpose(transpose(W) * transpose(cntrTrnMat));
    %Now we will project the first 5 images back to original dimensions
    figure
    for i = 1:5
        subplot(1, 5, i);
        lowDimImage = projTrnMat(i, :);
        origDimImage = transpose(W * transpose(lowDimImage)) + trnMean;
        imagesc(reshape(origDimImage,32,30)');
    end
end