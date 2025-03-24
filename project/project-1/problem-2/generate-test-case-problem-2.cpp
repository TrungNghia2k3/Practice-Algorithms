#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

void generateTestCase(const string &filename, int N, int M)
{
    ofstream outFile(filename);
    if (!outFile)
    {
        cerr << "Lỗi: Không thể mở file!" << endl;
        return;
    }

    srand(time(0)); // Khởi tạo seed cho số ngẫu nhiên

    outFile << N << "\n"; // Ghi số N
    for (int i = 0; i < N; i++)
    {
        outFile << rand() % 1000000000 << " "; // Sinh số từ 0 đến 10^9
    }
    outFile << "\n";

    outFile << M << "\n"; // Ghi số M
    for (int i = 0; i < M; i++)
    {
        outFile << rand() % 1000000000 << "\n"; // Sinh số từ 0 đến 10^9
    }

    outFile.close();
    cout << "Test case đã được tạo và lưu vào " << filename << "\n";
}

int main()
{
    int N = rand() % 100000 + 1; // Kích thước mảng (1 ≤ N ≤ 10^5)
    int M = rand() % 1000 + 1;   // Số lượng truy vấn (1 ≤ M ≤ 10^3)

    generateTestCase("inpLN.txt", 15, 20);
    return 0;
}
