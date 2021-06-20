import numpy as np

def ab(a, b):
    n = a.shape[0]
    alpha = np.zeros((n, n))
    beta = np.zeros(n)
    for i in range(n):
        alpha[i] = -a[i] / a[i][i]
        beta[i] = b[i]/a[i][i]
        alpha[i][i] = 0
    return alpha, beta
    
def norm_abs(a):
    res = 0
    for i in range(a.shape[0]):
        s = 0
        try:
            for j in range(a.shape[0]):
                s += abs(a[j][i])
            if s > res:
                res = s
        except:
            res += abs(a[i])
    return res
    
def norm_sq(a):
    res = 0
    for i in range(a.shape[0]):
        try:
            for j in range(a.shape[0]):
                res += a[i][j]**2
        except:
            res += a[i]**2
    return res**0.5
    
def norm_c(a):
    res = 0
    for i in range(a.shape[0]):
        s = 0
        try:
            for j in range(a.shape[0]):
                s += abs(a[i][j])
            if s > res:
                res = s
        except:
            if abs(a[i]) > res:
                res = abs(a[i])
    return res
    

print('1. Решить пример из своего варианта')
print('2. Решить произвольный пример')
print('Выберите: ', end=' ')
answer = int(input())
while answer not in [1, 2]:
    answer = int(input('Выберите 1 или 2!\n'))

if answer == 1:

    a = np.zeros((4, 4))

    #1
    a[0][0] = 14; a[0][1] = -4; a[0][2] = -2; a[0][3] = 3

    #2
    a[1][0] = -3; a[1][1] = 23; a[1][2] = -6; a[1][3] = -9

    #3
    a[2][0] = -7; a[2][1] = -8; a[2][2] = 21; a[2][3] = -5

    #4
    a[3][0] = -2; a[3][1] = -2; a[3][2] = 8; a[3][3] = 18

    b = np.zeros(4)
    b[0] = 38; b[1] = -195; b[2] = -27; b[3] = 142
    
else:
    n = 'a'
    n = int(input('Введите размерность (число) \n'))
    a = np.zeros((n, n))
    b = np.zeros(n)
    
    for i in range(1, n+1):
        s = input('Введите {}-ю строку\n'.format(i))
        a[i] = [int(s_i) for s_i in s.split()]
        b[i] = int(input('Введите правую часть\n'))
    
print('Матрица A\n', a, '\n'); print('Правая чаасть', b, '\n')
alpha, beta = ab(a, b)
print('Alpha:\n', alpha, '\n')
print('beta\n', beta, '\n')
print('Нормы\n', norm_abs(alpha), '\n', norm_sq(alpha), '\n', norm_c(alpha), '\n')
eps = float(input('Введите эпсилон:\n'))
print('Метод простых итераций.')
prev = beta
curr = beta + alpha.dot(beta)
i = 0
norm_alpha = norm_c(alpha)
while norm_c(curr - prev) * ( norm_alpha / (1 - norm_alpha) ) > eps:
    prev = curr
    curr = beta + alpha.dot(prev)
    print('Текущее приближение: ', curr)
    i += 1
print('Решение закончилось на {}-й итерации'.format(i))

print('Решение x:\n', curr)

print('Проверка, A*x', a.dot(curr))

print('Метод Зейделя')
k = 0
prev = beta
converge = False
m = alpha.shape[0]
while not converge:
    curr = np.copy(prev)
    for i in range(m):
        s = 0
        for j in range(m):
            s += alpha[i, j] * curr[j]
        curr[i] = beta[i] + s
    converge =  norm_c(curr - prev) * ( norm_alpha / (1 - norm_alpha) ) < eps
    k += 1
    prev = np.copy(curr)

print('Решение закончилось на {}-й итерации'.format(k))

print('Решение x:\n', curr)

print('Проверка, A*x', a.dot(curr))
