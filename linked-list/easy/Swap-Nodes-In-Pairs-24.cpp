#include <iostream>
#include <vector> // Để dễ dàng tạo danh sách liên kết từ vector

// Định nghĩa cấu trúc cho một nút trong danh sách liên kết đơn
struct ListNode
{
    int val;        // Giá trị của nút
    ListNode *next; // Con trỏ trỏ đến nút tiếp theo

    // Hàm khởi tạo
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// Lớp giải pháp với phương thức đệ quy
class SolutionRecursive
{
public:
    ListNode *swapPairs(ListNode *head)
    {
        // Điều kiện dừng của đệ quy:
        // Nếu danh sách liên kết rỗng (head là nullptr) hoặc chỉ có một nút (head->next là nullptr),
        // thì không có cặp nào để hoán đổi, nên ta trả về chính head.
        if (!head || !head->next)
        {
            return head;
        }

        // Xác định hai nút đầu tiên trong cặp hiện tại cần được hoán đổi.
        ListNode *first_node = head;        // Nút đầu tiên của cặp.
        ListNode *second_node = head->next; // Nút thứ hai của cặp.

        // *** Bước 2: Sử dụng đệ quy để xử lý các cặp tiếp theo ***
        // Gọi đệ quy cho phần còn lại của danh sách, bắt đầu từ nút thứ ba (second_node->next).
        // Giả sử phần còn lại của danh sách sau khi được hoán đổi sẽ có đầu là một nút nào đó (hoặc nullptr).
        // Kết quả trả về từ lời gọi đệ quy này chính là đầu của danh sách *đã được hoán đổi* từ nút thứ ba trở đi.
        // Chúng ta gán con trỏ này cho `first_node->next`.
        // Điều này có nghĩa là nút đầu tiên của cặp hiện tại (sau khi nút thứ hai được đưa lên đầu)
        // sẽ trỏ đến đầu của phần danh sách *đã được hoán đổi* ở phía sau.
        first_node->next = swapPairs(second_node->next);

        // *** Bước 1: Hướng liên kết để hoán đổi hai nút trong cặp hiện tại ***
        // Thực hiện việc hoán đổi liên kết giữa hai nút đầu tiên của cặp hiện tại.
        // Nút thứ hai (`second_node`) bây giờ sẽ trở thành nút đầu tiên của cặp *đã hoán đổi*.
        // Chúng ta cho `second_node->next` trỏ đến `first_node`.
        second_node->next = first_node;

        // `second_node` hiện tại đang là nút đầu của cặp đã được hoán đổi.
        // Trong mỗi bước đệ quy, chúng ta trả về nút đầu mới của đoạn danh sách (đã được xử lý).
        return second_node;
    }
};

// Hàm tiện ích: Tạo danh sách liên kết từ một vector các số nguyên
ListNode *createLinkedList(const std::vector<int> &values)
{
    if (values.empty())
    {
        return nullptr;
    }
    ListNode *head = new ListNode(values[0]);
    ListNode *current = head;
    for (size_t i = 1; i < values.size(); ++i)
    {
        current->next = new ListNode(values[i]);
        current = current->next;
    }
    return head;
}

// Hàm tiện ích: In các phần tử của danh sách liên kết
void printLinkedList(ListNode *head)
{
    ListNode *current = head;
    while (current != nullptr)
    {
        std::cout << current->val << " -> ";
        current = current->next;
    }
    std::cout << "nullptr" << std::endl;
}

// Hàm tiện ích: Xóa danh sách liên kết để tránh rò rỉ bộ nhớ
void deleteLinkedList(ListNode *head)
{
    ListNode *current = head;
    while (current != nullptr)
    {
        ListNode *next = current->next;
        delete current;
        current = next;
    }
}

// Hàm main để kiểm tra
int main()
{
    SolutionRecursive solver;

    // Trường hợp 1: Danh sách có số nút chẵn
    std::vector<int> vals1 = {1, 2, 3, 4};
    ListNode *head1 = createLinkedList(vals1);
    std::cout << "Danh sách ban đầu 1: ";
    printLinkedList(head1);
    head1 = solver.swapPairs(head1);
    std::cout << "Danh sách sau khi hoán đổi 1: ";
    printLinkedList(head1);
    deleteLinkedList(head1); // Giải phóng bộ nhớ
    std::cout << "--------------------------" << std::endl;

    // // Trường hợp 2: Danh sách có số nút lẻ
    // std::vector<int> vals2 = {1, 2, 3, 4, 5};
    // ListNode* head2 = createLinkedList(vals2);
    // std::cout << "Danh sách ban đầu 2: ";
    // printLinkedList(head2);
    // head2 = solver.swapPairs(head2);
    // std::cout << "Danh sách sau khi hoán đổi 2: ";
    // printLinkedList(head2);
    // deleteLinkedList(head2);
    // std::cout << "--------------------------" << std::endl;

    // // Trường hợp 3: Danh sách chỉ có một nút
    // std::vector<int> vals3 = {1};
    // ListNode* head3 = createLinkedList(vals3);
    // std::cout << "Danh sách ban đầu 3: ";
    // printLinkedList(head3);
    // head3 = solver.swapPairs(head3);
    // std::cout << "Danh sách sau khi hoán đổi 3: ";
    // printLinkedList(head3);
    // deleteLinkedList(head3);
    // std::cout << "--------------------------" << std::endl;

    // // Trường hợp 4: Danh sách rỗng
    // std::vector<int> vals4 = {};
    // ListNode* head4 = createLinkedList(vals4);
    // std::cout << "Danh sách ban đầu 4: ";
    // printLinkedList(head4);
    // head4 = solver.swapPairs(head4);
    // std::cout << "Danh sách sau khi hoán đổi 4: ";
    // printLinkedList(head4);
    // deleteLinkedList(head4); // Mặc dù head4 là nullptr, gọi hàm này vẫn an toàn
    // std::cout << "--------------------------" << std::endl;

    // // Trường hợp 5: Danh sách có hai nút
    // std::vector<int> vals5 = {1, 2};
    // ListNode* head5 = createLinkedList(vals5);
    // std::cout << "Danh sách ban đầu 5: ";
    // printLinkedList(head5);
    // head5 = solver.swapPairs(head5);
    // std::cout << "Danh sách sau khi hoán đổi 5: ";
    // printLinkedList(head5);
    // deleteLinkedList(head5);
    // std::cout << "--------------------------" << std::endl;

    return 0;
}