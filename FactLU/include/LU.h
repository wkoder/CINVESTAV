double *x;
int n = 3;
int a = -1;
int b = 1;
int a1  = 1;
int a2 = 1;
int b1 = 1;
int b2 = 1;
int tam = 0;

double ua = 1;
double ub = 2;

double h;
double alfa;
double beta ;

double functionQ();
double functionT();
double functionT2();
double functionM();

void matrixLU(int tam, double **matA, double **matLRes, double **matURes);
void factorizeUL(int tam, double **matA, double *l, double **v);


double (*funcT)();
double (*funcT2)();
double (*funcQ)();
double (*funcM)();
