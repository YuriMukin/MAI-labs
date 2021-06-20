import numpy as np

def swp(a, b):
    p = np.zeros(len(b))
    q = np.zeros(len(b))
    p[0] = -a[0][1]/a[0][0]
    q[0] = b[0]/a[0][0]

    for i in range(1, len(p)-1):
        p[i] = -a[i][i+1]/(a[i][i] + a[i][i-1]*p[i-1])
        q[i] = (b[i] - a[i][i-1]*q[i-1])/(a[i][i] + a[i][i-1]*p[i-1])

    i = len(a)-1
    p[-1] = 0
    q[-1] = (b[-1] - a[-1][-2]*q[-2])/(a[-1][-1] + a[-1][-2]*p[-2])
    
    x = np.zeros(len(b))
    x[-1] = q[-1]

    for i in reversed(range(len(b)-1)):
        x[i] = p[i]*x[i+1] + q[i]
    
    return x

print('1. Решить пример из своего варианта')
print('2. Решить произвольный пример')
print('Выберите: ', end=' ')
answer = int(input())
while answer not in [1, 2]:
    answer = int(input('Выберите 1 или 2!\n'))
    
if answer == 1:
    
    a = np.zeros((5, 5))
    b = np.zeros(5)

    #1
    a[0][0] = -11; a[0][1] = 9; b[0] = -114

    #2
    a[1][0] = 1; a[1][1] = -8; a[1][2] = 1; b[1] = 81

    #3
    a[2][1] = -2; a[2][2] = -11; a[2][3] = 5; b[2] = -8

    #4
    a[3][2] = 3; a[3][3] = -14; a[3][4] = 7; b[3] = -38

    #5
    a[4][3] = 8; a[4][4] = 10; b[4] = 144
    
    print('Матрица:\n', a, '\n')
    print('Правая часть матрицы:\n', b, '\n')

    
else:
    n = int(input('Введите размерность (число)\n'))
    a = np.zeros((n, n))
    b = np.zeros(n)
    a[0][0] = int(input('Введите b (число)\n'))
    a[0][1] = int(input('Введите c (число)\n'))
    b[0] = int(input('Введите правую часть (число)\n'))
    for i in range(1, n-1):
        a[i][i-1] = int(input('Введите а (число)\n'))
        a[i][i] = int(input('Введите b (число)\n'))
        a[i][i+1] = int(input('Введите c (число)\n'))
        b[i] = int(input('Введите правую часть (число)\n'))
    a[-1][-2] = int(input('Введите a (число)\n'))
    a[-1][-1] = int(input('Введите b (число)\n'))
    b[-1] = int(input('Введите правую часть (число)\n'))

    print('Матрица:\n', a, '\n')
    print('Правая часть матрицы:\n', b, '\n')
print('Решение: ', swp(a, b))
        
