#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include "libs/my_lib/laba_lib.h"

double *xfd;
double **yfd;
int n_point, n_graf;

//функция из моего варианта лаба 3_1
double function_v12_1(double x)
{
    return sin(x) + x; 
}

//функция из моего варианта лаба 3_5
double function_v12_5(double x)
{
    return x/(pow(x,3)+8); 
    //return 1/(256-pow(x,4));
}

//произведение разностей для Лагранжа 
double omega_function_Lagrange(double x, int n, double X[])
{
    double res = 1;
    for(int i=0; i<n; i++)
        res*= x-X[i];
    return res;
}

//произведение разностей используется для Ньютона
double omega_function_Newton(double x, int n, double X[])
{
    double res = 1;
    for(int i=0; i<=n; i++)
        res*= x-X[i];
    return res;
}

//производная произведения разностей
double omega_function_derivative(int k, int n, double X[])
{
    double res =1;
    for(int i=0; i<n; i++)
        if(i!=k) res*= X[k]-X[i];
    return res;
}

//вычисляем значения y
void count_y(double(*fun)(double x),double Y[], double X[], int n)
{
    printf("Y: ");
    for(int i = 0; i<n; i++)
    {
        Y[i] = fun(X[i]);
        printf("%lf; ", Y[i]);
    }
}

//посторитель граффиков
void draw_graph(HDC hdc, RECT rectClient) // количество рядов данных (по умолчанию 1)
{
    double MAX_X, MAX_Y;
    double ScaleX, ScaleY;
    double minX, maxX, minY, maxY;
    int height, width;
    int X, Y; // координаты в окне (в px)
    HPEN hpen;
    char buffer[24];
    LPCSTR ti;
    height = rectClient.bottom - rectClient.top;
    width = rectClient.right - rectClient.left;
    minX = xfd[0];
    maxX = xfd[n_point];
    for (int i = 0; i<n_point; i++)
    {
        if (xfd[i] < minX) minX = xfd[i];
        if (xfd[i] > maxX) maxX = xfd[i];
    }
    for (int i = 0; i<n_point; i++)
        xfd[i] = xfd[i]+fabs(minX);
    MAX_X = maxX - minX;
    ScaleX = (double)width / MAX_X; // масштабный коэффициент X
    minY = yfd[1][0];
    maxY = yfd[1][0];
    for (int i = 0; i<n_graf; i++)
        for (int j = 0; j < n_point; j++)
        {
            if (yfd[i][j] < minY) minY = yfd[i][j];
            if (yfd[i][j] > maxY) maxY = yfd[i][j];
        }
    for (int i = 0; i<n_graf; i++)
        for (int j = 0; j < n_point; j++)
            yfd[i][j] = yfd[i][j] + fabs(minY);
    MAX_Y = maxY - minY;
    ScaleY = (double)height / MAX_Y; // масштабный коэффициент Y
    hpen = CreatePen(PS_SOLID, 2, 0); // формирование пера 2px
    SelectObject(hdc, hpen);
    for (int i = 0; i<n_point; i++)
    {
        xfd[i] = xfd[i];
        X = xfd[i] * ScaleX;
        Y = height - (yfd[0][i] * ScaleY);
        MoveToEx(hdc, X, height, 0);
        LineTo(hdc, X, height-10);
        MoveToEx(hdc, 0, Y, 0);
        LineTo(hdc, 10, Y);
        SetTextColor(hdc, 0x00FF0000); // синий цвет букв
        sprintf(buffer, "%f", xfd[i]-fabs(minX));
        ti = (LPCSTR)buffer;
        TextOut(hdc, X-10, height-25, ti, 8);
        sprintf(buffer, "%f", yfd[0][i]-fabs(minY));
        ti = (LPCSTR)buffer;
        TextOut(hdc, 15, Y-9, ti, 8);
    }
    DeleteObject(hpen);
    int color = 0xFF; // красное перо для первого ряда данных
    for (int i = 0; i < n_graf; i++)
    {
        hpen = CreatePen(PS_SOLID, 3, color); // формирование пера 2px
        SelectObject(hdc, hpen);
        X = (int)(xfd[0] * ScaleX); // начальная точка графика
        Y = (int)(height - (yfd[i][0] * ScaleY));
        MoveToEx(hdc, X, Y, 0); // перемещение в начальную точку
        for (int j = 1; j<n_point; j++)
        {
            X = xfd[j] * ScaleX;
            Y = height - (yfd[i][j] * ScaleY);
            LineTo(hdc, X, Y);
        }
        color = color << 8; // изменение цвета пера для следующего ряда
        DeleteObject(hpen); // удаление текущего пера
  }
}

