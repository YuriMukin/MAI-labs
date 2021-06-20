#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "libs/my_lib/laba_lib.h"

//функция с заменой
void F_v12_1(double x, double yv[], double res[])
{
    double z = yv[1]; 
    double y = yv[0];
    res[0] = z; 
    res[1] = (2*x*z-2*y) / (pow(x,2)+1);
}

//стартовые значения
void get_start_value_v12_1(double y[])
{
    y[0] = 1; 
    y[1] = 1;
}

//точное значение
double precise_v12_1(double x) 
{ 
    return x - pow(x,2)+1; 
}

//точное значение
double precise_v12_2(double x) 
{ 
    return 2+x+2*x*log(fabs(x)); 
}

//множитель при y
double p_func_v12(double x)
{

    return -1/(x-1);
}

//множетель при производной y
double q_func_v12(double x)
{
    return 1/(x*x-x);
}

//множетель x
double f_func_v12(double x)
{
    return 0;
}

//приращение у в методе Рунге-Кутты
void delta_y(void(*F)(double x, double yv[], double res[]), double x, double y[], double h) 
{
    double *tmp = malloc(2*sizeof(double));
    double *k1 = malloc(2*sizeof(double));
    F(x, y, k1);

    double *k2 = malloc(2*sizeof(double));
    tmp[0] = k1[0]*h*0.5+y[0]; tmp[1] = k1[1]*h*0.5+y[1];
    F(x + h/2, tmp, k2); 

    double *k3 = malloc(2*sizeof(double));
    tmp[0] = k2[0]*h*0.5+y[0]; tmp[1] = k2[1]*h*0.5+y[1];
    F(x + h/2, tmp, k3); 

    double *k4 = malloc(2*sizeof(double));
    tmp[0] = k3[0]*h+y[0]; tmp[1] = k3[1]*h+y[1];
    F(x + h, tmp, k4); 
    y[0] += (k1[0]+k4[0]+k2[0]*2+k3[0]*2)*(h/6); y[1] += (k1[1]+k4[1]+k2[1]*2+k3[1]*2)*(h/6);
    free(tmp); free(k1); free(k2); free(k3); free(k4);
}

//реализация метода Эйлера
void Eiler_method(void(*get_start_value)(double y[]), void(*F)(double x, double yv[], double res[]), double(*precise)(double x), double x0, double b, double h)
{
    int k=0;
    double *y = malloc(2*sizeof(double)); 
    double *res = malloc(2*sizeof(double)); 
    get_start_value(y);
    double y_prec = y[0]; 
    double error = 0;
    printf("\n\n____________Eiler_method______________\n| k |     x    |     y    |   error  |"); 
    for(double x=x0; x<=b; x+=h) 
    {
        printf("\n______________________________________\n|%3d|%10.7lf|%10.7lf|%10.7lf|",k, x, y[0], error);
        k++;
        F(x,y, res);
        y[0] += res[0]*h; y[1] += res[1]*h;
        error = fabs(precise(x) - y[0]);
    }
    free(res); free(y);
}

//реализация метода Рунге-Кутты
double Runge_Kut_method(void(*get_start_value)(double y[]), void(*F)(double x, double yv[], double res[]), double(*precise)(double x), double x0, double b, double h)
{
	int k=0;
	double *y = malloc(2*sizeof(double)); 
    get_start_value(y);
	double error = 0;
    printf("\n\n_________Runge_Kut_method_____________\n| k |     x    |     y    |   error  |"); 
	for(double x=x0; x<=b; x+=h) 
	{ 
        error = fabs(precise(x) - y[0]);
		printf("\n______________________________________\n|%3d|%10.7lf|%10.7lf|%10.7lf|",k, x, y[0], error);
		k++; 
		delta_y(F, x, y, h);
	} 
    error = y[0];
    free(y);
    return error;
}

