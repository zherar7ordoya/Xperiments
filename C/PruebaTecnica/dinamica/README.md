# Crear la biblioteca dinámica (DLL)

## En Windows

```bash
gcc -shared -o string_utils.dll string_utils.c -D BUILD_DLL
```

## En Linux

```bash
gcc -shared -o string_utils.so string_utils.c
```

# Crear el ejecutable

## En Windows

```bash
gcc main.c -o main.exe -I. -L. -lstring_utils
```

## En Linux

```bash
gcc main.c -o main -I. -L. -lstring_utils -Wl,-rpath=.
```

# Ejecutar el programa

En Windows, string_utils.dll debe estar en la misma ubicación que el ejecutable o en una ubicación en la variable de entorno PATH.
En Linux, la biblioteca compartida debe estar en la variable de entorno LD_LIBRARY_PATH o en una ruta conocida por el sistema.
