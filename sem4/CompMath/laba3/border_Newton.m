function result = border_Newton(polinom)
  if polinom(1) < 0
    polinom = -polinom;
  endif
  C = 0;
  temp = true; 
  alld = true;
  while temp
    tmp = polinom;
    for i=1:length(polinom)
      if findPolinom(tmp,C)<0
        alld = true;
      endif
      tmp = dif(tmp);
    endfor
    if alld
      C+=1;
      alld = false;
    else
      temp = false; 
    endif
  endwhile
  result = C;
endfunction