//реализация метода Адамса
void Adams_method(void(*get_start_value)(double y[]), void(*F)(double x, double yv[], double res[]), double(*precise)(double x), double x0, double b, double h)
{
    double **f = malloc(((int)((b-x0)/h))*sizeof(double*));
	int k=0;
	double *y = malloc(2*sizeof(double)); 
    double *a1 = malloc(2*sizeof(double));
    double *a2 = malloc(2*sizeof(double));
    double *a3 = malloc(2*sizeof(double));
    double *a4 = malloc(2*sizeof(double));
    get_start_value(y);
    double error = 0;
    double x; 
	printf("\n\n____________Adams_method______________\n| k |     x    |     y    |   error  |"); 
	for(x=x0; k<4; x+=h) 
	{ 
        error = fabs(precise(x) - y[0]);
		printf("\n______________________________________\n|%3d|%10.7lf|%10.7lf|%10.7lf|",k, x, y[0], error);
        f[k] = malloc(2*sizeof(double));
		F(x,y, f[k]);
        y[0] += f[k][0]*h; y[1] += f[k][1]*h;
        k++;
	}
	for(; x<=b; x+=h) 
	{ 
		error = fabs(precise(x) - y[0]);
		printf("\n______________________________________\n|%3d|%10.7lf|%10.7lf|%10.7lf|",k, x, y[0], error);
		f[k] = malloc(2*sizeof(double));
		F(x,y, f[k]);
		a1[0] = f[k][0]*55; a1[1] = f[k][1]*55; 
		a2[0] = f[k-1][0]*(-59); a2[1] = f[k-1][1]*(-59); 
		a3[0] = f[k-2][0]*37; a3[1] = f[k-2][1]*37;
		a4[0] = f[k-3][0]*(-9); a4[1] = f[k-3][1]*(-9);
		k++; 
        y[0] += (a1[0]+a2[0]+a3[0]+a4[0])*(h/24); y[1] += (a1[1]+a2[1]+a3[1]+a4[1])*(h/24);
	}
    free(f); free(y); free(a1); free(a2); free(a3); free(a4);
}

//находим решение задачи коши призаданом начальном значении производной 
double f(double x, double y, double z)
{
    return z;
}

double g(double x, double y, double z)
{
    if((x*x-x)==0) return 3;
    return (x*z-y)/(x*x-x);
}

double shoot(double ksi, double coef[], int N, double ya, double yb, double h, double x[], double y[], double z[])
{
    y[0] = ksi;
    z[0] = (ya-coef[0]*ksi)/coef[1];
    for(int i=0; i<=N; i++)
    {
        y[i+1] = y[i] +h*f(x[i], y[i], z[i]);
        z[i+1] = z[i] +h*g(x[i], y[i], z[i]);
    }
return coef[2]*z[N-1] + coef[3]*y[N-1]-yb;
}

//метод стельбы 
void shoot_method(double coef[], double a, double b, double h, double eps)
{
    int N = (int)((b-a)/h) + 1;
    double ya = 3, yb = -4;
    double *x = malloc(N*sizeof(double));
    double *y = malloc(N*sizeof(double));
    double *z = malloc(N*sizeof(double));
    for(int i=0; i<=N; i++) 
        x[i] = a+h*i;
    double teta0 = 2, teta1 =3;
    double teta = teta1 - ((teta1 - teta0)*shoot(teta1, coef, N, ya, yb, h, x, y, z) / (shoot(teta1, coef, N, ya, yb, h, x, y, z) - shoot(teta0, coef, N, ya, yb, h, x, y, z)));
    while(fabs(shoot(teta, coef, N, ya, yb, h, x, y, z)) >= eps)
    {
        teta0 = teta1;
        teta1=teta;
        teta = teta1 - ((teta1 - teta0)*shoot(teta1, coef, N, ya, yb, h, x, y, z) / (shoot(teta1, coef, N, ya, yb, h, x, y, z) - shoot(teta0, coef, N, ya, yb, h, x, y, z)));
    }
    shoot(teta, coef, N, ya, yb, h, x, y, z);
    printf("\n\n__________shoot_methods__________\n|     x    |     y    |y  precise|");
    for(int i=0; i<=N; i++) 
        printf("\n_________________________________\n|%10.7lf|%10.7lf|%10.7lf|",x[i], y[i], precise_v12_2(x[i]));
    free(x); free(y); free(z);
}

