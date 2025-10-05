#include<stdio.h>

typedef struct Item{
    char name[50];
    int price;
    int quantity;
} Item;

typedef struct Customer{
    char name[50];
    Item item;
    int item_quantity;
} Customer;

typedef struct CustomerQueue{
    Customer customers[100];
    int front, back;
} CustomerQueue;

void createQueue(CustomerQueue* q){
    q->front = 0;
    q->back = 0;
}

void enQueue(CustomerQueue* q, Customer c){
    q->customers[q->back] = c;
    q->back++;
}

Customer deQueue(CustomerQueue* q){
    Customer servedCustomer = q->customers[q->front];
    for (int i = q->front + 1; i < q->back; i++){
        q->customers[i - 1] = q->customers[i];
    }
    q->back--;
    return servedCustomer;

    /*
    more simple
    Customer servedCustomer = q->customers[q->front];
    q->front++;
    return servedCustomer;
    */
}

void printQueue(CustomerQueue* q){
    for(int i = q->front; i < q->back; i++){
        printf("Customer Name: %s\n", q->customers[i].name);
        printf("Item Name: %s\n", q->customers[i].item.name);
        printf("Item Price: %d\n", q->customers[i].item.price);
        printf("Item Quantity: %d\n", q->customers[i].item_quantity);
        printf("\n");
    }
}



int main(){
    //create items
    Item item1 = {"Apple", 10, 100};
    Item item2 = {"Banana", 20, 100};
    Item item3 = {"Orange", 30, 100};

    //create customers
    Customer customer1 = {"John", item1, 10};
    Customer customer2 = {"Doe", item2, 20};
    Customer customer3 = {"Jane", item3, 30};

    //create queue
    CustomerQueue queue;
    createQueue(&queue);

    //add customers to queue
    enQueue(&queue, customer1);
    enQueue(&queue, customer2);
    enQueue(&queue, customer3);

    //print queue
    printQueue(&queue);
    printf("\n");

    //dequeue customers
    Customer servedCustomer = deQueue(&queue);
    printf("Served Customer: %s\n", servedCustomer.name);
    printf("\n");

    //dequeue customers
    servedCustomer = deQueue(&queue);
    printf("Served Customer: %s\n", servedCustomer.name);
    printf("\n");
   
    //dequeue customers
    servedCustomer = deQueue(&queue);
    printf("Served Customer: %s\n", servedCustomer.name);
    printf("\n");
    
   

    return 0;
}
