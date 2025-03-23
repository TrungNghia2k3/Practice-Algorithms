#include <bits/stdc++.h>
using namespace std;

int main()
{

    int N = rand() % (100000 - 2 + 1) + 2; // sinh số ngẫu nhiên trong khoảng từ 2 đến 10^5 cho N.
    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        A[i] = rand() % 1000000001;
    }
    int M = rand() % (10000 - 1 + 1) + 1; // sinh số ngẫu nhiên trong khoảng từ 1 đến 10^4 cho M.
    vector<int> Q(M);

    // for (int i = 0; i < M; i++)
    // {
    //     // Sử dụng rand() % 2 để quyết định giá trị sẽ là -1 hay giá trị ngẫu nhiên.
    //     if (rand() % 2 == 0)
    //     {
    //         Q[i] = -1; // Nếu rand() % 2 == 0, gán giá trị -1.
    //     }
    //     else
    //     {
    //         Q[i] = rand() % 1000000001; // Ngược lại, gán giá trị ngẫu nhiên từ 0 đến 1000000000.
    //     }
    // }
    for (int i = 0; i < M; i++)
    {
        // Tăng giá trị xuất hiện của Q = -1 lên 50%
        //  Sử dụng ((double) rand() / RAND_MAX) để sinh số ngẫu nhiên trong khoảng từ 0 đến 1.
        if ((double)rand() / RAND_MAX < 0.5)
        {
            Q[i] = -1; // Nếu giá trị ngẫu nhiên < 0.5, gán giá trị -1.
        }
        else
        {
            Q[i] = rand() % 1000000001; // Ngược lại, gán giá trị ngẫu nhiên từ 0 đến 1000000000.
        }
    }

    ofstream fout("inpTB.txt");
    fout << N << endl;
    for (int i = 0; i < N; i++)
    {
        fout << A[i] << " ";
    }
    fout << endl;
    fout << M << endl;
    for (int i = 0; i < M; i++)
    {
        fout << Q[i] << endl;
    }
    fout.close();

    return 0;
}
