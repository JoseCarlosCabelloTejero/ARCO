# Tarea 2: Roofline
## Preguntas
**1. Genera un roofline y analiza la información representada. Copia una captura del roofline en la respuesta para apoyar tu análisis. Finalmente genera un snapshot con el nombre "task2a" y añádelo a esta misma carpeta.**
![image](https://user-images.githubusercontent.com/26382537/140785436-f0f0cba7-9009-4fb2-b30a-11a09c5c794f.png)

En el gráfico `roofline` podemos ver que el _performance_ del bucle `for` de la línea 74 es de 0.415 `GFLOPS`, mientras que su intensidad aritmética es de 0.018 `FLOP/Byte`.

**2. ¿Porqué está limitado el algoritmo? ¿Qué técnicas podemos aplicar para mejorar el rendimiento?**

Viendo el gráfico podemos comprobar que este bucle está limitado por memoria, más concretamente por la caché L3. En la pestaña recomendaciones aparece un consejo en el que se indica lo comentado en la _task1_ en la pregunta 2, y además se nos propone como solución vectorizar el bucle para mejorar la eficiencia de la caché.