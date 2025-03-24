#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int MAX = 100;
char A[MAX][MAX];          // Ma trận ký tự chứa ‘X’ và ‘O’
int B[MAX][MAX];           // Ma trận kết quả
bool visited[MAX][MAX];    // Đánh dấu ô đã được thăm
int M, N;                  // Kích thước ma trận
int regionCount = 0;       // Đếm số vùng liên thông
int singleCellRegions = 0; // Đếm số vùng chỉ chứa 1 ô

// Hướng di chuyển (trái, phải, lên, xuống)
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

// Hàm kiểm tra tọa độ hợp lệ
bool isValid(int x, int y)
{
    return (x >= 0 && x < M && y >= 0 && y < N && !visited[x][y] && A[x][y] == 'X');
}

// Hàm DFS để tìm vùng liên thông
void dfs(int x, int y, int regionID, int &size)
{
    visited[x][y] = true;
    B[x][y] = regionID; // Cập nhật giá trị vùng liên thông
    size++;             // Đếm số ô trong vùng

    // Kiểm tra 4 hướng (trái, phải, lên, xuống)
    for (int i = 0; i < 4; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (isValid(nx, ny))
        {
            dfs(nx, ny, regionID, size);
        }
    }
}

// Hàm xử lý tìm các vùng liên thông
void findConnectedRegions()
{
    regionCount = 0;
    singleCellRegions = 0;

    // Duyệt toàn bộ ma trận, tìm các ô 'X' chưa được thăm và gọi DFS để đánh dấu vùng liên thông
    // Đồng thời đếm số vùng liên thông và số vùng chỉ chứa 1 ô
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            // Mỗi lần tìm thấy một vùng mới, tăng regionCount và kiểm tra nếu vùng chỉ có 1 ô (size == 1)
            if (A[i][j] == 'X' && !visited[i][j])
            {
                int size = 0;
                regionCount++;
                dfs(i, j, regionCount, size);

                if (size == 1)
                {
                    singleCellRegions++;
                }
            }
        }
    }
}

// Hàm đọc dữ liệu từ file
void readInput(const string &filename)
{
    ifstream inputFile(filename);
    inputFile >> M >> N;

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            inputFile >> A[i][j];
            B[i][j] = 0;           // Khởi tạo ma trận kết quả
            visited[i][j] = false; // Chưa thăm ô nào
        }
    }

    inputFile.close();
}

// Hàm ghi kết quả ra file
void writeOutput(const string &filename)
{
    ofstream outputFile(filename);
    outputFile << singleCellRegions << "\n";

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            outputFile << B[i][j] << " ";
        }
        outputFile << "\n";
    }

    outputFile.close();
}

int main()
{
    readInput("inpLT.txt");   // Đọc dữ liệu
    findConnectedRegions();   // Xác định các vùng liên thông
    writeOutput("outLT.txt"); // Xuất kết quả

    return 0;
}
