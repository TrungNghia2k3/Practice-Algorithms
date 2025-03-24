#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <ctime>

using namespace std;

/* Min Heap */

// Heapify là quá trình biến một cây nhị phân bất kỳ thành một Heap.
// Quá trình này có thể được thực hiện từ dưới lên trên hoặc từ trên xuống dưới.
// Đối với mỗi nút, ta so sánh với các nút con và hoán đổi chúng nếu cần thiết cho đến khi cây thỏa mãn tính chất Heap.

/*
arr: mảng đại diện cho Heap
n: Kích thước của Heap
i: Chỉ số của node cần kiêmr tra
*/

void heapify(vector<int> &arr, int n, int i)
{
    int smallest = i;           // Giả sử node i là nhỏ nhất
    int leftChild = 2 * i + 1;  // Chỉ số của nút con trái
    int rightChild = 2 * i + 2; // Chỉ số của nút con phải

    // Kiểm tra xem nút con trái có nhỏ hơn nút cha không
    if (leftChild < n && arr[leftChild] < arr[smallest])
    {
        smallest = leftChild;
    }

    // Kiểm tra xem nút con phải có nhỏ hơn nút cha không
    if (rightChild < n && arr[rightChild] < arr[smallest])
    {
        smallest = rightChild;
    }

    // Nếu smallest thay đổi (tức là con nhỏ hơn cha), hoán đổi arr[i] với arr[smallest] và tiếp tục gọi đệ quy heapify cho nút con đó

    if (smallest != i)
    {
        swap(arr[i], arr[smallest]);
        heapify(arr, n, smallest);
    }
}

// Thêm một phần tử vào Heap
void insertElement(vector<int> &arr, int value)
{
    int i = arr.size();
    arr.push_back(value); // Thêm phần tử mới vào cuối Heap


    // Duyệt ngược lên trên Heap và hoán đổi phần tử mới với phần tử cha cho đến khi Heap thỏa mã
    while (i != 0 && arr[(i - 1) / 2] > arr[i])
    {
        swap(arr[i], arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Xóa phần tử nhỏ nhất khỏi Heap
int extractMin(vector<int> &arr)
{
    if (arr.empty())
    {
        return INT_MIN; // Trả về giá trị INT_MIN nếu Heap rỗng
    }

    // Nếu Heap chỉ còn 1 phần tử, trả về phần tử đó và xóa nó khỏi Heap
    if (arr.size() == 1)
    {
        int root = arr[0];
        arr.pop_back();
        return root;
    }

    int root = arr[0]; // Lưu giá trị của phần tử nhỏ nhất
    arr[0] = arr.back(); // Di chuyển phần tử cuối cùng của Heap lên đầu Heap
    arr.pop_back(); // Xóa phần tử cuối cùng
    heapify(arr, arr.size(), 0); // Gọi heapify để điều chỉnh lại Heap

    return root; // Trả về giá trị của phần tử nhỏ nhất
}

int main()
{
    ifstream inputFile("inpTB.txt");
    if (!inputFile)
    {
        cerr << "Khong the mo tep dau vao" << endl;
        return 1;
    }

    ofstream outputFile("outTB.txt");
    if (!outputFile)
    {
        cerr << "Khong the mo tep dau ra" << endl;
        return 1;
    }

    int N, M;
    inputFile >> N;

    // Check constraint for N
    if (N < 1 || N > 100000)
    {
        cerr << "So phan tu trong mang khong hop le" << endl;
        return 1;
    }

    vector<int> A(N);

    // Nhập mảng A
    for (int i = 0; i < N; ++i)
    {
        inputFile >> A[i];

        // Check constraint for array element
        if (A[i] < 0 || A[i] > 1000000000)
        {
            cerr << "Phan tu mang khong hop le" << endl;
            return 1;
        }
    }

    inputFile >> M;

    // Check constraint for M
    if (M < 0 || M > 1000000000)
    {
        cerr << "So luong truy van khong hop le" << endl;
        return 1;
    }


    // Xây dựng Min-Heap từ mảng A
    for (int i = N / 2 - 1; i >= 0; --i)
    {
        heapify(A, N, i);
    }

    for (int i = 0; i < M; ++i)
    {
        int Q;
        inputFile >> Q;

        // Check constraint for Q
        if (Q < -1 || Q > 1000000000)
        {
            cerr << "Truy van khong hop le" << endl;
            return 1;
        }

        // Nếu Q = -1, trích xuất phần tử nhỏ nhất khỏi Heap và ghi vào file kết quả
        if (Q == -1)
        {
            int minValue = extractMin(A);
            if (minValue != INT_MIN)
            {
                outputFile << minValue << "\n";
            }
        }
        // Ngược lại, thêm phần tử Q vào Heap
        else
        {
            insertElement(A, Q);
        }
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
