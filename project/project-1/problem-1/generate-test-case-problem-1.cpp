#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

void generateTestCase(const string &filename, int M, int N, double X_ratio)
{
    ofstream outFile(filename);
    if (!outFile)
    {
        cerr << "Lỗi: Không thể mở file!" << endl;
        return;
    }

    outFile << M << " " << N << "\n"; // Ghi dòng đầu tiên chứa M, N

    srand(time(0)); // Khởi tạo seed cho số ngẫu nhiên

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            // Tỷ lệ xuất hiện của 'X' theo X_ratio
            if ((double)rand() / RAND_MAX < X_ratio)
            {
                outFile << 'X';
            }
            else
            {
                outFile << 'O';
            }
            if (j < N - 1)
                outFile << " "; // Giữ định dạng cách nhau 1 khoảng trắng
        }
        outFile << "\n"; // Xuống dòng
    }

    outFile.close();
    cout << "Test case đã được tạo và lưu vào " << filename << "\n";
}

int main()
{
    int M = rand() % 100 + 1; // Kích thước hàng (1 ≤ M ≤ 100)
    int N = rand() % 100 + 1; // Kích thước cột (1 ≤ N ≤ 100)
    double X_ratio = 0.3;     // Xác suất xuất hiện của 'X'

    generateTestCase("inpLT.txt", 10, 10, X_ratio);
    return 0;
}
