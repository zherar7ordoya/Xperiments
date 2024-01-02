#include <stdio.h> //imports int printf(...);

void print(const char* text)
{
    printf(text);
}

typedef struct 
{
    void (*Print) (const char*);
} class;

class Printer()
{
    class Printer;
    Printer.Print = &print;
    return Printer;
}