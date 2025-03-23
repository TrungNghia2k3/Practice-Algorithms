#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <ctime>

using namespace std;

void heapify(vector<int> &arr, int n, int i)
{
    int smallest = i;
    int leftChild = 2 * i + 1;
    int rightChild = 2 * i + 2;

    if (leftChild < n && arr[leftChild] < arr[smallest])
    {
        smallest = leftChild;
    }

    if (rightChild < n && arr[rightChild] < arr[smallest])
    {
        smallest = rightChild;
    }

    if (smallest != i)
    {
        swap(arr[i], arr[smallest]);
        heapify(arr, n, smallest);
    }
}

void insertElement(vector<int> &arr, int value)
{
    int i = arr.size();
    arr.push_back(value);

    while (i != 0 && arr[(i - 1) / 2] > arr[i])
    {
        swap(arr[i], arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int extractMin(vector<int> &arr)
{
    if (arr.empty())
    {
        return INT_MIN; // Giả sử INT_MIN là giá trị không hợp lệ
    }

    if (arr.size() == 1)
    {
        int root = arr[0];
        arr.pop_back();
        return root;
    }

    int root = arr[0];
    arr[0] = arr.back();
    arr.pop_back();
    heapify(arr, arr.size(), 0);

    return root;
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

        if (Q == -1)
        {
            int minValue = extractMin(A);
            if (minValue != INT_MIN)
            {
                outputFile << minValue << "\n";
            }
        }
        else
        {
            insertElement(A, Q);
        }
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
