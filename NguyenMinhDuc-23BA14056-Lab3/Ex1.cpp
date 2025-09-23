#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Struct để lưu thông tin sản phẩm
struct Item {
    string name;
    int quantity;
    double price;
};

// Struct để lưu thông tin yêu cầu của khách hàng
struct Customer {
    string customerName;
    string itemName;
    int quantityToBuy;
};

// Node trong Linked List, mỗi Node chứa 1 Customer
struct Node {
    Customer data;
    Node* next;
};

// Cấu trúc Queue dựa trên slide 49
struct Queue {
    Node* pFront;
    Node* pBack;
    int size;
};

// --- Các hàm thao tác với Queue ---

// Khởi tạo queue rỗng (dựa trên slide 50)
void init(Queue& q) {
    q.pFront = NULL;
    q.pBack = NULL;
    q.size = 0;
}

// Kiểm tra queue rỗng
bool isEmpty(Queue& q) {
    return q.size == 0;
}

// Thêm khách hàng vào cuối hàng đợi (dựa trên slide 52)
void enqueue(Queue& q, Customer customerData) {
    Node* p = new Node();
    p->data = customerData;
    p->next = NULL;

    if (isEmpty(q)) {
        q.pFront = q.pBack = p;
    } else {
        q.pBack->next = p;
        q.pBack = p;
    }
    q.size++;
}

// Lấy khách hàng ra khỏi đầu hàng đợi (cải tiến từ slide 54 để hiệu quả hơn O(1))
Customer dequeue(Queue& q) {
    if (isEmpty(q)) {
        return Customer{"", "", 0}; // Trả về một Customer rỗng nếu queue không có ai
    }

    Node* p = q.pFront;
    Customer customerData = p->data;

    q.pFront = q.pFront->next;
    delete p;

    if (q.pFront == NULL) {
        q.pBack = NULL;
    }

    q.size--;
    return customerData;
}

void displayItems(const vector<Item>& items) {
    cout << "\n--- Trang thai kho hang ---" << endl;
    for (const auto& item : items) {
        cout << "San pham: " << item.name << ", So luong ton kho: " << item.quantity << endl;
    }
    cout << "---------------------------\n" << endl;
}


int main() {
    // 1. Khởi tạo danh sách sản phẩm
    vector<Item> items = {
        {"Iphone 15 Pro", 10, 25000000},
        {"Samsung Galaxy S24", 5, 22000000},
        {"Xiaomi 14", 20, 18000000}
    };

    // 2. Khởi tạo hàng đợi khách hàng
    Queue customerQueue;
    init(customerQueue);

    cout << "CHUONG TRINH MO PHONG HANG DOI MUA HANG" << endl;
    displayItems(items);

    // 3. Thêm khách hàng vào hàng đợi
    cout << "Co khach hang vao xep hang..." << endl;
    enqueue(customerQueue, {"Anh Ba", "Iphone 15 Pro", 2});
    enqueue(customerQueue, {"Chi Tu", "Samsung Galaxy S24", 6}); // Yêu cầu quá số lượng
    enqueue(customerQueue, {"Cau Nam", "Iphone 15 Pro", 3});
    enqueue(customerQueue, {"Co Sau", "Xiaomi 14", 10});

    // 4. Xử lý lần lượt các khách hàng
    while (!isEmpty(customerQueue)) {
        Customer currentCustomer = dequeue(customerQueue);

        cout << "Dang xu ly cho khach hang: " << currentCustomer.customerName << endl;
        cout << "Yeu cau: Mua " << currentCustomer.quantityToBuy << " san pham '" << currentCustomer.itemName << "'" << endl;

        bool foundItem = false;
        for (int i = 0; i < items.size(); ++i) {
            if (items[i].name == currentCustomer.itemName) {
                foundItem = true;
                if (items[i].quantity >= currentCustomer.quantityToBuy) {
                    items[i].quantity -= currentCustomer.quantityToBuy;
                    cout << "==> Giao dich thanh cong! Kho hang da duoc cap nhat." << endl;
                } else {
                    cout << "==> Canh bao: San pham '" << items[i].name << "' khong du so luong (con " << items[i].quantity << ", can " << currentCustomer.quantityToBuy << ")." << endl;
                }
                break;
            }
        }

        if (!foundItem) {
            cout << "==> Canh bao: San pham '" << currentCustomer.itemName << "' khong ton tai." << endl;
        }

        displayItems(items);
    }
    
    cout << "Tat ca khach hang da duoc xu ly!" << endl;

    return 0;
}