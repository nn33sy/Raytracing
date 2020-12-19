#include <stdio.h>
#include <time.h>
#include <stdlib.h>

double get_random() { return ((double)rand() / (double)RAND_MAX); }

double generate_nb()
{
    double n = 0;
    srand(time(NULL)); // randomize seed
    n = get_random();
    if (n > 0.9 || n < 0.1)
        return(-n);
    return (n);
}
int main()
{
    printf("%f",generate_nb());
}