/*
 PSEUDOCODE:
FUNCTION is_sphenic(n):
    count = 0
FOR each distinct prime factor p of n:
    count = count + 1
RETURN (count == 3)

COMPLEXITY:
    - Time Complexity: O(sqrt(n))
 The main loop runs up to the square root of n, which is i * i <= n
*/

#include <stdio.h>
#include <math.h>
#include <stdbool.h> 


bool is_sphenic(int n) {
    if (n < 30) {     // The smallest sphenic number is 30 (2*3*5)
        return false;
    }

    int distinct_prime_factors_count = 0;

    if (n % 2 == 0) {
        distinct_prime_factors_count++;
        while (n % 2 == 0) {
            n /= 2;
        }
    }

    for (int i = 3; i * i <= n; i += 2) { // Check for odd factors because even factors are already checked above (all even numbers have 2 as a factor)
        if (n % i == 0) {     // i is always a prime factor because the non prime factors would have been divided out by smaller primes already. For example, if 9 is a factor, it would have been divided out by 3 already or 15 would have been divided out by 3 and 5 already
            distinct_prime_factors_count++;
            if (distinct_prime_factors_count > 3) {
                 return false;
            }
            while (n % i == 0) {
                n /= i;
            }
        }
    }

    if (n > 1) {
        distinct_prime_factors_count++;
    }

    return (distinct_prime_factors_count == 3);
}


int main() {
    int n;
    printf("enter a natural number n: ");
    
    if (scanf("%d", &n) != 1) {
        printf("Invalid input. Please run again and enter an integer.\n");
        return 1;
    }

    if (n <= 0) {
        printf("Please enter a natural number greater than 0.\n");
    } else {
        if (is_sphenic(n)) {
            printf("%d is a sphenic number.\n", n);
        } else {
            printf("%d is not a sphenic number.\n", n);
        }
    }

    return 0;
}