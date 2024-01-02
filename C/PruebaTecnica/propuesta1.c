#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char **strings;
    int count;
} StringDatabase;


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
    free(db);
}


int main() {
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

    printf("Ingrese la cadena de búsqueda: ");
    // CADENA A BUSCAR (HASTA 14 CARACTERES)
    scanf("%14s", search_query); 

    int index = search_string(db, search_query);
    if (index != -1) {
        printf("Cadena encontrada en el índice %d: %s\n", index + 1, db->strings[index]);
    } else {
        printf("Cadena no encontrada.\n");
    }

    free_database(db);
    return 0;
}
