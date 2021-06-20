#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#include <math.h>
#ifdef __APPLE__
#include <OpenCL/cl.h>
#else
#include "lib/CL/cl.h"
#endif

#define PROGRAM_FILE "QR.cl"
#define KERNEL_FUNC "QR_decompos"

cl_kernel matrix_mult, matrix_transpose, matrix_getA, matrix_getB;
cl_command_queue queue;
cl_context context;
cl_int err;
int is_chaing;

const char *getErrorString(cl_int error)
{
switch(error){
    // run-time and JIT compiler errors
    case 0: return "CL_SUCCESS";
    case -1: return "CL_DEVICE_NOT_FOUND";
    case -2: return "CL_DEVICE_NOT_AVAILABLE";
    case -3: return "CL_COMPILER_NOT_AVAILABLE";
    case -4: return "CL_MEM_OBJECT_ALLOCATION_FAILURE";
    case -5: return "CL_OUT_OF_RESOURCES";
    case -6: return "CL_OUT_OF_HOST_MEMORY";
    case -7: return "CL_PROFILING_INFO_NOT_AVAILABLE";
    case -8: return "CL_MEM_COPY_OVERLAP";
    case -9: return "CL_IMAGE_FORMAT_MISMATCH";
    case -10: return "CL_IMAGE_FORMAT_NOT_SUPPORTED";
    case -11: return "CL_BUILD_PROGRAM_FAILURE";
    case -12: return "CL_MAP_FAILURE";
    case -13: return "CL_MISALIGNED_SUB_BUFFER_OFFSET";
    case -14: return "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST";
    case -15: return "CL_COMPILE_PROGRAM_FAILURE";
    case -16: return "CL_LINKER_NOT_AVAILABLE";
    case -17: return "CL_LINK_PROGRAM_FAILURE";
    case -18: return "CL_DEVICE_PARTITION_FAILED";
    case -19: return "CL_KERNEL_ARG_INFO_NOT_AVAILABLE";

    // compile-time errors
    case -30: return "CL_INVALID_VALUE";
    case -31: return "CL_INVALID_DEVICE_TYPE";
    case -32: return "CL_INVALID_PLATFORM";
    case -33: return "CL_INVALID_DEVICE";
    case -34: return "CL_INVALID_CONTEXT";
    case -35: return "CL_INVALID_QUEUE_PROPERTIES";
    case -36: return "CL_INVALID_COMMAND_QUEUE";
    case -37: return "CL_INVALID_HOST_PTR";
    case -38: return "CL_INVALID_MEM_OBJECT";
    case -39: return "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
    case -40: return "CL_INVALID_IMAGE_SIZE";
    case -41: return "CL_INVALID_SAMPLER";
    case -42: return "CL_INVALID_BINARY";
    case -43: return "CL_INVALID_BUILD_OPTIONS";
    case -44: return "CL_INVALID_PROGRAM";
    case -45: return "CL_INVALID_PROGRAM_EXECUTABLE";
    case -46: return "CL_INVALID_KERNEL_NAME";
    case -47: return "CL_INVALID_KERNEL_DEFINITION";
    case -48: return "CL_INVALID_KERNEL";
    case -49: return "CL_INVALID_ARG_INDEX";
    case -50: return "CL_INVALID_ARG_VALUE";
    case -51: return "CL_INVALID_ARG_SIZE";
    case -52: return "CL_INVALID_KERNEL_ARGS";
    case -53: return "CL_INVALID_WORK_DIMENSION";
    case -54: return "CL_INVALID_WORK_GROUP_SIZE";
    case -55: return "CL_INVALID_WORK_ITEM_SIZE";
    case -56: return "CL_INVALID_GLOBAL_OFFSET";
    case -57: return "CL_INVALID_EVENT_WAIT_LIST";
    case -58: return "CL_INVALID_EVENT";
    case -59: return "CL_INVALID_OPERATION";
    case -60: return "CL_INVALID_GL_OBJECT";
    case -61: return "CL_INVALID_BUFFER_SIZE";
    case -62: return "CL_INVALID_MIP_LEVEL";
    case -63: return "CL_INVALID_GLOBAL_WORK_SIZE";
    case -64: return "CL_INVALID_PROPERTY";
    case -65: return "CL_INVALID_IMAGE_DESCRIPTOR";
    case -66: return "CL_INVALID_COMPILER_OPTIONS";
    case -67: return "CL_INVALID_LINKER_OPTIONS";
    case -68: return "CL_INVALID_DEVICE_PARTITION_COUNT";

    // extension errors
    case -1000: return "CL_INVALID_GL_SHAREGROUP_REFERENCE_KHR";
    case -1001: return "CL_PLATFORM_NOT_FOUND_KHR";
    case -1002: return "CL_INVALID_D3D10_DEVICE_KHR";
    case -1003: return "CL_INVALID_D3D10_RESOURCE_KHR";
    case -1004: return "CL_D3D10_RESOURCE_ALREADY_ACQUIRED_KHR";
    case -1005: return "CL_D3D10_RESOURCE_NOT_ACQUIRED_KHR";
    default: return "Unknown OpenCL error";
    }
}

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

