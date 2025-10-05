#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Car{
    int max_passengers;
    int num_passengers;
    char type[50];
    struct Car *next;
} Car;

typedef struct Train{
    int size;
    Car *head;
} Train;

void createCar(Car* car, int max_passengers, char* type, int num_passengers){
    car->max_passengers = max_passengers;
    strcpy(car->type, type);
    car->num_passengers = num_passengers;
    car->next = NULL;
}

void createTrain(Train* list){
    list->size = 0;
    list->head = NULL;
}


//add car to the end of the list
void addCar(Train* list, char* type, int max_passengers, int num_passengers){
    Car* newCar = (Car*)malloc(sizeof(Car));
    strcpy(newCar->type, type);
    newCar->max_passengers = max_passengers;
    newCar->num_passengers = num_passengers;
    newCar->next = NULL;

    if(list->head == NULL){
        list->head = newCar;
    }else{
        Car*temp = list->head;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newCar;
    }
    list->size++;
    printf("Added car: %s with max passengers: %d and current passengers: %d\n", type, max_passengers, num_passengers);
    
}


void removeEmptyCar(Train* list){
    Car* temp = list->head;
    Car* prev = NULL;   
    printf("\n--- Checking and removing empty cars... ---\n");
    while(temp != NULL){
        if(temp->num_passengers == 0){
            if(prev == NULL){
                list->head = temp->next;
            }else{
                prev->next = temp->next;
            }
            free(temp);
            list->size--;
            printf("Removed an empty car.\n");
            if(prev == NULL){
                temp = list->head;
            }else{
                temp = prev->next;
            }
        }else{
            prev = temp;
            temp = temp->next;
        }
    }
}

void printCar(Car* car){
    printf("Car Type: %s\n", car->type);
    printf("Max Passengers: %d\n", car->max_passengers);
    printf("\n");
}

void printTrain(Train* list){
    Car* temp = list->head;
    while(temp != NULL){
        printCar(temp);
        temp = temp->next;
    }
}


void destroyTrain(Train* list) {
    Car* current = list->head;
    Car* nextCar;
    while (current != NULL) {
        nextCar = current->next; // Lưu lại node tiếp theo
        free(current);           // Giải phóng node hiện tại
        current = nextCar;       // Di chuyển tới node tiếp theo
    }
    list->head = NULL; // Tránh con trỏ trỏ lung tung
    list->size = 0;
}

int main(){
    Train carList;
    createTrain(&carList);

    Car car1, car2, car3;
    addCar(&carList, "Passenger", 100, 50);
    addCar(&carList, "Cargo", 200, 0);
    addCar(&carList, "Passenger", 150, 0);

    printTrain(&carList);

    removeEmptyCar(&carList);

    printTrain(&carList);

    removeEmptyCar(&carList);

    printTrain(&carList);
    destroyTrain(&carList);

    return 0;
}