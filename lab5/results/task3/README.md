# Tarea 3
El código src/task3/mult_complex.cpp realiza la multiplicación de números complejos mediante un método escalar y un
método paralelo.

## Realiza todas las modificaciones al código, revisa todos los comentarios
Se creado el archivo [mult_complex.cpp](src/mult_complex.cpp).

## Muestra el resultado de salida

Resultado del programa:

```
Target Device: 
Device name: Intel(R) Core(TM) i5-6300HQ CPU @ 2.30GHz
Vendor: Intel(R) Corporation
Version: 3.0
****************************************Multiplying Complex numbers in Parallel********************************************************
[0] (2 : 4i) * (4 : 6i) = (-16 : 28i)
[1] (3 : 5i) * (5 : 7i) = (-20 : 46i)
[2] (4 : 6i) * (6 : 8i) = (-24 : 68i)
[3] (5 : 7i) * (7 : 9i) = (-28 : 94i)
[4] (6 : 8i) * (8 : 10i) = (-32 : 124i)
...
[9999] (10001 : 10003i) * (10003 : 10005i) = (-40012 : 200120014i)
Complex multiplication successfully run on the device
```

El resultado es correcto, ya que, ambos resultados, tanto la multiplicación de numero complejos en paralelo como escalar son iguales.

Lo que se ha añadido en el código es lo siguiente:

Se imprime información sobre el dispositivo, en este caso es un `cpu_selector`, por tanto imprimirá información sobre mi CPU.

```c++
std::cout << "Target Device: " << std::endl;
std::cout << "Device name: " << q.get_device().get_info<info::device::name>() << std::endl;
std::cout << "Vendor: " << q.get_device().get_info<info::device::vendor>()<< std::endl;
std::cout << "Version: " << q.get_device().get_info<info::device::version>()<< std::endl;
```
Por último, se ha establecido los permisos de acceso a los _accessors_. Para V1 y V2 se ha establecido `read_only`, ya que son los vectores que se van a multiplicar y solo en necesario permisos de lectura y para V3 se han establecido `write_only`, ya que es donde se va almacenar dichas multiplicaciones.

```c++
accessor V1(bufin_vect1, h, read_only);
accessor V2(bufin_vect2, h, read_only);
accessor V3(bufout_vect, h, write_only);
```

Al final del `command group` se utiliza la función `wait()`, para así esperar a que la operación termine.