# Tarea 1: Intel Advisor

## Preguntas
***1. En la vista de "Survey & Roofline" se hace referencia a Total time y self-time. ¿Qué diferencia hay entre ambas?***

Ambos muestran el tiempo de ejecución de un segmento o unidad de un programa. La diferencia es que _Self Time_ indica el tiempo de ejecución de las instrucciones que se ejecutan *directamente* en esa función. Si esta función llama a otras, el tiempo que tarden no se sumará al _Self Time_ de la padre. En _Total Time_, se suma el tiempo que tarda la función en ejecutar sus instrucciones, y además el tiempo de otras funciones a las que ésta llame.

***2. Compilando con g++ salen un conjunto de advertencias en intel advisor (buscar mensajes de warning) ¿A qué se deben?. ¿Qué compilador podríamos usar para solucionar estos mensajes? ¿Dónde has encontrado estos mensajes?***

Una sugerencia que nos recomienda el programa de `intel advisor` dentro de la sección de `offload modeling` 
Nos recomienda lo siguiente:
  - Compilar con el compilador de intel `icpc`
  - En lugar compilar con el conjunto de instrucciones `SSE2`, compilar con el conjunto de instrucciones `AVX2` que es, en este caso, el más elevado que hay en el equipo donde se han ejecutado los análisis. Para ello utilizar en el compilador `g++` la flag `-mavx2`.

***3. Realiza un análisis de tipo Survey, accede a  la pestaña "Survey & Roofline" y haz una captura de la información (se usará más tarde).***

![image](https://user-images.githubusercontent.com/26382537/140787411-7d457f8b-18da-49d9-9cf9-4461c0ba8bef.png)

No se muestran datos sobre la gráfica `Roofline`. En la siguiente pregunta veremos a qué se debe.

***4. Pulsa sobre roofline (dentro de Survey & Roofline) y comprueba que no aparece ningún gráfico. ¿A qué se debe?***

El informe de `Roofline` depende de operaciones en punto flotante y enteros, por lo que para recolectar dichas operaciones hay que realizar un análisis de `FLOPS` (Find Trip Counts and FLOP). Si ejecutamos el análisis de trip-counts y flop, se generará el `Roofline`.

***5. Haz un análisis de trip-counts y flop. ¿Qué información nueva aparece en la vista de survey? Haz una captura y comenta los datos nuevos más relevantes.***

![image](https://i.imgur.com/G5HDfHE.png)

Podemos ver los _Self Time_ y _Total Time_ del programa. Vemos como el _Self Time_ corresponde a la línea 74 del código que es donde se encuentra el tercer bucle `for` anidado es de 0.130 segundos.En este caso el _Self Time_ es igual al _Total Time_ ya que el 100% del tiempo de CPU se corresponde con la llamada a ese bucle. Por tanto, si somo capaces de reducir el tiempo de ese bucle a la mitad, entonces el _Self Time_ se reduciría a unos 0.065 segundos al igual que el _Total time_.

![image](https://i.imgur.com/pgvEEuq.png)

En la sección de `Trip Counts` como la media es de 300, ya que en el código definimos unas matrices de 300x300 y que el `Call Count` es de 90000 que indica el número de veces que esa función, en este caso, este bucle, es llamado, y tiene sentido ya que tenemos dos bucles anidados encima lo que hace un total de 300x300 = 90000 llamadas al tercer bucle. En este caso lo bucles son escalares y no están vectorizados. También vemos la _performance_ e intensidad aritmética correspondientes a ese bucle. Estos datos se comentarán en la siguiente tarea.