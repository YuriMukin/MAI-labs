#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define PI 3.14159265 

//структура матрицы
typedef struct matrix
{
    int columns, rows;
    double *body;
}matrix;

//создание новой матрицы
matrix create_matrix(int n_row, int n_col)
{
    assert(n_row>0 && n_col>0);
    matrix mat;
    mat.columns = n_col;
    mat.rows = n_row;
    mat.body = calloc(n_col* n_row, sizeof(double));
    return mat;
}

//метод получения элемента матрицы
double* get_element(matrix *mat, int row, int col)
{
    assert(col < (*mat).columns && row < (*mat).rows);
    return &(*mat).body[row*((*mat).columns) + col];
}

matrix invert_sign(matrix mat)
{
    matrix result = create_matrix(mat.rows, mat.columns);
    for(int i=0; i<mat.rows; i++)
        for(int j=0; j<mat.columns; j++)
            *get_element(&result,i,j) = -(*get_element(&mat,i,j));
    return result;
}

//создание новой единичной матрицы
matrix create_singular_matrix(int n)
{
    assert(n>0);
    matrix mat;
    mat.columns = n;
    mat.rows = n;
    mat.body = calloc(n* n, sizeof(double));
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
        {
            if(i==j)
                *get_element(&mat, i, j) = 1;
            else
                *get_element(&mat, i, j) = 0;
        }
    return mat;
}

//получить строку матрицы
matrix get_matrix_line(matrix mat, int i)
{
    assert(mat.rows>i);
    matrix res = create_matrix(1,mat.columns);
    for (int j=0; j<mat.columns; j++)
        *get_element(&res, 0, j) = *get_element(&mat, i, j);
    return res;
}

//транспонируем матрицу
matrix transpose_matrix(matrix mat)
{
    matrix result = create_matrix(mat.columns, mat.rows);
    for(int i=0; i<mat.rows; i++)
        for(int j=0; j<mat.columns; j++)
            *get_element(&result,j,i) = *get_element(&mat,i,j);
    return result;
}

//получить столбец матрицы
matrix get_matrix_column(matrix mat, int i)
{
    assert(mat.columns>i);
    matrix res = create_matrix(mat.rows,1);
    for (int j=0; j<mat.rows; j++)
        *get_element(&res, j, 0) = *get_element(&mat, j, i);
    return res;
}

//заменить строку матрицы
void insert_matrix_line(matrix *matA, matrix matB, int i)
{
    for (int j=0; j<(*matA).columns; j++)
        *get_element(&(*matA), i, j) = *get_element(&matB, 0, j);
}

//заменить столбец матрицы
void insert_matrix_column(matrix *matA, matrix matB, int i)
{
    for (int j=0; j<(*matA).rows; j++)
        *get_element(&(*matA), j, i) = *get_element(&matB, j, 0);
}

//вычислим скалярное произведение 
double scalar_product(matrix matA, matrix matB)
{
    assert(matA.columns == matB.columns && matA.rows == matB.rows);
    double res=0;
    if (matA.columns == 1)
    {
        for (int i=0; i< matA.rows; i++)
            res+= (*get_element(&matA, i, 0))*(*get_element(&matB, i, 0));
    }
    else
    {
        for (int i=0; i< matA.columns; i++)
            res+= (*get_element(&matA, 0, i))*(*get_element(&matB, 0, i));
    }
    return res;
}

//метод для вывода матрицы
void print_matrix(matrix *mat)
{
    for (int i=0; i<(*mat).rows; i++)
    {
        printf("\n");
        for (int j=0; j<(*mat).columns; j++)
            printf("%lf ", *get_element(&(*mat), i, j));
    }
}

//умножение матриц
matrix multiply_matrix(matrix matA, matrix matB)
{
    assert(matA.columns == matB.rows);
    matrix matC = create_matrix(matA.rows, matB.columns);
    for(int i = 0; i < matA.rows; i++)
        for(int j = 0; j < matB.columns; j++)
        {
            *get_element(&matC, i,j) = 0;
            for(int k = 0; k < matB.rows; k++)
                *get_element(&matC, i,j) += *get_element(&matA, i,k) * *get_element(&matB, k,j);
        }
    return matC;
}

