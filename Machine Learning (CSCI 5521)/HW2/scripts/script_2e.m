training_data = "optdigits_train.txt";
test_data = "optdigits_test.txt";
rawDataMat = dlmread(training_data);
[~, width] = size(rawDataMat);
trnMat = rawDataMat(:, 1:width-1);
trnLbls = rawDataMat(:, width);

rawDataMat2 = dlmread(test_data);
[~, width] = size(rawDataMat2);
testMat = rawDataMat2(:, 1:width-1);
testLbls = rawDataMat2(:, width);



%Get the principle components for the training set
[W, pcEigs] = myLDA(rawDataMat, 2);

%Project the training matrix onto the principle components
trnMean = mean(trnMat);
cntrTrnMat = trnMat - trnMean;
projTrnMat = transpose(transpose(W) * transpose(cntrTrnMat));

testMean = mean(testMat);
cntrTestMat = testMat - testMean;
projTestMat = transpose(transpose(W) * transpose(cntrTestMat));

projTrnMat = [projTrnMat; projTestMat];
trnLbls = [trnLbls; testLbls];

[m, n] = size(projTrnMat);
X = projTrnMat(:,1);
Y = projTrnMat(:,2);

figure
title('Optdigits with 2 Principle Components');
gscatter(X, Y, trnLbls);
ii = 1;

%Draw numbers on the plot
while ii <= m
    x = projTrnMat(ii,1);
    y = projTrnMat(ii,2);
    text(x, y, int2str(trnLbls(ii)));
    ii = ii + 25;
end

%myLDA(rawDataMat, 3);