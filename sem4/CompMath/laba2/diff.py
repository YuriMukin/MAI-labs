def diff_pol(polinom):
    result = list()
    for i in range(len(polinom)-1):
        result.append(polinom[i]*(len(polinom)-i-1))
    return result

print (diff_pol(list(map(int, input().split()))))