//функция процессинга окна
LONG WINAPI wind_proc(HWND hwnd, UINT massage, WPARAM wparam, LPARAM lparam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    switch (massage)
    {
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        draw_graph(hdc, ps.rcPaint);
        EndPaint(hwnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, massage, wparam, lparam);
  }
  return 0;
}

//готовим окно и его основной цикл
int drow_graf()
{
    HWND hwnd;
    MSG msg;
    WNDCLASS w;
    memset(&w, 0, sizeof(WNDCLASS));
    w.style = CS_HREDRAW | CS_VREDRAW;
    w.lpfnWndProc = wind_proc;
    w.lpszClassName = "My Class";
    RegisterClass(&w);
    hwnd = CreateWindow("My Class", "charts", WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME, 500, 300, 1280, 720, NULL, NULL, NULL, NULL);
    ShowWindow(hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);
    while(GetMessage(&msg, NULL, 0,0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

//строим полином Лагранжа в точке
double lagrange_polinom(double x, int n, double X[], double Y[])
{
    double L = 0;
    printf("L(x) = ");
    for(int i=0; i<n; i++)
    {
        double tmp = Y[i]/omega_function_derivative(i, n, X);
        if(tmp>0 && i>0) printf("+");
        printf("%lf", tmp);
        for(int j=0; j<n; j++)
        {
            if(i!=j)
                X[j]>0 ? printf("(x - %lf)",X[j]):printf("(x + %lf)",-X[j]);
        }
        L += (omega_function_Lagrange(x, n, X) * Y[i])/((x - X[i]) * omega_function_derivative(i, n, X));
    }
    return L;
}

//находим значение коэффицентов полинома Ньютона
double f(int n, int i, int j, double X[], double Y[])
{
    if(n==0) 
        return (Y[i] - Y[j]) / (X[i] - X[j]);
    else 
        return (f(n-1, i, j-1, X, Y) - f(n-1, i+1, j, X, Y)) / (X[i] - X[j]);
}

//строим полином Ньютона в точке
double newton_polynom(double(*fun)(double x), double x, int n, double X[], double Y[])
{
    double N = fun(X[0]) + (x- X[0])*f(0, 1, 0, X, Y);
    printf("\nN(x) = %lf + %lf(x - %lf )", fun(X[0]), f(0, 1, 0, X, Y), X[0]);
    for(int i=1; i<n-1; i++)
    {
        double tmp = f(i, 0, i+1, X, Y);
        printf(" + %lf", tmp);
        for(int j=0; j<=i; j++)
            printf("(x - %lf)", X[j]);
        N += omega_function_Newton(x, i, X)*tmp;
    }
    return N;
}

//сокрашения записи формул
double h(int i, double x[])
{
    return(x[i]-x[i-1]);
}

//решаем систему уравнений и получаем коэффиценты для сплайна
void get_c_value(double x[], double y[], int n, double t[])
{
    t[0] = 0;
    matrix A = create_matrix(n-2,n-2);
    matrix B = create_matrix(1, n-2);
    *get_element(&A, 0,0) = 2*(h(1, x)+h(2, x));
    *get_element(&A, 0,1) = h(2, x);
    *get_element(&B, 0,0) = 3*(((y[2] - y[1]) / h(2, x)) - ((y[1] - y[0]) / h(1, x)));
    int j=0;
    for(int i=3; i<n-1; i++)
    {
        *get_element(&A, i-2,j) = h(i-1,x);
        *get_element(&A, i-2,j+1) = 2*(h(i-1, x)+h(i, x));
        *get_element(&A, i-2,j+2) = h(i,x);
        *get_element(&B, 0,i-2) = 3*(((y[i] - y[i-1]) / h(i, x)) - ((y[i-1] - y[i-2]) / h(i-1, x)));
        j++;
    }
    *get_element(&A, n-3,j) = h(n-2, x);
    *get_element(&A, n-3,j+1) = 2*(h(n-2, x)+h(n-1, x));
    *get_element(&B, 0,n-3) = 3*(((y[n-1] - y[n-2]) / h(n-1, x)) - ((y[n-2] - y[n-3]) / h(n-2, x)));
    matrix X = run_method(A, B, n-2);
    for (int j=0; j<n-2; j++)
        t[j+1] = X.body[j];
    destroy_matrix(&A); destroy_matrix(&B); destroy_matrix(&X);
}

//найдем остальные коэффиценты
void get_a_b_d(int n, double a[], double b[], double d[], double x[], double y[], double c[])
{
    for(int i=1; i<n; i++)
    {
        a[i-1] =  y[i-1];
        b[i-1] = ((y[i] - y[i-1])/h(i,x)) - ((h(i,x)*(c[i] + 2*c[i-1]))/3);
        d[i-1] = (c[i] - c[i-1]) / (3*h(i,x));
    }
    a[n-1] = y[n-1];
    b[n-1] = ( ((y[n] - y[n-1]) / h(n-1,x)) - 2*h(n-1,x)*c[n-1]/3 );
    d[n-1] = (-c[n-1]/(3*h(n-1, x)));
}

//формируем сплайн
double get_spline(int n, double X, double a[], double b[], double c[], double d[], double x[])
{
    int j;
    double k;
    for(k=x[0], j=0; k<=x[n-1]; j++, k++)
    {
        if ((k<=X)&&(k>=X-1)) break;
    }
    for(int i=0; i<n-1;i++)
    {
        printf("\nSpline: %lf + %lf(x - %lf) + %lf(x - %lf)^2 + %lf(x - %lf)^3", a[i], b[i], x[i], c[i], x[i], d[i], x[i]);
        if (i==j)
            printf(" #");
    }
    double t = X-x[j];
    return a[j] + b[j]*t + c[j]*t*t + d[j]*t*t*t;
}

//рассчитаем коэффиценты полинома
void find_a_vector(int n, int N, double x[], double y[], double A[])
{
    double tmp_x, tmp_y;
    matrix a, b;
    a = create_matrix(n,n); b = create_matrix(1,n);
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            tmp_x = 0;
            tmp_y = 0;
            for(int k=0; k<N; k++)
            {
                tmp_x += pow(x[k], i+j);
                tmp_y += y[k]*pow(x[k], i);
            }
            *get_element(&a,i,j) = tmp_x;
            printf("a%d*%lf + ", j, tmp_x);
        }
        printf("\b\b= %lf\n", tmp_y);
        *get_element(&b,0,i) = tmp_y;
    }
    matrix tmp = LU_method(a, b, n);
    for(int i=0; i<n; i++)
        A[i] = tmp.body[i];
    printf("\nF(x) = %lf",A[0]);
    for(int i=1; i<n; i++)
        if(A[i]>0)
            printf(" + %lfx^%d",A[i], i);
        else
            printf(" - %lfx^%d",-A[i], i);
    destroy_matrix(&a); destroy_matrix(&b); destroy_matrix(&tmp);
}

//определим значение полинома в точке
double get_value(double A[], double x, int n)
{
    double tmp=0;
    for(int i=0; i<n; i++)
        tmp+=A[i]*pow(x, i);
    return tmp;
}

//первая производная
double first_derivative(int i, double x[], double y[])
{
    return (y[i+1] - y[i]) / (x[i+1] - x[i]);
}

//вторая производная
double second_derivative(int i, double x[], double y[])
{
    double a = (y[i+2] - y[i+1]) / (x[i+2] - x[i+1]);
    double b = (y[i+1] - y[i]) / (x[i+1] - x[i]);
    double c = x[i+2] - x[i];
    return 2 * (a - b) /c;
}

//метод прямоугольников
double rectangle_method(double(*func)(double x), double h, double x[], int n)
{
    double sum=0;
    for(int i=1; i<n; i++)
        sum += func((x[i]+x[i-1])/2);
    return h*sum;
}

//метод трапеций
double trapeze_method(double(*func)(double x), double h, double x[], int n)
{
    double sum = (func(x[0]) + func(x[n-1])) / 2;
    for(int i=1; i<n-1; i++)
    {
        sum += func(x[i]);
    }
    return h*sum;
}

//метод Симпсона
double sympson_method(double(*func)(double x), double h, double x[], int n)
{
    double sum = func(x[0]) + func(x[n-1]);
    for(int i=1; i<n-1; i++)
    {
        if(i%2==0) 
            sum += 2*func(x[i]);
        else 
            sum += 4*func(x[i]);
    }
    return h*sum/3;
}

//метод... их короче
double runge_romberg_method(double Fh, double Fkh, double p)
{
    return Fh + ((Fh - Fkh) / (pow(2,p) - 1));
}

void Lagrange_and_Newton_polynomial()
{
    int n; 
    double x, L, N;
    printf("\n\nLagrange polynomial\n");
    printf("\nenter quantity of x: ");
    scanf("%d",&n);
    double *X = malloc(n*sizeof(double)); double *Y = malloc(n*sizeof(double));
    printf("\nenter X: ");
    for(int i = 0; i<n; i++)
        scanf("%lf", &X[i]);
    count_y(function_v12_1, Y, X, n);
    printf("\nenter x of point: ");
    scanf("%lf",&x);
    L = lagrange_polinom(x, n, X, Y);
    printf("\nL(x) = %lf", L);
    printf("\ny(x) = %lf", function_v12_1(x));
    printf("\ndelta = %lf\n",fabs(L - function_v12_1(x)));

    printf("\nNewton polynomial\n");
    N = newton_polynom(function_v12_1, x, n, X, Y);
    printf("\nN(x) = %lf", N);
    printf("\ny(x) = %lf", function_v12_1(x));
    printf("\ndelta = %lf",fabs(N - function_v12_1(x)));
    free(X); free(Y);
}

void cubic_spline()
{
    int n;
    printf("specify the number of records: ");
    scanf("%d", &n);
    double **table  = malloc(2*sizeof(double*));
    printf("enter values from table: \n");
    for(int i=0; i<2; i++)
    {
        table[i] = malloc(n*sizeof(double));
        for (int j=0; j<n; j++)
            scanf("%lf", &table[i][j]);
    }
    double *c =  malloc(n*sizeof(double));
    double *a = malloc(n*sizeof(double));
    double *b = malloc(n*sizeof(double));
    double *d = malloc(n*sizeof(double));
    get_c_value(table[0], table[1], n, c);
    get_a_b_d(n-1,a,b,d,table[0], table[1], c);
    double X;
    printf("enter the point at which you want to find the value: ");
    scanf("%lf", &X);
    double r = get_spline(n, X, a, b, c, d, table[0]);
    printf("\nf(x) = %lf ", r);
    free(table); free(a); free(b); free(c);free(d);
}

void approximating_polynomials()
{
    int n, N;
    printf("specify the number of records: ");
    scanf("%d", &n);
    double **table  = malloc(2*sizeof(double*));
    double *A = malloc(5*sizeof(double));
    printf("enter values from table: \n");
    for(int i=0; i<2; i++)
    {
        table[i] = malloc(n*sizeof(double));
        for (int j=0; j<n; j++)
            scanf("%lf", &table[i][j]);
    }
    printf("enter the degree of the polynomial: ");
    scanf("%d", &N);
    N++;
    find_a_vector(N, n, table[0], table[1], A);
    double tmp = 0;
    double tmp1=0;
    printf("\n");
    for(int i=0; i<n; i++)
    {
        tmp1  = get_value(A, table[0][i], N);
        tmp += pow((table[1][i]-tmp1),2);
        printf("%lf ", tmp1);
    }
    printf("\n(y-F)^2 = %lf", tmp);
    n_point = n; n_graf = 2;
    xfd = malloc(n_point*sizeof(double));
    yfd = malloc(n_graf*sizeof(double*));
    for(int i=0; i<n_graf; i++)
        yfd[i] = malloc(n_point*sizeof(double));
    yfd[0] = table[1];
    for(int i=0; i<n; i++)
        yfd[1][i] = get_value(A, table[0][i], N);
    xfd = table[0];
    drow_graf();
    free(table); free(A); free(xfd); free(yfd);
}

void rectangle_trapeze_sympson_rrm()
{
    int n;
    double k0, k1;
    printf("\nenter the number of steps to consider: ");
    scanf("%d", &n);
    printf("\nindicate the limits of integration: ");
    scanf("%lf %lf", &k0, &k1);
    double *h = malloc(n*sizeof(double));
    double *rectangle = malloc(n*sizeof(double));
    double *trapeze = malloc(n*sizeof(double));
    double *sympson = malloc(n*sizeof(double));
    double **rrm = malloc((n-1)*sizeof(double));
    printf("\nindicate step sizes: ");
    for(int i=0; i<n; i++)
        scanf("%lf", &h[i]);
    for(int i=0; i<n; i++)
    {
        int N = (int)((k1-k0)/h[i]+1);
        double *x = malloc(N*sizeof(double));
        x[0] = k0;
        for(int j = 1; j<N; j++)
            x[j] = x[j-1] + h[i];
        rectangle[i] = rectangle_method(function_v12_5, h[i], x, N);
        trapeze[i] = trapeze_method(function_v12_5, h[i], x, N);
        sympson[i] = sympson_method(function_v12_5, h[i], x, N);
        printf("\nh = %lf: rectangle = %lf; trapeze = %lf; sympson = %lf",h[i], rectangle[i], trapeze[i], sympson[i]);
    }
    printf("\n");
    for(int i=1; i<n; i++)
    {
        rrm[i-1] = malloc(3*sizeof(double));
        rrm[i-1][0] = runge_romberg_method(rectangle[i], rectangle[i-1], 2);
        rrm[i-1][1] = runge_romberg_method(trapeze[i], trapeze[i-1], 2);
        rrm[i-1][2] = runge_romberg_method(sympson[i], sympson[i-1], 4);
        printf("\nrefined rectangle = %lf; refined trapeze = %lf; refined sympson = %lf; betwe h%d=%lf and h%d=%lf", rrm[i-1][0], rrm[i-1][1], rrm[i-1][2], i-1, h[i-1], i, h[i]);
        printf("\nerror: rectangle = %lf; trapeze = %lf;  sympson = %lf;\n", fabs(rectangle[i] - rrm[i-1][0]), fabs(trapeze[i] - rrm[i-1][1]), fabs(sympson[i] - rrm[i-1][2]));
    }
    free(h); free(rectangle); free(trapeze); free(sympson); free(rrm);
}

void derivatives()
{
    int n, i;
    double x0;
    printf("specify the number of records: ");
    scanf("%d", &n);
    double **table  = malloc(2*sizeof(double*));
    printf("enter values from table: \n");
    for(int i=0; i<2; i++)
    {
        table[i] = malloc(n*sizeof(double));
        for (int j=0; j<n; j++)
            scanf("%lf", &table[i][j]);
    }
    printf("specify point of derivative: ");
    scanf("%lf", &x0);
    for(i=0; i<n; i++) 
        if ((table[0][i]<=x0) && (x0 <=table[0][i+1])) 
            break;
    printf("\ny' = %lf", first_derivative(i, table[0], table[1]));
    printf("\ny'' = %lf", second_derivative(i, table[0], table[1]));
    free(table);
}

int menu() //меню программы
{
	{
		int sw = 0;
		while (sw < 1 || sw > 6)
		{
			printf("\n 1. Lagrange and Newton polynomial method \n 2. cubic spline \n 3. approximating polynomials of the first and second degrees \n 4. calculate the first and second derivatives \n 5. calculate the definite integral \n 6. end work \n choos action : ");
			scanf("%d", &sw);
			if (sw < 1 || sw>6) printf("\n this action dosn'n exist \n");
		}
		return (sw);
	}
}

int main()
{
    int act = 42;
    while (act != 6)
		switch (act)
		{
		case 1: Lagrange_and_Newton_polynomial(); act = 42; break;
		case 2: cubic_spline(); act = 42; break;
		case 3: approximating_polynomials(); act = 42; break;
		case 4: derivatives(); act = 42; break;
		case 5: rectangle_trapeze_sympson_rrm(); act = 42; break;
        case 6: exit(1); break;
		default: act = menu(); break;
		}
}