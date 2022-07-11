# Tarea 2 - Resultados

Para la realización de este análisis se ha utilizado la herramienta gráfica `advisor-gui`. Simplemente creando un nuevo proyecto y asignando el archivo compilado del programa. Para la compilación se ha ejecutado el siguiente comando:

    g++ -fopenmp -g src/mamut.cpp

Después en las opciones de `advisor` se ha indicado en las propiedades del proyecto la ubicación del código fuente del programa compilado ([matmul.cpp](https://github.com/ESI-ARCO-21-22/lab2-albertovazquez-alvaroramos/blob/main/src/matmul.cpp)).

Por último, se ha creado un `snapshot` desde las opciones del menú, generando un archivo, marcando las opciones `cache sources` y `cache binaries`. El archivo generado es el [matmul.advixeexpz](https://github.com/ESI-ARCO-21-22/lab2-albertovazquez-alvaroramos/blob/main/results/task2/matmul.advixeexpz).

Es importante tener en cuenta que si lo estamos ejecutando desde un portátil, como es este caso, si queremos tener el mayor rendimiento posible tendríamos que tener **enchufado a la luz el portátil** y así no estaría limitada la potencia por la batería.