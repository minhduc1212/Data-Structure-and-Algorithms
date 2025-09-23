#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_URL_LENGTH 100
#define MAX_TITLE_LENGTH 100

// Struct để lưu thông tin trang web
typedef struct {
    char url[MAX_URL_LENGTH];
    char title[MAX_TITLE_LENGTH];
} Website;

// Node trong Linked List, mỗi Node chứa 1 Website
typedef struct Node {
    Website data;
    struct Node* next;
} Node;

// Cấu trúc Stack dựa trên slide 25
typedef struct {
    Node* pTop;
    int size;
} Stack;

// --- Các hàm thao tác với Stack ---

// Khởi tạo stack rỗng (dựa trên slide 27)
void init(Stack* s) {
    s->pTop = NULL;
    s->size = 0;
}

// Kiểm tra stack rỗng
bool isEmpty(Stack* s) {
    return s->size == 0;
}

// Đẩy một phần tử vào stack (dựa trên slide 28)
void push(Stack* s, Website webData) {
    Node* p = (Node*)malloc(sizeof(Node));
    if (p == NULL) {
        printf("Loi cap phat bo nho!\n");
        return;
    }
    p->data = webData;
    p->next = s->pTop;
    s->pTop = p;
    s->size++;
}

// Lấy một phần tử ra khỏi stack (cải tiến từ slide 29)
Website pop(Stack* s) {
    Website emptyWeb = {"", "Empty"};
    if (isEmpty(s)) {
        return emptyWeb;
    }
    Node* p = s->pTop;
    Website webData = p->data;
    s->pTop = p->next;
    free(p); // Giải phóng bộ nhớ
    s->size--;
    return webData;
}

// Hàm xóa toàn bộ stack
void clear(Stack* s) {
    while (!isEmpty(s)) {
        pop(s);
    }
}

// Hiển thị nội dung của một stack
void displayStack(Stack* s, const char* stackName) {
    printf("--- %s ---\n", stackName);
    if (isEmpty(s)) {
        printf("(Empty)\n");
        return;
    }
    Node* p = s->pTop;
    while (p != NULL) {
        printf("  %s (%s)\n", p->data.title, p->data.url);
        p = p->next;
    }
}

void printCurrentState(Website currentPage, Stack* backwardStack, Stack* forwardStack) {
    printf("\n========================================\n");
    printf("Trang hien tai: %s\n", currentPage.title);
    displayStack(backwardStack, "Lich su Back");
    displayStack(forwardStack, "Lich su Forward");
    printf("========================================\n");
}


int main() {
    Stack backwardStack, forwardStack;
    init(&backwardStack);
    init(&forwardStack);

    Website currentPage = {"", "New Tab"};

    // 1. Bắt đầu duyệt web
    printf("Mo tab moi...\n");
    
    // Visit google.com
    printf("\nDang truy cap trang Google...\n");
    push(&backwardStack, currentPage);
    strcpy(currentPage.url, "google.com");
    strcpy(currentPage.title, "Google Search");
    clear(&forwardStack);

    // Visit usth.edu.vn
    printf("\nDang truy cap trang USTH...\n");
    push(&backwardStack, currentPage);
    strcpy(currentPage.url, "usth.edu.vn");
    strcpy(currentPage.title, "USTH Website");
    clear(&forwardStack);

    // Visit moodle.usth.edu.vn
    printf("\nDang truy cap trang Moodle...\n");
    push(&backwardStack, currentPage);
    strcpy(currentPage.url, "moodle.usth.edu.vn");
    strcpy(currentPage.title, "Moodle USTH");
    clear(&forwardStack);

    printCurrentState(currentPage, &backwardStack, &forwardStack);

    // 2. Bấm nút Back
    printf("\nNhan nut 'Back'...\n");
    if (!isEmpty(&backwardStack)) {
        push(&forwardStack, currentPage);
        currentPage = pop(&backwardStack);
    } else {
        printf("Khong the back!\n");
    }
    
    printCurrentState(currentPage, &backwardStack, &forwardStack);
    
    // 3. Bấm nút Back lần nữa
    printf("\nNhan nut 'Back' mot lan nua...\n");
    if (!isEmpty(&backwardStack)) {
        push(&forwardStack, currentPage);
        currentPage = pop(&backwardStack);
    } else {
        printf("Khong the back!\n");
    }
    
    printCurrentState(currentPage, &backwardStack, &forwardStack);

    // 4. Bấm nút Forward
    printf("\nNhan nut 'Forward'...\n");
    if (!isEmpty(&forwardStack)) {
        push(&backwardStack, currentPage);
        currentPage = pop(&forwardStack);
    } else {
        printf("Khong the forward!\n");
    }

    printCurrentState(currentPage, &backwardStack, &forwardStack);
    
    return 0;
}