//сложение матриц
matrix addition_matrix(matrix matA, matrix matB)
{
    assert(matA.columns == matB.columns && matA.rows == matB.rows);
    matrix matC = create_matrix(matA.rows, matA.columns);
    for(int i = 0; i < matA.rows; i++)
        for(int j = 0; j < matA.columns; j++)
            *get_element(&matC, i,j) = *get_element(&matA, i,j) + *get_element(&matB, i,j);
    return matC;
}

//вычитание матриц
matrix subtraction_matrix(matrix matA, matrix matB)
{
    assert(matA.columns == matB.columns && matA.rows == matB.rows);
    matrix matC = create_matrix(matA.rows, matA.columns);
    for(int i = 0; i < matA.rows; i++)
        for(int j = 0; j < matA.columns; j++)
            *get_element(&matC, i,j) = *get_element(&matA, i,j) - *get_element(&matB, i,j);
    return matC;
}

//считаем норму
double get_norm(matrix matA, matrix matB)
{
    assert(matA.columns == matB.columns && matA.rows == matB.rows);
    double tmp = 0;
    for(int i = 0; i < matA.rows; i++)
        for(int j = 0; j < matA.columns; j++)
            tmp += pow((*get_element(&matA, i,j) - *get_element(&matB, i,j)),2);
    return sqrt(tmp);
}

//разбиваем матрицу на L и U составляющие 
void get_LU(matrix *matA, matrix *matL, matrix *matU)
{
    for (int i=0; i<(*matA).columns; i++)
        for (int j=0; j<(*matA).columns; j++)
        {
            if(i==0)
            {
                *get_element(&(*matU), 0, j) = *get_element(&(*matA), 0, j);
                *get_element(&(*matL), j, 0) = *get_element(&(*matA), j, 0)/ *get_element(&(*matU), 0, 0);
            }
            else
            {
                double tmp = 0;
                for(int k=0; k<i; k++)
                    tmp+=((*get_element(&(*matL), i, k))*(*get_element(&(*matU), k, j)));
                if (i<=j)
                    *get_element(&(*matU), i, j) = *get_element(&(*matA), i, j) - tmp;
                if(i>j)
                    *get_element(&(*matL), j, i) = 0;
                else
                {
                    tmp = 0;
                    for(int k=0; k<i; k++)
                        tmp+=((*get_element(&(*matL), j, k))*(*get_element(&(*matU), k, i)));
                    *get_element(&(*matL), j, i) = (*get_element(&(*matA), j, i)-tmp)/(*get_element(&(*matU), i, i));
                }
            }
        }
}

