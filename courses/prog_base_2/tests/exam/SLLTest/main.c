#include <stdio.h>
#include <stdlib.h>
#include "parking.h"

int main()
{
    parking_t * parking=parking_new();
    parking_addNote(parking, AUTO_IN);
    parking_addNote(parking, AUTO_OUT);
    parking_addNote(parking, AUTO_IN);
    parking_addNote(parking, AUTO_OUT);
    parking_getNotes(parking);

    return 0;
}
