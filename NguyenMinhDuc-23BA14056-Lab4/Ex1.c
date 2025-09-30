#include<stdio.h>

int sum_iter(int n)
{
    int sum = 0;
    while (n > 0)
    {
        sum += n % 10;
        n = n / 10;
    }
    return sum;
}


int sum_rec(int n){
    if (n == 0){
        return 0;
    }
    else{
        return (n % 10 + sum_rec(n / 10));
    }
}

int main()
{
    int a = 1798;
    int sum = sum_iter(a);
    printf("Sum of digits (iterative) of %d is: %d\n", a, sum);
    sum = sum_rec(a);
    printf("Sum of digits (recursive) of %d is: %d\n", a, sum);

}