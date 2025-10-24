#include<stdio.h>

int fib_rec(int n){
    if (n <= 1){
        return n;
    }
    else{
        return fib_rec(n-1) + fib_rec(n-2);
    }
}


int fib_iter(int n){
    int a = 0;
    int b = 1;
    int c;
    for (int i = 2; i <= n; i++){
        c = a + b;
        a = b;
        b = c;
    }
    return c;
}

int main (){
    int n = 8;
    int fib = fib_rec(n);
    printf("The %dth Fibonacci number is: %d\n", n, fib);


    int fib2 = fib_iter(n);
    printf("The %dth Fibonacci number is: %d\n", n, fib2);

}