//разбиваем матрицу на L и U составляющие с выбором главного элемента
int get_LU_with_main_element(matrix *matA, matrix *matL, matrix *matU, int P[])
{
    int n = (*matA).columns; int p=0;
    int t;
    matrix tmp1, tmp2;
    matrix C = create_matrix(n,n);
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            *get_element(&C, i, j) = (*get_element(&(*matA), i, j));
    for( int i = 0; i < n; i++ ) 
    {
        double pivotValue = 0;
        int pivot = -1;
        for( int row = i; row < n; row++ ) 
        {
            if( fabs((*get_element(&C, row, i))) > pivotValue ) 
            {
                pivotValue = fabs((*get_element(&C, row, i)));
                pivot = row;
            }
        }
        if( pivotValue != 0 ) 
        {
            p++;
            tmp1 = get_matrix_line(C, i);
            tmp2 = get_matrix_line(C, pivot);
            insert_matrix_line(&C, tmp1, pivot);
            insert_matrix_line(&C, tmp2, i);
            t = P[i]; P[i] = P[pivot]; P[pivot] = t;
            for( int j = i+1; j < n; j++ ) 
            {
                *get_element(&C, j, i) /= (*get_element(&C, i, i));
                for( int k = i+1; k < n; k++ ) 
                    *get_element(&C, j, k) -= (*get_element(&C, j, i)) * (*get_element(&C, i, k));
            }
        }
    }
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
        {
            if(i<j)
                *get_element(&(*matU), i, j) = *get_element(&C, i, j);
            if(i==j)
            {
                *get_element(&(*matU), i, j) = *get_element(&C, i, j);
                *get_element(&(*matL), i, j) = 1;
            }  
            if(i>j)
                *get_element(&(*matL), i, j) = *get_element(&C, i, j);
        }
    return p;
}
//решаем уравнением 
matrix solve_by_LU(matrix matL, matrix matU, matrix b)
{
    int n = matL.columns;
    //решаем Lz = b
    matrix z = create_matrix(1,n);
    *get_element(&z, 0, 0) = *get_element(&b, 0, 0);
    for(int i=1; i<n; i++)
	{
        double tmp = 0;
        for(int j=0; j<i; j++)
            tmp += (*get_element(&matL, i, j)) * (*get_element(&z, 0, j));
        *get_element(&z, 0, i) = *get_element(&b, 0, i) - tmp;
    }
    matrix x = create_matrix(1,n);
    //решаем Ux = z
    *get_element(&x, 0, n-1) = *get_element(&z, 0, n-1) / *get_element(&matU, n-1, n-1);
    for(int i=n-2; i>=0; i--)
	{
        double tmp = 0;
        for(int j=i+1; j<n;j++) 
            tmp += (*get_element(&matU, i, j)) * (*get_element(&x, 0, j));
        *get_element(&x, 0, i) = (*get_element(&z, 0, i) - tmp)/(*get_element(&matU, i, i));
    }
    return x;
}

//выделяем диагонали 
void get_ABC(matrix mat, matrix *A, matrix *B, matrix *C)
{
    int n = mat.columns;
    *get_element(&(*A), 0, 0) = 0;
    *get_element(&(*B), 0, 0) = *get_element(&mat, 0, 0);
    *get_element(&(*C), 0, 0) = *get_element(&mat, 0, 1);
    for(int i=1; i<n-1; i++)
    {
        *get_element(&(*A), 0, i) = *get_element(&mat, i, i-1);
        *get_element(&(*B), 0, i) = *get_element(&mat, i, i);
        *get_element(&(*C), 0, i) = *get_element(&mat, i, i+1);
    }
    *get_element(&(*A), 0, n-1) = *get_element(&mat, n-1, n-2);
    *get_element(&(*B), 0, n-1) = *get_element(&mat, n-1, n-1);
    *get_element(&(*C), 0, n-1) = 0;
}

//рассчитываем пограничные коэффициенты 
void get_PQ(matrix A, matrix B, matrix C, matrix D, matrix *P, matrix *Q)
{
    int n = A.columns;
    *get_element(&(*P), 0, 0) = -( *get_element(&C, 0, 0))/(*get_element(&B, 0, 0));
    *get_element(&(*Q), 0, 0) = ( *get_element(&D, 0, 0))/(*get_element(&B, 0, 0));
    for(int i=1; i<n-1; i++)
    {
        *get_element(&(*P), 0, i) = -( *get_element(&C, 0, i))/((*get_element(&B, 0, i))+(*get_element(&A, 0, i))*(*get_element(&(*P), 0, i-1)));
        *get_element(&(*Q), 0, i) = ((*get_element(&D, 0, i))-(*get_element(&A, 0, i)*(*get_element(&(*Q), 0, i-1))))/((*get_element(&B, 0, i))+(*get_element(&A, 0, i)*(*get_element(&(*P), 0, i-1))));
    }
    *get_element(&(*P), 0, n-1) = 0;
    *get_element(&(*Q), 0, n-1) = ((*get_element(&D, 0, n-1))-(*get_element(&A, 0, n-1)*(*get_element(&(*Q), 0, n-2))))/((*get_element(&B, 0, n-1))+(*get_element(&A, 0, n-1)*(*get_element(&(*P), 0, n-2))));
}

