function result = gorner_for_nm(polinom, xy)
  for column = polinom(:,1:size(polinom,2))
    vector(end+1) = findPolinom(transpose(column), xy(2));
  endfor
  result = findPolinom(vector, xy(1));
endfunction
