disp("KNN Classification Errors");

%Iterate over all the relavant K values
for k = [1, 3, 5, 7]
    training_data = "optdigits_train.txt";
    test_data = "optdigits_test.txt";
    
    %Read the training matrix in
    trnData = dlmread(training_data);
    
    %Read the test matrix in
    testData = dlmread(test_data);
    [~, width] = size(testData);
    testLbls = testData(:, width);
    [m, n] = size(testLbls);
    
    %Get the class prediction vector
    prediction = myKNN(trnData, testData, k);

    %Count all the incorrect classifications
    errors = 0;
    for i=1:m
        if (not(prediction(i,:) == testLbls(i,:)))
            errors = errors + 1;
        end
    end
    
    %Divide the error count by the total number of labels
    errorProportion = errors/m; 
    
    disp("k = " + k + ": " + errorProportion);
end