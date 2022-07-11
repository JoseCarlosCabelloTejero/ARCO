# Tarea 3: Análisis de memoria

## Preguntas
* Genera un análisis de memoria marcando los bucles del cómputo de "c", en concreto marca el bucle i,j y k. Escribe a
continuación la orden que has utilizado para generar dicho análisis.
* Abre advisor y selecciona la vista "Refinement Reports".

    * ¿Qué información nos proporciona esta vista? enumera cada elemento de la tabla resumiendo el significado
    * ¿Qué comportamiento de memoria se obtiene con el código original? ¿Por qué es deseable tener un stride uniforme?
    * Busca el bucle más interno (el del índice k en el código original) y comprueba que el stride es de 300.

        * ¿Por qué el stride tiene este valor? (Revisa los conceptos de row-order y column-order)
        * ¿Sobre que variable se está accediendo con un stride de 300? ¿Cómo afecta esto a la caché?
        * ¿Se te ocurre algún modo de modificar el programa, manteniendo los tres bucles y el mismo resultado, para que
        el acceso a la variable sea uniforme?
* Genera un snapshot y llámalo "task3a", añádelo a esta misma carpeta.