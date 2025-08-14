#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

int roll() {
    return rand() % 6 + 1;
}

int main() {
    srand(time(NULL));
    
    int* cont = malloc(sizeof(int));
    if (cont == NULL) {
        perror("Failed to allocate memory");
        return 1;
    }
    cont[0] = roll();
    int cont_size = 1;
    const int* pAddressOfOriginalBegin = &cont[0];

    struct timeval start, end;
    double durTime = 0.0;

    while (getc(stdin)) {
        const int* pAddressBegin = &cont[0];

        printf("Contain %d elements, took %.0f us\n", 
               cont_size, durTime * 1000000); 

        for (int i = 0; i < cont_size; i++) {
            const int* pAddressOfX = &cont[i];
            int OffsetFromCurrent = pAddressOfX - pAddressBegin;
            int OffsetFromBegin = pAddressOfX - pAddressOfOriginalBegin;
            printf("OffsetFromCurrent - %d  OffsetFromBegin - %d\n", 
                   OffsetFromCurrent, OffsetFromBegin);
        }

        gettimeofday(&start, NULL);
        int* temp = realloc(cont, (cont_size + 1) * sizeof(int));
        if (temp == NULL) {
            perror("Failed to reallocate memory");
            free(cont);
            return 1;
        }
        cont = temp;
        cont[cont_size] = roll();
        cont_size++;
        gettimeofday(&end, NULL);

        durTime = (end.tv_sec - start.tv_sec) + 
                 (end.tv_usec - start.tv_usec) / 1000000.0;
    }

    free(cont);
    return 0;
}