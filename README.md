# Tarea 1 ICI2244-1
![image](https://github.com/MatiasPUCV/Tarea_1_ICI2244-1/assets/142541831/697cadcf-5b6e-4fd4-9301-baa3883555c3)


## Compilación:

Ejecute en el directorio:

`gcc -Iinclude -o Tarea1 src/main.c src/app.c src/book.c src/util.c src/list.c src/queue.c`

Después ejecute:

`Tarea1.exe`

> Alternativamente puede usar cmake

## Información de uso:

La aplicación acepta 11 comandos que siguen la sintaxis: <comando, parámetros…>.
Los parámetros están separados por un espacio, si se requiere usar un parámetro de más de una palabra pongalo entre comillas.

Ejemplo de uso:

`mostrar_datos_libro "Fahrenheit 451" Bradbury`

**1. registrar_libro** <título, autor, género,asbm, ubicación>:

Ingresa los datos del libro y la aplicación los almacena. Debe validarse que ningún string tenga un largo mayor a 50 caracteres.
> Alternativamente puede poner todos los datos juntos separados por comas.

**2. mostrar_datos_libro** <título, autor>:

Ingresa el título y autor de un libro y la aplicación muestra sus datos y las reservas si las hay. Si el libro no existe, se muestra un aviso.

**3. mostar_todos_los_libros**:

La aplicación muestra por pantalla los títulos y autores de todos los libros registrados.

**4. reservar_libro** <título, autor, nombre_estudiante>:

Ingresa el título y autor del libro y el nombre del estudiante que quiere reservarlo. La aplicación agrega la reserva a la cola de reservas del libro. Si el libro no existe, se muestra un aviso.

**5. cancelar_reserva** <título, autor, nombre_estudiante>:

Ingresa el título y autor del libro y el nombre del estudiante que quiere cancelar la reserva. La aplicación elimina la reserva de la cola de reservas del libro. Si el libro o la reserva no existen, se muestra un aviso.

**6. retirar_libro** <título, autor, nombre_estudiante>:

Si el libro está "Disponible" o si el estudiante es el primero en la cola de reservas para un libro "Reservado", entonces el libro puede ser retirado y su estado cambia a "Prestado". Si el libro ya está "Prestado" o el estudiante no tiene prioridad, se muestra un aviso.

**7. devolver_libro** <título, autor>:

Al devolver un libro, si hay una cola de reservas, el estado cambia a "Reservado". Si no hay reservas, el estado cambia a "Disponible".

**8. mostrar_prestados**:

La aplicación muestra por pantalla los títulos y autores de todos los libros que están prestados y el estudiante al que se le prestó.

**9. importar_csv** <nombre_archivo>:

Ingresa el nombre del archivo y la aplicación carga todos los libros y sus datos, incluyendo las colas de reservas.

**10. exportar_csv** <nombre_archivo>:

La aplicación exporta todos los libros, sus datos y las colas de reservas a un archivo que sigue el formato csv.

> Alternativamente se puede usar un comando poniendo el número que está en la lista.

## Contribuciones

Matías (Puntos 3): Implementación de la interfaz de la aplicación, la lista, operaciones relacionadas con los libros, funciones misceláneas y documentación de la aplicación.

Angelo (Puntos 1): Implementación del Queue, depuración de código.

> **Para más información revisar historial de commits**


