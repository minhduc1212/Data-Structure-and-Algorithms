#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define NUM_ITEMS 3
#define MAX_QUEUE_SIZE 10 



typedef struct Item{
    char name[MAX_NAME_LENGTH];
    int quantity;
    double price;
} Item;

typedef struct Customer{
    char customerName[MAX_NAME_LENGTH];
    char itemName[MAX_NAME_LENGTH];
    int quantityToBuy;
} Customer;

typedef struct CustomerQueue {
    Customer data[MAX_QUEUE_SIZE];
    int front;
    int back;
} CustomerQueue;


// Các hàm logic của bạn được giữ nguyên
void init (CustomerQueue* qc){
    qc->front = 0;
    qc->back = 0;
}   

int length (CustomerQueue* qc){
    return qc->back - qc->front;
}

int theEmpty(CustomerQueue* qc){
    return (qc->back == qc->front);
}

int enqueue(CustomerQueue* qc, Customer newCustomer){
    if(length(qc) == MAX_QUEUE_SIZE){
        printf("Queue is full");
        return 0;
    }
    qc->data[qc->back] = newCustomer;
    qc->back++;
    return 1;
}   

Customer dequeue(CustomerQueue* qc){
    Customer emptyCustomer = {"", "", 0};
    if(theEmpty(qc)){
        return emptyCustomer;
    }
    Customer processedCustomer = qc->data[0];

    if (length(qc) > 1){
        for (int i = 1; i < length(qc); i++){
            qc->data[i-1] = qc->data[i];
        }
    }
    qc->back = qc->back - 1;

    return processedCustomer;
}

void displayItems(Item items[], int numItems) {
    printf("\nStock Status\n");
    for (int i = 0; i < numItems; ++i) {
        printf("Product: %s, The quantity: %d\n", items[i].name, items[i].quantity);
    }
}

int main(){
    Item items[NUM_ITEMS] = {
        {"Iphone 15 Pro", 10, 25000000},
        {"Samsung Galaxy S24", 5, 22000000},
        {"Xiaomi 14", 20, 18000000}
    };

    CustomerQueue customerQueue;
    init(&customerQueue);

    displayItems(items, NUM_ITEMS);

    Customer c1, c2, c3, c4;
    strcpy(c1.customerName, "Anh Ba"); strcpy(c1.itemName, "Iphone 15 Pro"); c1.quantityToBuy = 2;
    strcpy(c2.customerName, "Chi Tu"); strcpy(c2.itemName, "Samsung Galaxy S24"); c2.quantityToBuy = 6;
    strcpy(c3.customerName, "Cau Nam"); strcpy(c3.itemName, "Iphone 15 Pro"); c3.quantityToBuy = 3;
    strcpy(c4.customerName, "Co Sau"); strcpy(c4.itemName, "Xiaomi 14"); c4.quantityToBuy = 10;

    printf("Start enter the queue\n");
    enqueue(&customerQueue, c1);
    enqueue(&customerQueue, c2);
    enqueue(&customerQueue, c3);
    enqueue(&customerQueue, c4);

    printf("\n--- Starting to process customers ---\n");
    while(!theEmpty(&customerQueue)){
        Customer currentCustomer = dequeue(&customerQueue);

        printf("\nProcessing customer: %s\n", currentCustomer.customerName);
        printf("Request: Buy %d of '%s'\n", currentCustomer.quantityToBuy, currentCustomer.itemName);

        int foundItem = 0;
        for (int i = 0; i < NUM_ITEMS; ++i) {
            if (strcmp(items[i].name, currentCustomer.itemName) == 0) {
                foundItem = 1;
                if (items[i].quantity >= currentCustomer.quantityToBuy) {
                    items[i].quantity -= currentCustomer.quantityToBuy;
                    printf("Successful transaction!\n");
                } else {
                    printf("WARNING: Not enough stock for '%s'.\n", items[i].name);
                }
                break;
            }
        }

        if (!foundItem) {
            printf("==> WARNING: Product '%s' does not exist.\n", currentCustomer.itemName);
        }
        
        displayItems(items, NUM_ITEMS);
    }
    
    printf("\nAll customers have been processed!\n");

    return 0;
}