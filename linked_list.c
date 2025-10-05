#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
} Node;

typedef struct List{
    int size;
    Node* head;
} List;

//create node
Node* initNode(int data){
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL; 
    return newNode;
}

//create linked list
void initList(List* list){
    list->size = 0;
    list->head = NULL;
}
//check the empty
int isEmpty(List* list){
    return list->size == 0;
}

//insert node at the first if the list is empty
void insertFirst(Node* newNode, List* list){
    if (newNode == NULL) {
        return; 
    }
    if (isEmpty(list)) {
        newNode->next = list->head;
        list->head = newNode;
        list->size++;   
    }
}

//insert node in the specified position
void insert(Node* newNode, Node* prevNode, List* list){
    if (prevNode == NULL) {
        return; 
    }
    newNode->next = prevNode->next; //ô next chứa địa chỉ của node kế tiếp -> ô next của newNode sẽ trỏ đến node kế tiếp là node địa chỉ chứa trong ô next của prevNode
    prevNode->next = newNode;//sau đó ô next của prevNode sẽ trỏ đến đại chỉ của newNode
    list->size++;
}


//print the linked list
void printList(List* list){
    Node* current = list->head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

//free the memory
void freeList(List* list) {
    Node* current = list->head;
    Node* nextNode;
    while (current != NULL) {
        nextNode = current->next; // Lưu lại node kế tiếp
        free(current);            // Giải phóng node hiện tại
        current = nextNode;       // Di chuyển tới node kế tiếp
    }
    initList(list);
}




int main(){
    List list;
    initList(&list);

    Node* node1 = initNode(10);
    insertFirst(node1, &list);

    Node* node2 = initNode(20);
    insert(node2, node1, &list);

    Node* node3 = initNode(30);
    insert(node3, node2, &list);

    printList(&list);
    freeList(&list);
    return 0;
}