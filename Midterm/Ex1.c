#include <stdio.h>
#include <math.h>
#include <stdbool.h>

// Helper function for integer exponentiation to avoid floating-point issues.
int int_pow(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}


bool check_armstrong_num(int num)
{
    // Handle non-positive numbers
    if (num <= 0) {
        return false;
    }
    int original_num, remainder, result = 0, n = 0;
    original_num = num; // Use a copy to find the number of digits

    while (original_num != 0) {
        original_num /= 10;
        ++n;
    }

    original_num = num;
    
    while (original_num != 0) {
        remainder = original_num % 10;
        result += int_pow(remainder, n);
        original_num /= 10;
    }

    return (result == num);
}

// Recursive helper function to calculate the sum of powers of digits.
int armstrong_sum_rec(int num, int n)
{
    if (num == 0)
        return 0; // Base case for the sum is 0.
    int remainder = num % 10;
    return int_pow(remainder, n) + armstrong_sum_rec(num / 10, n);
}

// Main recursive function to check for an Armstrong number.
bool check_armstrong_num_rec(int num)
{
    if (num <= 0) {
        return false;
    }
    // First, find the number of digits.
    int n = 0;
    int temp = num;
    while (temp != 0) {
        temp /= 10;
        ++n;
    }
    // Then, compare the number with the recursive sum.
    return num == armstrong_sum_rec(num, n);
}

int main ()
{
    int num = 153;
    printf("--- Iterative Check ---\n");
    if (check_armstrong_num(num))
        printf("%d is an Armstrong number.\n", num);
    else
        printf("%d is not an Armstrong number.\n", num);

    printf("\n--- Recursive Check ---\n");
    if (check_armstrong_num_rec(num))
        printf("%d is an Armstrong number.\n", num);
    else
        printf("%d is not an Armstrong number.\n", num);
    
    return 0;
}


/*
The complexity of code is 

*/