matrix get_matrix_column(matrix mat, int i)
{
    assert(mat.columns>i);
    matrix res = create_matrix(mat.rows,1);
    for (int j=0; j<mat.rows; j++)
        *get_element(&res, j, 0) = *get_element(&mat, j, i);
    return res;
}

void insert_matrix_column(matrix *matA, matrix matB, int i)
{
    for (int j=0; j<(*matA).rows; j++)
        *get_element(&(*matA), j, i) = *get_element(&matB, j, 0);
}

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

matrix multiply_matrix_GPU(matrix matA, matrix matB)
{
    assert(matA.columns == matB.rows);
    matrix matC = create_matrix(matA.rows, matB.columns);
    cl_mem matA_buff, matB_buff, cr_buff, res_buff;
    int *cr = malloc(4*sizeof(int));
    cr[0] = matA.rows; cr[1] = matA.columns; cr[2] = matB.rows; cr[3] = matB.columns;
    matA_buff = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(double)*cr[0]*cr[1], matA.body, &err); 
    matB_buff = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(double)*cr[2]*cr[3], matB.body, &err); 
    cr_buff = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(int)*4, cr, &err); 
    res_buff = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(double)*cr[0]*cr[3], NULL, &err); 
    clSetKernelArg(matrix_mult, 0, sizeof(cl_mem), &matA_buff); //линкуем буферы с аргументами фунции ядра
    clSetKernelArg(matrix_mult, 1, sizeof(cl_mem), &matB_buff);
    clSetKernelArg(matrix_mult, 2, sizeof(cl_mem), &cr_buff);
    clSetKernelArg(matrix_mult, 3, sizeof(cl_mem), &res_buff);
    size_t *dimG = malloc(2*sizeof(size_t));
    dimG[0]=matA.rows; dimG[1]=matB.columns;
    clEnqueueNDRangeKernel(queue, matrix_mult, 2, NULL, dimG, NULL, 0, NULL, NULL); //запускаем ядро
    clEnqueueReadBuffer(queue, res_buff, CL_TRUE, 0,sizeof(double)*cr[0]*cr[3], matC.body, 0, NULL, NULL); //значение из буфера переписываем в понятный си вид
    free(cr); free(dimG); clReleaseMemObject(matA_buff); clReleaseMemObject(matB_buff); clReleaseMemObject(cr_buff);
    return matC;
}

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

matrix transpose_matrix_GPU(matrix mat)
{
    matrix result = create_matrix(mat.columns, mat.rows);
    cl_mem matA_buff, matB_buff, cr_buff, res_buff;
    int *cr = malloc(1*sizeof(int));
    cr[0] = mat.columns;
    matA_buff = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(double)*cr[0]*cr[0], mat.body, &err); 
    matB_buff = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(double), NULL, &err); 
    cr_buff = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(int), cr, &err); 
    res_buff = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(double)*cr[0]*cr[3], NULL, &err); 
    clSetKernelArg(matrix_transpose, 0, sizeof(cl_mem), &matA_buff); //линкуем буферы с аргументами фунции ядра
    clSetKernelArg(matrix_transpose, 1, sizeof(cl_mem), &matB_buff);
    clSetKernelArg(matrix_transpose, 2, sizeof(cl_mem), &cr_buff);
    clSetKernelArg(matrix_transpose, 3, sizeof(cl_mem), &res_buff);
    size_t *dimG = malloc(2*sizeof(size_t));
    dimG[0]=mat.rows; dimG[1]=mat.columns;
    clEnqueueNDRangeKernel(queue, matrix_transpose, 2, NULL, dimG, NULL, 0, NULL, NULL); //запускаем ядро
    clEnqueueReadBuffer(queue, res_buff, CL_TRUE, 0,sizeof(double)*cr[0]*cr[0], result.body, 0, NULL, NULL); //значение из буфера переписываем в понятный си вид
    free(cr); free(dimG); clReleaseMemObject(matA_buff); clReleaseMemObject(matB_buff); clReleaseMemObject(cr_buff);
    return result;
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

