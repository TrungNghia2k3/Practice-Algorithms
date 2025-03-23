#include <stdio.h>
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *plusOne(int *digits, int digitsSize, int *returnSize)
{
    for (int i = digitsSize - 1; i >= 0; i--)
    {
        if (digits[i] < 9)
        {
            digits[i]++; // Increment the current digit
            *returnSize = digitsSize;
            return digits; // Return the modified array
        }
        digits[i] = 0; // If digit is 9, set it to 0 and continue loop
    }

    // If all digits were 9, we need a new array
    int *result = (int *)malloc((digitsSize + 1) * sizeof(int));
    result[0] = 1;
    for (int i = 1; i <= digitsSize; i++)
    {
        result[i] = 0;
    }
    *returnSize = digitsSize + 1;
    return result;
}

// Hàm chính để kiểm tra chương trình
int main()
{
    int digits[] = {9, 9, 9}; // Nhập số cần cộng 1
    int digitsSize = sizeof(digits) / sizeof(digits[0]);
    int returnSize;

    int *result = plusOne(digits, digitsSize, &returnSize);

    // In kết quả
    printf("Result: ");
    for (int i = 0; i < returnSize; i++)
    {
        printf("%d", result[i]);
    }
    printf("\n");

    // Giải phóng bộ nhớ nếu mảng mới được cấp phát
    if (returnSize > digitsSize)
    {
        free(result);
    }

    return 0;
}
