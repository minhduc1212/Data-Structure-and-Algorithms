#include <iostream>
#include <string>

using namespace std;

// Struct để lưu thông tin trang web
struct Website {
    string url;
    string title;
};

// Node trong Linked List, mỗi Node chứa 1 Website
struct Node {
    Website data;
    Node* next;
};

// Cấu trúc Stack dựa trên slide 25
struct Stack {
    Node* pTop;
    int size;
};

// --- Các hàm thao tác với Stack ---

// Khởi tạo stack rỗng (dựa trên slide 27)
void init(Stack& s) {
    s.pTop = NULL;
    s.size = 0;
}

// Kiểm tra stack rỗng
bool isEmpty(Stack& s) {
    return s.size == 0;
}

// Đẩy một phần tử vào stack (dựa trên slide 28)
void push(Stack& s, Website webData) {
    Node* p = new Node();
    p->data = webData;
    p->next = s.pTop;
    s.pTop = p;
    s.size++;
}

// Lấy một phần tử ra khỏi stack (cải tiến từ slide 29 để trả về giá trị)
Website pop(Stack& s) {
    if (isEmpty(s)) {
        return {"", "Empty"};
    }
    Node* p = s.pTop;
    Website webData = p->data;
    s.pTop = p->next;
    delete p;
    s.size--;
    return webData;
}

// Xem phần tử ở đỉnh stack mà không xóa
Website top(Stack& s) {
    if (isEmpty(s)) {
        return {"", "Empty"};
    }
    return s.pTop->data;
}

// Hiển thị nội dung của một stack (hữu ích cho việc debug)
void displayStack(Stack& s, string stackName) {
    cout << "--- " << stackName << " ---" << endl;
    if (isEmpty(s)) {
        cout << "(Empty)" << endl;
        return;
    }
    Node* p = s.pTop;
    while (p != NULL) {
        cout << "  " << p->data.title << " (" << p->data.url << ")" << endl;
        p = p->next;
    }
}

// Hàm xóa toàn bộ stack
void clear(Stack& s) {
    while (!isEmpty(s)) {
        pop(s);
    }
}


int main() {
    Stack backwardStack, forwardStack;
    init(backwardStack);
    init(forwardStack);

    Website currentPage = {"", "New Tab"};

    // 1. Bắt đầu duyệt web
    cout << "Mo tab moi..." << endl;
    
    // Visit google.com
    cout << "\nDang truy cap trang Google..." << endl;
    push(backwardStack, currentPage);
    currentPage = {"google.com", "Google Search"};
    clear(forwardStack);

    // Visit usth.edu.vn
    cout << "\nDang truy cap trang USTH..." << endl;
    push(backwardStack, currentPage);
    currentPage = {"usth.edu.vn", "USTH Website"};
    clear(forwardStack);

    // Visit moodle.usth.edu.vn
    cout << "\nDang truy cap trang Moodle..." << endl;
    push(backwardStack, currentPage);
    currentPage = {"moodle.usth.edu.vn", "Moodle USTH"};
    clear(forwardStack);

    cout << "\n========================================\n";
    cout << "Trang hien tai: " << currentPage.title << endl;
    displayStack(backwardStack, "Lich su Back");
    displayStack(forwardStack, "Lich su Forward");
    cout << "========================================\n";

    // 2. Bấm nút Back
    cout << "\nNhan nut 'Back'..." << endl;
    if (!isEmpty(backwardStack)) {
        push(forwardStack, currentPage);
        currentPage = pop(backwardStack);
    } else {
        cout << "Khong the back!" << endl;
    }
    
    cout << "\n========================================\n";
    cout << "Trang hien tai: " << currentPage.title << endl;
    displayStack(backwardStack, "Lich su Back");
    displayStack(forwardStack, "Lich su Forward");
    cout << "========================================\n";
    
    // 3. Bấm nút Back lần nữa
    cout << "\nNhan nut 'Back' mot lan nua..." << endl;
    if (!isEmpty(backwardStack)) {
        push(forwardStack, currentPage);
        currentPage = pop(backwardStack);
    } else {
        cout << "Khong the back!" << endl;
    }
    
    cout << "\n========================================\n";
    cout << "Trang hien tai: " << currentPage.title << endl;
    displayStack(backwardStack, "Lich su Back");
    displayStack(forwardStack, "Lich su Forward");
    cout << "========================================\n";

    // 4. Bấm nút Forward
    cout << "\nNhan nut 'Forward'..." << endl;
    if (!isEmpty(forwardStack)) {
        push(backwardStack, currentPage);
        currentPage = pop(forwardStack);
    } else {
        cout << "Khong the forward!" << endl;
    }

    cout << "\n========================================\n";
    cout << "Trang hien tai: " << currentPage.title << endl;
    displayStack(backwardStack, "Lich su Back");
    displayStack(forwardStack, "Lich su Forward");
    cout << "========================================\n";
    
    return 0;
}