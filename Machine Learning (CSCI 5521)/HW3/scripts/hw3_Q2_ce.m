%{
NOTE: THIS SCRIPT DOES PART C, D, and E.
First it runs regular EMG on goldy.bmp with 7 clusters.
Next it runs k-means on goldy.bmp with 7 clusters.
Finally, it runs improved EMG on goldy.bmp with 7 clusters.

Obviously regular EMG has a good chance of failing, so most of the
time, the result of the first EMG call will be a handled exception.
%}

%Run EM on goldy.bmp with 7 clusters
try
    [h, colorMap, Q] = EMG(0, 'goldy.bmp', 7);
catch
    disp("One of the covariance matrices is singular! mvnpdf failed!");
end

%Now do k-means on it.
[img_double, m, n] = readImageToMatrix('goldy.bmp');
%Convert 3d image matrix to 2d matrix of pixels (rows are rgb values)
rgbArray = convert3Dto2D(img_double);
numPixels = m * n;

%Perform k-means
[clusterIndices, colorMap] = kmeans(rgbArray, 7);
disp("K-means complete, starting improved EM (this make take several minutes)...");

%Generate compressed image with new-found colormap
indexCount = 1;
compressedMat = [];
for i = 1:m
    for j = 1:n
        currentColor = colorMap(clusterIndices(indexCount), :);
        compressedMat(i, j, 1) = currentColor(1);
        compressedMat(i, j, 2) = currentColor(2);
        compressedMat(i, j, 3) = currentColor(3);
        indexCount = indexCount + 1;
    end
end

%Display the image
figure
imagesc(compressedMat);
title("K-means Compression of goldy.bmp with 7 Colors");

%Finally, run improved EMG on goldy.bmp
[h, colorMap, Q] = EMG(1, 'goldy.bmp', 7);





