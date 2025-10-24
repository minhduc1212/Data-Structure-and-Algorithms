#include<stdio.h>#include<stdlib.h>

// Function to flip (reverse) a subarray from index 0 to i
void flip(int arr[], int i) {
    int start = 0;
    while (start < i) {
        int temp = arr[start];
        arr[start] = arr[i];
        arr[i] = temp;
        start++;
        i--;
    }
}

// Function to find the index of the maximum element in a subarray arr[0...n-1]
int findMax(int arr[], int n) {
    int mi = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > arr[mi]) {
            mi = i;
        }
    }
    return mi;
}

// The main function that sorts the given array using pancake sort
void pancakeSort(int arr[], int n) {
    // Start from the complete array and one by one reduce current size
    for (int curr_size = n; curr_size > 1; --curr_size) {
        // Find index of the maximum element in arr[0...curr_size-1]
        int mi = findMax(arr, curr_size);

        // Move the maximum element to the end of current array if it's not already there
        if (mi != curr_size - 1) {
            // To move at the end, first move the maximum number to the beginning
            flip(arr, mi);

            // Now move the maximum number to the end by flipping the whole current array
            flip(arr, curr_size - 1);
        }
    }
}

// A utility function to print an array of size n
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {3, 2, 4, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: \n");
    printArray(arr, n);

    pancakeSort(arr, n);

    printf("Sorted array: \n");
    printArray(arr, n);

    return 0;
}
