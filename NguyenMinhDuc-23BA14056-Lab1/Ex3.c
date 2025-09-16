#include <stdio.h>

struct complex{
  int real;
  int image;
} ;


typedef struct complex complex;

complex add(complex n1, complex n2){
  complex sum;
  sum.real = n1.real + n2.real;
  sum.image = n1.image + n2.image;
  return sum;
}

complex multi(complex n1, complex n2){
  complex mul;
  mul.real = n1.real * n2.real - n1.image * n2.image;
  mul.image = n1.real * n2.image + n1.image * n2.real;
  return mul;
}


int main(){
  complex n1, n2, sum, mul;
  n1.real = 5;
  n1.image = 4;
  n2.real = 3;
  n2.image = 2;

  sum = add(n1, n2);

  mul = multi(n1, n2);

  printf("The sum of 2 complex number is: %d + %di \n", sum.real, sum.image);

  printf("The multiplication of 2 complex number is: %d + %di", mul.real, mul.image);

}