#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define COLUMNS 6

void print_number(int n) {
    static int count = 0;
    printf("%10d", n);
    count++;
    if (count == COLUMNS) {
        printf("\n");
        count = 0;
    }
}

int find_prime_at_position(int position) {
    if (position <= 0) {
        printf("Invalid position. Please enter a positive integer.\n");
        return -1;
    }

    int count = 0;
    int num = 2;

    while (count < position) {
        bool is_prime = true;

        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) {
                is_prime = false;
                break;
            }
        }

        if (is_prime) {
            count++;
            if (count == position) {
                return num;
            }
        }

        num++;
    }

    return -1; // In case something unexpected happens
}

void print_prime_at_position(int position) {
    int prime = find_prime_at_position(position);

    if (prime != -1) {
        printf("Prime number at position %d: %d\n", position, prime);
    }
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        int position = atoi(argv[1]);
        print_prime_at_position(position);
    } else {
        printf("Please provide a position to find the prime number.\n");
    }

    return 0;
}
