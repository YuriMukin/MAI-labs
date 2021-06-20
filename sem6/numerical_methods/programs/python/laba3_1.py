import numpy as np


#функция из варианта
def function_v12(x):
    return np.sin(x) + x

#произведения разностей искомого х и Х с известным значением без n-го элемента
def omega_function_Lagrange(x, n, X):
    res = 1
    for i in range(n):
        res*= x-X[i]
    return res

#произведения разностей искомого х и Х с известным значением с n-ым элементом
def omega_function_Newton(x, n, X):
    res = 1
    for i in range(n+1):
        res*= x-X[i]
    return res

#произведения разностей текущего х и Х с известным значением
def omega_function_derivative(k, n, X):
    res = 1
    for i in range(n):
        if (i!=k):
            res*= X[k]-X[i]
    return res

#генирируем значения Y
def count_y(fun, X):
    n = len(X)
    Y = [] 
    for i in range(n):
        Y.append(fun(X[i]))
    print("Y: ", Y)
    return Y

#составляем полином Лагранжа
def lagrange_polinom(x, X, Y):
    n = len(X)
    L = 0;
    res = "L(x) = "
    for i in range(n):
        tmp = Y[i]/omega_function_derivative(i, n, X);
        if(tmp>0 and i>0):
            res+=" + "
        res+=str(tmp)
        for j in range(n):
            if(i!=j):
                if (X[j]>0):
                    res+="(x - {})".format(X[j])
                else:
                    res+="(x + {})".format(-X[j])
        L += (omega_function_Lagrange(x, n, X) * Y[i])/((x - X[i]) * omega_function_derivative(i, n, X))
    print(res)
    return L

#находим значение коэффицентов полинома Ньютона
def f(n, i, j, X, Y):
    if(n==0):
        return (Y[i] - Y[j]) / (X[i] - X[j])
    else:
        return (f(n-1, i, j-1, X, Y) - f(n-1, i+1, j, X, Y)) / (X[i] - X[j])

#составляем полином Ньютона
def newton_polynom(x, X, Y):
    n = len(X)
    N = Y[0] + (x- X[0])*f(0, 1, 0, X, Y);
    res="\nN(x) = {} + {}(x - {} )".format(Y[0], f(0, 1, 0, X, Y), X[0])
    for i in range(1, n-1):
        tmp = f(i, 0, i+1, X, Y)
        res+=" + {}".format(tmp)
        for j in range(i+1):
            res+="(x - {})".format(X[j])
        N += omega_function_Newton(x, i, X)*tmp
    print(res)
    return N

def main():
    all_X = [[0, np.pi/6, 2*np.pi/6, 3*np.pi/6],[0, np.pi/6, np.pi/4, np.pi/2]] #это нужно считать откуда-то 
    for X in all_X:
        print("\nX: ", X)
        Y = count_y(function_v12, X)
        L = lagrange_polinom(1, X, Y)
        print("L(x) = ", L)
        print("y(x) = ", function_v12(1))
        print("delta = ",abs(L - function_v12(1)))
        N =  newton_polynom(1, X, Y)
        print("L(x) = ", N)
        print("y(x) = ", function_v12(1))
        print("delta = ",abs(N - function_v12(1)))
    
if __name__ == "__main__":
    main()