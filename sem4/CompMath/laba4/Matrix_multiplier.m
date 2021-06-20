function result = Matrix_multiplier(m1, m2)
  if (size(m1)(1)==1 && size(m1)(2)==1) || (size(m2)(1)==1 && size(m2)(2)==1)
    tmp = false;
  else
    tmp = true;
  endif
  if size(m1)(2) == size(m2)(1) && tmp
    if size(m1)(2) == 1
      r11 = Matrix_multiplier(m1(1,1), m2(1,1));
      r12 = Matrix_multiplier(m1(1,1), m2(1,2:end));
      r21 = Matrix_multiplier(m1(2:end,1), m2(1,1));
      r22 = Matrix_multiplier(m1(2:end,1), m2(1,2:end));
      result = [r11,r12;r21,r22];
    elseif size(m2)(2)>1
      for i=1:size(m1)(1)
        r11 = Matrix_multiplier(m1(i,1), m2(1,1));
        r12 = Matrix_multiplier(m1(i,1), m2(1,2:end));
        r21 = Matrix_multiplier(m1(i,2:end), m2(2:end,1));
        r22 = Matrix_multiplier(m1(i,2:end), m2(2:end,2:end));
        if i == 1
          result = [r11+r21, r12+r22];
        else
          result = [result; r11+r21, r12+r22];
        endif
      endfor
    else
      for i=1:size(m1)(1)
        r11 = Matrix_multiplier(m1(i,1), m2(1,1));
        r12 = Matrix_multiplier(m1(i,2:end), m2(2:end,1));
        if i == 1
          result = [r11+r12];
        else
          result = [result; r11+r12];
        endif
      endfor
    endif
  elseif size(m1) == [1,1] || size(m2) == [1,1]
    result = m1*m2;
  elseif size(m1)(2) != size(m2)(1)
    result = 0;
  endif
endfunction
