import numpy as np

def LU(a):

    n = a.shape[0]
    u = np.matrix(np.zeros([a.shape[0], a.shape[1]]))
    l = np.matrix(np.zeros([a.shape[0], a.shape[1]]))
    
    for k in range(n):
        
        for j in range(k, n):
            u[k, j] = a[k, j] - l[k, :k] * u[:k, j]
        
        for i in range(k + 1, n):
            if i == k:
                l[i, k] = 1
            l[i, k] = (a[i, k] - l[i, : k] * u[: k, k]) / u[k, k]

    for i in range(n):
        for k in range(n):
            if i == k:
                l[i, k] = 1
    return l, u
    
def solve(a, b):
    n = a.shape[0]
    l, u = LU(a)
    x = np.zeros(n)
    y = np.zeros(n)
    
    def sum_y(i):
        res = 0
        for k in range(n):
            res += l[i, k] * y[k]
        return res
    for i in range(n):
        y[i] = b[i] - sum_y(i)
    
    def sum_x(i):
        res = 0
        for j in range(i, n):
            res += u[i, j]*x[j]
        return res
        
    for i in reversed(range(n)):
        x[i] = (y[i] - sum_x(i))/u[i, i]
        
    return x
    
def invert(a):
    n = a.shape[0]
    L, U = LU(a)
    x = np.zeros((n, n))
    es = []
    ys = []

    for i in range(n):
        es.append(np.zeros(n))
        es[i][i] = 1
        ys.append(solve(L, es[i]))
        x[i] = solve(U, ys[i])

    return x.transpose()
    
def det(a):
    L, U = LU(a)
    d = 1
    for i in range(a.shape[0]):
        d *= a[i, i]
    return d
    

  
print('1. Решить пример из своего варианта')
print('2. Решить произвольный пример')
print('Выберите: ', end=' ')
answer = int(input())
while answer not in [1, 2]:
    answer = int(input('Выберите 1 или 2!\n'))
    
if answer == 1:
    a = np.zeros((4, 4))

    #1
    a[0][0] = -1; a[0][1] = -8; a[0][2] = 0; a[0][3] = 5

    #2
    a[1][0] = 6; a[1][1] = -6; a[1][2] = 2; a[1][3] = 4

    #3
    a[2][0] = 9; a[2][1] = -5; a[2][2] = -6; a[2][3] = 4

    #4
    a[3][0] = -5; a[3][1] = 0; a[3][2] = -9; a[3][3] = 1

    b = np.zeros(4)
    b[0] = -60; b[1] = -10; b[2] = 65; b[3] = 18

    print('Матрица A\n', a, '\n'); print('Правая часть\n', b, '\n')
    L, U = LU(a)
    print('L*U:\n', L*U, '\n')
    print('L:\n', L, '\n')
    print('U:\n', U, '\n')
    print('det A = ', det(a), '\n')
    print('Решение:\n', solve(a, b), '\n')
    print('Обратная:\n', invert(a), '\n')

    print( np.dot(a, invert(a)))
    
    
else:
    n = 'a'
    n = int(input('Введите размерность (число)\n'))
    a = np.zeros((n, n))
    b = np.zeros(n)
    
    for i in range(1, n+1):
        s = input('Введите {}-ю строку (числа через запятую)\n'.format(i))
        a[i] = [int(s_i) for s_i in s.split()]
        b[i] = int(input('Введите правую часть (число)\n'))
    
    print('Матрица A\n', a, '\n'); print('Правая часть\n', b, '\n')
    L, U = LU(a)
    print('L*U:\n', L*U, '\n')
    print('L:\n', L, '\n')
    print('U:\n', U, '\n')
    print('Det(A) = ', det(a), '\n')
    if det(a) != 0:
        print('Решение:\n', solve(a, b), '\n')
        print('Обратная:\n', invert(a), '\n')
    else:
        print('Система несовместна.\n')
