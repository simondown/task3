#include"head.h"

void* solution(void *args){

    data_t *th = (data_t*)args;

    int size = th->size;
    double* M = th->M;
    double* V = th->V;
    double* X = th->X;
    double* Xn = th->Xn;
    int num = th->num;
    int p = th->p;
    int* check = th->check;;

    //printf("th № %d size =  %d p = %d\n", num, size, p);

    int i = 0;
    int j = 0;
    int k = 0;
    double t;

    double temp1 = 0;
    int temp2 = 0;

    t = get_full_time();

        //printf("thr %d here 1 \n", num);

    if(num==0){

       // printf("thr %d here 2 \n", num);

        if(fabs(M[0]) < eps*1e-10) {

        //    printf("00\n");

            *check = 5;
          //  pthread_exit(&check);
        }



    }

    //printf("thr %d here 3 \n", num);


    synchronize(p);

    if(num==0){

       // printf("thr %d here 4 \n", num);

        X[0] = sign(M[0]);

        M[0] = sqrtf(std::fabs(M[0]));

        for(i=1; i<size; i++){

            M[i*size] = M[i*size]/(M[0]*X[0]);

        }

    }

   // pthread_barrier_wait(&sync);

   // printf("thr %d here 5 \n", num);

    synchronize(p);

    for(i=1; i<size; i++){

        //printf("i = %d\n", i);

        if(num==0){

          //  printf("thr %d here 6 \n", num);

            temp1 = M[i*size + i];

           /*  if(std::fabs(temp1) < eps){

                printf("0\n");

                *check = 5;

                //pthread_exit(NULL);

            }*/

            for(j = 0; j < i; j++){

                temp1 -= M[i*size + j]*M[i*size + j]*X[j];

            }

            if(std::fabs(temp1/M[i*size + i]) < eps*size){

               // printf("1\n");

                *check = 5;

               // pthread_exit(NULL);

            }

            X[i] = sign(temp1);

            M[i*size + i] = sqrtf(fabs(temp1));

            if(std::fabs(M[i*size + i]) < eps*size){

               // printf("2\n");

                *check = 5;


            }

        }

        synchronize(p);

        // printf("M[%d %d] = %10.3e\n", i, i, M[i*size +i]);

        temp1 = 0;

        temp2 = (size-i-1)/p + (int)sign(size-i-1)%p;

       // printf("thr %d says temp 2 = %d\n", num, temp2);

        for(j=i+1+num*temp2; j<fmin(size, i+1+(1+num)*temp2); j++){

            for(k=0; k<i; k++){

                temp1 += M[i*size + k]*M[j*size + k]*X[k];
            }

            M[j*size + i] = ((M[j*size + i] - temp1)/(M[i*size + i]*X[i]));

            temp1 = 0;
        }

       // printf("thr %d here 7 \n", num);

        synchronize(p);

        temp1 = 0;
    }

    if(num==0){

        for(i=0; i<size-1; i++){

            for (j=i+1; j<size; j++){

                M[i*size + j] = 0;

            }
        }

    }

    /*printf("The L-matrix is:\n");

    for(i=0; i<4; i++){

        for (j=0; j<4; j++){

            printf("%10.3e ", M[i*size + j]);

        }

        printf("\n");
    }
    printf("\n");*/


    if(num==0){

        for(i=0; i < size; i++){

            for (j = 0; j<i; j++){

                V[i] -= M[i*size + j]*Xn[j];

            }

            Xn[i] = V[i]/M[i*size + i];
        }



    /*printf("\n\nVector is:\n");

    for(i = 0; i<size; i++)
        printf("%.2f ", Xn[i]);

    printf("\n\n"); */




        for(i=0; i<size; i++){

            for ( j=0; j<size; j++){

                M[i*size + j] = M[j*size + i];
            }
        }



        for(j=0; j<size-1; j++){

            for (i=j+1; i<size; i++){

                M[i*size + j] = 0;

            }
        }



    /*printf("\n\n");
    printf("Trans:\n");

    for(i=0; i<size; i++){

        for (j=0; j<size; j++){

            printf("%.2f ", M[i*size + j]);
        }

        printf("\n");
    }

    printf("\n\n"); */

        for(i=0; i<size; i++)
            Xn[i] *= X[i];


        for(i=0; i<size; i++)
            X[i] = 0;

        for (i = size-1; i>=0; i--){

            for( j = size-1; j>i; j--){

                Xn[i] -= M[i*size + j]*X[j];

            }
            X[i] = Xn[i]/M[i*size + i];
        }

    }

    t = get_full_time() - t;


    return 0;
}

double get_full_time()
{
    struct timeval buf;
    gettimeofday(&buf, 0);
    return (double)buf.tv_sec + (double)buf.tv_usec/1000000.0;
}

int sign(double x){

    if (x > 0.0) return 1;
    if (x < 0.0) return -1;

    return 0;
}