//вычисляем корни 
matrix solve_by_run(matrix P, matrix Q)
{
    int n = P.columns;
    matrix x = create_matrix(1,n);
    *get_element(&x, 0, n-1) = *get_element(&Q, 0, n-1);
    for(int i=2; i<=n; i++)
        *get_element(&x, 0, n-i) = (*get_element(&P, 0, n-i)) * (*get_element(&x, 0, n-i+1)) + *get_element(&Q, 0, n-i);
    return x;
}

//вычисляем вектор бетта и матрицу альфа
void get_alpha_betta(matrix matA, matrix B, matrix *alpha, matrix *betta)
{
    int n = matA.columns;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
        {
            *get_element(&(*betta), i, 0) = *get_element(&B, i, 0) /(*get_element(&matA, i, i));
            if(i != j)
                *get_element(&(*alpha), i, j) = -(*get_element(&matA, i, j))/(*get_element(&matA, i, i));
            else
                *get_element(&(*alpha), i, j) = 0;
        }
}

//разделяем матрицу на верхнюю и нижнюю диагональные
void get_CB(matrix alpha, matrix *B, matrix *C)
{
    int n = alpha.columns;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
        {
            if(i < j)
            {
                *get_element(&(*B), i, j) = *get_element(&alpha, i, j);
                *get_element(&(*C), i, j) = 0;
            }
            else
            {
                *get_element(&(*B), i, j) = 0;
                *get_element(&(*C), i, j) = *get_element(&alpha, i, j);
            }
        }
}

//найдем обратную матрицу
matrix get_inverse_matrix(matrix L, matrix U, int P[])
{
    int n = L.columns;
    matrix res = create_matrix(n,n);
    matrix res1 = create_matrix(n,n);
    matrix E = create_singular_matrix(n);
    for(int i=0; i<n; i++)
    {
        matrix y = solve_by_LU(L, E, get_matrix_line(E,i));
        matrix x = solve_by_LU(E, U, y);
        for(int j=0; j<n; j++)
            *get_element(&res, j, i) = *get_element(&x, 0, j);
    }
    //res = transpose_matrix(res);
    for(int i=0; i<n; i++)
        insert_matrix_column(&res1, get_matrix_column(res,i), P[i]);
    return res1;//PAA^-1=E
}

//найдем определитьель матрицы
double get_det(matrix matU, int p)
{
    double det = 1;
    for (int i=0;i<matU.columns; i++)
        det *= (*get_element(&matU, i, i));
    return pow(-1,p)*det;
}

//вычесляем х методом простых итераций 
matrix solve_by_iterative_method(matrix alpha, matrix betta, double epsilon)
{
    matrix x = betta;
    matrix pre_x;
    double epsilon_i;
    int k = 0;
    do
    {
        pre_x = x;
        x =  addition_matrix(betta, multiply_matrix(alpha, pre_x));
        epsilon_i = get_norm(pre_x, x);
        k++;
    }
    while (epsilon_i > epsilon && k<100);
    printf("\n%d iterations have been done",k);
    return x;
}

//вычесляем х методом Зейделя
matrix solve_by_Seidel(matrix alpha, matrix betta, double epsilon)
{
    int n = alpha.rows;
    matrix x = create_matrix(n, 1); matrix B = create_matrix(n, n); matrix C = create_matrix(n, n);
    matrix pre_x = create_matrix(n, 1);
    for(int i=0; i<n; i++)
            *get_element(&x, i, 0) = *get_element(&betta, i, 0);
    double epsilon_i, tmp;
    int k = 0;
    do
    {
        for(int i=0; i<n; i++)
            *get_element(&pre_x, i, 0) = *get_element(&x, i, 0);
        for(int i=0; i<n; i++)
        {
            tmp = 0;
            for(int j=0; j<n; j++)
                tmp += *get_element(&alpha, i, j) *(*get_element(&x, j, 0));
            *get_element(&x, i, 0) = *get_element(&betta, i, 0) + tmp;
        }
        epsilon_i = get_norm(pre_x, x);
        k++;
    }
    while (epsilon_i > epsilon && k<40);
    printf("\n%d iterations have been done",k);
    return x;
}

