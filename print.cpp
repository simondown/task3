#include"head.h"

void print(int res,int size, int p, double* M){

    if(p == 1){

        for (int i=0; i<res; i++){

            for(int j=0; j<res; j++){

                printf(" %10.3e", M[i*size + j]);

            }

            printf("\n");
        }

    }

    if(p==2){

        for(int i=0; i<res; i++)
            printf(" %10.3e", M[i]);

    }
    printf("\n\n");
}
