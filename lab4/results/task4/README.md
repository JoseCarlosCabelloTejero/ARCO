# Tarea 4: Paralelización con OpenMP
## Preguntas
* Paraleliza el programa todo lo que puedas, fíjate en los comentarios marcados con "TODO" para ver donde tienes que incorporar código.

Primero se han añadido las funciones de `omp_get_num_procs()` y `omp_get_num_threads()` para ver cuantos procesadores y hebras se ejecutan. Además se han utilizado la directiva `omp_set_num_threads()` para _setear_ el número de hilos, en este caso se han seleccionado `n` hilos, siendo `n` el orden de las matrices, para que así por cada iteración de los bucles principales se cree un hilo.

Para paralelizar los bucles se ha utilizado las siguientes dos directivas de `omp`:

Directiva `#pragma omp parallel`, para crear una sección paralela con el número de hilos previamente definidos y se establece con `shared` y `private` las variables correspondientes.
Directiva `#pragma omp for schedule(static)`, para dividir el trabajo en _chunks_. Cada _chunk_ se asigna en orden para cada hilo.

* ¿Cuántas hebras hay disponibles? ¿A qué crees que se debe este resultado?

Hay 1 hebra disponible. Esta hebra se corresponde con la hebra principal del programa y como todavía o se han ejecutado las directivas de `omp` aplicadas en los bucles, entonces las demás hebras todavía no se han creado. Si llamamos a `omp_get_num_threads()` desde una sección paralelizada entonces si nos devuelve el número de hilos correcto.

* Comprueba que la ejecucion paralela y secuencial es la misma. Recuerda que estás trabajando con números decimales
    * ¿Cómo lo has comprobado?

Ejecución del algoritmo secuencial:
```
MATMUL:
C = A * B.
Order N                 = 300
Elapsed seconds = 0.143133
C(100,100)  = 1

Matmul:
Normal end of execution.
```
Ejecución del algoritmo paralelo (`n` hilos):
```
MATMUL:
  C = A * B.
  Order N                 = 300

Number of processors: 4
Number of threads: 1

  Elapsed seconds = 0.0458958
  C(100,100)  = 1

Matmul:
  Normal end of execution.
```

Vemos como el tiempo de ejecución del secuencial es de unos `0.14 s`, mientras que el paralelo es de unos `0.04 s`, es decir, que se reduce en más de un tercio el tiempo de ejecución con respecto al secuencial. También comprobamos que el resultado es el mismo para C(100,100) = 1, en ambos casos.

* Realiza una tabla modificando el valor de "n" para el programa secuencial y el paralelo y con los siguientes valores:
    * Valor "n"
    * Tiempo
    * Performance del bucle principal (GFLOPS)
    * Tráfico de memoria GB

Se ha obviado un `n` igual o menor que 300, ya que en el caso del programa paralelo, la ejecución es tan rápida que `advisor` no es capaz de recolectar suficiente información en tan poco tiempo.

|                                             |  Secuencial  |   Paralelo  |
|---------------------------------------------|:------------:|:-----------:|
| **Valor "n"**                               |    600       |     600     |
| **Tiempo (segundos)**                       |  1.11994     | 0.311368    |
| **Performance del bucle principal (GFLOPS)**|    0.343     |      43.2   |
| **Tráfico de memoria (GB)**                 |    24.195    |     27.657  |

|                                             |  Secuencial  |   Paralelo  |
|---------------------------------------------|:------------:|:-----------:|
| **Valor "n"**                               |   900        |    900      |
| **Tiempo (segundos)**                       |   4.78601    |  1.10343    |
| **Performance del bucle principal (GFLOPS)**|      0.233   |    72.9     |
| **Tráfico de memoria (GB)**                 |     81.654   |    93.331   |

