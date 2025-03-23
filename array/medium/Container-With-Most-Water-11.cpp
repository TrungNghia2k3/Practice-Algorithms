#include <stdio.h>

int maxArea(int *height, int heightSize);
int maxAreaTwo(int *height, int heightSize);

int main()
{
    // Test case: Mảng chiều cao các cột
    int height[] = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    int size = sizeof(height) / sizeof(height[0]); // Số lượng phần tử

    // Gọi hàm maxArea và in kết quả
    int result = maxArea(height, size);
    printf("❤️  Diện tích chứa nước lớn nhất: %d\n", result);

    return 0;
}
// 1️⃣ Brute Force
int maxArea(int *height, int heightSize)
{
    int maxWater = 0;
    for (int i = 0; i < heightSize - 1; i++)
    {
        for (int j = i + 1; j < heightSize; j++)
        {
            int minHeight = height[i] < height[j] ? height[i] : height[j];
            int width = j - i;
            int area = minHeight * width;
            if (area > maxWater)
            {
                maxWater = area;
            }
        }
    }
    return maxWater;
}
// Độ phức tạp
// Duyệt qua tất cả các cặp (i, j), nên O(n^2)
// Không tối ưu cho mảng lớn

// 2️⃣ Two Pointers
int maxAreaTwo(int *height, int heightSize)
{
    int left = 0, right = heightSize - 1;
    int maxWater = 0;

    while (left < right)
    {
        int minHeight = height[left] < height[right] ? height[left] : height[right];
        int width = right - left;
        int area = minHeight * width;

        if (area > maxWater)
        {
            maxWater = area;
        }

        // Di chuyển con trỏ có chiều cao nhỏ hơn
        if (height[left] < height[right])
        {
            left++;
        }
        else
        {
            right--;
        }
    }

    return maxWater;
}
// Độ phức tạp
// Chỉ duyệt một lần qua mảng, nên O(n)
// Tối ưu hơn brute force, chạy nhanh ngay cả với các mảng lớn