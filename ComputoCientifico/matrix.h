#define EPS 1e-9

void createMatrix(double ***mat, int n, int m);
void createVector(double **vector, int n);
void destroyMatrix(double ***mat, int n, int m);
void destroyVector(double **vector, int n);

int isSymmetricMatrix(double **a, int n);
void escaleByMatrix(int m, int n, double escale, double **mat, double **matRes);
void addMatrix(int m, int n, double **mat, double **mat2, double **matRes);
void multiplicationMatrix(int m, int n, double **mat1, double **mat2, double **matRes);
void diagonalMatrix(int n, double(*f)(), double **matRes);
int isUpperTriangular(int n, double **mat);
void triDiagonalMatrix(int n, double(*f)(), double(*f2)(), double(*f3)(), double **matRes);
void transposedMatrix(int m, int n, double **matrix, double **matRes);
double determinantMatrix(double **a, int n);
void cofactorMatrix(int n, double **matrix, double **matRes);
void AdjointMatrix(int n, double **matrix, double **matRes);
void inverseMatrix(int n, double **matrix, double **matRes);
void inverseRMatrix(int n, double **matrix, double **matRes);
void unitMatrix(int n, double **mat);
int isDiagonal(int n, double **mat);
int isCeroDiagonalInf(double **UL, int tam);
void copyMatrix(int m, int n, double **mat, double **matRes);
void printMatrix(int m, int n, double **mat);
void multiplyMatrix(int m, int n, int o, double **mat1, double **mat2, double **matRes);
void multiplyMatrixVector(int m, int n, double **mat, double *v, double *vres);

void escaleByVector(int tam, double escale, double *vector, double *vectorRes);
void projection(int tam, double *vector1, double *vector2, double *vectorRes);
double norm(int tam, double *vector);
void vectoru(int tam, int tammatrix, double **matrixe, double *vectora, double *vectorRes);
void restVector(int tam, double *vector1, double *vector2, double *vectorRes);
void vectore(int tam, double *vectoru, double *vectorRes);
void printVector(int tam, double *vector);