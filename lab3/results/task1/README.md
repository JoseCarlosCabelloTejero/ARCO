# Ejercicio 1

Para este ejercicio se han codificado 4 tipos de soluciones para encontrar el valor mínimo y máximo en un array de n enteros.
Los archivos [maxmin_seq.cpp](https://github.com/ESI-ARCO-21-22/lab3-albertovazquez-alvaroramos/blob/main/results/task1/src/maxmin_seq.cpp) y [maxmin_parallel.cpp](https://github.com/ESI-ARCO-21-22/lab3-albertovazquez-alvaroramos/blob/main/results/task1/src/maxmin_parallel.cpp) se corresponden a un algoritmo que lo que hace recorrer el array elemento a elemento buscando elementos que sean mayores que una variable llamada `max` y que sean menores que una variable llamada `min`.
Otro heuristica que se ha considerado es la de buscar esos valores a traveś de un `algoritmo de divide y vencerás`, este algoritmo se puede encontrar en los archivos [maxmin_seq2.cpp](https://github.com/ESI-ARCO-21-22/lab3-albertovazquez-alvaroramos/blob/main/results/task1/src/maxmin_seq2.cpp) y [maxmin_parallel2](https://github.com/ESI-ARCO-21-22/lab3-albertovazquez-alvaroramos/blob/main/results/task1/src/maxmin_parallel2.cpp).cpp

## Comparación de los tiempos para cada una de los algoritmos propuestos.
#### Leyenda

- Secuencial (recorrer array): maxmin_seq.cpp 
- Paralelo (recorrer array): maxmin_parallel.cpp
- Secuencial (DyC): maxmin_seq2.cpp
- Paralelo (DyC): maxmin_parallel2.cpp

|                             |      Elapsed time (10000000 enteros)|
|-----------------------------|:-----------------------------------:|
| Secuencial (recorrer array) |               0.029 s               |
| Paralelo (recorrer array)   |               0.01 s                |
| Secuencial (DyC)            |                0.18 s               |
| Paralelo (DyC)              |               4.32 s                |

En los resultados vemos claramente como las estrategias de divide y vencerás no son tan óptimas como las de ir recorriendo el array elemento por elemento. Además en los algoritmos donde se va recorriendo el array, si comparamos el secuencial y al paralelo, vemos como efectivamente mejora el tiempo reduciendolo en casi un 35%.

## Comparación de los gráficos roofline
### Secuencial normal
En este gráfico `roofline` vemos como la parte del bucle del programa esta siendo limitada por el ancho de banda de la memoria caché L3.
![roofline1](https://i.imgur.com/Rho3TWm.png)

### Paralelo normal
En este gráfico `roofline` vemos como la parte del bucle del programa esta siendo limitada por el ancho de banda de la DRAM.
![roofline2](https://i.imgur.com/yorxWlg.png)