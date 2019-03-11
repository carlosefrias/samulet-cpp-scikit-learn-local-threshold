X = imread('KH25257-T81211-05-aerofoil_15.000_-57.000.tif');
minI = min(X(:));
maxI = max(X(:));
tic
T = Threshold(X, 0.01, 0);
toc
minT = min(T(:));
maxT = max(T(:));
csvwrite('file.csv',T);