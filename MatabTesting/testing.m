X = imread('t19452-09_27.100_-87.700.tif');
minI = min(X(:));
maxI = max(X(:));
tic
T = Threshold(X, 0.02, 0);
toc
minT = min(T(:));
maxT = max(T(:));
csvwrite('file.csv',T);