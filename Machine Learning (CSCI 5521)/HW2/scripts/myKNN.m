function [prediction] = myKNN(training_data, test_data, k)
%Interpret the training matrix
[h, width] = size(training_data);
trnMat = training_data(:, 1:width-1);
trnLbls = training_data(:, width);

%Interpret the test matrix
[height, width] = size(test_data);
testMat = test_data(:, 1:width-1);

prediction = [];
for i = 1:height
    currentVec = testMat(i, :);
    dists = [];
    
    %Find the distance from the currentVec to all vectors in the
    %training set
    for j = 1:h
        comparingTo = trnMat(j, :);
        dists(j) = norm(currentVec - comparingTo);
    end
    
    %Get the indices of the sort of the distances
    [~, indices] = sort(dists);
    
    %Sort the training labels by the distance sort indices
    sortedLabels = trnLbls(indices, :);
    
    %Take only the top k
    sortedLabels = sortedLabels(1:k, :);
    
    %Find the most frequent among those top k
    class = mode(sortedLabels);
    prediction(i) = class;
end
prediction = transpose(prediction);
end