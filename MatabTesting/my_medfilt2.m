function X = my_medfilt2(currentPattern,medFiltParam)

    X= medfilt2(currentPattern, [medFiltParam medFiltParam]);

end

