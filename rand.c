/*
    Scott Bouloutian
    2/14/15

    This program is used to generate a file containing
    a given number of random integers.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void writeFile(char *, int);

int main(int argc, char *argv[]) {
    // Parse command line arguments
    if(argc == 3) {
        int n = atoi(argv[2]);
        printf("Generating %d random integers...\n",n);
        writeFile(argv[1], n);
        printf("...finished generating the integers.\n");
    } else {
        printf("Proper command line arguments not specified.\n");
    }
}

void writeFile(char *fileName, int n) {
    // Open the file and check that it opened correctly
    FILE *f = fopen(fileName, "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    // Seed the random number generator
    srand(time(NULL));

    // Print random numbers to the file
    int i;
    for(i=0;i<n;i++) {
        int r = rand();
        fprintf(f, "%d\n", r);
    }

    // Close the file
    fclose(f);
}
