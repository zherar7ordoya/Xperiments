/**
 * @file string_utils.c
 * @brief Contiene las definiciones de funciones para operaciones de cadenas.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "string_utils.h"

// Función auxiliar para intercambiar dos cadenas
void swap_strings(char **a, char **b) {
    char *temp = *a;
    *a = *b;
    *b = temp;
}

// Función auxiliar para dividir el arreglo y colocar el pivote en su posición correcta
int partition(StringDatabase *db, int low, int high) {
    char *pivot = db->strings[high]; // Elegir el último elemento como pivote
    int i = low - 1; // índice del elemento más pequeño

    for (int j = low; j <= high - 1; j++) {
        if (strcmp(db->strings[j], pivot) < 0) {
            i++;
            swap_strings(&db->strings[i], &db->strings[j]);
        }
    }

    swap_strings(&db->strings[i + 1], &db->strings[high]);
    return i + 1;
}

// Función principal de QuickSort
void quick_sort(StringDatabase *db, int low, int high) {
    if (low < high) {
        int pivot_index = partition(db, low, high);

        // Ordenar las dos mitades separadamente
        quick_sort(db, low, pivot_index - 1);
        quick_sort(db, pivot_index + 1, high);
    }
}

// Función para ordenar las cadenas en la base de datos usando QuickSort
void sort_strings(StringDatabase *db) {
    quick_sort(db, 0, db->count - 1);
}

// Función para eliminar cadenas duplicadas en la base de datos utilizando una tabla hash
void remove_duplicates(StringDatabase *db) {
    bool *seen = (bool *)calloc(db->count, sizeof(bool));
    if (!seen) {
        perror("ERROR AL ASIGNAR MEMORIA");
        return;
    }

    int unique_count = 0; // Contador de cadenas únicas

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

// Función para eliminar cadenas de longitud inválida en la base de datos
void remove_invalid_lengths(StringDatabase *db) {
    int valid_count = 0; // Contador de cadenas válidas

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

// Función para guardar las cadenas en un archivo de texto
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

// Función para cargar las cadenas desde un archivo de texto
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

// Función para buscar una cadena en la base de datos
int search_string(StringDatabase *db, const char *query) {
    for (int i = 0; i < db->count; i++) {
        if (strcmp(db->strings[i], query) == 0) {
            // Devolver el indice de la cadena encontrada
            return i;
        }
    }
    // Cadena no encontrada
    return -1;
}

// Función para liberar la memoria utilizada por la base de datos
void free_database(StringDatabase *db) {
    for (int i = 0; i < db->count; i++) {
        free(db->strings[i]);
    }
    free(db->strings);
    free(db);
}
