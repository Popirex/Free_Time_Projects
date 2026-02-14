#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
int fibonacci(int n){

    uint64_t t1, t2;

    t1 = 0;

    t2 = 1;

    if( n <= 0){
        return 0;
    }
    if(n  == 1){
        printf("%ld\n", t1);
    }
    if( n == 2){
        printf("%ld\n", t1);
        printf("%ld\n", t2);
    }
    if( n > 2){
        uint64_t prossimo = t2;
        printf("%ld\n", t1);
        printf("%ld\n", t2);
        for(int i = 3; i <= n; i++){
           
            prossimo = t2 + t1; 

            printf("%ld\n", prossimo);
            t1 = t2; 
            t2 = prossimo;

        }
    }

    printf("\n");

    return 1;
}

int main(int argc, char** argv)
{

    int n;


    if(argc != 2 ){
    
        printf("Usage: %s <quantità da generare ( int )>\n", argv[0]);
        exit(1);

    }
    else{
        n = atoi(argv[1]);
    }

    
    int risultato;

    risultato = fibonacci(n);

    if( risultato == 0){
        printf("C'è stato un errore con la generazione della sequenza\n");
    }
    else{
        printf("Ecco i primi %d numeri della sequenza di Fibonacci!!\n", n);
    }


    return 0;    
}
