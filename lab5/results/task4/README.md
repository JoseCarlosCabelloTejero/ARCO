# Tarea 4
El código src/task4/usm.cpp busca sumar ua serie de valores a un valor inicial para obtener el valor final 20.
En principio el código puede parecer que es correcto, es más, si se ejecuta es muy probable que el resultado sea el correcto.
Sin embargo, esto no significa que el programa sea correcto. Esto pasa a menudo en programas paralelos.

En este caso, el problema está en acceder de forma concurrente a la memoria compartida. Si nos fijamos bien, no hay
ningún tipo de dependencia de datos explicita. Sin embargo, si todas las tareas acceden de manera concurrente pueden
causar problemas de comportamiento.

Para solucionar esta problemática cuando se usa USM hay varias opciones.
1. Marcar las dependencias mediante eventos.
2. Marcar las dependencias mediante waits.
3. Marcar las dependencias mediante in_order_queues.

## Realiza las modificaciones al código para solucionar las condiciones de carrera mediante eventos.
**Guarda el código en results/task4/src/usm_events.cpp**
## Realiza las modificaciones al código para solucionar las condiciones de carrera mediante waits.
**Guarda el código en results/task4/src/usm_waits.cpp**
## Realiza las modificaciones al código para solucionar las condiciones de carrera mediante in_order_queue.
**Guarda el código en results/task4/src/usm_inorder.cpp**