//найдем максимальный элемент матрицы
void get_max(matrix matA, int a[])
{
    a[0] = 0; a[1] = 1;
    int n =  matA.columns;
    double max = abs(*get_element(&matA, a[0], a[1]));
    for (int i=0; i<n; i++)
        for(int j=i+1; j<n; j++)
        {
            if(max<abs(*get_element(&matA, i, j)))
                {
                    a[0] = i;
                    a[1] = j;
                    max = abs(*get_element(&matA, i, j));
                }
        }
}

//найдем угол поворота
double get_angle(matrix matA, int i, int j)
{
    if ((*get_element(&matA, i, i))==(*get_element(&matA, j, j)))
        return PI / 4;
    else
        return 0.5 * atan(2*(*get_element(&matA, i, j))/((*get_element(&matA, i, i))-(*get_element(&matA, j, j))));
}

//корень из суммы квадратов внедиаганальных элементов 
double get_square_summ(matrix matA)
{
    int n = matA.columns;
    double sum = 0;
    for(int i=1; i<n; i++)
            for(int j=0; j<i; j++)
                sum+=(*get_element(&matA, i, j))*(*get_element(&matA, i, j));
    return sqrt(sum);
}

//вращаем матрицу
matrix jakobi_method(matrix matA, double epsilon, matrix *lambda)
{
    int n = matA.columns;
    int a[2] = {0,0};
    matrix X = create_singular_matrix(n);
    double p;
    int iter=0;
    double angle;
    do
    {
        get_max(matA, a);
        int i = a[0]; int j = a[1];
        angle = get_angle(matA, i, j);
        matrix matU = create_singular_matrix(n);
        *get_element(&matU, i, i) = cos(angle);
        *get_element(&matU, i, j) = -sin(angle);
        *get_element(&matU, j, i) = sin(angle);
        *get_element(&matU, j, j) = cos(angle);
        X = multiply_matrix(X,matU);

        matrix tmp = create_matrix(n,n);
        for(int i1=0; i1<n; i1++)
            for(int j1=0; j1<n; j1++)
                *get_element(&tmp, i1, j1) = *get_element(&matU, i1, j1);
        *get_element(&tmp, i, j) = sin(angle);
        *get_element(&tmp, j, i) = -sin(angle);

        matrix tmp1 =  multiply_matrix(tmp, matA);
        matA = multiply_matrix(tmp1, matU);
        
        p= get_square_summ(matA);
        //printf("\n%lf", p);
        iter++;
    } while (epsilon < p && angle != 0 && iter < 100);
    
    for (int k=0; k<n; k++)
        *get_element(&(*lambda), k, 0) = *get_element(&matA, k, k);
    printf("\n%d iterations have been done", iter);
    return X;
}

//разложим матрицу на Q и R
void get_QR(matrix matA, matrix *matQ, matrix *matR)
{
    int n = matA.columns;
    double ab, bb, norm;
    matrix c, a, b, e;
    a = create_matrix(n,1);
    b = create_matrix(n,n);
    e = create_matrix(n,1);
    c = create_matrix(n-1,1);
    for (int i=0; i<n; i++)
    {
        if (i==0)
        {
            insert_matrix_column(&b,get_matrix_column(matA, i),i);
            norm = scalar_product(get_matrix_column(b, i),get_matrix_column(b, i));
            for(int j =0;j<n; j++)
                *get_element(&e, j, 0) = (*get_element(&b, j, 0))/sqrt(norm);
        }
        else
        {
            a = get_matrix_column(matA, i);
            for(int l=0; l<i; l++)
            {
                ab = scalar_product(a,get_matrix_column(b, l));
                bb = scalar_product(get_matrix_column(b, l),get_matrix_column(b, l));
                *get_element(&c, l, 0) = ab/bb;
            }
            printf("\n");
            for(int k=0; k<i;k++)
                for(int j =0;j<n; j++)
                    *get_element(&a, j, 0) -= (*get_element(&b, j, k))*(*get_element(&c, k, 0));
            insert_matrix_column(&b,a,i);
            norm = scalar_product(a,a);
            for(int j =0;j<n; j++)
                *get_element(&e, j, 0) = (*get_element(&b, j, i))/sqrt(norm);
        }
        insert_matrix_column(&(*matQ),e, i);
    }
    (*matR) = multiply_matrix(transpose_matrix(*matQ), matA);
}

