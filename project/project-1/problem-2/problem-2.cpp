#include <iostream>
#include <fstream>
using namespace std;

// Cấu trúc node trong cây BST
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
        root->left = insert(root->left, value);
    else
        root->right = insert(root->right, value);

    return root;
}

// Hàm tìm giá trị lớn nhất không vượt quá K
int findMaxLEQ(TreeNode *root, int K)
{
    int maxVal = -1; // -1 nếu không tìm thấy số nào phù hợp

    while (root)
    {
        if (root->value <= K)
        {
            maxVal = root->value; // Cập nhật giá trị phù hợp
            root = root->right;   // Tìm số lớn hơn nhưng vẫn ≤ K
        }
        else
        {
            root = root->left; // Giảm giá trị xuống để tìm giá trị phù hợp hơn
        }
    }

    return maxVal;
}

// Hàm xóa toàn bộ cây BST để giải phóng bộ nhớ
void deleteTree(TreeNode *root)
{
    if (root)
    {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
}

int main() {
    ifstream inputFile("inpLN.txt");
    ofstream outputFile("outLN.txt");

    if (!inputFile || !outputFile) {
        cerr << "Không thể mở file!" << endl;
        return 1;
    }

    int N, M;
    inputFile >> N;

    // Kiểm tra điều kiện N
    if (N < 1 || N > 100000) {
        cerr << "Giá trị N không hợp lệ!" << endl;
        return 1;
    }

    // Xây dựng cây BST từ mảng A
    TreeNode* root = nullptr;
    for (int i = 0; i < N; ++i) {
        int value;
        inputFile >> value;

        // Kiểm tra điều kiện giá trị A[i]
        if (value < 0 || value > 1000000000) {
            cerr << "Giá trị không hợp lệ trong mảng A!" << endl;
            return 1;
        }

        root = insert(root, value);
    }

    inputFile >> M;

    // Kiểm tra điều kiện M
    if (M < 1 || M > 1000) {
        cerr << "Giá trị M không hợp lệ!" << endl;
        return 1;
    }

    // Xử lý từng truy vấn K
    for (int i = 0; i < M; ++i) {
        int K;
        inputFile >> K;

        // Kiểm tra điều kiện K
        if (K < 0 || K > 1000000000) {
            cerr << "Giá trị K không hợp lệ!" << endl;
            return 1;
        }

        int result = findMaxLEQ(root, K);
        outputFile << result << "\n";
    }

    // Giải phóng bộ nhớ
    deleteTree(root);

    inputFile.close();
    outputFile.close();

    return 0;
}

