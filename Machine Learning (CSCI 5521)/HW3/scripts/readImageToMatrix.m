function [img_double, m, n] = readImageToMatrix(filePath)
    [img cmap] = imread(filePath);
    img_rgb = ind2rgb(img, cmap);
    img_double = im2double(img_rgb);
    [m, n, ~] = size(img_double);
end

