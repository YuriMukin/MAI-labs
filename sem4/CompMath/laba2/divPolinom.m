function vector = divPolinom(polinom, a)
    b = polinom(1);
    vector(1)=b;
    for element = polinom(2:numel(polinom))
      b = element + b*a;
        vector(end+1)=b;
    end
end