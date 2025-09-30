#include <stdio.h>

#define MAX_NAME_LENGTH 50
#define NUM_ITEMS 3
#define MAX_QUEUE_SIZE 10 


void my_strcpy(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

int my_strcmp(const char* s1, const char* s2) {
    int i = 0;
    while (s1[i] == s2[i]) {
        if (s1[i] == '\0') return 0;
        i++;
    }
    return s1[i] - s2[i];
}


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

// PHƯƠNG PHÁP TỐT HƠN: Hàng đợi vòng (Circular Queue)
typedef struct CustomerQueue {
    Customer data[MAX_QUEUE_SIZE];
    int front; // Chỉ số của phần tử đầu hàng
    int back;  // Chỉ số của ô trống tiếp theo để thêm vào
    int size;  // Số phần tử hiện có
} CustomerQueue;


// Khởi tạo queue rỗng
void init (CustomerQueue* qc){
    qc->front = 0;
    qc->back = 0;
    qc->size = 0;
}   

// Kiểm tra rỗng (dựa vào size)
int isEmpty(CustomerQueue* qc){
    return (qc->size == 0);
}

// Kiểm tra đầy (dựa vào size)
int isFull(CustomerQueue* qc){
    return (qc->size == MAX_QUEUE_SIZE);
}

// Thêm vào hàng đợi - O(1), RẤT NHANH
int enqueue(CustomerQueue* qc, Customer newCustomer){
    if(isFull(qc)){
        printf("Queue is full\n");
        return 0;
    }

    // Đặt khách hàng mới vào vị trí 'back' hiện tại
    qc->data[qc->back] = newCustomer;
    
    // Di chuyển 'back' tới vị trí trống tiếp theo, vòng lại nếu cần
    qc->back = (qc->back + 1) % MAX_QUEUE_SIZE;
    
    // Tăng số lượng phần tử
    qc->size++;
    
    return 1;
}   


// Lấy ra khỏi hàng đợi - O(1), RẤT NHANH
Customer dequeue(CustomerQueue* qc){
    Customer emptyCustomer = {"", "", 0};
    if(isEmpty(qc)){
        return emptyCustomer;
    }
    
    // 1. Lấy khách hàng tại vị trí 'front'
    Customer processedCustomer = qc->data[qc->front];
    
    // 2. Di chuyển 'front' đến phần tử tiếp theo, vòng lại nếu cần
    qc->front = (qc->front + 1) % MAX_QUEUE_SIZE;
    
    // 3. Giảm số lượng phần tử
    qc->size--;
    
    return processedCustomer;
}

void displayItems(Item items[], int numItems) {
    printf("\nStock Status\n");
    for (int i = 0; i < numItems; ++i) {
        printf("Product: %s, The quantity: %d\n", items[i].name, items[i].quantity);
    }
    printf("---------------------------\n\n");
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
    my_strcpy(c1.customerName, "Anh Ba"); my_strcpy(c1.itemName, "Iphone 15 Pro"); c1.quantityToBuy = 2;
    my_strcpy(c2.customerName, "Chi Tu"); my_strcpy(c2.itemName, "Samsung Galaxy S24"); c2.quantityToBuy = 6;
    my_strcpy(c3.customerName, "Cau Nam"); my_strcpy(c3.itemName, "Iphone 15 Pro"); c3.quantityToBuy = 3;
    my_strcpy(c4.customerName, "Co Sau"); my_strcpy(c4.itemName, "Xiaomi 14"); c4.quantityToBuy = 10;

    printf("Start enter the queue\n");
    enqueue(&customerQueue, c1);
    enqueue(&customerQueue, c2);
    enqueue(&customerQueue, c3);
    enqueue(&customerQueue, c4);

    printf("\n--- Starting to process customers ---\n");
    while(!isEmpty(&customerQueue)){
        Customer currentCustomer = dequeue(&customerQueue);

        printf("\nProcessing customer: %s\n", currentCustomer.customerName);
        printf("--> Request: Buy %d of '%s'\n", currentCustomer.quantityToBuy, currentCustomer.itemName);

        int foundItem = 0;
        for (int i = 0; i < NUM_ITEMS; ++i) {
            if (my_strcmp(items[i].name, currentCustomer.itemName) == 0) {
                foundItem = 1;
                if (items[i].quantity >= currentCustomer.quantityToBuy) {
                    items[i].quantity -= currentCustomer.quantityToBuy;
                    printf("==> Successful transaction!\n");
                } else {
                    printf("==> WARNING: Not enough stock for '%s'.\n", items[i].name);
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