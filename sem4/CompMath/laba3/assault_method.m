function answer = assault_method(polinom)
    border  = borders(polinom);
    a=border(1)-1;
    b=border(2)+1;
    function ans = count_differents(polinom)
      ans = 0;
      sign = polinom(1);
      for e = polinom(2:end)
        if (e != sign) && (e!=0)
          ans+=1;
          sign = e;
        endif
      endfor
    endfunction
    sign1 = sign(findPolinom(polinom, b));
    sign_1 = sign(findPolinom(polinom, a));
    polinom1 = dif(polinom);
    sign1 = [sign1, sign(findPolinom(polinom1, b))];
    sign_1 = [sign_1, sign(findPolinom(polinom1, a))];
    while length(polinom1) > 1
        tmp = -div_pol_into_pol(polinom, polinom1).b;
        polinom = polinom1;
        polinom1 = tmp;
        sign1 = [sign1, sign(findPolinom(polinom1, b))];
        sign_1 = [sign_1, sign(findPolinom(polinom1, a))];
    endwhile
  n1 = count_differents(sign1);
  n_1 = count_differents(sign_1);
  answer = (n_1 - n1);
endfunction
