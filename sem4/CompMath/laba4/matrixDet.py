import numpy as np


def MatrixDet(mat):
    res = 1 
    _ = 0
    if mat.shape[0] == mat.shape[1]:
        for i in range(mat.shape[0]-1):
            if mat[i,i] !=0:
                for j in range(i+1,mat.shape[0]):
                    mat[j,i:] = mat[j,i:]-(mat[j,i]/mat[i,i])*mat[i,i:]
            else:
                tmp = np.copy(mat[i])
                k = 0
                while (mat[i+k,i] == 0) and (i+k+1<=mat.shape[1]-1):
                    k+=1
                if mat[i+k,i] != 0:   
                    mat[i] = mat[i+k] 
                    mat[i+k] = tmp
                    _+=1
                    for j in range(i+1,mat.shape[0]):
                        mat[j,i:] = mat[j,i:]-(mat[j,i]/mat[i,i])*mat[i,i:]
    for i in range(mat.shape[0]):
        res*=mat[i,i]
    if _ % 2 == 1:
        res=res*(-1)
    return res


print("enter number of lines:")
l= int(input())
p=list()
for i in range(l):
    p.append(list(map(float, input().split())))
print ('det is: ',MatrixDet(np.asarray(p)))