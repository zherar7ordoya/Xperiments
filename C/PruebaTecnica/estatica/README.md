# Compilar la biblioteca estática

```bash	
gcc -c string_utils.c -o string_utils.o
ar rcs libstring_utils.a string_utils.o
```

# Compilar el programa principal

```bash
gcc main.c -o main -L. -lstring_utils
```
