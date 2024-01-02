#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * Esta versión incluye las funciones sort_strings, remove_duplicates y 
 * remove_invalid_lengths que se encargan de realizar las operaciones requeridas.
 * Además, el programa principal ahora muestra respuestas específicas 
 * dependiendo del resultado de la búsqueda y la limpieza de la lista.
*/

typedef struct {
    char **strings;
    int count;
} StringDatabase;


// *****************************************************************************

void sort_strings(StringDatabase *db) {
    // Ordenar las cadenas usando el algoritmo de burbuja
    for (int i = 0; i < db->count - 1; i++) {
        for (int j = 0; j < db->count - i - 1; j++) {
            if (strcmp(db->strings[j], db->strings[j + 1]) > 0) {
                char *temp = db->strings[j];
                db->strings[j] = db->strings[j + 1];
                db->strings[j + 1] = temp;
            }
        }
    }
}

void remove_duplicates(StringDatabase *db) {
    for (int i = 0; i < db->count - 1; i++) {
        if (strcmp(db->strings[i], db->strings[i + 1]) == 0) {
            free(db->strings[i]);
            for (int j = i; j < db->count - 1; j++) {
                db->strings[j] = db->strings[j + 1];
            }
            db->count--;
            i--;
        }
    }
}

void remove_invalid_lengths(StringDatabase *db) {
    for (int i = 0; i < db->count; i++) {
        int len = strlen(db->strings[i]);
        if (len != 8 && len != 14) {
            free(db->strings[i]);
            for (int j = i; j < db->count - 1; j++) {
                db->strings[j] = db->strings[j + 1];
            }
            db->count--;
            i--;
        }
    }
}

// *****************************************************************************

// Función para hacer backup de la base de datos en memoria (para depuración) y
// comparación de la salida en pantalla

void save_strings(const char *filename, StringDatabase *db) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("ERROR AL ABRIR EL ARCHIVO");
        return;
    }

    for (int i = 0; i < db->count; i++) {
        fprintf(file, "%s\n", db->strings[i]);
    }

    fclose(file);
}



// *****************************************************************************

StringDatabase* load_strings(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("ERROR AL ABRIR EL ARCHIVO");
        return NULL;
    }

    StringDatabase *db = (StringDatabase *)malloc(sizeof(StringDatabase));
    if (!db) {
        perror("ERROR AL ASIGNAR MEMORIA");
        fclose(file);
        return NULL;
    }

    db->count = 0;
    db->strings = NULL;

    // AJUSTAR LA CANTIDAD DE CARACTERES
    char line[16];
    while (fgets(line, sizeof(line), file)) {
        // BORRAR EL SALTO DE LINEA
        line[strcspn(line, "\n")] = '\0';
        db->strings = (char **)realloc(db->strings, (db->count + 1) * sizeof(char *));
        db->strings[db->count] = strdup(line);
        db->count++;
    }

    fclose(file);
    return db;
}


int search_string(StringDatabase *db, const char *query) {
    for (int i = 0; i < db->count; i++) {
        if (strstr(db->strings[i], query)) {
            // REGRESAR EL INDICE DE LA CADENA ENCONTRADA
            return i;                   
        }
    }
    // CADENA NO ENCONTRADA
    return -1;                          
}


void free_database(StringDatabase *db) {
    for (int i = 0; i < db->count; i++) {
        free(db->strings[i]);
    }
    free(db->strings);

    /**
     * La línea free(db); libera la memoria asignada para la estructura
     * StringDatabase que fue asignada con malloc en la función load_strings.
     * La función free se utiliza para liberar la memoria que previamente se
     * asignó con malloc, calloc, o realloc.
    */

    free(db);
}


int main() {


    clock_t start, end;
    double cpu_time_used;
    
    // VARIABLE PARA EL NOMBRE DEL ARCHIVO
    char filename[100]; 
    // VARIABLE PARA LA CADENA A BUSCAR EN EL ARCHIVO
    char search_query[100]; 

    printf("Ingrese el nombre del archivo: ");
    // NOMBRE DE ARCHIVO (HASTA 99 CARACTERES)
    scanf("%99s", filename); 

    StringDatabase *db = load_strings(filename);
    if (!db) {
        return 1;
    }

    printf("Ingrese la cadena de busqueda: ");
    // CADENA A BUSCAR (HASTA 14 CARACTERES)
    scanf("%14s", search_query); 


    start = clock();

    // ORDENAR LISTA DE CADENAS
    sort_strings(db);

    // ELIMINAR CADENAS DE LONGITUD INVALIDA
    remove_invalid_lengths(db);

    // ELIMINAR CADENAS REPETIDAS
    remove_duplicates(db);
    
    // BUSCAR CADENA
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

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tiempo de operaciones: %f segundos\n", cpu_time_used);


    // GUARDAR LA LISTA DEPURADA EN UN ARCHIVO DE TEXTO
    save_strings("depurada.txt", db);
    printf("Lista depurada guardada en 'depurada.txt'\n");

    // LIBERAR MEMORIA
    free_database(db);

    // RETORNO DE FORMA EXITOSA
    return 0;
}
