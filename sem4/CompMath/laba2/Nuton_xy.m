function result = Nuton_xy(polinom, polinomi)
  result = [];
  result(end+1) = 3;
  result(end+1) = 3;
  eps = 0.001;
  Jac = det([gorner_for_nm(diff_by_xy(polinom,'x'),[result(1),result(2)]),gorner_for_nm(diff_by_xy(polinom,'y'),[result(1),result(2)]); 
         gorner_for_nm(diff_by_xy(polinomi,'x'),[result(1),result(2)]),gorner_for_nm(diff_by_xy(polinomi,'y'),[result(1),result(2)])]);
  if Jac == 0
    result = 'non';
  elseif Jac != 0 
    xp = inf;
    yp = inf;
    while (result(1)-xp)^2 + (result(2)-yp)^2 >=eps^2
      xp = result(1);
      yp = result(2);
      result(1) = xp - (1/Jac)*det([gorner_for_nm(polinom,[xp,yp]),gorner_for_nm(diff_by_xy(polinom,'y'),[xp,yp]); 
                                gorner_for_nm(polinomi,[xp,yp]),gorner_for_nm(diff_by_xy(polinomi,'y'),[xp,yp])]);
      result(2) = yp - (1/Jac)*det([gorner_for_nm(diff_by_xy(polinom,'x'),[xp,yp]),gorner_for_nm(polinom,[xp,yp]); 
                                gorner_for_nm(diff_by_xy(polinomi,'x'),[xp,yp]),gorner_for_nm(polinomi,[xp,yp])]);
      Jac = det([gorner_for_nm(diff_by_xy(polinom,'x'),[xp,yp]),gorner_for_nm(diff_by_xy(polinom,'y'),[xp,yp]); 
             gorner_for_nm(diff_by_xy(polinomi,'x'),[xp,yp]),gorner_for_nm(diff_by_xy(polinomi,'y'),[xp,yp])]);
    endwhile
  endif
endfunction
