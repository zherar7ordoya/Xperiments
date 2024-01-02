#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <stdbool.h>

// Definición de la estructura que almacenará las cadenas y su cantidad
typedef struct {
    char **strings;
    int count;
} StringDatabase;

void sort_strings(StringDatabase *db);
void remove_duplicates(StringDatabase *db);
void remove_invalid_lengths(StringDatabase *db);
void save_strings(const char *filename, StringDatabase *db);
StringDatabase* load_strings(const char *filename);
int search_string(StringDatabase *db, const char *query);
void free_database(StringDatabase *db);

#endif