void prepare_GPU_code()
{
    cl_platform_id platform;
    cl_device_id device;
    clGetPlatformIDs(1, &platform, NULL); //находим все устройства в системе
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1,&device, NULL); //находим первое устройство
    context = clCreateContext(NULL, 1, &device, NULL, NULL, &err); //выбираем устройство для выполнения кода
    FILE *program_handle = fopen("matvec.cl", "r"); //открываем программу выполняемую на GPU
    fseek(program_handle, 0, SEEK_END);
    size_t program_size = ftell(program_handle);
    rewind(program_handle);
    char *program_buffer = (char*)malloc(program_size + 1);
    program_buffer[program_size] = '\0'; //создаем буфер для программы
    fread(program_buffer, sizeof(char), program_size, program_handle); //записываем в него программу
    fclose(program_handle); //закрываем файл
    cl_program program = clCreateProgramWithSource(context, 1,(const char**)&program_buffer, &program_size, &err); //создаем программу
    free(program_buffer); //чистим буфер
    clBuildProgram(program, 0, NULL, NULL, NULL, NULL); //компилируем 
    matrix_mult = clCreateKernel(program, "matrix_mult", &err); //создаем указатель на функцию
    printf("%s\n", getErrorString(err));
    matrix_transpose = clCreateKernel(program, "matrix_transpose", &err);
    printf("%s\n", getErrorString(err));
    matrix_getA = clCreateKernel(program, "matrix_getA", &err);
    printf("%s\n", getErrorString(err));
    matrix_getB = clCreateKernel(program, "matrix_getB", &err);
    printf("%s\n", getErrorString(err));
    queue = clCreateCommandQueue(context, device, 0, &err);
}

void get_c(matrix a, matrix b, matrix *c, int l)
{
    cl_mem matA_buff, matB_buff, cr_buff, res_buff;
    int *cr = malloc(sizeof(int));
    cr[0] = b.columns;
    matA_buff = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(double)*cr[0], a.body, &err); 
    matB_buff = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(double)*b.rows*b.columns, b.body, &err); 
    cr_buff = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(int), cr, &err); 
    res_buff = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(double)*(*c).rows, NULL, &err); 
    clSetKernelArg(matrix_getA, 0, sizeof(cl_mem), &matA_buff); //линкуем буферы с аргументами фунции ядра
    clSetKernelArg(matrix_getA, 1, sizeof(cl_mem), &matB_buff);
    clSetKernelArg(matrix_getA, 2, sizeof(cl_mem), &cr_buff);
    clSetKernelArg(matrix_getA, 3, sizeof(cl_mem), &res_buff);
    size_t dim=l;
    clEnqueueNDRangeKernel(queue, matrix_getA, 1, NULL, &dim, NULL, 0, NULL, NULL); //запускаем ядро
    clEnqueueReadBuffer(queue, res_buff, CL_TRUE, 0,sizeof(double)*l, c->body, 0, NULL, NULL); //значение из буфера переписываем в понятный си вид
    free(cr); clReleaseMemObject(matA_buff); clReleaseMemObject(matB_buff); clReleaseMemObject(cr_buff);
}

void get_b(matrix *a, matrix b, matrix c, int k)
{
    cl_mem matA_buff, matB_buff, cr_buff, res_buff;
    int *cr = malloc(2*sizeof(int));
    cr[0] = k; cr[1] = b.columns;
    matA_buff = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(double)*b.columns*b.rows, b.body, &err); 
    matB_buff = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(double)*b.columns-1, c.body, &err); 
    cr_buff = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(int)*2, cr, &err); 
    res_buff = clCreateBuffer(context, CL_MEM_WRITE_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(double)*b.columns, a->body, &err); 
    clSetKernelArg(matrix_getB, 0, sizeof(cl_mem), &matA_buff); //линкуем буферы с аргументами фунции ядра
    clSetKernelArg(matrix_getB, 1, sizeof(cl_mem), &matB_buff);
    clSetKernelArg(matrix_getB, 2, sizeof(cl_mem), &cr_buff);
    clSetKernelArg(matrix_getB, 3, sizeof(cl_mem), &res_buff);
    size_t dim=b.columns;
    clEnqueueNDRangeKernel(queue, matrix_getB, 1, NULL, &dim, NULL, 0, NULL, NULL); //запускаем ядро
    clEnqueueReadBuffer(queue, res_buff, CL_TRUE, 0,sizeof(double)*b.columns, a->body, 0, NULL, NULL); //значение из буфера переписываем в понятный си вид
    free(cr); clReleaseMemObject(matA_buff); clReleaseMemObject(matB_buff); clReleaseMemObject(cr_buff);
}

