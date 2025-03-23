#include <stdlib.h>
#include <stdio.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume
 * caller calls free().
 */

int compare(const void *a, const void *b);
int **threeSum(int *nums, int numsSize, int *returnSize, int **returnColumnSizes);

int main()
{
    int nums[] = {-1, 0, 1, 2, -1, -4};
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    int returnSize;
    int *returnColumnSizes;
    int **result = threeSum(nums, numsSize, &returnSize, &returnColumnSizes);

    printf("❤️  Số lượng bộ ba hợp lệ: %d\n", returnSize);
    for (int i = 0; i < returnSize; i++)
    {
        printf("[%d, %d, %d]\n", result[i][0], result[i][1], result[i][2]);
        free(result[i]);
    }
    free(result);
    free(returnColumnSizes);

    return 0;
}

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int **threeSum(int *nums, int numsSize, int *returnSize, int **returnColumnSizes)
{
    qsort(nums, numsSize, sizeof(int), compare);

    int **result = (int **)malloc(sizeof(int *) * numsSize * numsSize);
    *returnColumnSizes = (int *)malloc(sizeof(int) * numsSize * numsSize);
    *returnSize = 0;

    for (int num1Idx = 0; num1Idx < numsSize - 2; num1Idx++)
    {
        // Skip duplicate values for num1Idx
        if (num1Idx > 0 && nums[num1Idx] == nums[num1Idx - 1])
        {
            continue;
        }

        int num2Idx = num1Idx + 1;
        int num3Idx = numsSize - 1;

        while (num2Idx < num3Idx)
        {
            int sum = nums[num1Idx] + nums[num2Idx] + nums[num3Idx];

            if (sum == 0)
            {
                result[*returnSize] = (int *)malloc(sizeof(int) * 3);
                result[*returnSize][0] = nums[num1Idx];
                result[*returnSize][1] = nums[num2Idx];
                result[*returnSize][2] = nums[num3Idx];
                (*returnColumnSizes)[*returnSize] = 3;
                (*returnSize)++;

                // Skip duplicate values for num2Idx
                while (num2Idx < num3Idx && nums[num2Idx] == nums[num2Idx + 1])
                {
                    num2Idx++;
                }

                // Skip duplicate values for num3Idx
                while (num2Idx < num3Idx && nums[num3Idx] == nums[num3Idx - 1])
                {
                    num3Idx--;
                }

                num2Idx++;
                num3Idx--;
            }
            else if (sum > 0)
            {
                num3Idx--;
            }
            else
            {
                num2Idx++;
            }
        }
    }

    return result;
}
