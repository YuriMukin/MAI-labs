import class_polinom as cp
import numpy as np

p = cp.Polinom(np.asarray(list(map(float, input().split()))))
print (p.ring_of_roots())