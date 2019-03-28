function [PCs, eigens] = myPCA(data, num_PC)
    [vecs,vals] = eig(cov(data));
    [sortedEVals, indices] = sort(diag(vals), 'descend');
    sortedEVecs = vecs(:,indices);
    PCs = sortedEVecs(:,1:num_PC);
    eigens = sortedEVals(1:num_PC,:);
end