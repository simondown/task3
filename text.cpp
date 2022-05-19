#include"head.h"

int  text(int size, char* file, double* M ){

    int amount=0;

    FILE *f = fopen(file, "r");

    if(f==NULL){

        return 1;

    }
    for (int i = 0; !feof(f) && !ferror(f) && i!= size; i++){

        for (int j = 0; !feof(f) && !ferror(f) && j!=size; j++){

            if (!fscanf(f, "%lf", &M[i*size + j])){
            return 2;
            }

            if(!feof(f)){
                amount++;
            }
        }
    }

    fclose(f);

    if (amount < (size*size) ) {

        printf("Add %d more numbers\n", (size*size - amount));
        return 3;
    }

    return 0;

}
