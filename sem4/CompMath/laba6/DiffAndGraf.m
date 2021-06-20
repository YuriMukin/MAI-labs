function DiffAndGraf(pol, bord, step)
  x=bord(1):step:bord(2);
  resY = [];
  resX = [];
  for j = 1:length(x)-min(length(pol), 3)
    delta = pol((j:length(pol)-1)+1)-pol(j:length(pol)-1);
    count = 0;
    tmp = 0;
    for i = 2:min(length(pol), 3)
      (delta(1)*((-1)^count))/(count+1);
      tmp =tmp + (delta(1)*((-1)^count))/(count+1);
      count = count+1;
      delta = delta((1:length(delta)-1)+1)-delta(1:length(delta)-1);
    endfor
    resY(end+1) = (1/step)*tmp;
    resX(end+1) = x(j);
  endfor
  plot(x, pol);
  hold on;
  grid on;
  plot(resX, resY);
endfunction
