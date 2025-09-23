#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Định nghĩa kích thước tối đa cho chuỗi
#define MAX_NAME_LENGTH 50
#define NUM_ITEMS 3

// Struct để lưu thông tin sản phẩm
typedef struct {
    char name[MAX_NAME_LENGTH];
    int quantity;
    double price;
} Item;

// Struct để lưu thông tin yêu cầu của khách hàng
typedef struct {
    char customerName[MAX_NAME_LENGTH];
    char itemName[MAX_NAME_LENGTH];
    int quantityToBuy;
} Customer;

// Node trong Linked List, mỗi Node chứa 1 Customer
typedef struct Node {
    Customer data;
    struct Node* next;
} Node;

// Cấu trúc Queue dựa trên slide 49
typedef struct {
    Node* pFront;
    Node* pBack;
    int size;
} Queue;

// --- Các hàm thao tác với Queue ---

// Khởi tạo queue rỗng (dựa trên slide 50)
void init(Queue* q) {
    q->pFront = NULL;
    q->pBack = NULL;
    q->size = 0;
}

// Kiểm tra queue rỗng
bool isEmpty(Queue* q) {
    return q->size == 0;
}

// Thêm khách hàng vào cuối hàng đợi (dựa trên slide 52)
void enqueue(Queue* q, Customer customerData) {
    // Cấp phát bộ nhớ cho node mới
    Node* p = (Node*)malloc(sizeof(Node));
    if (p == NULL) {
        printf("Loi cap phat bo nho!\n");
        return;
    }
    p->data = customerData;
    p->next = NULL;

    if (isEmpty(q)) {
        q->pFront = q->pBack = p;
    } else {
        q->pBack->next = p;
        q->pBack = p;
    }
    q->size++;
}

// Lấy khách hàng ra khỏi đầu hàng đợi (hiệu quả hơn slide 54)
Customer dequeue(Queue* q) {
    // Trả về một Customer rỗng nếu queue không có ai
    Customer emptyCustomer = {"", "", 0};
    if (isEmpty(q)) {
        return emptyCustomer;
    }

    Node* p = q->pFront;
    Customer customerData = p->data;

    q->pFront = q->pFront->next;
    free(p); // Giải phóng bộ nhớ

    if (q->pFront == NULL) {
        q->pBack = NULL;
    }

    q->size--;
    return customerData;
}

// Hiển thị trạng thái kho hàng
void displayItems(Item items[], int numItems) {
    printf("\n--- Trang thai kho hang ---\n");
    for (int i = 0; i < numItems; ++i) {
        printf("San pham: %s, So luong ton kho: %d\n", items[i].name, items[i].quantity);
    }
    printf("---------------------------\n\n");
}

int main() {
    // 1. Khởi tạo danh sách sản phẩm (dùng mảng C)
    Item items[NUM_ITEMS] = {
        {"Iphone 15 Pro", 10, 25000000},
        {"Samsung Galaxy S24", 5, 22000000},
        {"Xiaomi 14", 20, 18000000}
    };

    // 2. Khởi tạo hàng đợi khách hàng
    Queue customerQueue;
    init(&customerQueue);

    printf("CHUONG TRINH MO PHONG HANG DOI MUA HANG\n");
    displayItems(items, NUM_ITEMS);

    // 3. Thêm khách hàng vào hàng đợi
    printf("Co khach hang vao xep hang...\n");
    Customer c1, c2, c3, c4;
    strcpy(c1.customerName, "Anh Ba"); strcpy(c1.itemName, "Iphone 15 Pro"); c1.quantityToBuy = 2;
    strcpy(c2.customerName, "Chi Tu"); strcpy(c2.itemName, "Samsung Galaxy S24"); c2.quantityToBuy = 6;
    strcpy(c3.customerName, "Cau Nam"); strcpy(c3.itemName, "Iphone 15 Pro"); c3.quantityToBuy = 3;
    strcpy(c4.customerName, "Co Sau"); strcpy(c4.itemName, "Xiaomi 14"); c4.quantityToBuy = 10;
    
    enqueue(&customerQueue, c1);
    enqueue(&customerQueue, c2); // Yêu cầu quá số lượng
    enqueue(&customerQueue, c3);
    enqueue(&customerQueue, c4);

    // 4. Xử lý lần lượt các khách hàng
    while (!isEmpty(&customerQueue)) {
        Customer currentCustomer = dequeue(&customerQueue);

        printf("Dang xu ly cho khach hang: %s\n", currentCustomer.customerName);
        printf("Yeu cau: Mua %d san pham '%s'\n", currentCustomer.quantityToBuy, currentCustomer.itemName);

        bool foundItem = false;
        for (int i = 0; i < NUM_ITEMS; ++i) {
            // Dùng strcmp để so sánh chuỗi trong C
            if (strcmp(items[i].name, currentCustomer.itemName) == 0) {
                foundItem = true;
                if (items[i].quantity >= currentCustomer.quantityToBuy) {
                    items[i].quantity -= currentCustomer.quantityToBuy;
                    printf("==> Giao dich thanh cong! Kho hang da duoc cap nhat.\n");
                } else {
                    printf("==> Canh bao: San pham '%s' khong du so luong (con %d, can %d).\n", items[i].name, items[i].quantity, currentCustomer.quantityToBuy);
                }
                break;
            }
        }

        if (!foundItem) {
            printf("==> Canh bao: San pham '%s' khong ton tai.\n", currentCustomer.itemName);
        }

        displayItems(items, NUM_ITEMS);
    }
    
    printf("Tat ca khach hang da duoc xu ly!\n");

    return 0;
}