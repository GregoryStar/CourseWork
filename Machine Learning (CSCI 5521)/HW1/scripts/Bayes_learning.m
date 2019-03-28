function [p1, p2, pc1, pc2] = Bayes_learning(training_data, validation_data)
    %Read the training data in
    trainDataMat = dlmread(training_data);
    trainMat = trainDataMat(:, 1:22);
    trainLabels = trainDataMat(:, 23:23);
    
    %These correspond to P_ij = p(x_j = 0|C_j) for
    %both C_1 and C_2
    c1Dists = [];
    c2Dists = [];
    for i = 1:22
        c1Dists(i) = 0;
        c2Dists(i) = 0;
    end
    numC1 = 0;
    numC2 = 0;
    
    %Calculate the Bernoulli densities
    for i = 1:89
        if trainLabels(i) == 1
            numC1 = numC1 + 1;
        else
            numC2 = numC2 + 1;
        end
        for j = 1:22
            if trainLabels(i) == 1
                if trainMat(i, j) == 0
                    c1Dists(j) = c1Dists(j) + 1;
                end
            else 
                if trainMat(i, j) == 0
                    c2Dists(j) = c2Dists(j) + 1;
                end
            end
        end
    end
    
    %We know how many c1s and c2s there are in each column, but we need
    %to divide by the total number of c1s and c2s to get the probability
    %if one of the probabilities is either 0 or 1, change it so that
    %that there's no log(0).
    for i = 1:22
        c1Dists(i) = c1Dists(i)/numC1;
        c2Dists(i) = c2Dists(i)/numC2;
        if c1Dists(i) == 0
            c1Dists(i) = 0.00000001;
        elseif c1Dists(i) == 1
            c1Dists(i) = 0.99999999;
        elseif c2Dists(i) == 0
            c2Dists(i) = 0.00000001;
        elseif c2Dists(i) == 1
            c2Dists(i) = 0.99999999;
        end
    end
    %We now know the Bernoulli densities for each column.
    
    
    %Read in the validation data
    validDataMat = dlmread(validation_data);
    validMat = validDataMat(:, 1:22);
    validLabels = validDataMat(:, 23:23);
    [n, D] = size(validMat);
    
    %Test the various parameters on the validation set
    params = [-5,-4,-3,-2,-1,0,1,2,3,4,5];
    errors = zeros(size(params));
    classChoices = zeros(n);
    
    %For every sigma
    for k = 1:length(params)
       sigma = params(k);
       
       %Compute the priors based on the given rule
       priorC1 = 1/(1+exp(-sigma));
       priorC2 = 1 - priorC1;
       
       %For every sample in the data set
       for i = 1:n
           
           %Compute the classifier value
           classifier = log(priorC1/priorC2);
           %This part here corresponds to a summation (see my derivation
           %in the written portion of the homework).
           for j = 1:D
            classifier = classifier + (1-validMat(i, j))*log(c1Dists(j)/c2Dists(j));
            classifier = classifier + validMat(i, j)*log((1-c1Dists(j))/(1-c2Dists(j))); 
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
           if classChoices(i) == validLabels(i)
               numCorrect = numCorrect + 1;
           end
       end
       %Store the error in an array so we can later print the each param
       %with its error in a table.
       errors(k) = 1 - numCorrect/n;
    end
    
    %Find best prior
    bestIndex = -1;
    minError = 2;
    for i = 1:length(errors)
        if minError > errors(i)
            minError = errors(i);
            bestIndex = i;
        end
    end
    
    bestPriorC1 = 1/(1+exp(-params(bestIndex)));
    bestPriorC2 = 1 - bestPriorC1;

    %fprintf doesn't work the way I thought it did, so this is a somewhat
    %wonky method of getting fprintf to print the table, by putting both
    %columns into one array.
    combined = [];
    for i = 1:2*length(params)
        if mod(i, 2) == 1
            combined(i) = params((i+1)/2);
        else
            combined(i) = errors(i/2);
        end
    end
    
    %return parameters
    p1 = c1Dists;
    p2 = c2Dists;
    pc1 = bestPriorC1;
    pc2 = bestPriorC2;

    %Print the table out
    disp("Parameter    error");
    fprintf("%f    %f \n", combined);
    
    %Bayes_testing("SPECT_test.txt", p1, p2, pc1, pc2);
end