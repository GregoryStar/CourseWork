
%Create some class 1 data
rng(1); % For reproducibility
r = sqrt(rand(100,1)); % Radius
t = 2*pi*rand(100,1); % Angle
data1 = [r.*cos(t), r.*sin(t)]; % Points

%Create some class 2 data
r2 = sqrt(3*rand(100,1)+2); % Radius
t2 = 2*pi*rand(100,1); % Angle
data2 = [r2.*cos(t2), r2.*sin(t2)]; % points

%Combine and label data
data3 = [data1;data2];
theclass = ones(200,1);
theclass(1:100) = -1;

%------ PART A ------
%Train the Kernel Perceptron on the generated data
[alphas, b] = kernPercGD(data3, theclass);

%Find the classification error rate of the kernel perceptron
[predictions] = predictKPerceptron(data3, data3, theclass, alphas, b);
numCorrect = 0;
for i = 1:200
    if predictions(i) * theclass(i) > 0
        numCorrect = numCorrect + 1;
    end
end
errorRate = 1 - (numCorrect/200);
disp("Generated Data Error Rate: " + errorRate);

% ------ PART B -------
%Train the SVM Classifier with various box constraints
cl = fitcsvm(data3,theclass,'KernelFunction','polynomial',...
'PolynomialOrder',2,'BoxConstraint',Inf,'ClassNames',[-1,1]);
c2 = fitcsvm(data3,theclass,'KernelFunction','polynomial',...
'PolynomialOrder',2,'BoxConstraint',0.1,'ClassNames',[-1,1]);
c3 = fitcsvm(data3,theclass,'KernelFunction','polynomial',...
'PolynomialOrder',2,'BoxConstraint',0.01,'ClassNames',[-1,1]);
c4 = fitcsvm(data3,theclass,'KernelFunction','polynomial',...
'PolynomialOrder',2,'BoxConstraint',0.001,'ClassNames',[-1,1]);

% Generate a grid of data points which will be used for the decision
% boundary
d = 0.02;
[x1Grid,x2Grid] = meshgrid(min(data3(:,1)):d:max(data3(:,1)),...
    min(data3(:,2)):d:max(data3(:,2)));
xGrid = [x1Grid(:),x2Grid(:)];

%Get the scores for both the kernal perceptron and the SVM
[perceptronScores] = predictKPerceptron(xGrid, data3, theclass, alphas, b);
[~,svmScores1] = predict(cl,xGrid);
[~,svmScores2] = predict(c2,xGrid);
[~,svmScores3] = predict(c3,xGrid);
[~,svmScores4] = predict(c4,xGrid);

%PLOT THE DATA AND THE DECISION BOUNDARY FOR THE KERNEL PERCEPTRON
figure;
h = gscatter(data3(:,1),data3(:,2),theclass,'rb','.');
hold on
title("Generated Data with Kernel Perceptron Decision Boundary")

%Plot the kernel perceptron decision boundary
contour(x1Grid,x2Grid,reshape(perceptronScores,size(x1Grid)),[0 0],'k');

legend(h,{'-1','+1'});

axis equal
hold off

%PLOT THE DATA AND THE DECISION BOUNDARY FOR THE SVMs

%%%%% SVM 1 %%%%%
figure;
h = gscatter(data3(:,1),data3(:,2),theclass,'rb','.');
hold on
title("Generated Data with SVM Decision Boundary (Box Contraint inf)")
contour(x1Grid,x2Grid,reshape(svmScores1(:, 2),size(x1Grid)),[0 0],'k');
legend(h,{'-1','+1'});
axis equal
hold off

%%%%% SVM 2 %%%%%
figure;
h = gscatter(data3(:,1),data3(:,2),theclass,'rb','.');
hold on
title("Generated Data with SVM Decision Boundary (Box Contraint 0.1)")
contour(x1Grid,x2Grid,reshape(svmScores2(:, 2),size(x1Grid)),[0 0],'k');
legend(h,{'-1','+1'});
axis equal
hold off