//метод конечных разностей
double finite_differences(double(*value)(double x), double(*p)(double x), double(*q)(double x), double(*f)(double x), double yb[], double a, double b, double h)/*yb[] - массив с 2 коэффицентами: 1 - множител при производной в выражении для точки, 2 - чему равно выражение в точке*/
{
    matrix A, B;
    double x = a+h;
    int N = (int)(fabs(b-a)/h);
    A = create_matrix(N+1,N+1); B = create_matrix(1,N+1);
    *get_element(&A, 0, 0) = -2 + h*h*q(x); *get_element(&A, 0, 1) = 1+p(x)*h/2; *get_element(&B, 0, 0) = h*h*f(x) - (1-p(x)*h/2)*value(a);
    x+=h;
    for(int i=1; i<N; i++, x+=h)
    {
        *get_element(&A, i, i-1) = 1-p(x)*h/2;
        *get_element(&A, i, i) = -2 + h*h*q(x);
        *get_element(&A, i, i+1) = 1+p(x)*h/2;
        *get_element(&B, 0, i) = h*h*f(x);
    }
    *get_element(&A, N, N-1) = -yb[0]; *get_element(&A, N, N) = yb[0]+h; *get_element(&B, 0, N) = yb[1]*h;
    matrix X = run_method(A, B, N+1);
    x=a+h;
    printf("\n\n________finite_differences________\n|     x    |     y    |y  precise|");
    for(int i=0; i<=N; i++)
    {
        printf("\n_________________________________\n|%10.7lf|%10.7lf|%10.7lf|", x, X.body[i], precise_v12_2(x));
        x+=h;
    }
}

void task_4_1()
{
    double start, end, step;
    printf("specify line boundaries and step size: ");
    scanf("%lf%lf%lf", &start, &end, &step);
    Eiler_method(get_start_value_v12_1, F_v12_1, precise_v12_1, start, end, step);
    Runge_Kut_method(get_start_value_v12_1, F_v12_1, precise_v12_1, start, end, step);
    Adams_method(get_start_value_v12_1, F_v12_1, precise_v12_1, start, end, step);
    //0 1 0.1
}

void task_4_2()
{
    double start, end, step, eps;
    double *y = malloc(2*sizeof(double));
    y[0] = -3; y[1] = -4;
    printf("specify line boundaries and step size: ");
    scanf("%lf%lf%lf", &start, &end, &step);
    printf("enter the desired precision: ");
    scanf("%lf", &eps);
    double *coef = malloc(4*sizeof(double));
    coef[0] = 0; coef[1] = 1; coef[2] = -3; coef[3] = 1;
    finite_differences(precise_v12_2, p_func_v12, q_func_v12, f_func_v12, y, start, end, step);
    shoot_method(coef, start, end, step, eps);
    free(y); free(coef);
    //1 3 0.1 0.1
}

int menu() //меню программы
{
	{
		int sw = 0;
		while (sw < 1 || sw > 6)
		{
			printf("\n 1. solve the Cauchy problem for the ODE of the 2nd order on the specified segment \n 2. solve a boundary value problem for an ordinary differential 2nd order equations \n 3. end work \n choos action : ");
			scanf("%d", &sw);
			if (sw < 1 || sw>3) printf("\n this action dosn'n exist \n");
		}
		return (sw);
	}
}

int main()
{
    int act = 43;
    while (act != 3)
		switch (act)
		{
		case 1: task_4_1(); act = 42; break;
		case 2: task_4_2(); act = 42; break;
		case 3: exit(1); break;
		default: act = menu(); break;
		}
}
//cd "c:\Users\Sorjo\Desktop\books & doc\sem6\numerical methods\" ; if ($?) {  gcc -c laba_4.c; gcc -o laba_4  laba_4.o  libs/my_lib/laba_lib.a; rm laba_4.o } ; if ($?) { .\laba_4 } 