import math
from array import *
import numpy as np

#здесь подставить функцию из списка ниже
func_value = lambda x: f4(x)
#здесь создаются новые функции
f1 = lambda x: (math.sin(x)) ** 3 - (math.cos(x/2)) ** 2 + 2
f2 = lambda x: - x ** 4 + 3 * x ** 3 + 4 * x - 5
f3 = lambda x: (math.sin(x)) ** 3 - 3 * math.sin(x ** 2) +4 * math.sin(x) + 4 * x
f4 = lambda x: math.log(10 * math.sin((3 * (x/5)) ** 2) + 1)


def laba_6(interval: list, step):
    start = interval[0]
    stop = interval[1]
    sum_odd = 0
    sum_even = 0
    j = 0
    y_0 = func_value(start)
    y_n = func_value(stop)
    start += step

    values = [y_0]#список всех значений функции

    for i in np.arange(start, stop, step):
        if j % 2 == 0:
            sum_odd += func_value(i)
        else:
            sum_even += func_value(i)
        values.append(func_value(i))
        j += 1
    values.append(y_n)
    return step*(y_n + y_0 + sum_odd * 4 + sum_even * 2)/3
