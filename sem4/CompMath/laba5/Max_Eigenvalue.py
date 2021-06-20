import numpy as np


def Max_Eigenvalue(matrix):
    y0 = np.array([[1],[1],[1]], dtype = float)
    y1 = np.dot(matrix, y0)
    y2 = np.dot(np.linalg.matrix_power(matrix, 2), y0)
    res = 0
    count = 2
    while abs(res - (1/3)*sum(y2/y1))>=0.001:
        res = (1/3)*sum(y2/y1)
        y1 = y2
        count+=1
        y2 = np.dot(np.linalg.matrix_power(matrix, count), y0)
    return (1/3)*sum(y2/y1)
    
 
print('enter matrix 3x3 line by line')
,p=list()
for i in range(3):
    p.append(list(map(float, input().split())))
print (Max_Eigenvalue(np.asarray(p, dtype = float)))