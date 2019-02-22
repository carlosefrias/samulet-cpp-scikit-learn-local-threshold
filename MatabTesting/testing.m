img = imread('t19452-09_27.100_-87.700.tif');
minI = min(img(:));
maxI = max(img(:));
tic
T = Threshold(img, 0.01, 0);
toc
minT = min(T(:));
maxT = max(T(:));
csvwrite('file.csv',T);