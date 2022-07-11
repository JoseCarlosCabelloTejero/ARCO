/* Programa serie para calcular pi */ 
#include <math.h> 
#include <stdio.h> 
#include <omp.h> 

int main() 
{  
	int n,i; 
	double xi,a,z; 
	double pi16ds = 3.1415926535897932; // con 25 decimales 3.141592653589793238462643 
	double sum = 0.0; 
	

	printf("Introduce la precision del calculo (número de intervalos > 0): "); 
	scanf("%d", &n); 
	omp_set_num_threads(n);
	a = omp_get_wtime(); 

	double h = 1.0 / (double)n; // tamaño intervalo 

	xi = h*0.5;     // centro del primer intervalo
	
	#pragma omp simd safelen(1)
	for (i = 0; i < n; i++) {
			sum += (4.0 / (1.0 + xi*xi)); 
			xi += h; // xi: centro del siguiente intervalo 
	} 

	double pi = sum * h; 

	printf("\nEl valor aproximado de PI es %0.16f con un error de %0.16f\n", pi, fabs(pi-pi16ds)); 

	z = omp_get_wtime(); 

	printf("El programa ha tardado %0.10f segundos \n", z-a); 

	return 0;
} 