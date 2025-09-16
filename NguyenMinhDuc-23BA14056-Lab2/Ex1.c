#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct to represent an unbounded integer using a dynamic array
typedef struct {
    int sign;          // 1 for positive, -1 for negative
    int* digits;       // Pointer to the dynamic array of digits
    size_t size;       // Current number of digits
    size_t capacity;   // Allocated capacity of the array
} UnboundedInteger;

// Function to create and initialize an UnboundedInteger
UnboundedInteger* createUnboundedInteger(int sign, const int* initial_digits, size_t num_digits) {
    // Allocate memory for the struct itself
    UnboundedInteger* u_int = (UnboundedInteger*)malloc(sizeof(UnboundedInteger));
    if (!u_int) {
        perror("Failed to allocate UnboundedInteger");
        return NULL;
    }

    // Set sign
    u_int->sign = (sign == -1) ? -1 : 1;

    // Set size and initial capacity
    u_int->size = num_digits;
    u_int->capacity = (num_digits > 0) ? num_digits * 2 : 10; // Start with some capacity

    // Allocate memory for the digits
    u_int->digits = (int*)malloc(u_int->capacity * sizeof(int));
    if (!u_int->digits) {
        perror("Failed to allocate digits array");
        free(u_int);
        return NULL;
    }

    // Copy initial digits
    for (size_t i = 0; i < num_digits; ++i) {
        if (initial_digits[i] >= 0 && initial_digits[i] <= 9) {
            u_int->digits[i] = initial_digits[i];
        } else {
            // Handle invalid digit input
            fprintf(stderr, "Error: Invalid digit %d provided.\n", initial_digits[i]);
            free(u_int->digits);
            free(u_int);
            return NULL;
        }
    }

    return u_int;
}

// Function to free the memory used by an UnboundedInteger
void freeUnboundedInteger(UnboundedInteger* u_int) {
    if (u_int) {
        free(u_int->digits); // Free the digits array first
        free(u_int);         // Then free the struct
    }
}

// Adds a new digit at a specific position (1-based index)
void addDigit(UnboundedInteger* u_int, int digit, size_t position) {
    if (digit < 0 || digit > 9) {
        printf("Error: Invalid digit. Must be between 0 and 9.\n");
        return;
    }
    // Position 1 means at the beginning, position size+1 means at the end
    if (position < 1 || position > u_int->size + 1) {
        printf("Error: Invalid position.\n");
        return;
    }
    size_t index = position - 1; // Convert to 0-based index

    // Check if we need to resize the array
    if (u_int->size >= u_int->capacity) {
        size_t new_capacity = u_int->capacity * 2;
        int* new_digits = (int*)realloc(u_int->digits, new_capacity * sizeof(int));
        if (!new_digits) {
            perror("Failed to reallocate memory for digits");
            return;
        }
        u_int->digits = new_digits;
        u_int->capacity = new_capacity;
    }

    // Shift elements to the right to make space for the new digit
    // Use memmove for safe overlapping memory operations
    memmove(&u_int->digits[index + 1], &u_int->digits[index], (u_int->size - index) * sizeof(int));

    // Insert the new digit
    u_int->digits[index] = digit;
    u_int->size++;
}

// Removes a digit at a specific position (1-based index)
void removeDigit(UnboundedInteger* u_int, size_t position) {
    if (u_int->size == 0 || position < 1 || position > u_int->size) {
        printf("Error: Invalid position or empty number.\n");
        return;
    }
    size_t index = position - 1; // Convert to 0-based index

    // Shift elements to the left to overwrite the removed digit
    memmove(&u_int->digits[index], &u_int->digits[index + 1], (u_int->size - index - 1) * sizeof(int));
    u_int->size--;
}

// Calculates the sum of all digits
int sumOfDigits(const UnboundedInteger* u_int) {
    int sum = 0;
    for (size_t i = 0; i < u_int->size; ++i) {
        sum += u_int->digits[i];
    }
    return sum;
}

// Displays the whole number on the screen
void display(const UnboundedInteger* u_int) {
    if (u_int->size == 0) {
        printf("0\n");
        return;
    }
    if (u_int->sign == -1) {
        printf("-");
    }
    for (size_t i = 0; i < u_int->size; ++i) {
        printf("%d", u_int->digits[i]);
    }
    printf("\n");
}

int main() {
    printf("--- Exercise 1: Unbounded Integers ---\n");
    int initial_digits[] = {1, 2, 3, 4, 5};
    size_t num_digits = sizeof(initial_digits) / sizeof(initial_digits[0]);

    UnboundedInteger* myInt = createUnboundedInteger(1, initial_digits, num_digits);
    if (!myInt) return 1;

    printf("Initial number: ");
    display(myInt);

    printf("Sum of digits: %d\n", sumOfDigits(myInt));

    // Add 9 at position 3 (between 2 and 3)
    addDigit(myInt, 9, 3);
    printf("After adding 9 at position 3: ");
    display(myInt);

    // Remove digit at position 2 (the '2')
    removeDigit(myInt, 2);
    printf("After removing digit at position 2: ");
    display(myInt);

    printf("Final sum of digits: %d\n", sumOfDigits(myInt));

    freeUnboundedInteger(myInt); // Clean up memory
    printf("\n");
    return 0;
}