//подсчитаем сумму значений под диаганалью
double square_sum_column(matrix mat, int column_number, int first_index)
{
    int n = mat.columns;
    double sum =0;
    for(int i=first_index; i<n;i++) 
        sum+= (*get_element(&mat,i, column_number)) * (*get_element(&mat,i, column_number));
    return sqrt(sum);
}

//проверим критерий окончания
int is_end(matrix mat, double eps)
{
    int n = mat.columns; int z;
    double sum1, sum2;
    for(int j=0; j<n;j++)
    {
        sum1 = square_sum_column(mat, j, j+1);
        sum2 = square_sum_column(mat, j, j+2);
        if(sum2 > eps)
            return 0;
        else if(sum1 <= eps)
        {
            printf("\nlambda%d: %lf",j ,*get_element(&mat,j, j));
        }
        else if(sum1 > eps)
        {
            double aii = *get_element(&mat, j, j);
            double ajj = *get_element(&mat, j+1, j+1);
            double aij = *get_element(&mat, j, j+1);
            double aji = *get_element(&mat, j+1, j);
            double x = (aii + ajj) / 2;
            double D = (-(aii+ajj)*(aii+ajj) + 4*(aii*ajj - aij*aji));
            if (D<0)
                return 0;
            double y = sqrt(D) / 2;
            printf("\nlambda%d: %lf + %lfi", j, x, y);
            printf("\nlambda%d: %lf - %lfi", j+1, x, y);
            j++;
        }
    }
    return 1;
}

void LU_method()
{
    matrix matA, matL, matU, B;
    int n, perm;
    printf("enter the dimension of the matrix: ");
    scanf("%d", &n);
    int *P = malloc(n*sizeof(int));
    printf("enter the matrix in one line: ");
    matA = create_matrix(n,n); matL = create_matrix(n,n); matU = create_matrix(n,n); B = create_matrix(1,n);
    for (int i=0; i<matA.columns; i++)
    {
        P[i] = i;
        for (int j=0; j<matA.columns; j++)
            scanf("%lf", &*get_element(&matA, i, j));
    }
    perm = get_LU_with_main_element(&matA, &matL, &matU, P);
    printf("\n%s \n%d %d %d %d ", "P", P[0], P[1], P[2], P[3]);
    printf("\n%s ", "U");
    print_matrix(&matU);
    printf("\n%s ", "L");
    print_matrix(&matL);
    matrix matR = get_inverse_matrix(matL, matU, P);
    /*matrix tmp = multiply_matrix(matA, matR);
    print_matrix(&tmp);*/
    printf("\n%s ", "inverse matrix");
    print_matrix(&matR);
    printf("\n%s %lf", "determinant of matrix A", get_det(matU, perm));
    printf("\nenter vector B: ");
    for (int i=0; i<B.rows; i++)
        for (int j=0; j<B.columns; j++)
            scanf("%lf", &*get_element(&B, i, P[j]));
    matrix x = solve_by_LU(matL, matU, B);
    printf("\nX: ");
    print_matrix(&x);
}

void run_method()
{
    matrix mat, A, B, C, P, Q, D;
    int n;
    printf("enter the dimension of the matrix: ");
    scanf("%d", &n);
    printf("enter the matrix in one line: ");
    mat = create_matrix(n,n); A = create_matrix(1,n); B = create_matrix(1,n); C = create_matrix(1,n); D = create_matrix(1,n); P = create_matrix(1,n); Q = create_matrix(1,n);
    for (int i=0; i<mat.columns; i++)
        for (int j=0; j<mat.columns; j++)
            scanf("%lf", &*get_element(&mat, i, j));
    get_ABC(mat, &A, &B, &C);
    printf("\n%s ", "A");
    print_matrix(&A);
    printf("\n%s ", "B");
    print_matrix(&B);
    printf("\n%s ", "C");
    print_matrix(&C);
    printf("\nenter vector D: ");
    for (int i=0; i<D.rows; i++)
        for (int j=0; j<D.columns; j++)
            scanf("%lf", &*get_element(&D, i, j));
    get_PQ(A,B,C,D,&P,&Q);
    printf("\n%s ", "P");
    print_matrix(&P);
    printf("\n%s ", "Q");
    print_matrix(&Q);
    matrix x = solve_by_run(P,Q);
    printf("\n%s ", "X");
    print_matrix(&x);
}

