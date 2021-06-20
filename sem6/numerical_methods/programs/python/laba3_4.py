import numpy as np


def first_derivative(i, x, y):
    return (y[i+1] - y[i]) / (x[i+1] - x[i])


def second_derivative(i, x, y):
    a = (y[i+2] - y[i+1]) / (x[i+2] - x[i+1])
    b = (y[i+1] - y[i]) / (x[i+1] - x[i])
    c = x[i+2] - x[i]
    return 2 * (a - b) /c


def main():
    x = [-1.0, -0.4, 0.2, 0.6, 1.0]
    y = [-1.4142, -0.55838, 0.27870, 0.84008, 1.4142]
    x0 = 0.2
    for i in range(len(x)):
        if ((x[i]<=x0) and (x0 <=x[i+1])):
            print("y' = {}".format(first_derivative(i, x, y)))
            print("y'' = {}".format(second_derivative(i, x, y)))
            break


if __name__ == "__main__":
    main()