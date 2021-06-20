function res = top_border_Lagrange(polinom)
  if polinom(1)<0
    polinom=-polinom;
  endif
  pos = [];
  for i = 1:length(polinom)
    if polinom(i)<0
      pos(end+1)=i;
    endif
  endfor
  B=max(abs(polinom(pos)));
  res = 1+(abs(B/polinom(1)))^(1/(pos(1)-1));
endfunction
