function [z] = mlptest(test_path, w, v)
    %Read the test matrix in
    rawTestMat = dlmread(test_path);
    testMat = rawTestMat(:, 1:end-1);
    testLbls = rawTestMat(:, end);

    [errorRate, z] = computeMLPError(v, w, testMat, testLbls);
    disp("Test Error Rate: " + errorRate);
end

