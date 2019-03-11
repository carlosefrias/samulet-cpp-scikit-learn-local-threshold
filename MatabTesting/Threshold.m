function BW = Threshold(X, sensitivity, mode)
    if mode == 0
        thresMode = 'mean';
    elseif mode == 1
         thresMode = 'gaussian';
    else
        thresMode = 'median';
    end
    T = adaptthresh(X, sensitivity,'ForegroundPolarity', 'bright','Statistic', thresMode);
    BW = imbinarize(X, T);
end

