function answer = replacePolinom(polinom, a)
  while (numel(polinom) >= 1)
    polinom = divPolinom(polinom, a);
    answer(end+1)=polinom(end);
    polinom = polinom(1:end-1);
  end
  answer = flip(answer);
endfunction
