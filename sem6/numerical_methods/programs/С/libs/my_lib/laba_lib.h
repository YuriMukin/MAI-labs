typedef struct matrix
{
    int columns, rows;
    double *body;
}matrix;

matrix create_matrix(int n_row, int n_col);
double* get_element(matrix *mat, int row, int col);
matrix invert_sign(matrix mat);
matrix create_singular_matrix(int n);
matrix get_matrix_line(matrix mat, int i);
matrix transpose_matrix(matrix mat);
matrix get_matrix_column(matrix mat, int i);
void insert_matrix_line(matrix *matA, matrix matB, int i);
void insert_matrix_column(matrix *matA, matrix matB, int i);
double scalar_product(matrix matA, matrix matB);
void print_matrix(matrix *mat);
matrix multiply_matrix(matrix matA, matrix matB);
matrix addition_matrix(matrix matA, matrix matB);
matrix subtraction_matrix(matrix matA, matrix matB);
matrix run_method(matrix mat, matrix D, int n);
void destroy_matrix(matrix *mat);
matrix LU_method(matrix matA, matrix B, int n);