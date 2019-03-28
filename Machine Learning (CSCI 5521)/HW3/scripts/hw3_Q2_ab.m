%{
NOTE: THIS SCRIPT DOES PART C, D, and E.
First it runs regular EMG on goldy.bmp with 7 clusters.
Next it runs k-means on goldy.bmp with 7 clusters.
Finally, it runs improved EMG on goldy.bmp with 7 clusters.

Obviously regular EMG has a good chance of failing, so most of the
time, the result of the first EMG call will be a handled exception.
%}

for i = [4, 8, 12]
    try
        [~, ~, ~] = EMG(0, 'stadium.bmp', i);
    catch
        disp("One of the covariance matrices is singular! mvnpdf failed!");
    end

end





