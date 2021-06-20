function result = method_Leverrier(matrix)
  tmpR = [];
  for i=1:size(matrix)(1)
    tmpR(end+1) = sum(diag(matrix^i));
  endfor
  tmpR = tmpR(size(matrix)(1):-1:1);
  result = [1];
  for i=1:size(matrix)(1)
    result(end+1) = (-1/i)*sum(tmpR(end-(i-1):end).*result);
  endfor
endfunction