void Seidel_iterative_methods()
{
    matrix matA, B, alpha, betta;
    double eps;
    int n;
    printf("enter the dimension of the matrix: ");
    scanf("%d", &n);
    printf("enter the matrix in one line: ");
    matA = create_matrix(n,n); alpha = create_matrix(n,n); B = create_matrix(n,1); betta = create_matrix(n,1);
    for (int i=0; i<matA.columns; i++)
        for (int j=0; j<matA.columns; j++)
            scanf("%lf", &*get_element(&matA, i, j));
    printf("\nenter vector B: ");
    for (int i=0; i<B.rows; i++)
        for (int j=0; j<B.columns; j++)
            scanf("%lf", &*get_element(&B, i, j));
    get_alpha_betta(matA, B, &alpha, &betta);
    printf("\n%s ", "alpha");
    print_matrix(&alpha);
    printf("\n%s ", "betta");
    print_matrix(&betta);
    printf("\nenter precision: ");
    scanf("%lf", &eps);
    matrix x1 = solve_by_iterative_method(alpha, betta, eps);
    printf("\n%s ", "X iterative method");
    print_matrix(&x1);
    matrix x2 = solve_by_Seidel(alpha, betta, eps);
    printf("\n%s ", "X Seidel");
    print_matrix(&x2);
}

void rotation_method()
{
    matrix matA, lambda;
    int n; double eps = 0.001;
    printf("enter the dimension of the matrix: ");
    scanf("%d", &n);
    printf("enter the matrix in one line: ");
    matA = create_matrix(n,n); lambda = create_matrix(n,1);
    for (int i=0; i<matA.columns; i++)
        for (int j=0; j<matA.columns; j++)
            scanf("%lf", &*get_element(&matA, i, j));
    printf("enter the desired precision: ");
    scanf("%lf", &eps);
    matrix X = jakobi_method(matA, eps, &lambda);
    printf("\n%s ", "X");
    print_matrix(&X);
    printf("\n%s ", "lambda");
    print_matrix(&lambda);
}

void GR_method()
{
    matrix matA, matR, matQ;
    int n, k;
    double eps;
    k=0;
    printf("enter the dimension of the matrix: ");
    scanf("%d", &n);
    printf("enter the matrix in one line: ");
    matA = create_matrix(n,n); matR = create_matrix(n,n); matQ = create_matrix(n,n);
    for (int i=0; i<matA.columns; i++)
        for (int j=0; j<matA.columns; j++)
            scanf("%lf", &*get_element(&matA, i, j));
    printf("enter the desired precision: ");
    scanf("%lf", &eps);
    while(is_end(matA, eps)==0 && k<200)
    {
        get_QR(matA, &matQ, &matR);
        matA = multiply_matrix(matR, matQ);
        printf("\nA%d:",k);
        print_matrix(&matA);
        k++;
    }
}

int menu() //меню программы
{
	{
		int sw = 0;
		while (sw < 1 || sw > 6)
		{
			printf("\n 1. LU method \n 2. run method \n 3. Seidel and iterative methods \n 4. rotation method \n 5. QR algorithm \n 6. end work \n choos action : ");
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
		case 1: LU_method(); act = 42; break;
		case 2: run_method(); act = 42; break;
		case 3: Seidel_iterative_methods();act = 42; break;
		case 4: rotation_method(); act = 42; break;
		case 5: GR_method();act = 42; break;
        case 6: exit(1); break;
		default: act = menu(); break;
		}
}