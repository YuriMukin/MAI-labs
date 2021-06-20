def nuton_method(polinom):
    xp = borders(polinom)[1]
    result = xp - findPolinom(polinom, xp)/findPolinom(diff_pol(polinom), xp)
    while abs(xp-result)>0.001:
        xp=result
        result = xp - findPolinom(polinom, xp)/findPolinom(diff_pol(polinom), xp)
    return result


def borders(polinomin):
    answer = [1]
    polinom = polinomin.copy()
    polinomC = polinom.copy()
    if polinom[0]<0:
        for i in range(len(polinom)-1):
            polinom[i]=polinom[i]*(-1)
            polinomC[i] = polinomC[i]*(-1)        
    for i in range(len(polinom)):
        if ((i)%2 == 1):
            polinom[len(polinom)-(i+1)] = -polinom[len(polinom)-(i+1)]
    if ((len(polinom)-1)%2==1):
        for i in range(len(polinom)-1):
            polinom[i] = polinom[i]*(-1)
    LBF = True
    while LBF:
        d = divPolinom(polinom, answer[0])
        allpos = True
        for i in d:
            if i<0:
                allpos = False
        if allpos:
            answer[0] = -answer[0]
            LBF = False
        if LBF:
            answer[0] = answer[0]+1
    answer.append(answer[0])
    allpas = True
    while allpas:
        d = divPolinom(polinomC, answer[1])
        allpas = False
        for i in d:
            if i<0:
                allpas = True
        if allpas:
            answer[1] = answer[1]+1
    return answer

def divPolinom(polinomin, x):
    polinom = polinomin.copy()
    p = polinom[0]
    polinom.remove(p)
    result = [p]
    for i in polinom:
        p = i + p*x
        result.append(p)
    return result
    
def findPolinom(polinom, x):
    result = polinom[0]
    for i in range(len(polinom)-1):
        result = polinom[i+1] + result*x
    return result

def diff_pol(polinomin):
    polinom = polinomin.copy()
    result = list()
    for i in range(len(polinom)-1):
        result.append(polinom[i]*(len(polinom)-i-1))
    return result

print (nuton_method(list(map(int, input().split()))))