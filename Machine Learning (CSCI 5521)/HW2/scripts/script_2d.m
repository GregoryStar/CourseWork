training_data = "optdigits_train.txt";
test_data = "optdigits_test.txt";
rawDataMat = dlmread(training_data);
[~, width] = size(rawDataMat);
dataMat = rawDataMat(:, 1:width-1);
lbls = rawDataMat(:, width);

rawDataMat2 = dlmread(test_data);
[~, width] = size(rawDataMat2);
dataMat2 = rawDataMat2(:, 1:width-1);
lbls2 = rawDataMat2(:, width);

for L = [2, 4, 9]
   %Perform LDA; W is the projection matrix
    [W, pcEigs] = myLDA(rawDataMat, L);

    %Use the projection matrix to project the data into lower
    %dimensional space.
    dataMean = mean(dataMat);
    cntrDataMat = dataMat - dataMean;
    projectedMat = transpose(transpose(W) * transpose(cntrDataMat));
    
    %This is the test matrix
    dataMean2 = mean(dataMat2);
    cntrDataMat2 = dataMat2 - dataMean2;
    projectedMat2 = transpose(transpose(W) * transpose(cntrDataMat2));
    
    disp("KNN error rates on data projected to " + L + " dimensions:");
    %Iterate over relavant K values
    for k = [1, 3, 5, 7]
        [pred] = myKNN([projectedMat lbls], [projectedMat2 lbls2], k);
        errors = 0;
        for i=1:size(pred)
            if (not(pred(i,:) == lbls2(i,:)))
                errors = errors + 1;
            end
        end
        [m, ~] = size(pred);
        errorProportion = errors/m; 
        disp("k = " + k + ": " + errorProportion);
    end
    
    

end