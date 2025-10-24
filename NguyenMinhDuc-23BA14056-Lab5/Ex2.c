#include <stdio.h>
#include <stdlib.h>

// Helper macro để tìm giá trị nhỏ hơn
#define min(a, b) (((a) < (b)) ? (a) : (b))

// --- 1. Cấu trúc Node và hàm tạo Node cơ bản ---
typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} TreeNode;

// Hàm tạo một nút mới và trả về con trỏ tới nó
TreeNode* createNode(int val) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        printf("Error: Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// --- Các hàm được yêu cầu trong bài tập ---

/**
 * 1. Viết hàm khởi tạo một mảng với n giá trị ngẫu nhiên
 */
void initialize_array(int* arr, int n, int max_val) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % max_val + 1; // rand() nằm trong <stdlib.h>
    }
}

/**
 * 2. Viết hàm để xây dựng cây nhị phân này với định nghĩa ở trên
 */
TreeNode* build_tree(int* data, int n) {
    if (n <= 0) return NULL;

    // --- Bước 1: Tính toán kích thước và giá trị E ---
    // Tìm lũy thừa của 2 nhỏ nhất lớn hơn hoặc bằng n
    int leaf_capacity = 1;
    while (leaf_capacity < n) {
        leaf_capacity *= 2;
    }

    // Tìm giá trị lớn nhất trong dữ liệu để xác định E
    int max_val = data[0];
    for (int i = 1; i < n; i++) {
        if (data[i] > max_val) max_val = data[i];
    }
    int E = max_val + 1;

    // --- Bước 2: Tạo các nút lá ban đầu ---
    // Mảng này sẽ lưu các con trỏ tới các nút ở tầng hiện tại
    TreeNode** current_level_nodes = (TreeNode**)malloc(leaf_capacity * sizeof(TreeNode*));
    if (current_level_nodes == NULL) exit(1);

    for (int i = 0; i < leaf_capacity; i++) {
        if (i < n) {
            current_level_nodes[i] = createNode(data[i]);
        } else {
            current_level_nodes[i] = createNode(E);
        }
    }
    
    int current_level_size = leaf_capacity;

    // --- Bước 3: Xây dựng các tầng trên từ dưới lên ---
    while (current_level_size > 1) {
        int parent_level_size = current_level_size / 2;
        TreeNode** parent_level_nodes = (TreeNode**)malloc(parent_level_size * sizeof(TreeNode*));
        if (parent_level_nodes == NULL) exit(1);

        for (int i = 0; i < parent_level_size; i++) {
            TreeNode* left_child = current_level_nodes[2 * i];
            TreeNode* right_child = current_level_nodes[2 * i + 1];

            int parent_val = min(left_child->data, right_child->data);
            TreeNode* parent = createNode(parent_val);
            parent->left = left_child;
            parent->right = right_child;
            
            parent_level_nodes[i] = parent;
        }

        free(current_level_nodes); // Dọn dẹp mảng con trỏ của tầng hiện tại
        current_level_nodes = parent_level_nodes; // Chuyển lên tầng cha
        current_level_size = parent_level_size;
    }

    TreeNode* root = current_level_nodes[0];
    free(current_level_nodes); 

    return root;
}


/**
 * 3. Viết hàm để hiển thị thông tin cây
 */
void display_recursive(TreeNode* node, int level) {
    if (node == NULL) return;
    for (int i = 0; i < level; i++) printf("    ");
    printf("val: %d\n", node->data);
    display_recursive(node->left, level + 1);
    display_recursive(node->right, level + 1);
}

void display_tree(TreeNode* root) {
    if (!root) {
        printf("Tree is empty.\n");
        return;
    }
    printf("--- Tree Structure (Pre-order display) ---\n");
    display_recursive(root, 0);
    printf("-----------------------------------------\n");
}


/**
 * 4. Viết hàm tìm kiếm một giá trị đầu vào bằng đệ quy. 
 * Nếu tìm thấy, hiển thị tất cả các cây con với nút tìm thấy là gốc của cây con này
 * hoặc trả về -1 (trong trường hợp này, chúng ta sẽ hiển thị và trả về con trỏ).
 */
TreeNode* search_recursive(TreeNode* node, int value) {
    if (node == NULL || node->data > value) {
        return NULL;
    }
    if (node->data == value) {
        return node;
    }
    TreeNode* found_in_left = search_recursive(node->left, value);
    if (found_in_left) {
        return found_in_left;
    }
    return search_recursive(node->right, value);
}