%%%%% SVM 3 %%%%%
figure;
h = gscatter(data3(:,1),data3(:,2),theclass,'rb','.');
hold on
title("Generated Data with SVM Decision Boundary (Box Contraint 0.01)")
contour(x1Grid,x2Grid,reshape(svmScores3(:, 2),size(x1Grid)),[0 0],'k');
legend(h,{'-1','+1'});
axis equal
hold off

%%%%% SVM 4 %%%%%
figure;
h = gscatter(data3(:,1),data3(:,2),theclass,'rb','.');
hold on
title("Generated Data with SVM Decision Boundary (Box Contraint 0.001)")
contour(x1Grid,x2Grid,reshape(svmScores4(:, 2),size(x1Grid)),[0 0],'k');
legend(h,{'-1','+1'});
axis equal
hold off

%------ PART C ------
%THIS FIRST PART IS FOR THE OPTDIGITS49 SET
train_path = 'optdigits49_train.txt';
test_path = 'optdigits49_test.txt';

%Read the training matrix in
rawTrainingMat = dlmread(train_path);
[numTrainPoints, width] = size(rawTrainingMat);
trnMat = rawTrainingMat(:, 1:width-1);
trnLbls = rawTrainingMat(:, width);

%Read the test matrix in
rawTestingMat = dlmread(test_path);
[numTestPoints, width] = size(rawTestingMat);
testMat = rawTestingMat(:, 1:width-1);
testLbls = rawTestingMat(:, width);

%Train the Kernal Perceptron on the optdigits49 set
[alphas, b] = kernPercGD(trnMat, trnLbls);

%Find the training error rate
[predictions] = predictKPerceptron(trnMat, trnMat, trnLbls, alphas, b);
numCorrect = 0;
for i = 1:numTrainPoints
    if predictions(i) * trnLbls(i) > 0
        numCorrect = numCorrect + 1;
    end
end
errorRate = 1 - (numCorrect/numTrainPoints);
disp("Optdigits49 Training Error Rate: " + errorRate);

%Find the test error rate
[predictions] = predictKPerceptron(testMat, trnMat, trnLbls, alphas, b);
numCorrect = 0;
for i = 1:numTestPoints
    if predictions(i) * testLbls(i) > 0
        numCorrect = numCorrect + 1;
    end
end
errorRate = 1 - (numCorrect/numTestPoints);
disp("Optdigits49 Test Error Rate: " + errorRate);

%THIS SECOND PART IS FOR THE OPTDIGITS79 SET
train_path = 'optdigits79_train.txt';
test_path = 'optdigits79_test.txt';

%Read the training matrix in
rawTrainingMat = dlmread(train_path);
[numTrainPoints, width] = size(rawTrainingMat);
trnMat = rawTrainingMat(:, 1:width-1);
trnLbls = rawTrainingMat(:, width);

%Read the test matrix in
rawTestingMat = dlmread(test_path);
[numTestPoints, width] = size(rawTestingMat);
testMat = rawTestingMat(:, 1:width-1);
testLbls = rawTestingMat(:, width);

%Train the Kernal Perceptron on the optdigits49 set
[alphas, b] = kernPercGD(trnMat, trnLbls);

%Find the training error rate
[predictions] = predictKPerceptron(trnMat, trnMat, trnLbls, alphas, b);
numCorrect = 0;
for i = 1:numTrainPoints
    if predictions(i) * trnLbls(i) > 0
        numCorrect = numCorrect + 1;
    end
end
errorRate = 1 - (numCorrect/numTrainPoints);
disp("Optdigits79 Training Error Rate: " + errorRate);

%Find the test error rate
[predictions] = predictKPerceptron(testMat, trnMat, trnLbls, alphas, b);
numCorrect = 0;
for i = 1:numTestPoints
    if predictions(i) * testLbls(i) > 0
        numCorrect = numCorrect + 1;
    end
end
errorRate = 1 - (numCorrect/numTestPoints);
disp("Optdigits79 Test Error Rate: " + errorRate);
