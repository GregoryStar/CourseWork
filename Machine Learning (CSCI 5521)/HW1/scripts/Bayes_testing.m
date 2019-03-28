function [] = Bayes_testing(test_data, p1, p2, pc1, pc2)
    %Read in the validation data
    rawDataMat = dlmread(test_data);
    dataMat = rawDataMat(:, 1:22);
    labels = rawDataMat(:, 23:23);
    [n, D] = size(dataMat);
    
    classChoices = [];
    %For every sample in the data set
   for i = 1:n
       %Compute the classifier value
       classifier = log(pc1/pc2);
       %This part here corresponds to a summation (see my derivation
       %in the written portion of the homework).
       for j = 1:D
        classifier = classifier + (1-dataMat(i, j))*log(p1(j)/p2(j));
        classifier = classifier + dataMat(i, j)*log((1-p1(j))/(1-p2(j))); 
       end

       %Use the classifier criteria to determine the class
       if classifier >= 0
           classChoices(i) = 1;
       else
           classChoices(i) = 2;
       end
   end 

   %Compute the percentage of correct results
   numCorrect = 0;
   for i = 1:n
       if classChoices(i) == labels(i)
           numCorrect = numCorrect + 1;
       end
   end
   error = 1 - numCorrect/n;
   
   disp("Error rate");
   disp(error);
end