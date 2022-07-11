# Tarea 3
Una vez completada la paralelización realiza las medidas de rendimiento para ver la mejora

## ¿Cómo mejora el código paralelo con respecto al código secuencial?
En nuestro caso, no se encontramos una mejora en la ejecución del código paralelo. Creemos que es debido a las dependecias de datos existentes, pero vemos como los tiempos van en aumento conforme la imagen es mayor, por lo que suponemos que para una imagen que una resolución muy grande, el código en paralelo sería mejor.

## ¿Por qué la primera vez tarda más que las siguientes?
Entendemos que ocurre por que la primera vez los datos tienen que ser cargados desde la memoria RAM, mientras que en las ejecuciones posteriores, gran parte de los datos son cargados desde la memoria cache.

## Realiza una tabla para cada imagen y cada configuración (serie, paralelo) con los tiempos medios

|  Imagen        |   Serie (s)     |  Paralelo (s) |
|:--------------:|:---------------:|:-------------:|
|    Homer       |   0.0312922     | 0.283976 s    |
|  Paisaje       |   0.103196      | 0.358646 s    |
|    Puente      |    0.20646      |   0.445763 s  |


## Modifica el código para poder desplegar el mismo en una GPU, utiliza devcloud para probar la ejecución en GPU
El código modificado se encuentra en [dpc_gpu.cpp](../../results/task2/src/dpc_gpu.cpp)

La única diferentecia es utilizar un selector de tipo `gpu`:
```c++
gpu_selector selector;
queue q(selector);

std::cout << "Device name: " << q.get_device().get_info<info::device::name>()<< std::endl;
```
La GPU que se obtenido usando `devcloud` es la Intel(R) UHD Graphics P630 [0x3e96]

### Modifica la tabla anterior para añadir los tiempos con GPU

|  Imagen        |   Serie        |  Paralelo     | Serie (GPU)   | Paralelo (GPU)|  
|:--------------:|:--------------:|:-------------:|:-------------:|:-------------:|
|    Homer       |   0.0312922 s  |  0.283976 s   |  0.00934887 s |  0.153461 s   |
|  Paisaje       |   0.103196 s   | 0.358646 s    |  0.0623989 s  |   0.202036 s  |
|    Puente      |    0.20646 s   |  0.445763 s   |   0.129117 s  |  0.288778 s   |

### ¿Cómo te has asegurado de ejecutar el código en una GPU?
Utilizando el selector de GPU y solicitando un nodo con GPU a `devcloud` con el siguiente comando:

```
qsub -I -l nodes=1:gpu:ppn=2
```

### Modifica el programa para obtener información sobre el nodo que ejecuta la cola

El código modificado se encuentra en [dpc_gpu_more_info.cpp](../../results/task2/src/dpc_gpu_more_info.cpp)

Salida:
```
Device name: Intel(R) UHD Graphics P630 [0x3e96]
Vendor: Intel(R) Corporation
Version: 1.1
Driver version: 1.1.20678
Image support: 1
Loaded image with a width of 1280 height of 1024 and 4 channels
Time 0.153461
```