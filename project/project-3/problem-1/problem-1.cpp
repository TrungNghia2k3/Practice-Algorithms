#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int MAX = 100;
char A[MAX][MAX];       // Ma trận ký tự chứa ‘X’ và ‘O’
int B[MAX][MAX];        // Ma trận đánh số vùng liên thông
bool visited[MAX][MAX]; // Đánh dấu ô đã được thăm
int M, N, K;

// Hướng di chuyển (trái, phải, lên, xuống)
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

// Hàm kiểm tra tọa đô hợp lệ
bool isValid(int x, int y)
{
    return (x >= 0 && x < M && y >= 0 && y < N && !visited[x][y] && A[x][y] == 'X');
}

// Hàm DFS để đánh số vùng liên thông
void dfs(int x, int y, int regionID)
{
    visited[x][y] = true;
    B[x][y] = regionID;

    for (int i = 0; i < 4; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (isValid(nx, ny))
        {
            dfs(nx, ny, regionID);
        }
    }
}

// Hàm tính các vùng liên thông
void findConnectedRegions()
{
    int regionID = 0;

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (A[i][j] == 'X' && !visited[i][j])
            {
                regionID++;
                dfs(i, j, regionID);
            }
        }
    }
}

// Hàm đọc dữ liệu từ file
void readInput(const string &filename, vector<vector<int>> &queries)
{
    ifstream inputFile(filename);
    inputFile >> M >> N;

    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            inputFile >> A[i][j];
            B[i][j] = 0;
            visited[i][j] = false;
        }
    }

    inputFile >> K;
    queries.resize(K);

    for (int i = 0; i < K; i++)
    {
        int a, b, c, d;
        inputFile >> a >> b >> c >> d;
        queries[i] = {a, b, c, d};
    }

    inputFile.close();
}

// Hàm xử lý các truy vấn
vector<string> processQueries(const vector<vector<int>> &queries)
{
    vector<string> results;

    for (const auto &q : queries)
    {
        int a = q[0], b = q[1], c = q[2], d = q[3];

        if (A[a][b] == 'O' || A[c][d] == 'O')
        {
            results.push_back("NO");
        }
        else if (B[a][b] == B[c][d])
        {
            results.push_back("YES");
        }
        else
        {
            results.push_back("NO");
        }
    }

    return results;
}

// Hàm ghi kết quả ra file
void writeOutput(const string &filename, const vector<string> &results)
{
    ofstream outputFile(filename);

    for (const string &res : results)
    {
        outputFile << res << "\n";
    }

    outputFile.close();
}

int main()
{
    vector<vector<int>> queries;
    readInput("inpLT.txt", queries);
    findConnectedRegions();
    vector<string> results = processQueries(queries);
    writeOutput("outLT.txt", results);

    return 0;
}
