#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Cấu trúc node trong BST
struct TreeNode
{
    int value;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int val)
    {
        value = val;
        left = right = nullptr;
    }
};

// Hàm chèn phần tử vào BST
TreeNode *insert(TreeNode *root, int value)
{
    if (root == nullptr)
        return new TreeNode(value);

    if (value < root->value)
        root->left = insert(root->left, value); // Node trái chứa giá trị bé hơn node gốc
    else if (value > root->value)
        root->right = insert(root->right, value); // Node phải chứa giá trị lớn hơn node gốc

    return root;
}

// Hàm kiểm tra xem một giá trị có tồn tại trong khoảng (a, b) hay không
bool existsInRange(TreeNode *root, int a, int b)
{
    if (!root)
        return false;

    // Nếu a < root->value < b, trả về true (có phần tử trong khoảng)
    if (root->value > a && root->value < b)
        return true;

    // Nếu root->value ≤ a, tìm ở cây con bên phải.
    if (root->value <= a)
        return existsInRange(root->right, a, b);

    // Nếu root->value ≥ b, tìm ở cây con bên trái.
    return existsInRange(root->left, a, b);
}

// Hàm đọc dữ liệu từ file và xử lý
void readInput(const string &filename, TreeNode *&root, int &M, vector<pair<int, int>> &queries)
{
    ifstream inputFile(filename);
    int N;

    inputFile >> N;
    for (int i = 0; i < N; i++)
    {
        int value;
        inputFile >> value;
        root = insert(root, value);
    }

    inputFile >> M;
    queries.resize(M);
    for (int i = 0; i < M; i++)
    {
        int a, b;
        inputFile >> a >> b;
        queries[i] = {a, b};
    }

    inputFile.close();
}

// Hàm xử lý truy vấn
vector<string> processQueries(TreeNode *root, const vector<pair<int, int>> &queries)
{
    vector<string> results;
    for (const auto &q : queries)
    {
        if (existsInRange(root, q.first, q.second))
            results.push_back("YES");
        else
            results.push_back("NO");
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

// Hàm xóa cây BST để giải phóng bộ nhớ
void deleteTree(TreeNode *root)
{
    if (root)
    {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
}

int main()
{
    TreeNode *root = nullptr;
    int M;
    vector<pair<int, int>> queries;

    readInput("inpBST.txt", root, M, queries);
    vector<string> results = processQueries(root, queries);
    writeOutput("outBST.txt", results);

    deleteTree(root);
    return 0;
}
