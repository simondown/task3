#include"head.h"

/*int main1(int, char**);

int main(int argc, char **argv){


    while(1){


        main1(argc, argv);
    }

}*/

int main (int argc, char **argv){

    int size;
    int res;
    int p;
    int formula;
    double N = 0;
    double P = 0;
    char file[50];
    double t_full;
    //clock_t start, stop;

    if(argc < 5 || argc > 6){

        printf("\nWrong parameters\n\n");
        return 1;

    }

    sscanf(argv[1], "%d", &size);
    printf("\nThe size of the matrix: %d\n\n", size);

    sscanf(argv[2], "%d", &p);
    printf("The number of the threads: %d\n\n", p);

    if(p>size-1) {

        printf("Too many threads\n");

        return 1;

    }



    sscanf(argv[3], "%d", &res);

    if(res > size){

        printf("Wrong parameters\n");

        return 1;

    }

    double* M = 0;

    try {

    M = new double[size*size];

    } catch (std::bad_alloc &e) {

        printf("Can't allocate memory");
        return 2;


    }

    sscanf(argv[4], "%d", &formula);

    if(formula < 0 || formula > 4){

        printf("Wrong formula\n\n");
        delete[] M;

        return 3;
    }


    if(formula != 0){

        printf("You chose formula №%d\n\n", formula);

        input(size, formula, M);
    }

    else{

        if(argc < 6) {

            printf("Please, enter the file\n");
            delete[] M;
            return 4;

        }

        sscanf(argv[5], "%s", file);

        printf("From the file: %s\n\n", file);

        if (text(size, file, M) != 0) {

            printf("Wrong file\n");

            delete[] M;

            return 5;
        }

    }


    printf("The matrix A is:\n");

    print(res, size, 1, M);

    double* V = new double[size];

    vector(size, M, V);

    printf("The vector b is:\n");

    print(res, size, 2, V);


    double* X = new double[size];
    double* Xn = new double[size];
    int* check = new int;

    pthrdata * args = new pthrdata[p];

    pthread_t *thread = new pthread_t[p];

    for(int i=0; i<p; i++){

        args[i].size = size;
        args[i].M = M;
        args[i].V = V;
        args[i].X = X;
        args[i].Xn = Xn;
        args[i].num = i;
        args[i].p = p;
        args[i].check = check;

    }

    t_full = get_full_time();

    for(int i=0; i<p; i++){

        if(pthread_create(thread + i, 0, solution, args + i) != 0){

            printf("%d-thread creation failed\n", i);

            delete[] M;
            delete[] V;
            delete[] Xn;
            delete[] X;
            delete[] args;
            delete[] thread;

            return 7;

        }
    }


    for(int i=0; i<p; i++){


        if (pthread_join(thread[i], 0) != 0) {

            printf("Can't join thread №%d", i);

            delete[] M;
            delete[] V;
            delete[] Xn;
            delete[] X;
            delete[] thread;
            delete[] args;
            delete check;

            return 9;
        }

    }

    check = args[0].check;

    //printf("check is %d\n", *check);

    if (*check == 5){

        printf("Non-zero minors of the matrix are required\n");

        delete[] M;
        delete[] V;
        delete[] Xn;
        delete[] X;
        delete[] thread;
        delete[] args;
        delete check;

        return 8;
    }


    //int_time -= get_full_time();

    //stop = clock();

   t_full = get_full_time() - t_full ;

    if(formula == 0)
        text(size, file, M);

    if(formula != 0)
        input(size, formula, M);

    vector(size, M, V);

    for(int i=0; i<size; i++)
        Xn[i] = 0;

    norma(size, M, V, X, Xn, &N);

    for(int i=0; i<size; i++)
        Xn[i] = 0;

    accuracy(size, X, Xn, &P);

   // printf("Accuracy: %10.3e\n", P);

    if(P > 1){

        printf("Non-zero minors of the matrix are required\n");

        delete[] M;
        delete[] V;
        delete[] Xn;
        delete[] X;
        delete[] thread;
        delete[] args;
        delete check;

        return 8;

    }

    printf("The solution is:\n");

    print(res, size, 2, X);

    printf("Time required: %10.3e\n\n", t_full);

    printf("%s: residual = %e, elapsed = %10.3e, s = %d, n = %d, m = %d, p = %d\n", argv[0], N, t_full, formula, size, res, p);


    printf("Accuracy: %10.3e\n", P);


    delete[] M;
    delete[] V;
    delete[] X;
    delete[] Xn;
    delete[] thread;
    delete[] args;
    delete check;

    return 0;
}
