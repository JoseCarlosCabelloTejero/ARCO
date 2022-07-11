# Ejercicio 3

## Primera propuesta

Para paralelizar la parte del bucle primero se ha optado por utilizar `directivas SIMD` para así las iteracciones del bucle se ejecuten de manera paralela/concurrente con `instrucciones SIMD`.

Código modificado:

```c++	
	#pragma omp simd safelen(1)
	for (i = 0; i < n; i++) {
		sum += (4.0 / (1.0 + xi*xi)); 
		xi += h;
	} 
```

Con la cláusula `safelen` indicamos el número de iteraciones que pueden ser ejecutadas a la vez, en este caso solo puede a ver 1, ya que existen dependencias `intraloop`, es decir, por cada nueva iteración del bucle existe una dependencia `WAR` y `WAW` con la variable `xi` y una dependencia `WAW` con la variable `sum`.

Resultado de la ejecución del algoritmo anterior con 12 de precisión:

    El valor aproximado de PI es 3.1421713566497971 con un error de 0.0005787030600040
    El programa ha tardado 0.0000575350 segundos

No mejora ni empeora el código original debido a que realmente se ejecutan una iteración y después otra y así sucesivamente, es decir, no hay paralelismo ni concurrencia a priori.

## Segunda propuesta

Otra opción que nos ofrece OpenMP es la de una directiva para paralelizar bucles for. 

Código modificado:
```c++	
    omp_set_num_threads(4);

	#pragma omp parallel for 
	for (i = 0; i < n; i++) {
		sum += (4.0 / (1.0 + xi*xi)); 
		xi += h;
	}
```

Sin embargo tenemos un problema similar al anterior, y es que, la variable `xi` es una variable compartida por los diferentes hilos lanzados. Por tanto, existe una necesidad de sincronizar los hilos para que no se produzca una inconsistencia en los datos debido a las condiciones de carrera y los resultados sean erróneos.

Resultado de la ejecución del algoritmo anterior con 12 de precisión:

    El valor aproximado de PI es 2.6092351772342539 con un error de 0.5323574763555392
    El programa ha tardado 0.0030990260 segundos

Para sincronizar y proteger esta variable compartida podemos hacer uso de la directiva `#pragma omp critical` donde se establece un bloque de código donde unicamente un hilo puede acceder de manera paralela/concurrente.

Código modificado:
```c++	
    omp_set_num_threads(n); /* Lanzamos tantos hilos como precisión indique el usuario */

	#pragma omp parallel for 
	for (i = 0; i < n; i++) {
        #pragma omp critical
        {
			sum += (4.0 / (1.0 + xi*xi)); 
			xi += h;
        }
    }
```

Resultado de la ejecución del algoritmo anterior con 12 de precisión:
    
    El valor aproximado de PI es 3.1421713566497971 con un error de 0.0005787030600040
    El programa ha tardado 0.0009121910 segundos 

Ahora los cálculos si son correctos, pero vemos que el tiempo de ejecución incrementa con rescepto al código original y a la primera propuesta. Entendemos que este incremento se debe a que realizar los cambios de contexto entre la ejecución de un hilo y otro consume mucho tiempo de CPU y debido a esto se incrementa el tiempo total del programa.

## Tercera propuesta

Por último probaremos a utilizar las directivas `#pragma omp parallel` y `#pragma omp for` con las directivas y cláusulas `reduction` y `schedule`.

Código modificado:
```c++	
xi = 0;
double h = 1.0 / (double) n;

	omp_set_num_threads(n); /* Lanzamos tantos hilos como precisión indique el usuario */

	#pragma omp parallel private(i,xi)
	{
	#pragma omp for reduction(+:sum) schedule(static)
		for (i=0; i<n; i=i+1){
			xi=(i+0.5)*h;
			sum = sum + 4.0/(1.0+xi*xi);
		}
	}
```
En este caso se establece con la cláusula `private` las variables que serán privadas por cada hilo. La cláusula `reduction` nos permite suma valor independiente que son producidos por los diferentes hilos, por eso se asocia a la variable `sum`. Con la directiva `schedule` con la cláusula `static`, la ejecución se programa se divide en diferentes _chucks_ y cuando se alcanza el último, la asignación vuelve a empezar desde el primero.

Resultado de la ejecución del algoritmo anterior con 12 de precisión:

    El valor aproximado de PI es 3.1421713566497962 con un error de 0.0005787030600031
    El programa ha tardado 0.0011686460 segundos 

### Comparación de tiempos con los resultados obtenidos

|                          |      Tiempo (Precisión de 12)   |
|--------------------------|:-------------------------------:|
| **Sin paralelizar**      |          0.0000603820 s         |
| **Simd safelen**         |             0.0000575350 s      |
| **Parallel for**         |               0.0009121910 s    |
| **Reduction y schedule** |           0.0011686460 s        |

