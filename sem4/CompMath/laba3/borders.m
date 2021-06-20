function answer = borders(polinom)
  if polinom(1)<0
    polinom=-polinom;
  endif
  answer(1)=lBorder(polinom);
  answer(2) = 0;
  allpos = true;
  while allpos
    d = divPolinom(polinom, answer(2));
    allpos = false;
    for i = d
      if i<0
        allpos = true;
      end
    end
    if allpos
    answer(2) = answer(2) + 1;
    end
  end
end
