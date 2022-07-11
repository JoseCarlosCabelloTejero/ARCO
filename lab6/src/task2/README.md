# Tarea 2
En esta tarea paralelizarás el código con DPC para obtener el máximo rendimiento a la vez que obtienes una gran
portabilidad.

## Preparar el código
En primer lugar, copia el código results/task1/task1_b.cpp en results/task2/base.cpp. Este será el fichero base
para las modificaciones necesarias.

## Crea la cola y un selector de dispositivo por defecto
Busca como crear la cola y pasa como parámetro a la cola el selector por defecto. Recuerda que la cola se tiene que crear
antes de cualquier tipo de computo.

## ¿Para que sirve la cola?
Se utilizan para enviar unidades de ejecución a un dispositivo como puede ser una CPU, GPU, FPGA...

## Para cada array crea sus buffer correspondientes
Recuerda que uno de los modos de acceder a memoria en DPC es mediante los buffers y los accessors. Este es el método que vamos
a usar en esta práctica.
Para ello, crea los buffers una vez inicializados los espacios de memoria donde vamos a trabajar, es decir, justo antes del for.

Algunas pistas:
* Necesitas 4 buffers, dos para imágenes (entrada/salida) y dos para filtros.
* El segundo parámetro que requiere el constructor es un objeto de tipo rango. Para las imágenes los rangos son: img_width img_height y para los filtros 3 * 3 o, directamente, 9.

## Crea un rango para indicar el espacio de trabajo del kernel
El primer parámetro del paralell_for va a ser el rango de trabajo. Para definir este rango tenemos que indicar, en tiempo de compilación,
el número de dimensiones que tiene y el tamaño de cada dimensión.

Pistas:
* El número de dimensiones viene determinado por el número de dimensiones de la imagen. ¿Cuantas dimensiones tiene una imagen en **blanco y negro**? **Recuerda que está en blanco y negro no en RGB**.
* El tamaño de cada dimensión viene determinado por el alto y el ancho.

Crea esta variable **justo debajo de la definición de los buffer**.

## Manda una tarea a la cola
Ahora crearemos el trabajo dentro de la cola donde, en las siguientes tareas, iremos metiendo el código para: solicitar acceso a las variables y ejecutar el trabajo.
Busca como crear el trabajo para la cola. Comprueba que el código compila.

## Solicitar acceso a los buffer
Recuerda que hemos creado los buffer para abstraer el acceso a las diferentes variables. Tal y como se ha visto en teoría hay que solicitar el acceso a cada
buffer por medio de los accessors. **En las primeras líneas dentro de la cola** define los accessor que necesitamos.

Pistas:
* Tenemos que crear tantos accessors como buffers hemos creado anteriormente.
* Elige bien los permisos.

## Crea el parallel_for
Ahora que ya tenemos acceso a cada uno de los buffer, hay que solicitar por medio del handler el parallel_for indicando: el rango del kernel (revisa los pasos anteriores)
y el kernel. Inicialmente deja el kernel vacio y comprueba que la compilación es correcta.

Pistas:
* Los for que recorren la imagen (row, col) desaparecen ya que el for se reparte por píxeles.
* Puedes acceder al valor de row y col mediante el segundo parámetro del kernel id<2>. Row será item[0] y col item[1].

Una vez finalizado el parallel_for (recuerda añadir el código para multiplicar por el kernel), compila el código y asegurate
de no tener errores de compilación.

## Esperar al trabajo y acceder a los resultados
Finalmente solo queda esperar a la cola, busca como puedes esperar y acceder mediante un host_accessor al buffer de salida
del kernel. Únicamente creando el host_accessor al buffer el runtime se asegura que tienes acceso al mismo y ya puedes acceder como lo harías normalmente.

**Comprueba que el código produce los mismos resultados que el código secuencial**
**Guarda el código final en results/task2/dpc.cpp**
El código se encuentra en el siguiente archivo: [dpc.cpp](../../results/task2/src/dpc.cpp)
