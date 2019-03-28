training_data = "face_train_data_960.txt";
test_data = "face_test_data_960.txt";
rawDataMat = dlmread(training_data);
[~, width] = size(rawDataMat);
trnMat = rawDataMat(:, 1:width-1);
trnLbls = rawDataMat(:, width);

rawDataMat = dlmread(test_data);
[~, width] = size(rawDataMat);
testMat = rawDataMat(:, 1:width-1);
testLbls = rawDataMat(:, width);

%Compute the plot of proportion of variance
eigens = sort(eig(cov(trnMat)),'descend');
totalVariance = sum(eigens);
proportions = [];
numEigens = [];
for i = 1:size(eigens)
    slicedEigens = eigens(1:i, :);
    explainedVariance = sum(slicedEigens);
    proportions(i) = explainedVariance/totalVariance;
    numEigens(i) = i;
end
propOfVarExp = 0;
K = 0;
while propOfVarExp < 0.9
    K = K + 1;
    propOfVarExp = proportions(K);
end

disp("Num PCs that explain 90% of the variance: " + K);

%Plot the proportion of variance
figure
plot(numEigens, proportions);
title('Proportion of explained variance');
xlabel('Eigenvectors');
ylabel('Prop. of var.');

%Perform PCA
[W, pcEigs] = myPCA(trnMat, K);

%Find training mean
trnMean = mean(trnMat);
cntrTrnMat = trnMat - trnMean;
projTrnMat = transpose(transpose(W) * transpose(cntrTrnMat));

%Fine test mean
testMean = mean(testMat);
cntrTestMat = testMat - testMean;
projTestMat = transpose(transpose(W) * transpose(cntrTestMat));

disp("KNN Classification Error for Projected Data");
%Iterate over relavant K values
for k = [1, 3, 5, 7]
    [pred] = myKNN([projTrnMat trnLbls], [projTestMat testLbls], k);
    errors = 0;
    for i=1:size(pred)
        if (not(pred(i,:) == testLbls(i,:)))
            errors = errors + 1;
        end
    end
    [m, ~] = size(pred);
    errorProportion = errors/m; 
    disp("k = " + k + ": " + errorProportion);
end