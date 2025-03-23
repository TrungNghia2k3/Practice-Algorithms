#include <stdio.h>

int searchInsert(int *nums, int numsSize, int target);
int searchInsertTwo(int *nums, int numsSize, int target);
int main()
{
    int nums[] = {1, 3, 5, 6};
    int size = sizeof(nums) / sizeof(nums[0]);

    // Test case 1: Tìm 5 (đã có trong mảng)
    printf("❤️  Vị trí của 5: %d\n", searchInsert(nums, size, 5)); // Output: 2

    // Test case 2: Tìm 2 (không có, nên chèn vào index 1)
    printf("❤️  Vị trí của 2: %d\n", searchInsert(nums, size, 2)); // Output: 1

    // Test case 3: Tìm 7 (không có, nên chèn vào index 4)
    printf("❤️  Vị trí của 7: %d\n", searchInsert(nums, size, 7)); // Output: 4

    // Test case 4: Tìm 0 (không có, nên chèn vào index 0)
    printf("❤️  Vị trí của 0: %d\n", searchInsert(nums, size, 0)); // Output: 0

    return 0;
}
// 1️⃣ Sequential search
int searchInsert(int *nums, int numsSize, int target)
{
    for (int i = 0; i < numsSize; i++)
    {
        if (nums[i] >= target)
        {
            return i; // Tìm thấy hoặc tìm vị trí cần chèn
        }
    }
    return numsSize; // Nếu target lớn hơn tất cả, chèn vào cuối
}

// 2️⃣ Binary Search
int searchInsertTwo(int *nums, int numsSize, int target)
{
    int left = 0, right = numsSize - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2; // Tránh tràn số khi cộng
        if (nums[mid] < target)
        {
            left = mid + 1;
        }
        else if (nums[mid] > target)
        {
            right = mid - 1;
        }
        else
        {
            return mid; // Tìm thấy target tại mid
        }
    }

    return left; // Vị trí cần chèn nếu không tìm thấy target
}