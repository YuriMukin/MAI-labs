function ans = dif(polinom)
ans(1) = polinom(1)*(length(polinom)-1);
for i=2:length(polinom)-1
    ans(end+1) = polinom(i)*(length(polinom)-i);
end
end