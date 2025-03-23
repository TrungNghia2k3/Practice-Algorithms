#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX = 100;

void generateTestCase(ofstream &inp, int M, int N, int K)
{
    inp << M << " " << N << "\n"; //  In ra file inpMC.txt kích thước của ma trận mê cung, nơi M là số hàng và N là số cột của ma trận
    for (int i = 0; i < M; i++)
    {
        // Tạo ra các hàng của ma trận mê cung.
        for (int j = 0; j < N; j++)
        {
            inp << (rand() % 2 == 0 ? 'O' : 'X') << " "; // Mỗi ô trong hàng được chọn ngẫu nhiên là 'O' hoặc 'X'
        }
        inp << "\n";
    }
    inp << K << "\n";
    for (int i = 0; i < K; i++)
    {
        // Tạo ra các truy vấn ngẫu nhiên trong ma trận.
        //  Mỗi truy vấn được mô tả bởi tọa độ ô xuất phát (rand() % M, rand() % N) và tọa độ ô đích (rand() % M, rand() % N)
        inp << rand() % M << " " << rand() % N << " " << rand() % M << " " << rand() % N << "\n";
    }
}

int main()
{
    srand(time(0));
    ofstream inp("inpMC.txt");
    if (!inp.is_open())
    {
        cout << "Error opening file" << endl;
        return 1;
    }

    // generateTestCase(inp, 3, 3, 2); // Kiểm tra xem chương trình có hoạt động đúng đắn với các trường hợp đơn giản hay không
    // generateTestCase(inp, 4, 4, 2);
    // generateTestCase(inp, 5, 5, 3);
    generateTestCase(inp, 6, 6, 4);
    // generateTestCase(inp, 8, 8, 5);
    // generateTestCase(inp, 7, 7, 6);
    // generateTestCase(inp, 10, 10, 5);
    // generateTestCase(inp, 50, 50, 10); // Kiểm tra hiệu suất của chương trình khi xử lý các trường hợp lớn
    // generateTestCase(inp, 100, 100, 20); // Kiểm tra hiệu suất của chương trình khi xử lý các trường hợp rất lớn.
    inp.close();
    return 0;
}
