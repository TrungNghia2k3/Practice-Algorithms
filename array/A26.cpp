#include <stdio.h>
#include <malloc.h>

int removeElement(int *nums, int numsSize, int val);
int removeElementTwo(int *nums, int numsSize, int val);
int removeElementThree(int *nums, int numsSize, int val);
int removeElementFour(int *nums, int numsSize, int val);

int main()
{
    int nums[] = {3, 2, 2, 3};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int val = 3;

    int newSize = removeElementThree(nums, numsSize, val);

    printf("❤️  Mảng sau khi xóa phần tử %d: ", val);
    for (int i = 0; i < newSize; i++)
    {
        printf("%d ", nums[i]);
    }
    printf("\n ❤️  Số lượng phần tử còn lại: %d\n", newSize);

    return 0;
}

// 1️⃣ Dùng hai con trỏ (Two Pointers - Forward)
int removeElement(int *nums, int numsSize, int val)
{
    int i = 0; // Con trỏ ghi kết quả
    for (int j = 0; j < numsSize; j++)
    {
        if (nums[j] != val)
        {
            nums[i] = nums[j]; // Giữ lại phần tử khác val
            i++;
        }
    }
    return i; // Kích thước mới của mảng
}

// Độ phức tap:
// Thời gian: 0(n) vì duyêt qua mảng một lần
// Không gian: 0(1) vì không dùng bộ nhớ bổ sung

// 2️⃣ Dùng hai con trỏ (Two Pointers - Backward)
int removeElementTwo(int *nums, int numsSize, int val)
{
    int i = 0;
    int j = numsSize;
    while (i < j)
    {
        if (nums[i] == val)
        {
            nums[i] = nums[j - 1]; // Thay thế bằng phần tử cuối cùng
            j--;                   // Giảm kích thước
        }
        else
        {
            i++; // Giữ lại phần tử hợp lệ
        }
    }
    return j;
}
// Độ phức tạp:
// Thời gian: 0(n)
// Không gian: 0(1)

// 3️⃣ Dùng vòng lặp một lần (One-pass scan)

int removeElementThree(int *nums, int numsSize, int val)
{
    int i = 0;
    while (i < numsSize)
    {
        if (nums[i] == val)
        {
            for (int j = i; j < numsSize - 1; j++)
            {
                nums[j] = nums[j + 1]; // Dịch phần còn lại lên một vị trí
            }
            numsSize--; // Giảm kích thước
        }
        else
        {
            i++;
        }
    }
    return numsSize;
}
// Độ phức tạp
// Thời gian: O(n^2) (do phải dich chuyển phần tử)
// Không gian: O(1)
// Nhược điểm: Chạy chậm khi val xuất hiện nhiều lần

int removeElementFour(int *nums, int numsSize, int val)
{
    int *temp = (int *)malloc(numsSize * sizeof(int)); // Mảng phụ
    int newSize = 0;
    for (int i = 0; i < numsSize; i++)
    {
        if (nums[i] != val)
        {
            temp[newSize++] = nums[i];
        }
    }
    for (int i = 0; i < newSize; i++)
    {
        nums[i] = temp[i];
    }
    free(temp);
    return newSize;
}
// Độ phức tạp
// Thời gian: O(n)
// Không gian: O(n) (do dùng mảng phụ)
// Nhược điểm: Tốn thêm bộ nhớ
