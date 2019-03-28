training_data = "face_train_data_960.txt";
test_data = "face_test_data_960.txt";
data = dlmread(training_data);
[m, width] = size(data);
noLbls = data(:, 1:width-1);

data2 = dlmread(test_data);
[m, width] = size(data2);
noLbls2 = data2(:, 1:width-1);

noLbls = [noLbls; noLbls2];

%Perform PCA
[W, eigenVals] = myPCA(noLbls, 5);
dataMean = mean(noLbls);
cntrData = noLbls - dataMean; 

%Create 5 separate figures for the top 5 eigenfaces
figure
for i = 1:5
    subplot(1, 5, i);
    currentEigen = W(:, i);
    imagesc(reshape(currentEigen,32,30)');
end