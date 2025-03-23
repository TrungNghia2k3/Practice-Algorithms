#include <iostream>
#include <fstream>
#include <deque>
#include <ctime>
using namespace std;

const int MAX = 100;                                               // Hằng số đại điện cho kích thước tối đa của ma trận mê cung và mảng visited
char maze[MAX][MAX];                                               // Biểu diễn ma trận mê cung. Mỗi phần tử của mảng là một ký tự ('O' và 'X')
bool visited[MAX][MAX];                                            // Mảng 2 chiều để theo dõi các ô đã được thăm trong quá trình thực hiện BFS
pair<int, int> directions[4] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; // Mảng chứa 4 đối tượng. Một đối tượng đại diện cho một hướng di chuyển có thể trong mê cung lần lượt là (lên, phải, xuống, trái)
int M, N;                                                          // Để lưu trữ kích thước của ma trận mê cung (số hàng và số cột)

// Input: Tọa độ (x, y) của ô cần kiểm tra.
// Output: Trả về true nếu ô là ô hợp lệ (có thể đi vào), ngược lại trả về false.
bool isValid(int x, int y)
{
    // x >= 0 && x < M && y >= 0 && y < N: Kiểm tra xem ô có nằm trong biên của ma trận không.
    // maze[x][y] == 'O': Kiểm tra xem ô có phải là ô có thể đi vào hay không (không phải là 'X').
    // !visited[x][y]: Kiểm tra xem ô đã được thăm chưa.
    return x >= 0 && x < M && y >= 0 && y < N && maze[x][y] == 'O' && !visited[x][y];
}

// Input: Điểm xuất phát start và điểm đích end.
// Output: Trả về "YES" nếu có đường đi từ start đến end, ngược lại trả về "NO".
string bfs(pair<int, int> start, pair<int, int> end)
{
    struct cell
    {
        // Định nghĩa một cấu trúc cell để lưu trữ tọa độ (x, y) của ô trong hàng đợi.
        int x, y;
    };
    deque<cell> queue;                             //  Sử dụng deque làm hàng đợi để thực hiện BFS.
    queue.push_front({start.first, start.second}); // Đưa điểm xuất phát vào hàng đợi và đánh dấu đã thăm.
    visited[start.first][start.second] = true;
    while (!queue.empty())
    {
        cell c = queue.front();
        queue.pop_front();
        if (c.x == end.first && c.y == end.second)
        {
            // Kiểm tra xem đã đến điểm đích hay chưa, nếu có thì trả về "YES".
            return "YES";
        }
        for (int i = 0; i < 4; i++)
        {
            // Duyệt qua các hướng di chuyển và thêm các ô kề cạnh có thể đi vào vào đầu hàng đợi (front) và đánh dấu đã thăm.
            int nx = c.x + directions[i].first, ny = c.y + directions[i].second;
            if (isValid(nx, ny))
            {
                queue.push_front({nx, ny});
                visited[nx][ny] = true;
            }
        }
    }
    // Nếu không tìm thấy đường đi sau khi duyệt hết, trả về "NO".
    return "NO";
}

int main()
{
    ifstream inp("inpMC.txt"); // Mở file inpMC.txt để đọc dữ liệu.
    if (!inp.is_open())
    {
        // Kiểm tra xem file đã được mở thành công hay không. Nếu không, xuất thông báo lỗi và kết thúc chương trình với mã lỗi 1.
        cout << "Error opening file" << endl;
        return 1;
    }
    ofstream out("outMC.txt"); // Mở file outMC.txt để ghi kết quả.
    inp >> M >> N;             // Đọc kích thước ma trận mê cung (M, N).
    bool hasOpenCell = false;
    for (int i = 0; i < M; i++)
    {
        // Đọc ma trận mê cung từ file.
        // Kiểm tra xem có ô 'O' nào không trong ma trận. Nếu không có, ghi "NO" vào file kết quả, đóng file và kết thúc chương trình.
        for (int j = 0; j < N; j++)
        {
            inp >> maze[i][j];
            if (maze[i][j] == 'O')
            {
                hasOpenCell = true;
            }
        }
    }
    if (!hasOpenCell)
    {
        out << "NO\n";
        inp.close();
        out.close();
        return 0;
    }
    int K;
    inp >> K; // Đọc số lượng truy vấn K.
    while (K--)
    {
        // Lặp qua mỗi truy vấn:
        // Đọc tọa độ (a, b) và (c, d).
        // Kiểm tra tính hợp lệ của ô xuất phát và ô đích.
        // Nếu không hợp lệ, ghi "NO" vào file kết quả.
        // Ngược lại, thực hiện BFS và ghi kết quả vào file kết quả.
        int a, b, c, d;
        inp >> a >> b >> c >> d;
        if (a < 0 || a >= M || b < 0 || b >= N || c < 0 || c >= M || d < 0 || d >= N || maze[a][b] == 'X' || maze[c][d] == 'X')
        {
            out << "NO\n";
        }
        else
        {
            for (int i = 0; i < M; i++)
                for (int j = 0; j < N; j++)
                    visited[i][j] = false;
            out << bfs({a, b}, {c, d}) << "\n";
        }
    }
    // Đóng các file đã mở.
    inp.close();
    out.close();

    return 0;
}
