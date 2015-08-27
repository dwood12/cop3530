/**
    Input generator for the Search Problem

    Commands:
        $g++ input-gen.cpp -o generator
        $./generator 1000000 100 > input-1m.in


**/

#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char *argv[])
{
    int NE;  // number of elements
    int NS;  // number of element to search
    if (argc != 3)
    {
        printf("<usage>: parameters.\n");
        return 1;
    }
    else
    {
        NE = atoi(argv[1]);
        NS = atoi(argv[2]);
        //printf("Number of elements = %d\nNumber of elements to search = %d\n", NE, NS);
    }

    // Initializing seed for pseudo-random sequence
    srand(time(NULL));

    printf("%d %d\n", NE, NS);
    for (int i=1; i<=NE; i++)
    {
        int number;

        number = rand();
        // coin toss
        double r = ((double) rand() / (RAND_MAX));

        if (r < 0.05)           // Introducing neg. numbers with 5% probability
            number = - number;
        printf("%d ", number);

        if (!(i % 100)) printf("\n");
    }
    printf("\n");
    for (int i=1; i<=NS; i++)
    {
        int number;

        number = rand();
        // coin toss
        double r = ((double) rand() / (RAND_MAX));

        if (r < 0.05)           // Introducing neg. numbers with 5% probability
            number = - number;
        printf("%d ", number);

        if (!(i % 100)) printf("\n");
    }

    return 0;
}
