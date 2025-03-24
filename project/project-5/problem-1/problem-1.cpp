#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

const int MAX = 100;
char A[MAX][MAX];       // Ma trận lưu trạng thái ('X' hoặc 'O')
bool visited[MAX][MAX]; // Đánh dấu ô đã kiểm tra
int M, N, K;
vector<int> regionSizes; // Lưu kích thước của từng vùng liên thông

// Hướng di chuyển (trái, phải, lên, xuống)
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

// Hàm kiểm tra tọa độ hợp lệ
bool isValid(int x, int y)
{
    return (x >= 0 && x < M && y >= 0 && y < N && !visited[x][y] && A[x][y] == 'X');
}

// Hàm BFS để tìm vùng liên thông
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

// Hàm tìm tất cả các vùng liên thông của 'X'
void findConnectedRegions()
{
    regionSizes.clear();

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (A[i][j] == 'X' && !visited[i][j])
            {
                int size = bfs(i, j);
                regionSizes.push_back(size);
            }
        }
    }
}

// Hàm đếm số vùng có diện tích không lớn hơn T
int countRegions(int T)
{
    int count = 0;
    for (int size : regionSizes)
    {
        if (size <= T)
            count++;
    }
    return count;
}

// Hàm đọc dữ liệu từ file
void readInput(const string &filename, vector<int> &queries)
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

    inputFile >> K;
    queries.resize(K);
    for (int i = 0; i < K; i++)
    {
        inputFile >> queries[i];
    }

    inputFile.close();
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
    vector<int> queries;
    readInput("inpGH.txt", queries);
    findConnectedRegions();

    vector<int> results;
    for (int T : queries)
    {
        results.push_back(countRegions(T));
    }

    writeOutput("outGH.txt", results);
    return 0;
}
