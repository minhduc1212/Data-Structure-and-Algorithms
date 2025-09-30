#include <iostream>
#include <string>   // Dùng std::string
#include <vector>   // Dùng std::vector cho danh sách sản phẩm
#include <queue>    // Dùng std::queue cho hàng đợi

// Dùng using namespace để code ngắn gọn hơn
using namespace std;

// Struct Item với std::string
struct Item {
    string name;
    int quantity;
    double price;
};

// Struct Customer với std::string
struct Customer {
    string customerName;
    string itemName;
    int quantityToBuy;
};

void displayItems(const vector<Item>& items) {
    cout << "\nStock Status" << endl;
    for (const auto& item : items) { // Dùng for-each tiện lợi
        cout << "Product: " << item.name << ", The quantity: " << item.quantity << endl;
    }
    cout << "---------------------------\n" << endl;
}

int main() {
    // Dùng std::vector linh hoạt hơn mảng C-style
    vector<Item> items = {
        {"Iphone 15 Pro", 10, 25000000},
        {"Samsung Galaxy S24", 5, 22000000},
        {"Xiaomi 14", 20, 18000000}
    };

    // Khai báo hàng đợi có sẵn của C++
    queue<Customer> customerQueue;

    displayItems(items);

    cout << "Start enter the queue" << endl;
    // Thêm khách hàng vào hàng đợi bằng hàm push()
    customerQueue.push({"Anh Ba", "Iphone 15 Pro", 2});
    customerQueue.push({"Chi Tu", "Samsung Galaxy S24", 6});
    customerQueue.push({"Cau Nam", "Iphone 15 Pro", 3});
    customerQueue.push({"Co Sau", "Xiaomi 14", 10});

    cout << "\n--- Starting to process customers ---\n";
    // Kiểm tra hàng đợi rỗng bằng hàm empty()
    while (!customerQueue.empty()) {
        // 1. Lấy khách hàng ở đầu hàng bằng hàm front()
        Customer currentCustomer = customerQueue.front();
        
        // 2. Xóa khách hàng đó khỏi hàng đợi bằng hàm pop()
        customerQueue.pop();

        cout << "\nProcessing customer: " << currentCustomer.customerName << endl;
        cout << "--> Request: Buy " << currentCustomer.quantityToBuy << " of '" << currentCustomer.itemName << "'" << endl;

        bool foundItem = false;
        for (auto& item : items) { // Dùng auto& để có thể thay đổi item
            // So sánh chuỗi bằng toán tử ==
            if (item.name == currentCustomer.itemName) {
                foundItem = true;
                if (item.quantity >= currentCustomer.quantityToBuy) {
                    item.quantity -= currentCustomer.quantityToBuy;
                    cout << "==> Successful transaction!" << endl;
                } else {
                    cout << "==> WARNING: Not enough stock for '" << item.name << "'." << endl;
                }
                break;
            }
        }

        if (!foundItem) {
            cout << "==> WARNING: Product '" << currentCustomer.itemName << "' does not exist." << endl;
        }
        
        displayItems(items);
    }
    
    cout << "\nAll customers have been processed!" << endl;

    return 0;
}