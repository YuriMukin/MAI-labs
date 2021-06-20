function answer = methodDihtomia(polinom)
br = borders(polinom)
a = br(1)-1;
b = br(2)+1;
 
while (b - a > 0.001)
  c = (a + b)/2;
  if(findPolinom(polinom, b)*findPolinom(polinom, c)<0)
    a = c;
  else
    b = c;
  end
end
answer = (a + b) / 2;  

end
