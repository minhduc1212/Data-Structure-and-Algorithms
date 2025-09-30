#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define MAX_NAME_LENGTH 50
#define NUM_ITEMS 3


// --- Cấu trúc dữ liệu ---

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

// Một "toa tàu" trong danh sách liên kết
typedef struct Node {
    Customer data;
    struct Node* next; // Khớp nối đến toa tiếp theo
} Node;

// "Người quản lý" của đoàn tàu
typedef struct CustomerQueue {
    Node* front; // Con trỏ chỉ đến đầu tàu
    Node* back;  // Con trỏ chỉ đến đuôi tàu
    int size;
} CustomerQueue;


// --- Các hàm thao tác với Queue ---

void init(CustomerQueue* qc) {
    qc->front = NULL;
    qc->back = NULL;
    qc->size = 0;
}

int isEmpty(CustomerQueue* qc) {
    return (qc->size == 0);
}

// Thêm khách hàng vào cuối hàng đợi - O(1)
void enqueue(CustomerQueue* qc, Customer newCustomer) {
    // 1. Tạo một "toa tàu" mới
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Loi cap phat bo nho!\n");
        return;
    }
    newNode->data = newCustomer;
    newNode->next = NULL;

    // 2. Móc toa mới này vào đoàn tàu
    if (isEmpty(qc)) {
        // Nếu đoàn tàu chưa có ai, toa mới là cả đầu và đuôi
        qc->front = qc->back = newNode;
    } else {
        // Móc vào sau đuôi tàu hiện tại và cập nhật lại đuôi tàu
        qc->back->next = newNode;
        qc->back = newNode;
    }
    qc->size++;
}

// Lấy khách hàng ra khỏi đầu hàng đợi - O(1)
Customer dequeue(CustomerQueue* qc) {
    Customer emptyCustomer = {"", "", 0};
    if (isEmpty(qc)) {
        return emptyCustomer;
    }

    // 1. Lưu lại toa tàu đầu tiên để xử lý và giải phóng
    Node* temp = qc->front;
    Customer processedCustomer = temp->data;

    // 2. Cập nhật lại "đầu tàu" là toa thứ hai
    qc->front = qc->front->next;

    // 3. Cho toa tàu cũ "về bãi" (giải phóng bộ nhớ)
    free(temp);
    qc->size--;

    // 4. Trường hợp đặc biệt: nếu hàng đợi trở nên rỗng
    if (qc->front == NULL) {
        qc->back = NULL;
    }

    return processedCustomer;
}

// Dọn dẹp bộ nhớ còn lại (hành động tốt)
void freeQueue(CustomerQueue* qc) {
    while (!isEmpty(qc)) {
        dequeue(qc);
    }
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
    while(!isEmpty(&customerQueue)){
        Customer currentCustomer = dequeue(&customerQueue);

        printf("\nProcessing customer: %s\n", currentCustomer.customerName);
        printf("--> Request: Buy %d of '%s'\n", currentCustomer.quantityToBuy, currentCustomer.itemName);

        int foundItem = 0;
        for (int i = 0; i < NUM_ITEMS; ++i) {
            if (strcmp(items[i].name, currentCustomer.itemName) == 0) {
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

    // Dọn dẹp bộ nhớ nếu cần, mặc dù ở đây chương trình kết thúc ngay sau đó
    freeQueue(&customerQueue);

    return 0;
}