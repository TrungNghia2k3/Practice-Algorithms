#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

const int MAX = 100;
char A[MAX][MAX];       // Ma trận lưu trạng thái ('O' hoặc 'X')
bool visited[MAX][MAX]; // Đánh dấu ô đã kiểm tra
int M, N;

// Hướng di chuyển (trái, phải, lên, xuống)
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

// Hàm kiểm tra tọa độ hợp lệ
bool isValid(int x, int y)
{
    return (x >= 0 && x < M && y >= 0 && y < N && !visited[x][y] && A[x][y] == 'O');
}

// Hàm BFS tìm vùng liên thông lớn nhất
int bfs(int startX, int startY)
{
    queue<pair<int, int>> q;
    q.push({startX, startY});
    visited[startX][startY] = true;
    int size = 1;

    while (!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (isValid(nx, ny))
            {
                visited[nx][ny] = true;
                q.push({nx, ny});
                size++;
            }
        }
    }
    return size;
}

// Hàm tìm vị trí tối ưu cho robot
void findBestStartPosition(int &bestX, int &bestY, int &maxArea)
{
    maxArea = 0;
    bestX = -1;
    bestY = -1;

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (A[i][j] == 'O' && !visited[i][j])
            {
                int area = bfs(i, j);
                if (area > maxArea)
                {
                    maxArea = area;
                    bestX = i;
                    bestY = j;
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
            visited[i][j] = false; // Chưa kiểm tra ô nào
        }
    }

    inputFile.close();
}

// Hàm ghi kết quả ra file
void writeOutput(const string &filename, int bestX, int bestY, int maxArea)
{
    ofstream outputFile(filename);
    outputFile << bestX << " " << bestY << " " << maxArea << "\n";
    outputFile.close();
}

int main()
{
    int bestX, bestY, maxArea;

    readInput("inpHB.txt");                          // Đọc dữ liệu
    findBestStartPosition(bestX, bestY, maxArea);    // Xác định vị trí tối ưu
    writeOutput("outHB.txt", bestX, bestY, maxArea); // Xuất kết quả

    return 0;
}
