#include<stdio.h>
void findMax (int *max, int a){
    if(a > *max){
        *max = a;
    }
}
int main(){
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];
    for(int i = 0; i < n; i++){
        printf("Enter element %d: ", i + 1);
        scanf("%d", &arr[i]);
    }
    int max = arr[0];
    for(int i = 1; i < n; i++){ 
        findMax(&max, arr[i]); // &max is the address of max
    }
    
    printf("The maximum value is: %d\n", max);
    return 0;
}