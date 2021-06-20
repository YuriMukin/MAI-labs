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

void destroy_matrix(matrix *mat)
{
    free(mat->body);
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

//умножить матрицу на число
matrix multiply_matrix_by_number(matrix *mat, double A)
{
    for(int i = 0; i < mat->rows; i++)
        for(int j = 0; j < mat->columns; j++)
            *get_element(&(*mat), i,j)*=A;
}

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

//разбиваем матрицу на L и U составляющие с выбором главного элемента
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
    destroy_matrix(&z);
    return x;
}

matrix run_method(matrix mat, matrix D, int n)
{
    matrix A, B, C, P, Q;
    A = create_matrix(1,n); B = create_matrix(1,n); C = create_matrix(1,n); P = create_matrix(1,n); Q = create_matrix(1,n);
    get_ABC(mat, &A, &B, &C);
    get_PQ(A,B,C,D,&P,&Q);
    matrix x = solve_by_run(P,Q);
    destroy_matrix(&A); destroy_matrix(&B); destroy_matrix(&C); destroy_matrix(&P); destroy_matrix(&Q);
    return x;
}

matrix LU_method(matrix matA, matrix B, int n)
{
    matrix matL, matU, x;
    matL = create_matrix(n,n); matU = create_matrix(n,n);
    get_LU(&matA, &matL, &matU);
    x = solve_by_LU(matL, matU, B);
    destroy_matrix(&matL); destroy_matrix(&matU);
    return x;
}