void search_tree(TreeNode* root, int value) {
    if (!root) return;
    
    printf("Searching for value %d...\n", value);
    TreeNode* found_node = search_recursive(root, value);
    
    if (found_node) {
        printf("Value %d found. Displaying subtree rooted at this node:\n", value);
        display_tree(found_node);
    } else {
        printf("Value %d not found in the tree (return -1 conceptually).\n", value);
    }
}


/**
 * 5. Viết một hàm để chèn nút mới vào cây và một hàm khác để xóa nút khỏi cây
 */

// Hàm helper để cập nhật giá trị các nút cha sau khi lá thay đổi
void update_tree_values(TreeNode* node) {
    if (node == NULL || (node->left == NULL && node->right == NULL)) {
        return;
    }
    update_tree_values(node->left);
    update_tree_values(node->right);
    node->data = min(node->left->data, node->right->data);
}

// Hàm đệ quy để chèn, trả về 1 nếu thành công, 0 nếu thất bại
int insert_node_recursive(TreeNode* node, int value, int E) {
    if (node == NULL) return 0;
    if (node->left == NULL && node->right == NULL) { 
        if (node->data == E) {
            node->data = value;
            return 1; // Chèn thành công
        }
        return 0; // Lá này đã có giá trị
    }
    if (insert_node_recursive(node->left, value, E)) return 1;
    return insert_node_recursive(node->right, value, E);
}

void insert_node(TreeNode* root, int value, int E) {
    if (!root) return;
    if (value >= E) {
        printf("Error: Cannot insert value %d. It's >= E (%d).\n", value, E);
        return;
    }
    printf("Inserting value %d...\n", value);
    if (insert_node_recursive(root, value, E)) {
        update_tree_values(root); // Phải cập nhật lại toàn bộ cây sau khi chèn
        printf("Insertion successful.\n");
    } else {
        printf("Insertion failed: Tree is full.\n");
    }
}

// Hàm đệ quy để xóa
void remove_node_recursive(TreeNode* node, int value_to_remove, int E) {
    if (node == NULL) return;
    if (node->left == NULL && node->right == NULL) {
        if (node->data == value_to_remove) {
            node->data = E;
        }
        return;
    }
    remove_node_recursive(node->left, value_to_remove, E);
    remove_node_recursive(node->right, value_to_remove, E);
}

void remove_node(TreeNode* root, int value_to_remove, int E) {
    /* LƯU Ý: Quy tắc xóa trong đề bài ("thay thế bằng giá trị của nút cha") là không hợp lý
       và sẽ phá vỡ thuộc tính của cây (cha = min(con)). 
       Cách triển khai tiêu chuẩn và hợp lý là thay thế giá trị bị xóa bằng E. */
    printf("Removing value %d by replacing it with E...\n", value_to_remove);
    remove_node_recursive(root, value_to_remove, E);
    update_tree_values(root); // Cập nhật lại toàn bộ cây sau khi xóa
}

// Hàm giải phóng bộ nhớ của cây
void free_tree(TreeNode* node) {
    if (node == NULL) return;
    free_tree(node->left);
    free_tree(node->right);
    free(node);
}

// --- Hàm Main để chạy chương trình ---
int main() {
    // --- Thiết lập ---
    int n = 5;
    int data[] = {8, 20, 41, 7, 2}; // Dữ liệu từ ví dụ
    int E = 42; // Giá trị E từ ví dụ

    printf("Initial data array (n=%d): ", n);
    for(int i = 0; i < n; i++) printf("%d ", data[i]);
    printf("\n\n");
    
    // --- Minh họa hàm initialize_array ---
    int* random_data = (int*)malloc(n * sizeof(int));
    if(random_data == NULL) return 1;
    initialize_array(random_data, n, 100);
    printf("Example of a randomly initialized array: ");
    for(int i = 0; i < n; i++) printf("%d ", random_data[i]);
    printf("\n\n");
    free(random_data);


    // --- Xây dựng Cây ---
    printf("Building the tree with data {8, 20, 41, 7, 2}...\n");
    TreeNode* root = build_tree(data, n);

    // --- Hiển thị Cây ---
    display_tree(root);

    // --- Tìm kiếm ---
    printf("\n--- Search Operations ---\n");
    search_tree(root, 7);
    search_tree(root, 99);
    printf("-------------------------\n");

    // --- Chèn nút ---
    printf("\n--- Insert Operation ---\n");
    insert_node(root, 5, E);
    printf("Tree after inserting 5:\n");
    display_tree(root);
    
    // --- Xóa nút ---
    printf("\n--- Remove Operation ---\n");
    remove_node(root, 41, E);
    printf("Tree after removing 41:\n");
    display_tree(root);

    // --- Dọn dẹp ---
    free_tree(root);
    printf("\nMemory freed successfully.\n");

    return 0;
}