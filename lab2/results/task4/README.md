# Tarea 4 - Análisis de los resultados obtenidos

### Características del PC local (Alberto Vázquez) vs PC local (Álvaro Ramos) vs Devcloud

|                       | Alberto                          | Alvaro                              |           Devcloud               |
|-----------------------|:--------------------------------:|:-----------------------------------:|:--------------------------------:|
| **Nombre CPU**        |    Intel (R) Core(TM) i5-6300HQ  | AMD Ryzen 5 1600 Six-Core Processor |   Intel(R) Xeon(R) Gold 6128     |
| **Frecuencia**        | 2,30 GHz                         | 3,65 GHz                            | 3,40 GHz                         |
| **CPUs lógicas**      | 4                                | 12                                  | 24                               |
| **Sistema Operativo** | Linux                            | Linux                               | Linux                            |

### Tabla comparativa de los diferentes resultados obtenidos con advisor

|                                    |    Alberto    |  Alvaro               |  Devcloud             |
|------------------------------------|:-------------:|:---------------------:|:---------------------:|
| **Elapsed time**                   |  0,15s        | 0,10s                 | 0,10s                 |
| **Vector Instruction Set**         |    SSE2       |   SSE2                |   SSE2                |
| **Número de hilos CPU**            | 1             |   1                   |   1                   |
| **Tiempo de CPU**                  | 0,14s         |   0,09s               |   0,09s               |
| **Tiempo en scalar code**          | 0,14s         |   0,09s               |   0,09s               |
| **Tiempo total bucle en línea 72** | 0,140s        |   0,09s               |   0,09s               |
| **Tiempo total bucle en línea 67** | 0,140s        |   0,09s               |   0,09s               |
| **Tiempo total bucle en línea 69** | 0,140s        |   0,09s               |   0,09s               |


### Análisis y recomendaciones
Podemos comprobar como claramente los tiempos en el nodo de cómputo de `devcloud` son menores con respecto al PC local de Alberto, tanto del tiempo de CPU total como del tiempo de ejecución de cada uno de los bucles. Sin embargo no hay mucha diferencia entre el `devcloud` y el PC local de Álvaro. En la tarea 5 se tratará de identificar el por que de estos resultados. En este caso, se han compilado con el mismo conjunto de intrucciones (_ISA_), el `SSE2` (Streaming "Single Instruction Multiple Data" Extensions 2). Además en los tres sistemas, se ha utilizado un único hilo de CPU para el análisis del programa.

Una de las recomendaciones que nos ofrece la herramienta de `advisor` es de la usar otro _ISA_ a la hora de compilar el programa.

Por ejemplo desde el PC local (Alberto Vázquez), se identifica que la aplicación ha sido compilada con el _ISA_ `SSE2`, sin embargo es más lenta que el conjunto de instrucciones `AVX2`, que esta disponible en este equipo. Desde la [página oficial de intel del procesador i5-6300hq](https://ark.intel.com/content/www/es/es/ark/products/88959/intel-core-i5-6300hq-processor-6m-cache-up-to-3-20-ghz.html) podemos confirmarlo, en el apartado de _Extensiones de conjunto de instrucciones_. Para ello tendriamos que compilar el código con la flag `-mavx2`. [En este recurso](https://gcc.gnu.org/legacy-ml/gcc-help/2015-02/msg00024.html) encontramos más información sobre como configurar por defecto ese _flag_ a la hora de compilar.

Algo parecido ocurre con el análisis del nodo de cómputo de `devcloud`, ya que ha sido compilado con la misma _ISA_ `SSE2`, sin embargo es más lenta que la conjunto de instrucciones de `AVX512`. En este caso para compilar con esa _ISA_ habría que compilar con una versión 5.1 del compilador de GNU o usar el compilador de Intel con la versión 15.0 o superior.

Sin embargo, leyendo foros por internet, documentación y demás, la vectorización automática cambiando esos unicamente ese _flag_, no marcará una gran diferencia, si no que habría que modificar el código para utilizar las funciones que provee el compilador. Un ejemplo de código para `AVX2` sería este:

    #include <immintrin.h>

    int main(int argc, char **argv) {
        __m256d a; /* __m256d es un tipo de dato que representa un entero */
        __m256d b;
        __m256d c;

        _mm256_fnmadd_pd(a, b, c);
    }

Información sobre la función [_mm256_fnmadd_pd](https://www.intel.com/content/www/us/en/develop/documentation/cpp-compiler-developer-guide-and-reference/top/compiler-reference/intrinsics/intrinsics-for-intel-advanced-vector-extensions-2/intrinsics-for-fused-multiply-add-operations/mm-fnmadd-pd-mm256-fnmadd-pd.html).