|                                             |  Secuencial  |   Paralelo  |
|---------------------------------------------|:------------:|:-----------:|
| **Valor "n"**                               |   1200       |    1200     |
| **Tiempo (segundos)**                       |  9.62499     | 2.37714     |
| **Performance del bucle principal (GFLOPS)**|    0.332     |  172.799    |
| **Tráfico de memoria (GB)**                 |    193.548   |   221.219   |

Podemos comprobar que, cuantos mayor sea el orden de las matrices, más diferencia en el tiempo podemos observar.
Con estos datos tambien podemos ver que el _peak_ de _performance_ en los algoritmos paralelos con respecto a los secuenciales esta muy por encima.

* Realiza un análisis completo y genera el snapshot "task4a"

Este análisis se realizará para el algoritmo paralelo para un `n` de 600. Se realizará el análisis tanto en local como utilizando el `devcloud`.

### Local
Desde la herramienta gráfica de `advisor`, generamos un `snapshot` llamado [task4a-local.advixeexpz]().

El `Elapsed time` es de 2.80 segundos y el `CPU time` es de 0.08 segundos. El _peak_ de _performance_ es de 43.2 `GFLOPS`, y la intensidad aritmética es de 0.016 `FLOP/Byte`. El tráfico de memoria es de 27.657 GB. El número de hilos ejecutados son de 6 en este caso y el `ISA` utilizado para compilar el programa es `SSE2`.

En el gráfico `roofline` podemos apreciar como el bucle de la línea 86 aparece como un punto pequeño y verde, lo que quiere decir que ocupa relativamente poco tiempo, por lo que comparado como estaba en el programa secuencial ([ver roofline de la task2]()), ha mejorado considerablemente. Tambien observamos como estamos "rompiendo" el techo de memoria, esto quiere decir que deberiamos de añadir más operaciones al algoritmo, para así, aumentar la intensidad aritmética y que el punto verde se mueve a la derecha.

![Roofline](https://i.imgur.com/kb5clgL.png)

En el análisis de las dependencias de datos, se han encontrado 2 dependencias reales `RAW` en el bucle de la línea 86. Sin embargo en los demás bucles no se han encontrado ninguna dependencia.

Las recomendaciones que nos da `advisor` son las de siempre, compilar con un `ISA` mayor como `AVX2` o utilizar el compilador de intel `icpc`. Si compilamos utilizando el `icpc` estos son los resultados:

```
MATMUL:
  C = A * B.
  Order N                 = 600
  Elapsed seconds = 0.0940671
  C(100,100)  = 1

Matmul:
  Normal end of execution.
```

Mejora el tiempo considerablemente pero a la hora de realizar al análisis y ver el `roofline` vemos que se han incrementado la intensidad aritmética pero se ha reducido la _performance_.

![roofline](https://i.imgur.com/cHOhnHC.png)

Se ha vectorizado el bucle de la línea 86. 

![vectorized](https://i.imgur.com/oHvUueo.png)


### Devcloud
Primero realizamos un analisis `survey` y de `FLOPS` y `Trip Counts` con el siguiente comando:

    advisor --collect=roofline --project-dir=./advi_results --search-dir all:=./src -- ./matmul

Por último para realizar un `snapshot` utilizamos el siguiente comando:

    advisor --snapshot --pack --cache-sources --cache-binaries --project-dir=./advi_results

Algunos datos extraidos del `snapshot` son los siguientes:
- Self time 0.140 segundos
- Total time 0.140 segundos
- Performance 43.2 GFLOPS
- Intensidad aritmética  0.016 FLOP/Bytes
- Tráfico de memoria 27.657 GB
- En este caso se han utilizado 16 hilos.

En el `roofline` podemos ver como el punto verde se encuentra muy cercano al `sweet point` entre el `Scalar Add Peak` y el `L1 Bandwidth`, por que este algoritmo esta bastante bien optimizado. De hecho, `advisor` ni siquiera nos advierte de que el algoritmo este limitado ni por memoria ni por rendimiento.

![Roofline](https://i.imgur.com/PvV5NCD.png)