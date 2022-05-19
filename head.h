#include<new>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<time.h>
#include<math.h>
#include<sys/time.h>
#define eps 1e-15


 double function(int, int, int, int );

 void input(int, int, double*);

 int text(int, char* , double* );

 void vector(int, double* , double* );

 void* solution(void* );

 int sign (double);

 void accuracy( int, double* , double* , double* );

 void norma(int, double* , double* , double* , double* , double*);

 void print(int, int, int, double*);

 void synchronize(int );

 double get_full_time();

 typedef struct pthrdata {

        int size;
        double *M;
        double *V;
        double *X;
        double *Xn;
        int num;
        int p;
        int *check;

    } data_t;

 //static  pthread_barrier_t sync;
