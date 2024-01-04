#include <stdlib.h>
#include <stdio.h>

#define BUCKETS (1 << (DIGITS * SEGMENT_BITS))
#define DIGITS 4
#define SEGMENT_BITS 6
#define RAND_MAX_24BIT ((1 << 24) - 1)
#define SIZE 1000

typedef struct {
    int num;
    int d[DIGITS];
} element;

void print(element* arr) {
    for (int i = 0; i < SIZE; i++) {
        printf("%d :", arr[i].num);
        for (int j = DIGITS - 1; j >= 0; j--) {
            for (int k = SEGMENT_BITS - 1; k >= 0; k--) {
                printf("%d", (arr[i].d[j] >> k) & 1);
            }
            printf(" ");
        }
        printf("\n");
    }
}

void make_rand_number(element input[]) {
    for (int i = 0; i < SIZE; i++) {
        int num = rand() & RAND_MAX_24BIT;
        input[i].num = num;

        for (int j = 0; j < DIGITS; j++) {
            input[i].d[j] = (num >> (j * SEGMENT_BITS)) & ((1 << SEGMENT_BITS) - 1);
        }
    }
}

void counting_sort(element input[], const int numdigit, element result[]) {
    unsigned int* digit = (unsigned int*)malloc(BUCKETS * sizeof(unsigned int));

    if (digit == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < BUCKETS; i++) {
        digit[i] = 0;
    }

    for (int i = 0; i < SIZE; i++) {
        unsigned int index = 0;
        for (int j = 0; j < DIGITS; j++) {
            index |= (input[i].d[j] << (j * SEGMENT_BITS));
        }
        digit[index]++;
    }

    for (int i = 1; i < BUCKETS; i++) {
        digit[i] = digit[i] + digit[i - 1];
    }

    for (int i = SIZE - 1; i >= 0; i--) {
        unsigned int index = 0;
        for (int j = 0; j < DIGITS; j++) {
            index |= (input[i].d[j] << (j * SEGMENT_BITS));
        }
        int c_index = digit[index] - 1;
        result[c_index] = input[i];
        digit[index]--;
    }

    free(digit);
}

void radix_sort(element input[]) {
    element* result_a = (element*)malloc(SIZE * sizeof(element));
    element* result_b = (element*)malloc(SIZE * sizeof(element));

    if (result_a == NULL || result_b == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Sort from LSB to MSB
    counting_sort(input, 0, result_a);
    counting_sort(result_a, 1, result_b);
    counting_sort(result_b, 2, result_a);
    counting_sort(result_a, 3, result_b);

    printf("Sorted Data:\n");
    print(result_b);

    free(result_a);
    free(result_b);
}

int main() {
    element input[SIZE];
    make_rand_number(input);

    printf("Original Data:\n");
    print(input);
    printf("=========================================================\n");

    radix_sort(input);

    return 0;
}
