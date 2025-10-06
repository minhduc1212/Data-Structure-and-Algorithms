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

void createTrain(Train* list){
    list->size = 0;
    list->head = NULL;
}

// Thêm toa vào cuối đoàn tàu
void addCar(Train* list, const char* type, int max_passengers, int num_passengers){
    if (num_passengers > max_passengers) {
        printf("Error: Cannot add car '%s'. Number of passengers (%d) exceeds capacity (%d).\n", type, num_passengers, max_passengers);
        return;
    }
    
    Car* newCar = (Car*)malloc(sizeof(Car));
    if (newCar == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    strcpy(newCar->type, type);
    newCar->max_passengers = max_passengers;
    newCar->num_passengers = num_passengers;
    newCar->next = NULL;

    if(list->head == NULL){
        list->head = newCar;
    } else {
        Car* temp = list->head;
        //find the last car which next is NULL
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newCar;
    }
    list->size++;
    printf("Added car: '%s' (%d/%d passengers).\n", type, num_passengers, max_passengers);
}

//delete all empty cars (num_passengers == 0)
void removeEmptyCar(Train* list){
    Car* temp = list->head;
    Car* prev = NULL;   
    
    printf("\nChecking and removing empty cars\n");
    
    while(temp != NULL){
        if(temp->num_passengers == 0){
            Car* node_to_delete = temp;
            printf("Removing empty car: '%s'\n", temp->type);

            if(prev == NULL){ // Xóa node đầu
                list->head = temp->next;
                temp = list->head;
            } else { // Xóa node ở giữa/cuối
                prev->next = temp->next;
                temp = prev->next;
            }
            free(node_to_delete);
            list->size--;
        } else {
            prev = temp;
            temp = temp->next;
        }
    }
    printf("--- Finished removing empty cars. ---\n");
}

void printTrain(Train* list){
    if (list->head == NULL) {
        printf("\nThe train is empty.\n");
        return;
    }
    printf("\n===== TRAIN STATUS (Total cars: %d) =====\n", list->size);
    Car* temp = list->head;
    int count = 1;
    while(temp != NULL){
        printf("Car #%d:\n", count++);
        printf("Type: %s\n", temp->type);
        printf("Passengers: %d / %d\n", temp->num_passengers, temp->max_passengers);
        temp = temp->next;
    }
}

void destroyTrain(Train* list) {
    Car* current = list->head;
    Car* nextCar;
    while (current != NULL) {
        nextCar = current->next; 
        free(current);           
        current = nextCar;       
    }
    list->head = NULL;
    list->size = 0;
}

int main(){
    Train myTrain;
    createTrain(&myTrain);

    addCar(&myTrain, "Passenger A", 100, 50);
    addCar(&myTrain, "Cargo", 0, 0); // Toa rỗng
    addCar(&myTrain, "Restaurant", 30, 25);
    addCar(&myTrain, "Sleeper B", 40, 0); // Toa rỗng
    addCar(&myTrain, "Passenger C", 100, 95);

    printTrain(&myTrain);

    removeEmptyCar(&myTrain);

    printTrain(&myTrain);

    removeEmptyCar(&myTrain);

    printTrain(&myTrain);

    printf("\nDestroying the train and freeing memory...\n");
    destroyTrain(&myTrain);

    return 0;
}