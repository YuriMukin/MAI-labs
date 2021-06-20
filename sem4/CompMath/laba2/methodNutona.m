function result = methodNutona(polinom)
  xp = borders(polinom)(2)
  result=xp-findPolinom(polinom, xp)/findPolinom(dif(polinom), xp);
  while (abs(xp-result)>0.001)
    xp=result;
    result=xp-findPolinom(polinom, xp)/findPolinom(dif(polinom), xp);
  endwhile
endfunction
