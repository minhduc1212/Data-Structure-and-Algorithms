#include <stdio.h> // Chỉ cần thư viện I/O cơ bản

#define MAX_CARS 50 // Giả sử đoàn tàu có tối đa 50 toa

// Cấu trúc cho một toa tàu (một node trong danh sách liên kết)
typedef struct CarNode {
    char id;              // Mã định danh của toa (ví dụ: 'A', 'B')
    int capacity;         // Sức chứa tối đa
    int passengers;       // Số hành khách hiện tại
    struct CarNode *next; // Con trỏ tới toa tàu tiếp theo
} CarNode;

// Cấu trúc để quản lý cả đoàn tàu (danh sách liên kết)
typedef struct {
    CarNode *head; // Con trỏ trỏ tới toa đầu tiên
    int length;    // Số lượng toa tàu hiện có
} Train;

// ----- Bể chứa bộ nhớ tĩnh (Memory Pool) cho các toa tàu -----
// Thay vì dùng malloc, chúng ta sẽ lấy các node từ mảng này.
CarNode car_node_pool[MAX_CARS];
int next_car_node_idx = 0; // Biến đếm để biết node tiếp theo còn trống

// Hàm này thay thế cho malloc()
// Nó "mượn" một node từ bể chứa và khởi tạo giá trị cho nó.
CarNode* get_new_car_node(char id, int capacity, int passengers) {
    // Kiểm tra xem bể chứa còn chỗ không
    if (next_car_node_idx >= MAX_CARS) {
        printf("LOI: Da het cho trong bai de xay toa tau moi!\n");
        return NULL; // Trả về NULL nếu hết bộ nhớ
    }

    // Lấy con trỏ tới node tiếp theo còn trống trong bể chứa
    CarNode* newNode = &car_node_pool[next_car_node_idx];
    next_car_node_idx++; // Di chuyển chỉ số tới vị trí trống tiếp theo
    
    // Gán giá trị cho node mới
    newNode->id = id;
    newNode->capacity = capacity;
    newNode->passengers = passengers;
    newNode->next = NULL; // Node mới luôn là node cuối, nên next là NULL
    
    return newNode;
}
// Hàm 1: Khởi tạo một đoàn tàu rỗng
void create_train(Train *t) {
    t->head = NULL;
    t->length = 0;
}

// Hàm 2: Thêm một toa tàu mới vào cuối đoàn
void add_car(Train *t, char id, int capacity, int passengers) {
    // Yêu cầu: Số khách phải nhỏ hơn hoặc bằng sức chứa
    if (passengers > capacity) {
        printf("Thong bao: So khach (%d) cua toa %c vuot suc chua (%d). Tu dong giam so khach ve mức tối đa.\n", 
               passengers, id, capacity);
        passengers = capacity;
    }
    
    // Lấy một toa tàu mới từ bể chứa
    CarNode* newCar = get_new_car_node(id, capacity, passengers);
    if (newCar == NULL) {
        // Nếu get_new_car_node trả về NULL, dừng hàm lại
        return;
    }

    // Nếu đoàn tàu đang rỗng, toa mới sẽ là toa đầu tiên
    if (t->head == NULL) {
        t->head = newCar;
    } else { 
        // Nếu không, đi đến cuối đoàn tàu để nối toa mới vào
        CarNode *current = t->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newCar; // Nối toa mới vào đuôi
    }
    t->length++; // Tăng số lượng toa lên 1
}

// Hàm 3: Loại bỏ các toa không có hành khách (passengers == 0)
void remove_empty_cars(Train *t) {
    CarNode *current = t->head;
    CarNode *prev = NULL;

    // Duyệt qua từng toa tàu
    while (current != NULL) {
        // Nếu tìm thấy toa rỗng
        if (current->passengers == 0) {
            printf("Thong bao: Loai bo toa %c vi khong co hanh khach.\n", current->id);
            
            // Trường hợp 1: Toa rỗng là toa đầu tiên
            if (prev == NULL) {
                t->head = current->next; // Cập nhật head để trỏ tới toa thứ hai
            } else { // Trường hợp 2: Toa rỗng ở giữa hoặc cuối
                prev->next = current->next; // Nối toa trước đó với toa ngay sau toa bị xóa
            }
            
            // Di chuyển con trỏ current tới toa tiếp theo để kiểm tra
            CarNode *node_to_remove = current;
            current = current->next;
            
            // Giảm số lượng toa. Lưu ý: chúng ta không "free" bộ nhớ vì không dùng malloc.
            t->length--;
        } else {
            // Nếu toa không rỗng, di chuyển cả hai con trỏไปข้างหน้า
            prev = current;
            current = current->next;
        }
    }
}

// Hàm 4: Hiển thị thông tin đoàn tàu
void display_train(Train *t) {
    printf("\n--- THONG TIN DOAN TAU ---\n");
    printf("So luong toa hien tai: %d\n", t->length);
    
    if (t->head == NULL) {
        printf("Doan tau rong.\n");
        printf("---------------------------\n");
        return;
    }
    
    CarNode *current = t->head;
    int car_number = 1;
    while (current != NULL) {
        printf("  Toa %d: [ID: %c, So khach: %d/%d]\n", 
               car_number, current->id, current->passengers, current->capacity);
        current = current->next;
        car_number++;
    }
    printf("---------------------------\n");
}
int main() {
    // Tạo một đoàn tàu mới
    Train my_train;
    create_train(&my_train);

    printf("Buoc 1: Khoi tao doan tau voi cac toa ban dau.\n");
    // Thêm các toa tàu ban đầu
    add_car(&my_train, 'A', 100, 80);
    add_car(&my_train, 'B', 80, 0);   
    add_car(&my_train, 'C', 120, 120);
    add_car(&my_train, 'D', 90, 50);
    add_car(&my_train, 'E', 70, 0);   

    // Hiển thị trạng thái ban đầu
    display_train(&my_train);

    // Thực hiện chức năng xóa các toa rỗng
    printf("\nBuoc 2: Thuc hien loai bo cac toa tau rong...\n");
    remove_empty_cars(&my_train);
    
    // Hiển thị trạng thái sau khi dọn dẹp
    display_train(&my_train);
    
    // Thử thêm một toa mới để đảm bảo đoàn tàu vẫn hoạt động
    printf("\nBuoc 3: Them mot toa tau G moi vao cuoi...\n");
    add_car(&my_train, 'G', 150, 160); // Thử trường hợp quá tải để kiểm tra
    
    // Hiển thị trạng thái cuối cùng
    display_train(&my_train);

    return 0;
}