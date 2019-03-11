function BW = Threshold(X, sensitivity, mode)
    if mode == 0
        thresMode = 'mean';
    elseif mode == 1
         thresMode = 'gaussian';
    else
        thresMode = 'median';
    end
%     X = X - min(X(:));
%     X = X / (max(X(:))-min(X(:)));
    T = adaptthresh(X, sensitivity,'ForegroundPolarity', 'bright','Statistic', thresMode);
    BW = imbinarize(X, T);
end

