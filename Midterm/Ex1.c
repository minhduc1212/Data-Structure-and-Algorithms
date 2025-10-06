#include<stdio.h>

int main(){
    int arr[6] = {3, 5, 6, 4, 8, 10};
    int max = arr[0];
    int sum_pow = 0;
    int arr_pow[6];
    for (int i = 0; i < 6; i++)
    {
        arr_pow[i] = arr[i] * arr[i];
        
    }
    for (int i = 0; i < 6; i++)
    {   
        for (int k = i + 1; k < 6; k++)
        {
            sum_pow = arr_pow[i] + arr_pow[k];
            for (int j = 0; j < 6; j++)
            {
                if (sum_pow == arr_pow[j] && arr[i] != arr[j] && arr[k] != arr[j])
                {
                    printf("The array forms a Pythagorean triplet: %d, %d, %d\n", arr[i], arr[k], arr[j]);
                }
            }
        }

    }
    return 0;
}