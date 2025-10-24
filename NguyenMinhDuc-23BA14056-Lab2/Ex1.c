#include <stdio.h>

typedef struct UnboundedInt {
    int digits[100];
    int count;           
} UnboundedInt;

void create_unbounded_int(UnboundedInt *num, const char *str_num) {
    int i = 0;

    if (str_num[0] == '-') {
        num->digits[0] = -1;
        i = 1; 
    } else {
        num->digits[0] = 1;
        i = 0;
    }

    num->count = 0;
    while (str_num[i] != '\0') {
        num->digits[num->count + 1] = str_num[i] - '0';
        num->count++;
        i++;
    }
}

void display_unbounded_int(UnboundedInt *num) {
    if (num->count == 0) {
        printf("0\n");
        return;
    }

    if (num->digits[0] == -1) {
        printf("-");
    }

    for (int i = 1; i <= num->count; i++) {
        printf("%d", num->digits[i]);
    }
    printf("\n");
}


void add_digit(UnboundedInt *num, int digit, int pos) {
    if (pos < 1 || pos > num->count + 1) {
        printf("Vi tri them khong hop le!\n");
        return;
    }

    for (int i = num->count; i >= pos; i--) {
        num->digits[i + 1] = num->digits[i];
    }

    num->digits[pos] = digit;
    num->count++;
}
void remove_digit(UnboundedInt *num, int pos) {
    if (pos < 1 || pos > num->count) {
        printf("Vi tri xoa khong hop le!\n");
        return;
    }

    for (int i = pos; i < num->count; i++) {
        num->digits[i] = num->digits[i + 1];
    }

    num->count--;
}
int sum_of_digits(UnboundedInt *num) {
    int sum = 0;
    for (int i = 1; i <= num->count; i++) {
        sum += num->digits[i];
    }
    return sum;
}

int main() {
    UnboundedInt my_num;

    printf("Create unbouned int: -1593\n");
    create_unbounded_int(&my_num, "-1593");
    printf("The number is: ");
    display_unbounded_int(&my_num);
    printf("\n");

    printf("Add 0 to number:\n");
    add_digit(&my_num, 0, 3);
    printf("The new num is: ");
    display_unbounded_int(&my_num); 
    printf("\n");


    printf("Delete the forth digit\n");
    remove_digit(&my_num, 4);
    printf("The new num is: ");
    display_unbounded_int(&my_num); 
    printf("\n");


    printf("The sum of ");
    int sum = sum_of_digits(&my_num);
    display_unbounded_int(&my_num);
    printf("is ");
    printf("%d\n", sum); 
    

    return 0;
}