#include "helper.h"

// ***************************************************************************
// Description: Does C have classes? C doesn't support classes, but we do have
//              tricky hacky workaround.
// Create Date: 2023-08-15
// Update Date: 2023-08-15
// Developer/s: Gerardo Tordoya
// Forked from: https://stackoverflow.com/a/68770306/14009797
// ***************************************************************************

void main()
{
    class printer1 = Printer();
    printer1.Print("Hello from class function");
}