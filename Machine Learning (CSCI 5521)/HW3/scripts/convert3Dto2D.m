function [pixelArray2D] = convert3Dto2D(img_array)
    [m, n, ~] = size(img_array);
    pixelArray2D = [];
    indexCount = 1;
    for i = 1:m
        for j = 1:n
            pixelArray2D(indexCount, 1) = img_array(i, j, 1);
            pixelArray2D(indexCount, 2) = img_array(i, j, 2);
            pixelArray2D(indexCount, 3) = img_array(i, j, 3);
            indexCount = indexCount + 1;
        end
    end
end

