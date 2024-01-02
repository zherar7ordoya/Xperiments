// gcc -o main main.c ../../libreria/src/libreria.c ../../libreria/src/traza.c pcsc.c

#include <stdio.h>
#include <stdlib.h>

int main() {

    char choice;
    
    while (1) {
        // Limpiar la pantalla
        #if defined(_WIN32)
			system("cls");
		#elif defined(__linux__)
			system("clear");
		#endif
        
        // Encabezado
        printf("***********************\n");
        printf("*    MENU PRINCIPAL   *\n");
        printf("***********************\n\n");
        
        // Mostrar opciones
        printf("1. Opcion 1\n");
        printf("2. Opcion 2\n");
        printf("3. Opcion 3\n");
        printf("4. Salir\n\n");
        
        // Solicitar entrada al usuario
        printf("Seleccione una opcion: ");
        scanf(" %c", &choice);
        
        // Limpiar el búfer del teclado
        while (getchar() != '\n');
        
        // Procesar la selección del usuario
        switch (choice) {
            case '1':
                printf("Ha seleccionado la opcion 1.\n");
                break;
            case '2':
                printf("Ha seleccionado la opcion 2.\n");
                break;
            case '3':
                printf("Ha seleccionado la opcion 3.\n");
                break;
            case '4':
                printf("Saliendo del programa...\n");
                return 0;
            default:
                printf("Por favor, elija una opcion valida.\n");
                break;
        }
        // Esperar a que el usuario presione Enter para continuar
        printf("\nPresione Enter para continuar...");
        getchar();
    }
    return 0;
}
