#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

// Definicion de la estructura que almacenara las cadenas y su cantidad
typedef struct {
    char **strings;
    int count;
} StringDatabase;

// ---------------------------------------------------INICIA REGIoN ORDENAMIENTO

// Funcion auxiliar para intercambiar dos cadenas
void swap_strings(char **a, char **b) {
    char *temp = *a;
    *a = *b;
    *b = temp;
}

// Funcion auxiliar para dividir el arreglo y colocar el pivote en su posicion correcta
int partition(StringDatabase *db, int low, int high) {
    char *pivot = db->strings[high]; // Elegir el ultimo elemento como pivote
    int i = low - 1; // indice del elemento mas pequeño

    for (int j = low; j <= high - 1; j++) {
        if (strcmp(db->strings[j], pivot) < 0) {
            i++;
            swap_strings(&db->strings[i], &db->strings[j]);
        }
    }

    swap_strings(&db->strings[i + 1], &db->strings[high]);
    return i + 1;
}

// Funcion principal de QuickSort
void quick_sort(StringDatabase *db, int low, int high) {
    if (low < high) {
        int pivot_index = partition(db, low, high);

        // Ordenar las dos mitades separadamente
        quick_sort(db, low, pivot_index - 1);
        quick_sort(db, pivot_index + 1, high);
    }
}

// Funcion para ordenar las cadenas en la base de datos usando QuickSort
void sort_strings(StringDatabase *db) {
    quick_sort(db, 0, db->count - 1);
}

// -------------------------------------------------FINALIZA REGIoN ORDENAMIENTO



// -----------------------------------------INICIA REGIoN LIMPIEZA DE DUPLICADOS

// Funcion para eliminar cadenas duplicadas en la base de datos utilizando una tabla hash
void remove_duplicates(StringDatabase *db) {
    bool *seen = (bool *)calloc(db->count, sizeof(bool));
    if (!seen) {
        perror("ERROR AL ASIGNAR MEMORIA");
        return;
    }

    int unique_count = 0; // Contador de cadenas unicas

    for (int i = 0; i < db->count; i++) {
        if (!seen[i]) {
            seen[i] = true;
            db->strings[unique_count++] = db->strings[i];
            
            for (int j = i + 1; j < db->count; j++) {
                if (strcmp(db->strings[i], db->strings[j]) == 0) {
                    seen[j] = true;
                }
            }
        }
    }

    db->count = unique_count;

    free(seen);
}

// ---------------------------------------FINALIZA REGIoN LIMPIEZA DE DUPLICADOS



// -----------------------INICIA REGIoN LIMPIEZA DE CADENAS DE LONGITUD INVaLIDA

// Funcion para eliminar cadenas de longitud invalida en la base de datos
void remove_invalid_lengths(StringDatabase *db) {
    int valid_count = 0; // Contador de cadenas validas

    for (int i = 0; i < db->count; i++) {
        int len = strlen(db->strings[i]);
        if (len == 8 || len == 14) {
            if (i != valid_count) {
                db->strings[valid_count] = db->strings[i];
            }
            valid_count++;
        } else {
            free(db->strings[i]);
        }
    }

    db->count = valid_count;
}

// ---------------------FINALIZA REGIoN LIMPIEZA DE CADENAS DE LONGITUD INVaLIDA


// Funcion para guardar las cadenas en un archivo de texto
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

// Funcion para cargar las cadenas desde un archivo de texto
StringDatabase* load_strings(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("ERROR AL ABRIR EL ARCHIVO");
        return NULL;
    }

    // Asignar memoria para la estructura StringDatabase
    StringDatabase *db = (StringDatabase *)malloc(sizeof(StringDatabase));
    if (!db) {
        perror("ERROR AL ASIGNAR MEMORIA");
        fclose(file);
        return NULL;
    }

    db->count = 0;
    db->strings = NULL;

    char line[16];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';
        // Asignar memoria para una nueva cadena y agregarla a la base de datos
        db->strings = (char **)realloc(db->strings, (db->count + 1) * sizeof(char *));
        db->strings[db->count] = strdup(line);
        db->count++;
    }

    fclose(file);
    return db;
}

// Funcion para buscar una cadena en la base de datos
int search_string(StringDatabase *db, const char *query) {
    for (int i = 0; i < db->count; i++) {
        if (strstr(db->strings[i], query)) {
            // Devolver el indice de la cadena encontrada
            return i;
        }
    }
    // Cadena no encontrada
    return -1;
}


// Funcion para liberar la memoria utilizada por la base de datos
void free_database(StringDatabase *db) {
    for (int i = 0; i < db->count; i++) {
        free(db->strings[i]);
    }
    free(db->strings);
    free(db);
}

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
