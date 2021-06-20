function answer = diff_by_xy(polinom, var)
  answer = [];
  if var == 'x'
    polinom = transpose(polinom);
    for column = polinom(:, 1:end)
      answer = [answer; dif(column)];
    endfor
  endif
  if var == 'y'
    for rows = polinom(:, 1:end)
      answer = [answer; dif(rows)];
    endfor
    answer = transpose(answer);
  endif
endfunction
