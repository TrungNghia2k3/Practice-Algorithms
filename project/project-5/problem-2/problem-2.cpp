#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

const int MAX = 100000;
int N, a, b;
priority_queue<int, vector<int>, greater<int>> minHeap; // Min-Heap

// Hàm đọc dữ liệu từ file
void readInput(const string &filename)
{
    ifstream inputFile(filename);
    inputFile >> N >> a >> b;

    for (int i = 0; i < N; i++)
    {
        int value;
        inputFile >> value;
        if (value >= a && value <= b)
        {
            minHeap.push(value); // Chỉ thêm giá trị nằm trong [a, b] vào Heap
        }
    }

    inputFile.close();
}

// Hàm xuất kết quả ra file
void writeOutput(const string &filename)
{
    ofstream outputFile(filename);
    outputFile << minHeap.size() << "\n"; // Ghi số lượng phần tử trong B

    while (!minHeap.empty())
    {
        outputFile << minHeap.top() << "\n"; // Lấy phần tử nhỏ nhất
        minHeap.pop();
    }

    outputFile.close();
}

int main()
{
    readInput("inpMCT.txt");   // Đọc dữ liệu từ file
    writeOutput("outMCT.txt"); // Xuất kết quả ra file

    return 0;
}
