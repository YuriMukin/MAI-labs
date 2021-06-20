import numpy as np

b=200
s = ""
a = np.random.randint(-2, 2, size=(b, b))
for i in range(b):
    for j in range(b):
        s+=str(a[i][j])+" "
print(s)
print(np.linalg.det(a))
print(np.linalg.eig(a))
f = open('input.txt', 'w')
f.write(s)
f.close()