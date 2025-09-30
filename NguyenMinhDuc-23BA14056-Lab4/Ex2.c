#include<stdio.h>
#include<stdbool.h>


bool check_sphenic_rec(int n, int i, int *count){
    if (n == 1){
        (*count)++;
    } 
    if (*count > 3){
        return false;
    }

    if (i * i > n){
        (*count)++; 
        return (*count == 3);
    }
    if (n % i == 0){
        if (n/i % i == 0){
            return false;
        }
        (*count)++;
        return check_sphenic_rec(n/i, i+1, count);
    }else{
        return check_sphenic_rec(n, i+1, count);
    }
    return (*count == 3);

}


int main(){
    int a = 66;
    int i = 2;
    int count = 0;
    if (a <30){
        printf("%d is not a sphenic number\n", a);
    }
    else{
        if (check_sphenic_rec(a, i, &count)){
            printf("%d is a sphenic number\n", a);
        }
        else{
            printf("%d is not a sphenic number\n", a);
        }
    }

}