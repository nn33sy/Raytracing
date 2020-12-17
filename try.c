#include <stdio.h>
#include <time.h>
#include <stdlib.h>

double get_random() { return ((double)rand() / (double)RAND_MAX); }

double generate_nb()
{
    double n = 0;
    srand(time(NULL)); // randomize seed
    n = get_random()
    return (n);
}