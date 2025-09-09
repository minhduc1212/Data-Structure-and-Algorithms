/*

*/
#include <stdio.h>

int main() {
    int n, theFirst, theLast, thePow = 1, theMid, theSwap, temp;
    printf("Enter a positive integer: ");
    scanf("%d", &n);

    theLast = n % 10;
    temp = n;
    while (temp >= 10) {
        temp /= 10;
        thePow *= 10;
    }
    theFirst = temp;
    theMid = (n / 10) % (thePow / 10);
    theSwap = theLast * thePow + theMid * 10 + theFirst;
    printf("The number after swapping the first and last digits is: %d\n", theSwap);
    
    return 0;
}