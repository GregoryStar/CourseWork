function [projMat, eigens] = myLDA(data, num_PC)
    [~, width] = size(data);
    lbls = data(:, width);
    
    %Split the data matrix into 10 matrices by class
    classes = cell(10);
    for i = 1:10
        classIndices = all(data(:, width) == i - 1, 2);
        classes{i} = data(classIndices, 1:width-1);
    end
    
    %Compute the in-class mean of each class
    %Use that to compute the total mean
    means = cell(10);
    totalMean = zeros(1, width-1);
    for i = 1:10
        means{i} = mean(classes{i});
        totalMean = totalMean + means{i};
    end
    totalMean = (1/10) * totalMean;
    
    %Compute the in-class scatter
    Sw = zeros(width-1, width-1);
    for i = 1:10
        currentClass = classes{i};
        %[m,n] = size(currentClass);
        %disp("m: " + m + " n: " + n);
        %disp(currentClass);
        [m, ~] = size(currentClass);
        for j = 1:m
            x = currentClass(j, :);
            diff = x - means{i};
            toAdd = transpose(diff) * diff;
            Sw = Sw + transpose(diff) * diff;
        end 
    end
  
    %Compute the between-class scatter
    Sb = zeros(width-1, width-1);
    for i = 1:10
        %Compute Ni, the number of data points in class i
        classCount = 0;
        for j = 1:size(lbls)
            if(lbls(j) == i-1)
                classCount = classCount + 1;
            end
        end
        meanDiff = means{i} - totalMean;
        toAdd = classCount * transpose(meanDiff) * meanDiff;
        Sb = Sb + toAdd;
    end
    
    [m, n] = size(Sw);
    for i = 1:m
        for j = 1:n
            if i == j && Sw(i, j) == 0
                Sw(i,j) = 0.000001;
            end
        end
    end

    criticalMat = Sw\Sb;
    
    [vecs,vals] = eig(criticalMat);
    [sortedEVals, indices] = sort(diag(vals), 'descend');
    sortedEVecs = vecs(:,indices);
    projMat = sortedEVecs(:,1:num_PC);
    eigens = sortedEVals(1:num_PC,:);
end