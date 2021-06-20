function result = methodChord(polinom)
    bd = borders(polinom);
    a = bd(1)-1;
    b = bd(2)+1;
    eps = 0.001;
    while (abs(a - b) > eps)
        a = b + (b - a) * findPolinom(polinom,b) / (findPolinom(polinom,b) - findPolinom(polinom,a));
        b = a - (a - b) * findPolinom(polinom,a) / (findPolinom(polinom,a) - findPolinom(polinom,b));
    end
    result = a;
end