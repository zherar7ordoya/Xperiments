#include <stdio.h>
#include <time.h>
#include "string_utils.h"

int main() {
    clock_t start, end;
    double cpu_time_used;

    // Variables para almacenar el nombre del archivo y la cadena de busqueda
    char filename[100];
    char search_query[100];

    // Solicitar al usuario ingresar el nombre del archivo
    printf("Ingrese el nombre del archivo: ");
    scanf("%99s", filename);

    // Cargar las cadenas desde el archivo
    StringDatabase *db = load_strings(filename);
    if (!db) {
        return 1;
    }

    // Solicitar al usuario ingresar la cadena de busqueda
    printf("Ingrese la cadena de busqueda: ");
    scanf("%99s", search_query);

    // Medir el tiempo de ejecucion de las operaciones
    start = clock();

    // Ordenar, limpiar y buscar la cadena en la base de datos
    sort_strings(db);
    remove_duplicates(db);
    remove_invalid_lengths(db);

    // Realizar la busqueda y mostrar el resultado
    if (db->count == 0) {
        printf("ERROR: La lista quedo vacia despues de la limpieza.\n");
    } else {
        int index = search_string(db, search_query);
        if (index != -1) {
            printf("EXISTE: Cadena encontrada en el indice %d: %s\n", index + 1, db->strings[index]);
        } else {
            printf("NO EXISTE: Cadena no encontrada.\n");
        }
    }

    // Calcular y mostrar el tiempo de operaciones
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tiempo de operaciones: %f segundos\n", cpu_time_used);

    // Guardar la lista depurada en un archivo de texto
    save_strings("depurada.txt", db);
    printf("Lista depurada guardada en 'depurada.txt'\n");

    // Liberar la memoria utilizada por la base de datos
    free_database(db);

    // Retornar de forma exitosa
    return 0;
}
