function b = findPolinom(polinom, x)
    b = polinom(1);
    for element = polinom(2:numel(polinom))
      b = element + b*x;
    end
end
