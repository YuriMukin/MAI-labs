import class_polinom as cp
import numpy as np

p = cp.Polinom(np.asarray(list(map(float, input().split()))))
print (p.div_pol_into_pol(np.array(list(map(float, input().split())))))