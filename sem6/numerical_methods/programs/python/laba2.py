import numpy as np

#Выраженная функция
def fi_func_v12(x):
    return np.log(5*pow(x,2)-1)/np.log(3)

#Исходня функция
def f_func_v12(x):
    return pow(3,x)-5*pow(x,2)+1

#Производня исходной функции
def f_derivative_v12(x):
    return pow(3,x)*np.log(3)-10*x

def fi_system_v12(x):
    return [3 + np.cos(x[1]), 3 + np.sin(x[0])]

#Исходная система уравнений
def f_system_v12(x):
    return [x[0]-np.cos(x[1])-3, x[1]-np.sin(x[0])-3]

#Производная исходной системы по х1
def f_system_dx1_v12(x):
    return [1, -np.cos(x[0])]

#Производная исходной системы по х2
def f_system_dx2_v12(x):
    return [np.sin(x[1]), 1]


#Метод простых итераций
def simple_iterations(fi_func, x0, epsilon, q):
    x = x0
    k=0
    cont = True
    while (cont):
        print("k={} x={} fi_func(x)={}".format(k, x, fi_func(x)))
        prev_x = x
        x = fi_func(x)
        k=k+1
        if ((q/(1-q)) * np.absolute(x - prev_x) < epsilon or k>1000):
            cont = False
    return x;

#Метод Ньютона
def newton_mathod(f_func, f_derivative, x0, epsilon):
    x = x0
    k=0
    cont = True
    while(cont):
        print("k={} x={} f_func(x)={} f_derivative(x)={} f_func(x)/f_derivative(x)={}".format(k, x, f_func(x), f_derivative(x), f_func(x)/f_derivative(x)))
        prev_x = x
        x -= f_func(x)/f_derivative(x)
        k=k+1
        if ( np.absolute(x-prev_x) <= epsilon or k>500):
            cont = False
    return x

#Метод итераций для системы 
def simple_iterations_fs(fi, x0, epsilon, q):
    k = 0
    cont = True
    while(cont):
        print("x1={} x2={} f1(x1,x2)={} f2(x1,x2)={}".format(x0[0],x0[1], fi(x0)[0], fi(x0)[1]))
        prevu_x = x0.copy()
        x0 = fi(x0)
        k=k+1
        if (np.sqrt(pow(x0[0]-prevu_x[0],2)+pow(x0[1]-prevu_x[1],2))<epsilon or k>150):
            cont = False
    print("{} iterations have been done".format(k));
    return x0

#Метод Ньютона для системы
def newton_method_fs(f, fdx1, fdx2, x0, epsilon):
    k = 0
    cont = True
    while(cont):
        prevu_x = x0.copy()
        fm = f(prevu_x)
        fdx1m = fdx1(prevu_x)
        fdx2m = fdx2(prevu_x)
        print("x1={} x2={} f1(x1,x2)={} f2(x1,x2)={} f1dx1(x1,x2)={} f1dx2(x1,x2)={} f2dx1(x1,x2)={} f2dx2(x1,x2)={}".format(x0[0], x0[1], fm[0], fm[1], fdx1m[0], fdx2m[0], fdx1m[1], fdx2m[1]))
        x0[0] -= (fm[0]*fdx2m[1]-fm[1]*fdx2m[0])/(fdx1m[0]*fdx2m[1]-fdx1m[1]*fdx2m[0])
        x0[1] -= (fm[1]*fdx1m[0]-fdx1m[1]*fm[0])/(fdx1m[0]*fdx2m[1]-fdx1m[1]*fdx2m[0])
        k=k+1
        if(np.sqrt(pow(x0[0]-prevu_x[0],2)+pow(x0[1]-prevu_x[1],2))<epsilon or k>150):
            cont = False
    print("{} iterations have been done".format(k));
    return x0



def main():
    eps = float(input("\nenter precision: "))
    print("\nequations\n")
    print("solution obtained by simple iteration method\nx={}\n".format(simple_iterations(fi_func_v12, 3, eps, 0.826)))
    print("solution obtained by Newton method\nx={}".format(newton_mathod(f_func_v12, f_derivative_v12, 5, eps)))
    print("\nsystems of equations\n")
    res = simple_iterations_fs(fi_system_v12, [np.pi, 2], eps, 0.9)
    print("solution obtained by simple iteration method\nx1={} x2={}\n".format(res[0], res[1]))
    res = newton_method_fs(f_system_v12, f_system_dx1_v12, f_system_dx2_v12, [4, 2.3464], eps)
    print("solution obtained by Newton method\nx1={} x2={}".format(res[0], res[1]))
    
    
if __name__ == "__main__":
    main()

    
    
    
    
    
    
    
    
    
    
    
    
    