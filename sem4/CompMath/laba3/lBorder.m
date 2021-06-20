function answer = lBorder(polinom)
  answer(1)=1;
  for i=1:length(polinom) - 1
    if rem(i,2) == 1
      polinom(length(polinom) - i) = -polinom(length(polinom) - i);
    end
  end
  if rem(length(polinom)-1, 2) == 1
    polinom = -polinom;
  end
  while true
    d = divPolinom(polinom, answer(1));
    allpos = true;
    for i = d
      if i<0
        allpos = false;
      end
    end
    if allpos
      answer(1) = -answer(1);
      return;
    end
    answer(1) = answer(1) + 1;
  end
end