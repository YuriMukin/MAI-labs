function result = div_pol_into_pol(pol, pold)
  if size(pol)(2)<size(pold)(2)
    result.a = [];
    result.b = pol;
  else
  dev = pold(1);
  pold = -pold(2:length(pold));
  res(end+1) = pol(1)/dev;
  for i = 2:length(pol)-length(pold)
      tmp = 0;
      if (i-1)<length(pold)
        for j=1:i-1
          tmp += res(j)*pold(i-j);
        endfor
      elseif (i-1)>=length(pold)
        for j=1:length(pold)
          tmp += res(length(res)-j+1)*pold(j);
        endfor
      endif
      res(end+1) = (pol(i)+tmp)/dev;
  endfor
  for i = 1:length(pold)
      tmp = 0;
      t=0;
      for j=i:length(pold)
        if length(pol)-length(pold) - t>0
          tmp += res(length(pol)-length(pold)-t)*pold(j);
        endif
        t+=1;
      endfor
      res(end+1) = pol(length(pol)-length(pold)+i)+tmp;
  endfor
  result.a = res(1:length(pol)-length(pold));
  result.b = res(length(pol)-length(pold)+1:length(res));
  endif
endfunction
