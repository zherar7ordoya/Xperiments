/**
 * @file string_utils.h
 * @brief Contiene las declaraciones de funciones y estructuras para operaciones de cadenas.
 */

#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <stdbool.h>

#ifdef _WIN32
    #ifdef BUILD_DLL
        #define DLL_EXPORT __declspec(dllexport)
    #else
        #define DLL_EXPORT __declspec(dllimport)
    #endif
#else
    #define DLL_EXPORT
#endif

/**
 * @struct StringDatabase
 * @brief Estructura para almacenar un conjunto de cadenas y su cantidad.
 */
typedef struct {
    char **strings; /**< Puntero a un arreglo de cadenas */
    int count;      /**< Cantidad de cadenas en el arreglo */
} StringDatabase;

/**
 * @brief Ordena las cadenas almacenadas en una base de datos de cadenas.
 * @param db Puntero a la base de datos de cadenas.
 */
DLL_EXPORT void sort_strings(StringDatabase *db);

/**
 * @brief Elimina cadenas duplicadas en una base de datos de cadenas.
 * @param db Puntero a la base de datos de cadenas.
 */
DLL_EXPORT void remove_duplicates(StringDatabase *db);

/**
 * @brief Elimina cadenas de longitud inválida en una base de datos de cadenas.
 * @param db Puntero a la base de datos de cadenas.
 */
DLL_EXPORT void remove_invalid_lengths(StringDatabase *db);

/**
 * @brief Guarda las cadenas en un archivo de texto.
 * @param filename Nombre del archivo de destino.
 * @param db Puntero a la base de datos de cadenas.
 */
DLL_EXPORT void save_strings(const char *filename, StringDatabase *db);

/**
 * @brief Carga las cadenas desde un archivo de texto.
 * @param filename Nombre del archivo a cargar.
 * @return Puntero a la base de datos de cadenas cargada.
 */
DLL_EXPORT StringDatabase* load_strings(const char *filename);

/**
 * @brief Busca una cadena en una base de datos de cadenas.
 * @param db Puntero a la base de datos de cadenas.
 * @param query Cadena a buscar.
 * @return Índice de la cadena encontrada o -1 si no se encuentra.
 */
DLL_EXPORT int search_string(StringDatabase *db, const char *query);

/**
 * @brief Libera la memoria utilizada por una base de datos de cadenas.
 * @param db Puntero a la base de datos de cadenas.
 */
DLL_EXPORT void free_database(StringDatabase *db);

#endif
