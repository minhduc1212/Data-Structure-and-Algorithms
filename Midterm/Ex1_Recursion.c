#include <stdio.h>


int find_third_num(int arr[], int arr_pow[], int n, int sum_pow, int i, int k, int j)
{
    if (j >= n)
        return -1;

    if (sum_pow == arr_pow[j] && arr[i] != arr[j] && arr[k] != arr[j]) {
        printf("The array forms a Pythagorean triplet: %d, %d, %d\n", arr[i], arr[k], arr[j]);
    }

    return find_third_num(arr, arr_pow, n, sum_pow, i, k, j + 1);
}

int find_sec_num(int arr[], int arr_pow[], int n, int i, int k)
{
    if (i >= n)
        return -1;

    int sum_pow = arr_pow[i] + arr_pow[k];
    int third_num = find_third_num(arr, arr_pow, n, sum_pow, i, k, 0);
    return find_sec_num(arr, arr_pow, n, i + 1, k);
}


int main()
{
    int arr[6] = {3, 4, 5, 6, 8, 10};
    int max = arr[0];
    int sum_pow = 0;
    int arr_pow[6];
    for (int i = 0; i < 6; i++)
    {
        arr_pow[i] = arr[i] * arr[i];
        
    }
    for (int i = 0; i < 6; i++)
    {
        find_sec_num(arr, arr_pow, 6, 0, i);
    }

   

    return 0;
}