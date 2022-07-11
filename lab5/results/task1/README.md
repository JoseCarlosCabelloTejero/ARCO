# Tarea 1
Familiarizarse con el uso de DPC.
En primer lugar copia el código de src/task1/query.cpp en results/task1/src y compilalo con dpcpp.

## ¿Qué salida obtienes?

Para compilar con `dpcpp` primero hay que _settear_ las variables de entorno de `OneAPI` usando el siguiente comando:

```
source setvars.sh
```
Después compilamos usando `dpcpp`, con el siguiente comando:

```
dpcpp src/query.cpp -o query
```

El resultado obtenido es el siguiente:

```
Device: Intel(R) Core(TM) i5-6300HQ CPU @ 2.30GHz
```

En este caso aparece como dispositivo mi procesador ya que se ha específicado un selector de tipo `CPU`.

## ¿Qué tipos de selectores tenemos en DPC? ¿Podemos obtener una GPU? ¿Qué pasa si no existe el dispositivo requerido?
Es probable que alguno de los dispositivos que te permite seleccionar DPC no los tengas disponibles en tu PC, no pasa nada, para eso tenemos
devcloud.

Tenemos los _host selector_ y los _device selector_, los _host selector_ se refiere al _host_ que ejecuta el código principal y distribuye el trabajo entre los dispositivos y el _device_ se refiere a una CPU, GPU, FPGA que se encarga de ejecutar el código _kernel_.

En este caso solo tenemos un _host_. Para modificar el tipo de _device_, tenemos que especificarlo a la hora de crearla _queue_, de la siguiente manera:

```c++
#include <CL/sycl.hpp>

using namespace cl::sycl;

int main() {
    gpu_selector selector; /* Se indica el selector de tipo GPU */

    queue q(selector);

    std::cout << "Device: " << q.get_device().get_info<info::device::name>()<< std::endl;

    return 0;
}
```
En mi caso el programa de devuelve lo siguiente:
```
terminate called after throwing an instance of 'cl::sycl::runtime_error'
  what():  No device of requested type available. Please check https://software.intel.com/content/www/us/en/develop/articles/intel-oneapi-dpcpp-system-requirements.html -1 (CL_DEVICE_NOT_FOUND)
Abortado
```

Esto quiere decir que no encuentra dicho dispositivo en mi PC.

## Prueba a obtener una GPU desde devcloud modificando el programa query.cpp en gpu_query.cpp
Se ha creado el [archivo gpu_query.cpp](src/gpu_query.cpp) con el código mostrado en la anterior pregunta, especificando un selector de tipo GPU.

Código:
```c++
#include <CL/sycl.hpp>

using namespace cl::sycl;

int main() {
    gpu_selector selector; /* Se indica el selector de tipo GPU */

    queue q(selector);

    std::cout << "Device: " << q.get_device().get_info<info::device::name>()<< std::endl;

    return 0;
}
```

## ¿Cómo has obtenido la GPU? ¿Cómo has solicitado a qsub que quieres un nodo con GPU?

Para obtener un nodo con GPU desde `devcloud` hay que ejecutar el siguiente comando desde la pasarela de `devcloud`:

```
qsub -I -l nodes=1:gpu:ppn=2
```

Con el parámetro `-l nodes=1:gpu:ppn=2` se asigna un nodo con GPU al trabajo. 


Si compilamos y ejecutas el programa anterior obtenemos el siguiente resultado:
```
Device: Intel(R) UHD Graphics P630 [0x3e96]
```

## Modifica el programa para obtener más datos del dispositivo.
Se ha creado el siguiente archivo: [more_query.cpp](src/more_query.cpp)

Se ha compilado y ejecutado el programa en el `devcloud` y el resultado es el siguiente:
```
Device name: Intel(R) UHD Graphics P630 [0x3e96]
Vendor: Intel(R) Corporation
Version: 1.1
Driver version: 1.1.20678
Image support: 1
Global memory size: 53798854656
Local memory size: 65536
Maximum work of group size: 256
```

- Global memory size: Tamaño de memoria global en bytes. 
- Local memory size: Tamaño de memoria local en bytes.
- Maximum work of group size: Número máximo de work-items que son permitidos en cada dimensión de un grupo de trabajo.

En el siguiente recurso se encuentra todos tipos de información que se pueden consultar sobre el dispositivo

https://oneapi-src.github.io/DPCPP_Reference/iface/device.html#device-info
