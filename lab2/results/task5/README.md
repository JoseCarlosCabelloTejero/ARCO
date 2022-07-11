# Tarea 5 - Características clave de los sistemas

Consideramos que las características claves de los sistemas donde se han realizado los análisis son:

- Frencuencia de CPU.
- Número de CPUs lógicas, aunque en este caso sólo se ha ejecutado el analisis con 1 único hilo de ejecución.
- En el caso de la _ISA_ no consideramos que haya grandes diferencias ya que todos los sistemas utilizan `SSE2`.
- _Flags_ indicadas a la hora de la compilación del programa.

Especialmente consideramos que el factor que mas influye en los tiempos es la frencuencia, ya que por ejemplo, en el PC local del Alberto tiene la menor frencuencia y mayor tiempo, sin embargo, tanto el `devcloud` como en el PC local de Álvaro, las frencuencias y los tiempos son muy similares. Y tiene sentido, ya que por muchos núcleos que tenga el `devcloud` de diferencia con respecto a los nuestros, no se están utilizando más de un hilo.

## Características del devcloud y mejora del programa
Por ejemplo con el roofline que generamos con el `devcloud`, podemos ver que los bucles que existen en el programa son escalares y por tanto no están vectorizados. El color azul indica que es escalar y el naranja indicaría que es vectorizado.

![roofline](https://i.imgur.com/S7M10MC.png)

Ahora, en el nodo de cómputo del `devcloud`, lo que hemos hecho es compilar en lugar de con `g++`, con el compilador de intel para c++, `icpc`, usando el comando:

    icpc -fopenmp src/matmul.cpp
    
Esta es una de las recomendaciones que nos ofreció `advisor`, la de compilar con el compilador de intel y efectivamente, ahora sí que encontramos diferencias significativas a la hora de lanzar los análisis con `advisor`.

## Tabla comparativa G++ vs ICPC en devcloud

|                                    |    G++        |  ICPC                 |
|------------------------------------|:-------------:|:---------------------:|
| **Elapsed time**                   |  0,10s        | 0,03s                 |
| **Vector Instruction Set**         |    SSE2       |   SSE2, SSE           |
| **Número de hilos CPU**            | 1             |   1                   |
| **Tiempo de CPU**                  | 0,09s         |   0,01s               |
| **Tiempo en scalar code**          | 0,09s         |      0s               |
| **Tiempo en un bucle vectorizado** | 0,09s         |   0,01s               |
| **Tiempo total bucle en línea 72** | 0,09s         |   0,010s              |
| **Tiempo total bucle en línea 67** | 0,09s         |   0,001s              |
| **Tiempo total bucle en línea 69** | 0,09s         |   0,001s              |

En este caso se ha reducido considerablemente el tiempo de CPU hasta 3 veces con respecto al compilar con `g++`. En el caso del programa compilado con `icpc`, todo el tiempo de CPU se corresponde con el vectorizado.

![roofline](https://i.imgur.com/dA7tdrg.png)

## Comparación G++ vs ICPC

| G++ | ICPC |
|:---:|:----:|
|![comparison](https://i.imgur.com/rKoogvt.png)|![](https://i.imgur.com/Rl3BmMR.png)|

Vemos como los tiempos se reducen, el tráfico de memoria también y como tanto los GFLOPS como la intensidad aritmética aumentan en el `icpc`.
