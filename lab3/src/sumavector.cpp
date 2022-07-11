/* Programa secuencial que calcula la suma de los elementos de un vector v[i] 
 * y la almacena en la variable sum */ 

#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#define N 50 // Probar distintos tamaños de vector 

void main() 
{ 
    int sum = 0; 
    int v[N];    

    // Damos valores aleatorios al vector (entre 0 y 99) 
    srand (time(NULL)); // Semilla de números aleatorios 
    for (i = 0; i < N; i++) v[i] = rand()%100; 

    // Cálculo del sumatorio 
    for (i = 0; i < N; i++) sum += v[i];           

    // Como comprobación, se visualizan los valores del vector y la suma 
    printf("\nVector de números: \n "); 
    for (i = 0; i < N; i++) printf("%d \t",v[i]);
    
	printf("\n La suma es: %d \n\n", sum); 
} 