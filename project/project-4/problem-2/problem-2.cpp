#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

const int MAX = 100000;
priority_queue<int, vector<int>, greater<int>> minHeap; // Min-Heap
int M;
vector<pair<int, int>> queries; // Lưu các truy vấn (a, b)

// Hàm đọc dữ liệu từ file
void readInput(const string &filename)
{
    ifstream inputFile(filename);
    int N, value;

    inputFile >> N;
    for (int i = 0; i < N; i++)
    {
        inputFile >> value;
        minHeap.push(value); // Thêm phần tử vào Min-Heap
    }

    inputFile >> M;
    queries.resize(M);
    for (int i = 0; i < M; i++)
    {
        inputFile >> queries[i].first >> queries[i].second;
    }

    inputFile.close();
}

// Hàm xử lý truy vấn
vector<int> processQueries()
{
    vector<int> results;

    for (auto [a, b] : queries)
    {
        if (minHeap.empty())
        {
            results.push_back(-1);
            continue;
        }

        int minValue = minHeap.top(); // Lấy phần tử nhỏ nhất

        if (minValue >= a && minValue <= b)
        {
            results.push_back(minValue);
            minHeap.pop(); // Xóa phần tử nhỏ nhất khỏi Heap
        }
        else
        {
            results.push_back(-1);
        }
    }

    return results;
}

// Hàm ghi kết quả ra file
void writeOutput(const string &filename, const vector<int> &results)
{
    ofstream outputFile(filename);
    for (int res : results)
    {
        outputFile << res << "\n";
    }
    outputFile.close();
}

int main()
{
    readInput("inpTV.txt");                 // Đọc dữ liệu
    vector<int> results = processQueries(); // Xử lý truy vấn
    writeOutput("outTV.txt", results);      // Ghi kết quả

    return 0;
}