void get_QR_GPU(matrix matA, matrix *matQ, matrix *matR)
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
            get_c(a,b,&c,i);
            get_b(&a,b,c,i);
            insert_matrix_column(&b,a,i);
            norm = scalar_product(a,a);
            for(int j =0;j<n; j++)
                *get_element(&e, j, 0) = (*get_element(&b, j, i))/sqrt(norm);
        }
        insert_matrix_column(&(*matQ),e, i);
    }
    (*matR) = multiply_matrix_GPU(transpose_matrix_GPU(*matQ), matA);
}

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

void get_lambda(double** lambda, matrix mat)
{
    int n = mat.columns;
    for(int j=0; j<n;j++)
        if(j==n-1)
        {
            lambda[j][0] = *get_element(&mat, j, j);
            lambda[j][1] = 0;
        }
        else
        {
            double aii = *get_element(&mat, j, j);
            double ajj = *get_element(&mat, j+1, j+1);
            double aij = *get_element(&mat, j, j+1);
            double aji = *get_element(&mat, j+1, j);
            double x = (aii + ajj) / 2;
            double D = (-(aii+ajj)*(aii+ajj) + 4*(aii*ajj - aij*aji));
            if (D<0)
            {
                lambda[j][0] = *get_element(&mat, j, j);
                lambda[j][1] = 0;
            }
            else
            {
                double y = sqrt(D) / 2;
                lambda[j][0] = x;
                lambda[j][1] = y;
                j++;
                lambda[j][0] = x;
                lambda[j][1] = -y;
            }
        }
}

int is_end_by_lambda(double** lambda_old, double** lambda_new, double eps, int n)
{
    int res = 0;
    for(int i=0; i<n; i++)
        if(fabs(lambda_old[i][0]-lambda_new[i][0])>eps)
            res++;
    return res;
}

void run_on_GPU(matrix mat, double eps, int n)
{
    matrix matR, matQ, matA = mat;
    int k;
    k=0;
    matR = create_matrix(n,n); matQ = create_matrix(n,n);
    double **lambda_old, **lambda_new;
    lambda_old = malloc(n*sizeof(double*));
    lambda_new = malloc(n*sizeof(double*));
    for(int i=0; i<n; i++)
    {
        lambda_old[i] = malloc(2*sizeof(double));
        lambda_new[i] = malloc(2*sizeof(double));
    }
    get_lambda(lambda_new, matA);
    do
    {
        for(int i=0; i<n; i++)
        {
            lambda_old[i][0] = lambda_new[i][0];
            lambda_old[i][1] = lambda_new[i][1];
        }
        get_QR_GPU(matA, &matQ, &matR);
        matA = multiply_matrix_GPU(matR, matQ);
        get_lambda(lambda_new, matA);
        k++;
    } while (is_end_by_lambda(lambda_old, lambda_new, eps, mat.columns)!=0 && k<200);
    printf("\n%d iterations have been done\n", k);
    for(int i=0; i<n; i++)
        printf("\nlambda%d: %lf + %lfi", i, lambda_new[i][0],  lambda_new[i][1]);
}

void run_on_CPU(matrix mat, double eps, int n)
{
    matrix matR, matQ, matA = mat;
    int k;
    k=0;
    matR = create_matrix(n,n); matQ = create_matrix(n,n);
    while(is_end(matA, eps)==0 && k<200)
    {
        get_QR(matA, &matQ, &matR);
        matA = multiply_matrix(matR, matQ);
        printf("\nA%d:",k);
        print_matrix(&matA);
        k++;
    }

}

int main()
{
    prepare_GPU_code();
    matrix matA;
    clock_t tic;
    int n, k;
    double eps;
    float cpu, gpu;
    k=0;
    FILE *fil = fopen("input1.txt", "r");
    printf("enter the dimension of the matrix: ");
    scanf("%d", &n);
    //printf("enter the matrix in one line: ");
    matA = create_matrix(n,n);
    for (int i=0; i<matA.columns; i++)
        for (int j=0; j<matA.columns; j++)
            //scanf("%lf", &*get_element(&matA, i, j));
            fscanf(fil, "%lf", &*get_element(&matA, i, j));
    printf("\nmatrix read successfully\n");
    fclose(fil);
    printf("enter the desired precision: ");
    scanf("%lf", &eps);
    tic = clock();
    run_on_GPU(matA, eps, n);
    gpu = (double)(clock() - tic) / CLOCKS_PER_SEC;
    printf("\ncomputed on GPU by %lf", gpu);
}
//gcc QR_openCl.c -c QR_openCl.c; gcc -o QR_openCl  QR_openCl.o lib/Win32/OpenCL.lib; rm QR_openCl.o