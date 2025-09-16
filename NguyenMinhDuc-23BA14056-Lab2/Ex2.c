#include <stdio.h>
#include <stdlib.h>

// Represents a railroad car (a node in the linked list)
typedef struct Car {
    char id;
    int capacity;
    int reservedPassengers;
    struct Car* next;
} Car;

// Represents the entire train (wrapper for the head of the list)
typedef struct {
    Car* head;
} Train;

// Function to create an empty train
Train* createTrain() {
    Train* train = (Train*)malloc(sizeof(Train));
    if (!train) {
        perror("Failed to allocate train");
        return NULL;
    }
    train->head = NULL;
    return train;
}

// Adds a new car to the end of the train
void addCar(Train* train, char id, int capacity, int reservedPassengers) {
    if (reservedPassengers > capacity) {
        printf("Error: Reserved passengers (%d) cannot exceed capacity (%d) for car %c.\n",
               reservedPassengers, capacity, id);
        return;
    }

    Car* newCar = (Car*)malloc(sizeof(Car));
    if (!newCar) {
        perror("Failed to allocate new car");
        return;
    }
    newCar->id = id;
    newCar->capacity = capacity;
    newCar->reservedPassengers = reservedPassengers;
    newCar->next = NULL;

    // If the train is empty, the new car becomes the head
    if (train->head == NULL) {
        train->head = newCar;
    } else {
        // Otherwise, find the last car and attach the new one
        Car* current = train->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newCar;
    }
}

// Removes all cars that have no passengers
void removeEmptyCars(Train* train) {
    Car* current = train->head;
    Car* prev = NULL;

    while (current != NULL) {
        if (current->reservedPassengers == 0) {
            printf("Removing empty car %c...\n", current->id);
            Car* to_delete = current;
            if (prev == NULL) { // The car to be removed is the head
                train->head = current->next;
                current = train->head;
            } else { // The car is in the middle or at the end
                prev->next = current->next;
                current = prev->next;
            }
            free(to_delete);
        } else {
            // Move to the next car
            prev = current;
            current = current->next;
        }
    }
}

// Displays information for all cars in the train
void displayCars(const Train* train) {
    if (train->head == NULL) {
        printf("The train is empty.\n");
        return;
    }
    printf("Train Cars Information:\n");
    Car* current = train->head;
    while (current != NULL) {
        printf("  - Car ID: %c | Capacity: %d | Reserved: %d\n",
               current->id, current->capacity, current->reservedPassengers);
        current = current->next;
    }
}

// Displays the total number of cars in the train
void displayLength(const Train* train) {
    int count = 0;
    Car* current = train->head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    printf("The train has %d car(s).\n", count);
}

// Frees all memory associated with the train
void freeTrain(Train* train) {
    if (train) {
        Car* current = train->head;
        while (current != NULL) {
            Car* next = current->next;
            free(current);
            current = next;
        }
        free(train);
    }
}

int main_train() { // Renamed to avoid conflict if both mains are in one file
    printf("--- Exercise 2: Railway Train ---\n");
    Train* myTrain = createTrain();
    if (!myTrain) return 1;

    addCar(myTrain, 'A', 50, 30);
    addCar(myTrain, 'B', 40, 0);  // Empty car
    addCar(myTrain, 'C', 60, 55);
    addCar(myTrain, 'D', 30, 0);  // Empty car

    printf("Initial train information:\n");
    displayCars(myTrain);
    displayLength(myTrain);

    printf("\nRemoving empty cars...\n");
    removeEmptyCars(myTrain);

    printf("\nTrain information after removing empty cars:\n");
    displayCars(myTrain);
    displayLength(myTrain);

    printf("\nAdding a new car...\n");
    addCar(myTrain, 'E', 70, 65);

    printf("\nFinal train information:\n");
    displayCars(myTrain);
    displayLength(myTrain);

    freeTrain(myTrain); // Clean up memory
    return 0;
}

// You can compile and run each exercise separately.
// To run Exercise 2, rename main_train() to main() and compile.
// I will combine them into a single runnable file.

int main() {
    main(); // Calls the UnboundedInteger main
    printf("\n=======================================\n\n");
    main_train(); // Calls the Train main
    return 0;
}