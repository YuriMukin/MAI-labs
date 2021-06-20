__kernel void matrix_mult(__global double* matA, __global double* matB, __global int* row_column, __global double* result) 
{
    int i = get_global_id(0);
    int j = get_global_id(1);
    for(int k = 0; k < row_column[2]; k++)
        result[i*row_column[3]+j] += matA[i*row_column[1]+k] * matB[k*row_column[3]+j];
}

__kernel void matrix_transpose(__global double* matA, __global double* matB, __global int* row_column, __global double* result) 
{
    int i = get_global_id(0);
    int j = get_global_id(1);
    result[j*row_column[0]+i] = matA[i*row_column[0]+j];
}

__kernel void matrix_getA(__global double* matA, __global double* matB, __global int* row_column, __global double* result) 
{
    int i = get_global_id(0);
    int j = get_global_id(1);
    double ab=0, bb=0;
    for(int k = 0; k < row_column[0]; k++)
    {
        ab+=matA[k]*matB[k*row_column[0]+i];
        bb+=matB[k*row_column[0]+i]*matB[k*row_column[0]+i];
    }
    result[i] = ab/bb;
}

__kernel void matrix_getB(__global double* matA, __global double* matB, __global int* row_column, __global double* result) 
{
    int i = get_global_id(0);
    int j = get_global_id(1);
    for(int k = 0; k < row_column[0]; k++)
        result[i] -= matA[i*row_column[1]+k]*matB[k];
}